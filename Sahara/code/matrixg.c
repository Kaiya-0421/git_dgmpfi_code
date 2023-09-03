#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpfi_io.h>
#include "mpfr.h"
#include "mpfi.h"
#include "gmpfi.h"
#define MAX_NUM 128
//#define coresize 1 //スレッドの個数
#define Nlog 5	   //外側ループ
#define Nlog2 4  //内側ループ
//グラフノード数


mpfi_t data_mpfi2[7000];
extern  volatile int data_count;//再利用　
int data_count2;
extern int *node_list;
// #define acc 1024  //仮数部長
int main(int argc, char *argv[])
{
	int coresize=0;
	int acc = 1024;
	if (argc <= 1)
	{
		fprintf(stderr, "no size\n.");
		exit(1);
	}
	sscanf(argv[1], "%d", &acc); ///ロジスティック写像の仮数部長
	thread_acc=acc;
	struct timespec start, end;
	int i, j,k,l; //反復用変数
	unsigned long prec;
    

	
	gmpfi_t matrix[Nlog2 + 1][Nlog2 +1],x[Nlog2 + 1][Nlog2 +1],y[Nlog2 + 1][Nlog2 +1], one, four,tmp_mpfi;
	
	//	mpfr_t relerr;

	// printf("prec(bits) = "); while(scanf("%ld", &prec) < 1);
	mpfr_set_default_prec(prec);
    for (i = 0; i < 1000; i++)
		mpfi_init2(data_mpfi2[i], acc);
		
	// 初期化
    
    size=Nlog2*Nlog;
//printf("size1=%d\n",size);	
	gmpfi_init2(one, acc); // 1
//printf("size2=%d\n",size);	
    gmpfi_init2 (tmp_mpfi, acc);
	gmpfi_set_str(one, "1.0", 10);
	gmpfi_init2(four, acc);
	gmpfi_set_str(four, "4.0", 10);
	
	
	for (i = 0; i < Nlog2 + 1; i++){
		for (l = 0; l < Nlog2 + 1; l++){
		    gmpfi_init2(x[i][l], acc);
		    gmpfi_init2(y[i][l], acc);
			gmpfi_init2(matrix[i][l], acc);
		}
	}
	gmpfi_set_str(x[0][0], "buf", 10); //初期値  set値2
	gmpfi_set_str(y[0][0], "buf", 10); //初期値  set値3
	///実行スタート
	clock_gettime(CLOCK_REALTIME, &start);
	// Nlog*Nlog2 times :logistic
//行列の値設定
    char buf[256];
	int as=1;
	for (j = 0; j < Nlog2; j++)
	{
		for (l = 0; l < Nlog2; l++){
		
		
		sprintf(buf, "%d", j+l+as);
		gmpfi_set_str (x[j][l] , buf ,10);
		gmpfi_set_str (x[j][l] , buf ,10);
		

		}
		as=1;
	}
	/*
	1 2 3 4          
	2 3 4 5     の2乗          
	3 4 5 6          
	4 5 6 7

	
	
	
	*/
	
	
	int firstcal=node_list[0];
	for (i = 0; i < Nlog; i++)
	{
		printf("\n--%d--開始\n",i);
		cmpfi_cal2(i);
        printf("\n--%d--終了\n",i);
		printf("\ndata[2]の値");
		mpfi_out_str(stdout , 10, 0, *data_mpfi[3].a);
		gmpfi_set(x[0][0], x[Nlog2][Nlog2],2);
		gmpfi_set(x[0][0], x[Nlog2][Nlog2],2);
	}

	//実行終了
	clock_gettime(CLOCK_REALTIME, &end);


	///　　ロジスティック写像の表示
	//#ifdef TEST_OUT
	
	
	printf("\n\n");
	for(i = 0; i < Nlog2+1; i++){
		
		if(i%5==0){
		printf("%d",i);
		mpfi_out_str (stdout , 10, 0, x[i][i]->mpfi);
		//mpfi_out_str(stdout, 10, 17, x[i]->mpfi);
		printf("\n\n");
		}	
	}
	
	for (i = 0; i < Nlog2 + 1; i++){
		for (j = 0; j < Nlog2 + 1; j++){
        gmpfi_clear(x[i][j]);
		gmpfi_clear(y[i][j]);
		gmpfi_clear(matrix[i][j]);
		}
	}
		
	//ロジスティック写像の表示

	//時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
	printf("%lf,", elasped_time);

	gmpfi_clear(one);
	gmpfi_clear(four);

	return 0;
}