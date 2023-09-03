#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <emmintrin.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>

#include <pthread.h>
#include <mpfi.h>
#include <mpfi_io.h>
#include "define.h"//gmpfiにまつわるdefine
//#include "define.h"

typedef struct
{
 mpfi_t mpfi;
 volatile int id;
 int store;
}__gmpfi_t;//gmpfi_t型で定義
typedef __gmpfi_t gmpfi_t[1];
typedef __gmpfi_t *gmpfi_ptr;
typedef const __gmpfi_t *gmpfi_srcptr;

typedef struct
{
 volatile int id;
 int store;
 bool done;
 int op;//ノード情報
 int lfg;//レフトエッジ(アドレス？)
 int rfg;//ライトエッジ(アドレス？)
}__gmpfi_dfg_data;//gmpfi_t型で定義。

typedef __gmpfi_dfg_data *gmpfi_dfg_data;


void gmpfi_init2(gmpfi_ptr a,int prec);//prec仮数部で変数aの初期化
void gmpfi_set_str (gmpfi_ptr a , const char *str,int n);//変数aをstrで書かれた数をn進数で代入
void gmpfi_clear(gmpfi_ptr a);//aのメモリ領域解放
void gmpfi_add(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c);
void gmpfi_sub(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c);
void gmpfi_mul(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c);
void gmpfi_div(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c);

void gmpfi_cal();
int get_node_id();