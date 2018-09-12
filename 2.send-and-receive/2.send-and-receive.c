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
	//  Write an MPI Program with two proceses working as follows:
	//	1.Process 0 sends and integer number to process 1
	//	2.Process 1 calculates the square of the number, and sends the result to process 0
	//	3.Process 0 prints out the result
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
