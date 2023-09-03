#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 3
/*
3  2  2  1
2 -3 -2  -8
4  2  3   0
//答えは-1,2,0
*/
int main(){
	double mat[N][N];
int k=0,j=0,i=0;
    for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			mat[i][j]= 1.0/(double)(1.0+i+j);
		}
	}
	double b[N]={1.0,0,0};
	
	double r=0;
	for(k=0;k<N-1;k++){
		for(i=k+1;i<N;i++){//i=1から
			r=mat[i][k]/mat[k][k];
			//係数で引いてく
			for(j=k;j<N;j++){
				mat[i][j]=mat[i][j]-mat[k][j]*r;
			}//j列のi+1行以下が0になった
			b[i]=b[i]-b[k]*r;
		}//k*k部分が上三角行列に
	}//全てが三角行列になった

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%lf ",mat[i][j]);
		}
		printf("b[%d]=%lf",i,b[i]);
		printf("\n");
	}
	/*
	for(i=0;i<N;i++){
		for(j=0;j<N+1;j++){
			//printf("%lf ",mat[i][j]);
		}printf("\n");
		printf("b[%d]=%lf",i,b[i]);
	}
	*/

//後退代入
	for(i=N-1;i>=0;i--){
		for(j=i+1;j<N;j++){
			b[i]=b[i]-mat[i][j]*b[j];
		}
		b[i]=b[i]/mat[i][i];
	}

	for(i=0;i<N;i++){
		for(j=0;j<N+1;j++){
			//printf("%lf ",mat[i][j]);
		}printf("\n");
		printf("b[%d]=%lf",i,b[i]);
	}
	return 0;
}
