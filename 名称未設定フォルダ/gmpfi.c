#include "gmpfi.h"

void gmpfi_set_str(gmpfi_ptr a , const char *str,int n){
    mpfi_set_str(a->mpfi, str, n);
}
//aの仮数部長の初期化
void gmpfi_init2(gmpfi_ptr a,int prec){
    mpfi_init2(a->mpfi, prec);
}
//データクリアー
void gmpfi_clear(gmpfi_ptr a){
    mpfi_clear(a->mpfi);
}