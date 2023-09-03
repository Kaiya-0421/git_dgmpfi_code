logfi:logfi.c
	gcc  -O3  logfi.c -lmpfr -lgmp -lmpfi -o logfi
haki_mp:hakidasi_mpfi.c
	gcc  -O3  hakidasi_mpfi.c -lmpfr -lgmp -lmpfi -o hakidasi_mpfi
heiretsu:heiretsu.c
	gcc  -O3  heiretsu.c -lmpfr -lgmp -lmpfi -o heiretsu
parallel: parallel.cpp
	g++ parallel.cpp -I /usr/local/include/eigen3 -std=c++14 -fopenmp -lpthread -O3 -o $@	
hei_g: heiretsu_g.c
	sh compile_h.sh
hei_g_div: heiretsu_g_div.c
	sh compile_h_div.sh
log: loggfi_a.c #ロジスティック写像分割
	sh compile_a.sh
haki_g: hakidasi_g.c
	sh compile_hakidasi_g.sh
pm: logic_pmpfi.c
	sh compile.sh