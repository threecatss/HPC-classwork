#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
long long num_steps = 1000000000;
double step;
int main(int argc, char* argv[]) {
	double buff[1];
	double t1, t2;
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();
	int world_rank, world_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int i;
	double x,pi = 0.0;
	step = 1.0/(double)num_steps;
	for(i=world_rank; i<=num_steps; i+=world_size) {
		x = (i-0.5)*step;
		buff[0] += 4.0/(1.0+x*x);
	}
	buff[0] *= step;
	if(world_rank!=0) {
		MPI_Send(buff,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);
	} else {
		pi = buff[0];
		for(i=1; i<world_size; i++) {
			MPI_Recv(buff,1,MPI_DOUBLE,MPI_ANY_SOURCE,99,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			pi += buff[0];
		}
		t2 = MPI_Wtime();
		printf("%d\t%f\t%f\n",world_size,pi,t2-t1);
	}
	return MPI_Finalize();
}
