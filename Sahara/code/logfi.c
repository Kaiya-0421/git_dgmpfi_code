#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpfi_io.h>
#include "mpfr.h"
#include "mpfi.h"
#include <time.h>
#define PLEC 1024
#define N 100
int main()
{
	struct timespec start, end;
	int i;
	unsigned long prec;
	mpfi_t x[N+1],one,four;
	//mpfr_t relerr;
    prec = PLEC; //変更する。仮数部長
	//printf("prec(bits) = "); while(scanf("%ld", &prec) < 1);
	mpfr_set_default_prec(prec);

	// initialize variables
	//mpfr_init(relerr);
	mpfi_init(one);
	mpfi_set_str(one, "1.0", 10);
	mpfi_init(four);
	mpfi_set_str(four, "4.0", 10);
	for(i = 0; i < N+1; i++)
		mpfi_init(x[i]);
    
	// set a initial interval
	mpfi_set_str(x[0], "0.7501", 10);
	//実行スタート
    clock_gettime(CLOCK_REALTIME, &start);
	for(i = 0; i <= N; i++)
	{
		
		//x[i + 1] = 4 * x[i] * (1 - x[i]);
		mpfi_sub(x[i + 1], one, x[i]);
		mpfi_mul(x[i + 1], x[i + 1], x[i]);
		mpfi_mul(x[i + 1], x[i + 1], four);

	}
    clock_gettime(CLOCK_REALTIME, &end);
	//実行終了

	for(i=0;i<N+1;i++){
		if((i % 10) == 0)
		{
			
			printf("%5d, ", i);
			mpfi_out_str(stdout , 10, 0, x[i]);
			printf("\n\n");
			//mpfi_out_str(stdout, 10, 17, x[i]);
		}
	}
		
	// delete variables
	//時間結果
	double elasped_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) * 1e-9;
    printf("\n\n時間は%lf\n", elasped_time);
	



	for(i = 0; i < N+1; i++)
		mpfi_clear(x[i]);
    
    mpfi_clear(one);
	mpfi_clear(four);
    
	return 0;
}