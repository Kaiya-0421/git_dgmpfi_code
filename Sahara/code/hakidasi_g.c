#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpfi_io.h>
#include "mpfr.h"
#include "mpfi.h"
#include "gmpfi.h"
#include <time.h>
#define N 3
int Nlog;
/*
1   1/2 1/3  1
1/2 1/3 1/4  0
1/3 1/4 1/5  0
//答えは9,-36,30
*/
int main(){
	int k=0,j=0,i=0;
	int acc=64;
	int thread_acc = acc;
	char buf[256];//簡単に係数を代入するため
	mpfr_set_default_prec(acc);//基本的な精度の指定

	gmpfi_t mat[N][N],b[N],set[N][N],set1[N][N],r;//求解に必要な変数
    //bベクトルの値代入
	gmpfi_init2(r, acc);
	/*gmpfi_init2(r[0], acc);//係数を消すやつ。
	gmpfi_init2(r[1], acc);
	gmpfi_init2(r[2], acc);
	gmpfi_init2(b[0], acc);
	*/
    gmpfi_set_str(b[0] ,"1" ,10); //0
    for(i = 1; i < N; i++){
        gmpfi_init2(b[i], acc);
        gmpfi_set_str (b[i] ,"0" ,10);  //1,2
    }
	//係数行列
	for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            gmpfi_init2(set1[i][j], acc);
            gmpfi_set_str(set1[i][j], "1" ,10);          //3,6,9, 12,15,18, 21,24,27
            sprintf(buf, "%d", (i+1)+(j+1)-1);
            gmpfi_init2(set[i][j], acc);
            gmpfi_set_str(set[i][j] , buf ,10);          //4,7,10, 13,16,19, 22,25,28
            gmpfi_init2(mat[i][j], acc);
            gmpfi_div(mat[i][j], set1[i][j], set[i][j]); //5,8,11, 14,17,20, 23,26,29
        }
    }

/*
	for(i=0;i<N;i++){//代入の表示
		for(j=0;j<N;j++){
			    printf("[%d]行[%d]列=",i,j);
				mpfi_out_str(stdout , 10, 0, mat[i][j]->mpfi);
		}
		printf("\n\n");
	}
*/
////掃き出しのC言語例
/*	
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
*/

	for(k=0;k<N-1;k++){
		for(i=k+1;i<N;i++){//i=1から//N-1にするとうまくいく
			gmpfi_div(r,mat[i][k],mat[k][k]);//r=mat[i][k]/mat[k][k];
			//係数で引いてく
			for(j=k;j<N;j++){
				gmpfi_mul(set[k][j],mat[k][j],r);//mat[k][j]*r
				gmpfi_sub(mat[i][j],mat[i][j],set[k][j]);//mat[i][j]=mat[i][j]-mat[k][j]*r;
			}//j列のi+1行以下が0になった
			gmpfi_mul(set1[i][k],b[k],r);//b[k]*r
			gmpfi_sub(b[i],b[i],set1[i][k]);//b[i]=b[i]-b[k]*r;
		}//k*k部分が上三角行列に
	}
	cmpfi_cal();//全てが三角行列になった
	//cmpfi_cal();

printf("三角行列\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			    printf("[%d][%d]",i,j);
				mpfi_out_str(stdout , 10, 0, mat[i][j]->mpfi);
		}
		printf("\n\n");
	}
	

	

//後退代入

/*
	for(i=N-1;i>=0;i--){
		for(j=i+1;j<N;j++){
			b[i]=b[i]-mat[i][j]*b[j];
		}
		b[i]=b[i]/mat[i][i];
	}
	*/
	//後退代入
	/*
	for(i=N-1;i>=0;i--){
		for(j=i+1;j<N;j++){
			gmpfi_mul(set1[i][j],mat[i][j],b[j]);//mat[i][j]*b[j];
			gmpfi_sub(b[i],b[i],set1[i][j]);
		}
		gmpfi_div(b[i],b[i],mat[i][i]);//b[i]=b[i]/mat[i][i];
	}cmpfi_cal();

	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<N;j++){
			mpfi_out_str(stdout , 10, 0, mat[i][j]->mpfi);
		}printf("\n");
	}
printf("解\n");
	for(i=0;i<N;i++){
		printf("\n");printf("\n");
		mpfi_out_str(stdout , 10, 0, b[i]->mpfi);
	}*/
	
	return 0;
}
