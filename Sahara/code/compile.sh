#!/bin/bash

main="hilf_pmpfi.c"
file="cmpfi.c nodelist.c gmpfi.c store_mpfi.c thread.c" 

filename="jikkou"
comp_option="-lmpfi -pthread -lgmp -lmpfr"

# gcc -O3 -o $filename $main $file $comp_option
#gcc -O3 -o logic_pmpfi logic_pmpfi.c $file $comp_option  
gcc -O3 -o hilf_pmpfi hilf_pmpfi.c $file $comp_option #LU分解
#先輩のロジスティックは上
#gcc -O3 -o logdbg loggfi_dbg.c $file $comp_option

#gcc -O3 -o loggfi_a loggfi_a.c $file $comp_option
#上は佐原分割実行　
#gcc -O3 -o loggfi loggfi.c $file $comp_option
# 佐原のは上 分割してない
#gcc -O3 -o loggfi_dbg loggfi_dbg.c $file $comp_option
# gcc -O3 -o test test.c $file $comp_option