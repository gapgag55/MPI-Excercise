#include <mpi.h>
#include <stdio.h>

int main ( int argc, char *argv[] )
{
	int rank; 
	int msg;
	int tag = 1;
	int master = 0;
	int slave = 1;
	MPI_Status status;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if ( rank == 0 ) {
		msg = 10;
		MPI_Send(&msg, 1, MPI_INT, slave, tag, MPI_COMM_WORLD);
		MPI_Recv(&msg, 1, MPI_INT, slave, tag, MPI_COMM_WORLD, &status);

		printf("Result from process 1 is: %d\n", msg);
	} 
	
	if ( rank == 1 ) {
		MPI_Recv(&msg, 1, MPI_INT, master, tag, MPI_COMM_WORLD, &status);
		msg = msg * msg;
		MPI_Send(&msg, 1, MPI_INT, master, tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();	
}
