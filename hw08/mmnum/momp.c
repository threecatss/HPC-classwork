#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "time.h"
#include "mpi.h"
#include "crt_rand.h"
typedef struct{
float value;
int index;
} mess;
int main(int argc, char* argv[]){
	int i,j,N;
	double t1, t2;
	N = atoi(argv[1]);
	float* a;
	a = crtarr(N,1);
	int world_rank, world_size;
	mess* arr = NULL;
	arr = (mess*)malloc(sizeof(mess)*N);
        if(arr==NULL){
                printf("�ڴ����ʧ��\n");
                exit(-1);
                }
	for(i=0;i<N;i++){
		arr[i].value = a[i];
		arr[i].index = i;
	}
	free(a);
	a = NULL;
	int provided;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED,&provided);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	int step = N/world_size;
	mess max, out;
	max = arr[world_rank*step];
	t1 = omp_get_wtime();
	if(world_rank!=world_size-1){
	#pragma omp parallel for
	for(i=world_rank*step;i<(world_rank+1)*step;i++){
		if(max.value<arr[i].value)
			max = arr[i];
	}
	}
	else{
	#pragma omp parallel for
        for(i=world_rank*step;i<N;i++){
                if(max.value<arr[i].value)
                        max = arr[i];
       	 }

	}
	free(arr);
	arr = NULL;
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&max,&out,1,MPI_FLOAT_INT,MPI_MAXLOC,0,MPI_COMM_WORLD);
	t2 = omp_get_wtime();
	if(world_rank==0)
		printf("maxrank=%d,maxindex=%d,maxvalue=%f,time=%f(s)\n",out.index/N,out.index%N,out.value,t2-t1);
	return MPI_Finalize();
}

