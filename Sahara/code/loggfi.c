#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpfi_io.h>
#include "mpfr.h"
#include "mpfi.h"
#include "gmpfi.h"
#define MAX_NUM 128
#define Nlog 100
#define coresize 32 //反復回数や配列の値の個数
// #define acc 1024  //仮数部長
int op2[10000];//グラフノード数
mpfi_t data_mpfi2[7000];
int main(int argc, char *argv[])
{
	
	size=Nlog*Nlog;
	int acc = 1024;
	if (argc <= 1)
	{
		fprintf(stderr, "no size\n.");
		exit(1);
	}
	sscanf(argv[1], "%d", &acc); ///ロジスティック写像の仮数部長
	struct timespec start, end;
	int i;
	unsigned long prec;
	

	gmpfi_t x[Nlog + 1], one, four;
	//	mpfr_t relerr;
	// printf("prec(bits) = "); while(scanf("%ld", &prec) < 1);
	mpfr_set_default_prec(prec);
	// 初期化
	// mpfr_init(relerr);
	gmpfi_init2(one, acc); // 1
	gmpfi_set_str(one, "1.0", 10);
	gmpfi_init2(four, acc);
	gmpfi_set_str(four, "4.0", 10);
	gmpfi_init2(x[0], acc);
	gmpfi_set_str(x[0], "0.7501", 10); //初期値
	for (i = 1; i < Nlog + 1; i++)
		gmpfi_init2(x[i], acc);

	///実行スタート
	clock_gettime(CLOCK_REALTIME, &start);

	//#pragma gmpfi 20
	for (i = 0; i < Nlog; i++)
	{
		// x[i] = 4 * x[i-1] * (1 - x[i-1])の計算;
		gmpfi_sub(x[i + 1], one, x[i]);
		gmpfi_mul(x[i + 1], x[i + 1], x[i]);
		gmpfi_mul(x[i + 1], x[i + 1], four);
	}
	//printf("node=%d\n",node_list[0]);
	//実行終了
	cmpfi_cal();

	clock_gettime(CLOCK_REALTIME, &end);
	///　　ロジスティック写像の表示
	//#ifdef TEST_OUT

	
		putchar ('\n');
		for(i = 0; i < Nlog+1; i++){
			if(i%5==0){
			printf("%d",i);
			mpfi_out_str (stdout , 10, 0, x[i]->mpfi);
			//mpfi_out_str(stdout, 10, 17, x[i]->mpfi);
			printf("\n\n");
			}
		}
		

	for (i = 0; i < Nlog + 1; i++)
		gmpfi_clear(x[i]);

	//実行終了

	///　　ロジスティック写像の表示
	//#ifdef TEST_OUT

	//時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
	// printf("DFG作成から演算終了までの時間\n");
	printf("%lf,", elasped_time);

	gmpfi_clear(one);
	gmpfi_clear(four);

	return 0;
}