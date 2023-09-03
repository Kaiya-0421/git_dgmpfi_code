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
int  Nlog=5;	   //外側ループ 分割数
#define Nlog2 20  //内側ループ　グラフの積み立て反復回数
//グラフノード数
#define DFG_TIME

mpfi_t data_mpfi2[10000];
extern  volatile int data_count;//再利用　
int data_count2;
extern int *node_list;
// #define acc 1024  //仮数部長
int main(int argc, char *argv[])
{
	int acc = 1024;
	if (argc <= 1)
	{
		fprintf(stderr, "no size\n.");
		exit(1);
	}
	sscanf(argv[1], "%d", &acc); ///ロジスティック写像の仮数部長
	thread_acc=acc;
	struct timespec start, end, DFGstart, DFGend;
	int i, j,k; //反復用変数
	unsigned long prec=acc;
    
	clock_gettime(CLOCK_REALTIME, &start);
	gmpfi_t x[Nlog2 + 1], one, four,tmp_mpfi;
	
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
	gmpfi_init2(x[0], acc);
	gmpfi_set_str(x[0], "0.7501", 10); //初期値
	for (i = 1; i < Nlog2 + 1; i++)
		gmpfi_init2(x[i], acc);

	
	//clock_gettime(CLOCK_REALTIME, &start);
	// Nlog*Nlog2 times :logistic
	//DFG作成時間の測定
	#ifdef DFG_TIME
    clock_gettime(CLOCK_REALTIME, &DFGstart);
	#endif
	for (j = 0; j < Nlog2; j++)
	{
		// x[i] = 4 * x[i-1] * (1 - x[i-1])の計算;
		gmpfi_sub(tmp_mpfi, one, x[j]);
		gmpfi_mul(tmp_mpfi, x[j], tmp_mpfi);
		gmpfi_mul(x[j + 1], four, tmp_mpfi);
	}
	#ifdef DFG_TIME
	clock_gettime(CLOCK_REALTIME, &DFGend);
	#endif
	//DFG作成終了
	//printf("data_mpfi.a=");
    //mpfi_out_str(stdout , 10, 0, *data_mpfi[6].a);///saharakaiya
	
	
	
	for (i = 0; i < Nlog; i++)
	{
		//int firstcal=node_list[0];
		printf("\n-----------cmpfi(%d)開始----------開始\n",i);
		cmpfi_cal2(i);
		//printf("終了saaa");
        printf("\n\n----------cmpfi(%d)終了-----------終了\n",i);
		//if(i<Nlog-1){
		gmpfi_set(x[0], x[Nlog2],2);
		//}
		//printf("saaa");
	}
	
	cmpfi_end();

	//実行終了
	clock_gettime(CLOCK_REALTIME, &end);


	///　　ロジスティック写像の表示
	//#ifdef TEST_OUT
	
	
	//printf("\n\n");
	for(i = 0; i < Nlog2+1; i++){
		
		if(i%5==0){
		printf("%d",i*Nlog);
		mpfi_out_str (stdout , 10, 0, x[i]->mpfi);
		//mpfi_out_str(stdout, 10, 17, x[i]->mpfi);
		printf("\n\n");
		}	
	}
	
	
	for (i = 0; i < Nlog2 + 1; i++)
		gmpfi_clear(x[i]);
	//ロジスティック写像の表示
	#ifdef DFG_TIME
	double DFGelasped_time = (double)(DFGend.tv_sec - DFGstart.tv_sec) + (double)(DFGend.tv_nsec - DFGstart.tv_nsec) * 1e-9;
	printf("DFG_generation=%lf,", DFGelasped_time);
	#endif
	//時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
	printf("%lf,", elasped_time);

	gmpfi_clear(one);
	gmpfi_clear(four);

	return 0;
}