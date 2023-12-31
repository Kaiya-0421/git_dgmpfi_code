// gcc -o hilf_mympfi hilf_mympfi.c -pthread -lgmp -lmympfi -lmpfr
// gcc -O3 -o hilf_mympfi hilf_mympfi.c -pthread -lgmp -lmympfi -lmpfr
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include "gmpfi.h"
int Nlog;//sahara
#ifdef __linux
#define CLOCK_REALTIME 0
#endif

void printTime(struct timespec start,struct timespec end, char str[]);
void printTime1(struct timespec start,struct timespec end, char str[]);

int main(int argc, char *argv[]){

    int i;
    int acc;
    struct timespec start,end,t1,t2,t3;
    if (argc <= 3) {
        fprintf(stderr, "no size\n.");
        exit(1);
    }
    sscanf(argv[1], "%d", &size);///ロジスティック写像の反復回数
    sscanf(argv[2], "%d", &coresize);
    sscanf(argv[3], "%d", &acc);//正確さ？何ビットまで与えるか？
    thread_acc  = acc;
//////////////////////////////////////////////////////////////////////////////////////////////////
    // aとx[0]が必要
    
    clock_gettime(CLOCK_REALTIME, &start);

    gmpfi_t four,tmp_mpfi,one;
    gmpfi_t x[size];
    printf("size1=%d",size);
    gmpfi_init2 (four, acc);//4
    printf("size2=%d",size);

    gmpfi_set_str (four ,"4" ,10);//4
    gmpfi_init2 (one, acc);//1
    gmpfi_set_str (one ,"1" ,10);//1
    gmpfi_init2 (tmp_mpfi, acc);//ビット数
    gmpfi_init2 (x[0], acc);//ビット数
    gmpfi_set_str (x[0] ,"0.7501" ,10);//初期値
    for(i=1;i<size;i++){
        gmpfi_init2 (x[i], acc);
    }
    clock_gettime(CLOCK_REALTIME, &t1); 
    ///ロジスティック写像の計算の反復



    for(i=1;i<size;i++){
        gmpfi_sub(tmp_mpfi,one,x[i-1]);
        gmpfi_mul(tmp_mpfi,x[i-1],tmp_mpfi);
        gmpfi_mul(x[i],four,tmp_mpfi);
    }
    clock_gettime(CLOCK_REALTIME, &t2); 
//ロジスティック写像の初項
  //  mpfi_out_str(stdout , 10, 0, x[0]->mpfi);
  // putchar('\n');


    cmpfi_cal();  //スレッド破棄の関数
///　　ロジスティック写像の表示
    //#ifdef TEST_OUT
    /*
    putchar ('\n');
    for(i = 0; i < size; i++){
      if(i%5==0){
        printf("%d",i);
        mpfi_out_str(stdout , 10, 0, x[i]->mpfi);
        mpfi_out_str(stdout, 10, 17, x[i]->mpfi);
        putchar ('\n');
      }
    }*/
    // mpfi_out_str (stdout , 10, 0, x[0]->mpfi);
    // putchar ('\n');
    // mpfi_out_str (stdout , 10, 0, x[size-1]->mpfi);
    // putchar ('\n');

    //#endif


    clock_gettime(CLOCK_REALTIME, &t3); 
    gmpfi_clear(tmp_mpfi);
    gmpfi_clear(one);
    gmpfi_clear(four);
    //mpfr_clear(relerr);
    for(i = 0;i < size; i++){
        gmpfi_clear(x[i]);
    }
    
    clock_gettime(CLOCK_REALTIME, &end); 

   
    #ifndef TEST__
    // printTime(start, t1, "init time\t" );
    // printTime(t1, t2, "DFG time\t" );
    // printTime(t2, t3, "cal time\t" );
    // printTime(t3, end, "clear time\t" );
    printTime1(start, end, "" );
    #endif

//////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}


void printTime(struct timespec start,struct timespec end,char str[]){
  if((end.tv_nsec - start.tv_nsec) < 0){ 
    end.tv_nsec += 1000000000; 
    end.tv_sec  -= 1; 
  }
  printf("%s :%10ld.%09ld\n",str ,end.tv_sec-start.tv_sec, end.tv_nsec-start.tv_nsec);
}

void printTime1(struct timespec start,struct timespec end,char str[]){
  if((end.tv_nsec - start.tv_nsec) < 0){ 
    end.tv_nsec += 1000000000; 
    end.tv_sec  -= 1; 
  }
  printf("%10ld.%09ld,",end.tv_sec-start.tv_sec, end.tv_nsec-start.tv_nsec);
}