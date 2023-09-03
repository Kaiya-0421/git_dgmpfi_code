#!/bin/bash

main="hilf_pmpfi.c"
file="cmpfi_old.c nodelist.c gmpfi.c store_mpfi.c thread.c" 

filename="jikkou"
comp_option="-lmpfi -pthread -lgmp -lmpfr"

gcc -O3 -o heiretsu_g heiretsu_g.c $file $comp_option
