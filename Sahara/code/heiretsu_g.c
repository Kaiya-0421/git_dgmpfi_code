#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpfi_io.h>
//#include "mpfr.h"
//#include "mpfi.h"
#include "gmpfi.h"
#define MAX_NUM 128
//#define coresize 1 //スレッドの個数
int Nlog;
#define Nlog2 100  //内側ループ
//グラフノード数
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
	struct timespec start, end;
	int i, j,k; //反復用変数
	unsigned long prec=acc;
    

	
	gmpfi_t A[Nlog2 + 1],E[Nlog2+1], b, c, d,x,y,tmp1,tmp2;
	
	//	mpfr_t relerr;

	// printf("prec(bits) = "); while(scanf("%ld", &prec) < 1);
	mpfr_set_default_prec(prec);
   
	// 初期化
    
    
	gmpfi_init2(A[0], acc);
	gmpfi_init2(E[0], acc);
	gmpfi_set_str(A[0], "2.01", 10); //初期値
	gmpfi_set_str(E[0], "1.99", 10); //初期値

	gmpfi_init2 (b, acc); // 1.01
    gmpfi_init2 (c, acc);//1.05
	gmpfi_init2 (d, acc);//0.99
	gmpfi_init2 (x, acc);//a*b=x
	gmpfi_init2 (y, acc);//d*e=y

	gmpfi_set_str(b, "1.01", 10);
	gmpfi_set_str(c, "1.05", 10);
	gmpfi_set_str(d, "0.99", 10);
	

	for (i = 1; i < Nlog2 + 1; i++){
		gmpfi_init2(A[i], acc);
		gmpfi_init2(E[i], acc);
	}

	///実行スタート
	clock_gettime(CLOCK_REALTIME, &start);
	

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
// Nlog*Nlog2 times :My graph
	for (j = 0; j < Nlog2; j++){
		gmpfi_mul(x,A[j],b);
		gmpfi_mul(y,d,E[j]);
		gmpfi_add(A[j+1],c,x);
		gmpfi_add(E[j+1],c,y);
	}
	cmpfi_cal();
	//printf("data_mpfi.a=");
    //mpfi_out_str(stdout , 10, 0, *data_mpfi[6].a);///saharakaiya
	
	
	
	

	//実行終了
	clock_gettime(CLOCK_REALTIME, &end);


	///　　ロジスティック写像の表示
	//#ifdef TEST_OUT
	
	
	printf("\n\n");
	for(i = 0; i < Nlog2+1; i++){
		
		if(i%5==0){
			printf("A-");
		    printf("%d",i);
		    mpfi_out_str (stdout , 10, 0, A[i]->mpfi);
			printf("E-");
		    printf("%d",i);
		    mpfi_out_str (stdout , 10, 0, E[i]->mpfi);
		    printf("\n\n");
		}	
	}
	
	
	for (i = 0; i < Nlog2 + 1; i++){
		gmpfi_clear(A[i]);
		gmpfi_clear(E[i]);
	}
	//My graphの表示

	//時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
	printf("%lf,", elasped_time);

	gmpfi_clear(b);
	gmpfi_clear(c);
	gmpfi_clear(d);

	return 0;
}