#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
void print_arr(int** arr, int N){
        int row,col;
	printf("[\n");
        for(row=0;row<5&&row<N;row++){
		printf("[");
                for(col=0;col<5&&col<N;col++){
                        printf("%d, ",arr[row][col]);
                }
                printf("……]\n");
        }
        printf("……\n]\n\n");
}
int main(){

        srand((unsigned) time(NULL));
        int N,row,col,k,temp;
        int **arr_1, **arr_2,**result = NULL;
        clock_t start, end;
	//printf("输入矩阵维度");

        //scanf("%d",&N);
        N = 1000;
        start = clock();
        arr_1 = (int**)malloc(sizeof(int*)*N);
        arr_2 = (int**)malloc(sizeof(int*)*N);
        result = (int**)malloc(sizeof(int*)*N);
        if(arr_1==NULL||arr_2==NULL||result==NULL){
                        printf("内存分配失败");
                        exit(-1);
                }
        for(k=0;k<N;k++){
                arr_1[k] = (int*)malloc(sizeof(int)*N);
                arr_2[k] = (int*)malloc(sizeof(int)*N);
                result[k] = (int*)malloc(sizeof(int)*N);
                if(arr_1[k]==NULL||arr_2[k]==NULL||result[k]==NULL){
                        printf("内存分配失败");
                        exit(-1);
                }
        }

        for(row=0;row<N;row++){
                for(col=0;col<N;col++){
                        arr_1[row][col] = (3*row+2*col)%100;
                        arr_2[row][col] = (2*row+7*col)%100;
                }
        }

        print_arr(arr_1,N);
        print_arr(arr_2,N);
        for(row=0;row<N;row++){
		printf("%d/%d\n",row,N);
                for(col=0;col<N;col++){
                        temp = 0;
                        for(k=0;k<N;k++){
                                temp += arr_1[row][k] * arr_2[k][col];
                        }
                        result[row][col] = temp;
                }
        }
        print_arr(result,N);
        end = clock();
        printf("clock=%.3f",(double)(end-start)/CLOCKS_PER_SEC);
        free(arr_1);
        free(arr_2);
        free(result);
        arr_1 = NULL;
        arr_2 = NULL;
        result  = NULL;
        return 0;
}


