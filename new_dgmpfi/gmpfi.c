#include "gmpfi.h"

int count_node_id=0;//node番号付与のためのカウンター
int count_node_id_for_worker=0;
//int op[];//個々のノード状態格納配列(オペランド、オペレータ)
//int queue[];//演算可能なノードを格納する配列
void gmpfi_set_str(gmpfi_ptr a , const char *str,int n){
    mpfi_set_str(a->mpfi, str, n);

    gmpfi_dfg_data[count_node_id]->op=NUM;
    a->id = count_node_id;
    count_node_id++;
}
//aの仮数部長の初期化
void gmpfi_init2(gmpfi_ptr a,int prec){
    mpfi_init2(a->mpfi, prec);
}
//データクリアー
void gmpfi_clear(gmpfi_ptr a){
    mpfi_clear(a->mpfi);
}
//足し算のグラフ追加
void gmpfi_add(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c){
    dfg_data[count_node_id]->op=ADD;
    
    a->id = count_node_id;
    count_node_id++;
}
//引き算のグラフ追加
void gmpfi_sub(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c){
    dfg_data[count_node_id]->op=SUB;
    a->id = count_node_id;
    count_node_id++;
}
//掛け算のグラフ追加
void gmpfi_mul(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c){
    dfg_data[count_node_id]->op=MUL;
    a->id = count_node_id;
    count_node_id++;
}
//割り算のグラフ追加
void gmpfi_div(gmpfi_ptr a, gmpfi_ptr b, gmpfi_ptr c){
    dfg_data[count_node_id]->op=DIV;
    a->id = count_node_id;
    count_node_id++;
}
//ワーカが演算子ノードidを取得する関数
int get_node_id(){
    //int node_id//=queue_node[count];
    //return node_id;
    return 1;
}
//演算部分
/*
gmpfi_cal(){
    while(1){
        int node_id=-1;


       // if(queue_node[count_node_id_for_worker]==-1){break;}
    }

}
*/