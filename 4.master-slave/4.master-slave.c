#include <mpi.h>
#include <stdio.h>

int main ( int argc, char *argv[] )
{
	int size = 8;
	int matrix[size][size]; 
		
	int masterID = 0;
	int receiveMaster;
	int sum = 0;

	int sizeSlave = 8;
	int receiveSlave[size];	

	int tag = 1;
	int i, j, rank;
	
	int test[size];
	for (i = 0; i < size; i++)
		test[i] = i;

	MPI_Status status;	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	

	if ( rank == 0 ) {	
		// Generate Matrix
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				matrix[i][j] = i + j;
			}
		}
	
		// Send each row to salve
		for (i = 1; i <= sizeSlave; i++) {
			MPI_Send(&matrix[i-1], size, MPI_INT, i, tag, MPI_COMM_WORLD); 
		}
		
		// Recevie sunmmation of each slave
		for (i = 1; i <= sizeSlave; i++) {
			MPI_Recv(&receiveMaster, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
			sum += receiveMaster;
		}

		printf("Summation: %d\n", sum);

	} else {
		MPI_Recv(&receiveSlave, size, MPI_INT, masterID, tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < size; i++)
			sum += receiveSlave[i];
		printf("Process %d sum: %d\n", rank, sum);
		MPI_Send(&sum, 1, MPI_INT, masterID, tag, MPI_COMM_WORLD);
	}

	MPI_Finalize();	
}
