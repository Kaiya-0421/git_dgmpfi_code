#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpfi_io.h>
//#include "mpfr.h"
//#include "mpfi.h"
#include "gmpfi.h"
#define MAX_NUM 128
#define DFG_TIME  //DFG 作成時間表示させるかどうか
#define TIME
// #define coresize 1 //スレッドの個数
int  Nlog=16;	   //外側ループ 分割数 分割回数cmpfi_Cal2()実行    ////3以上で値が正しく出力されない
#define Nlog2 2048  //グラフ積立ループ2    ///      3以上で セグフォ起きる
// グラフノード数
///////////グラフの形///////*
// b=1.01 c=1.05  d=0.99  A(n+1)=c+An*b  E(n+1)=c+d*e
//
//    nextA  nextE
//      |      |
//     c+x    c+y
//      |      |
// (*) x  \   / y (*)
//    / \  \ / / |
//   a   b  c  d  e
////////////グラフの形////////

mpfi_t data_mpfi2[7000];
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

	sscanf(argv[1], "%d", &acc); /// ロジスティック写像の仮数部長
    thread_acc=acc;
	struct timespec start, end, DFGstart, DFGend;
	int i, j, k; // 反復用変数
	unsigned long prec=acc;

	gmpfi_t A[Nlog2+1], E[Nlog2+1], b, c, d, x, y;

	//	mpfr_t relerr;

	// printf("prec(bits) = "); while(scanf("%ld", &prec) < 1);
	mpfr_set_default_prec(prec);
    for (i = 0; i < 1000; i++){
	    mpfi_init2(data_mpfi2[i], acc);
	}
	// 初期化
    size=Nlog2*Nlog;
	gmpfi_init2(A[0], acc);
	gmpfi_init2(E[0], acc);
	gmpfi_set_str(A[0], "2.01", 10); // 初期値
	gmpfi_set_str(E[0], "1.99", 10); // 初期値

	gmpfi_init2(b, acc); // 1.01
	gmpfi_init2(c, acc); // 1.05
	gmpfi_init2(d, acc); // 0.99
	gmpfi_init2(x, acc); // a*b=x
	gmpfi_init2(y, acc); // d*e=y

	gmpfi_set_str(b, "1.01", 10);
	gmpfi_set_str(c, "1.05", 10);
	gmpfi_set_str(d, "0.99", 10);

	for (i = 1; i < Nlog2 + 1; i++){
		gmpfi_init2(A[i], acc);
	    gmpfi_init2(E[i], acc);
	}
	/// 実行スタート
	clock_gettime(CLOCK_REALTIME, &start);

/*/////
a[0]はnodeID=0
e[0]はnodeID=1
bはnodeID=2
cはnodeID=3
dはnodeID=4
*/////

	///////////グラフの形///////*
	// a[0]=2.01,e[0]=1.99 b=1.01 c=1.05  d=0.99  A(n+1)=c+An*b  E(n+1)=c+d*e
	//
	//    nextA  nextE
	//      |      |
	//     c+x    c+y
	//      |      |
	// (*) x  \   / y (*)
	//    / \  \ / / |
	//   a   b  c  d  e
	////////////グラフの形////////
	// Nlog*Nlog2 times :My graph
	//DFG作成による時間計測
	#ifdef DFG_TIME
	clock_gettime(CLOCK_REALTIME, &DFGstart);
	#endif
	for (j = 0; j < Nlog2; j++){
		gmpfi_mul(x, A[j], b);//id=5 4n+1
		gmpfi_mul(y, d, E[j]);//id=6 4n+2
		gmpfi_add(A[j + 1], c, x);//id=7 4n+3
		gmpfi_add(E[j + 1], c, y);//id=8 4n+4
	}
	//DFG作成終了
	#ifdef DFG_TIME
	clock_gettime(CLOCK_REALTIME, &DFGend);
    #endif
	for (i = 0; i < Nlog; i++){
		//int firstcal=node_list[0];
		//printf("\n-----------cmpfi(%d)開始----------開始\n",i);
		cmpfi_cal2(i);
        //printf("\n\n----------cmpfi(%d)終了-----------終了\n",i);
		gmpfi_set(A[0], A[Nlog2],0);
		gmpfi_set(E[0], E[Nlog2],1);
	}
	cmpfi_end();



	// 実行終了
	clock_gettime(CLOCK_REALTIME, &end);

	/// 　　ロジスティック写像の表示
	// #ifdef TEST_OUT

	printf("\n\n");
	for (i = 0; i < Nlog2+1; i++)
	{
		//if (i % 5 == 0)
		//{
			printf("A");
			printf("%d", i);
			mpfi_out_str(stdout, 10, 0, A[i]->mpfi);
			printf("\n");
			printf("E");
			printf("%d", i);
			mpfi_out_str(stdout, 10, 0, E[i]->mpfi);
			printf("\n\n");
		//}
	}

	for (i = 0; i < Nlog + 1; i++){
		gmpfi_clear(A[i]);
	    gmpfi_clear(E[i]);
	}
	// My graphの表示

    //DFG作成時間結果
	#ifdef DFG_TIME
	double DFGelasped_time = (double)(DFGend.tv_sec - DFGstart.tv_sec) + (double)(DFGend.tv_nsec - DFGstart.tv_nsec) * 1e-9;
	printf("%lf,", DFGelasped_time);
	#endif
	#ifdef TIME
	// DFG作成と区間演算実行時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
	printf("%lf,", elasped_time);
	#endif

	gmpfi_clear(b);
	gmpfi_clear(c);
	gmpfi_clear(d);

	return 0;
}
