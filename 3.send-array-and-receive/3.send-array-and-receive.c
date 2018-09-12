#include <mpi.h>
#include <stdio.h>

int main ( int argc, char *argv[] )
{
	int size = 10;
	int msg[size]; 
	int tag = 1;
	int master = 0;
	int slave = 1;
	int i;
	int rank;
	MPI_Status status;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	

	if ( rank == 0 ) {
		for (i = 0; i < size; i++)
			msg[i] = i;

		MPI_Send(&msg, size, MPI_INT, slave, tag, MPI_COMM_WORLD);
		MPI_Recv(&msg, size, MPI_INT, slave, tag, MPI_COMM_WORLD, &status);
		
		for (i = 0; i < size; i++)
			printf("Result from process 1 at [%d]: %d\n", i, msg[i]);
	} 
	
	if ( rank == 1 ) {
		MPI_Recv(&msg, size, MPI_INT, master, tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < size; i++) {
			msg[i] = msg[i] * 10;
		}
		MPI_Send(&msg, size, MPI_INT, master, tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();	
}
