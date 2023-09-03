#!/bin/bash

main="hilf_pmpfi.c"
file="cmpfi.c nodelist.c gmpfi.c store_mpfi.c thread.c" 
filename="jikkou"
comp_option="-lmpfi -pthread -lgmp -lmpfr"

gcc -O3 -o heiretsu_g_div heiretsu_g_div.c $file $comp_option
