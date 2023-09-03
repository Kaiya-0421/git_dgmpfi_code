#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpfi_io.h>
#include "mpfr.h"
#include "mpfi.h"
#include <time.h>
#include "gmpfi.h"
int main(){
	
	int acc=64;
	mpfr_set_default_prec(acc);//基本的な精度の指定

	gmpfi_t a;//求解に必要な変数
	gmpfi_init2(a, acc);
	gmpfi_set_str(a,"0.7501",10);
  
	
	
    //gmpfi_set_str(a ,"1" ,10); //0
	mpfi_out_str(stdout , 10, 0, a->mpfi);
	
	return 0;
}
