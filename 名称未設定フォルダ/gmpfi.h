#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <emmintrin.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>

#include <pthread.h>
#include <mpfi.h>
#include <mpfi_io.h>
//#include "define.h"

typedef struct
{
 mpfi_t mpfi;
 volatile int id;
 int store;
}__gmpfi_t;//gmpfi_t型で定義。

typedef __gmpfi_t gmpfi_t[1];
typedef __gmpfi_t *gmpfi_ptr;
typedef const __gmpfi_t *gmpfi_srcptr;


void gmpfi_init2(gmpfi_ptr a,int prec);//
void gmpfi_set_str (gmpfi_ptr a , const char *str,int n);
void gmpfi_clear(gmpfi_ptr a);