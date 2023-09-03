#include "gmpfi.h"

int sub_thread = 0;
int count = 0;
int isWrite = 0;
int *log_node = NULL;
int id = -1;

int coresize = 0;//CORE_SIZE;
int size = 3;
extern int Nlog;//分割数//sahara

head_t *head = NULL;
head_t *head2 = NULL;//保存用sahara
int *op = NULL;
int op2[10000];//保存用
edge_t *g = NULL;
__data_core *data_core = NULL;
__data_mpfi *data_mpfi = NULL;

#ifdef VER11
mpfi_t main_data;
#endif

struct wait_t *wait_h = NULL;
struct wait_t *wait_l = NULL;

extern int *node_list;//sahara

#ifdef VER12
void initTmp()
{
    tmp_mpfi->store = 1;
}
#endif
int cmpfi_malloc()
{
    log_node = (int *)malloc(MAX_STACK * sizeof(int));
    if (log_node == NULL)
    {
        printf("lognode malloc error\n");
    }
    head = (head_t *)malloc(MAX_STACK * sizeof(head_t));
    if (head == NULL)
    {
        printf("head malloc error\n");
    }
    head2 = (head_t *)malloc(MAX_STACK * sizeof(head_t));
    if (head2 == NULL)
    {
        printf("head malloc error\n");
    }//sahara 保存用
    op = (int *)malloc(MAX_STACK * sizeof(int));
    if (op == NULL)
    {
        printf("op malloc error\n");
    }
    //op2 = (int *)malloc(MAX_STACK * sizeof(int));
    //if (op2 == NULL)
    //{
    //    printf("op2 malloc error\n");
    //}
    data_core = (__data_core *)malloc(CORE_SIZE * sizeof(__data_core));
    if (data_core == NULL)
    {
        printf("data_core malloc error\n");
    }
    data_mpfi = (__data_mpfi *)malloc(MAX_STACK * sizeof(__data_mpfi));
    if (data_mpfi == NULL)
    {
        printf("data_mpfi malloc error\n");
    }
    g = (edge_t *)malloc(MAX_STACK * sizeof(edge_t));
    if (g == NULL)
    {
        printf("g malloc error\n");
    }
    initList();
#ifdef VER12
    initTmp();
#endif
    return 0;
}

int cmpfi_free()
{
    free(log_node);
    free(head);
    free(head2);
    free(op);
    free(op2);
    free(g);
    free(data_core);
    free(data_mpfi);
    freeList();
    return 0;
}
int cmpfi_free2()
{
    free(log_node);
    free(head);
    free(op);
    free(op2);
    free(g);
    free(data_core);
    free(data_mpfi);
    freeList();
    return 0;
}

//ファイルOPEN
int cmpfi_create()
{
    cmpfi_malloc();
    isWrite = 1;
    return 1;
}
int cmpfi_create2()
{
    // cmpfi_malloc();
    isWrite = 1;
    return 1;
}

//ファイルCLOSE
int cmpfi_cancel()
{
    cancelThread();
    cmpfi_free();
    sub_thread = 0;
    isWrite = 0;
    return 1;
}

int cmpfi_cancel2()
{
    cancelThread(); // sahara
    // cmpfi_free2();
    sub_thread = 0;
    // isWrite = 0;
    return 1;
}

void tmp_cal()
{
    int i = 0;
    if (sub_thread == 0)
    {
#ifdef VER12
        init_storeData(thread_acc);
#endif
        createThread(coresize);
        sub_thread = 1;
    }
    else
    {
        emptyThread();
    }

    int id = -1;

    while (1)
    {
        if (id == -1)
        {
            id = atomicGetList(coresize);
            if (id != -1)
            {

                mpfi_cal(coresize, id);
                id = atomicAddList(coresize, id);
            }
#ifndef CHANGE_LIST
            else if ((wait_h == NULL && checkCORE() == 0))
            //{
#else
            else if (data_count == 0 && checkCORE() == 0)
            {
#endif
                break;
            }
        }
       else
       {
        mpfi_cal(coresize, id);
        id = atomicAddList(coresize, id);
       }
}
idolThread();
}

// スケジューリングを行う関数

void cmpfi_cal()
{


    int i = 0;
    if (sub_thread == 0)
    {
#ifdef VER12
        init_storeData(thread_acc);
#endif
        createThread(coresize);
        sub_thread = 1;
    }
    else
    {
        emptyThread();
    }
    int id = -1;

    while (1)
    {
        if (id == -1)
        {

            id = atomicGetList(coresize);
            
            if (id != -1)
            {
                
                mpfi_cal(coresize, id);
                id = atomicAddList(coresize, id);
            }
#ifndef CHANGE_LIST
            else if ((wait_h == NULL && checkCORE() == 0))
            //{
#else
            else if (data_count == 0 && checkCORE() == 0)
            {
#endif
                break;
            }
    }
    else
    {
        // printf("%d\n",id);
        mpfi_cal(coresize, id);
        id = atomicAddList(coresize, id);
    }
}

cmpfi_cancel();
}

void cmpfi_cal2(int split)
{

    // printf("開始---%d回目---\nsub_thread=%d\n", split + 1, sub_thread); // sahara
    for(int k=0;k<count;k++){
			op2[k]=op[k];
		}
    int i = 0;

    if (sub_thread == 0)
    { //////このルートをすべての回数通る

#ifdef VER12
        init_storeData(thread_acc);

#endif
        createThread(coresize);
        sub_thread = 1;
    }
    else
    {
        emptyThread();
    }

    int id = -1;
    int as = node_list[0]; // sahara最終的には自動入力。計算が始まる（初めてのオペランド部分）を代入。

    //実験用
    //if (split == 0){
    while (1)
    {
        

        if (id == -1)
        {   
            id = atomicGetList(coresize);//getNodeList jamp
            printf("Getlist_id=%d\n",id);

            
            if (id != -1)
            {
                printf("1id=%d\n",id);
                mpfi_cal2(coresize, id);
                id = atomicAddList(coresize, id);
                printf("1後id=%d\n",id);
            }
        #ifndef CHANGE_LIST
            else if ((wait_h == NULL && checkCORE() == 0))
            // sahara {
        #else
            else if (data_count == 0 && checkCORE() == 0)
            {
        #endif
                break;
            }
        }
        else
        {
            mpfi_cal2(coresize, id);
            printf("2id=%d\n",id);
            id = atomicAddList(coresize, id);
            printf("後2id=%d\n",id);
        }
    }
    //}

/////////////////////////saharakaityaここからしたはゼロスレッドの想定
// idの数取得済み
    /*
    if (split != 0)
    {
        while (1)
        {
        mpfi_cal2(coresize2, as);
        as++;
        if (as == count)
            break;
        }
    }
    */
    
    //data_count=1;
    //sahara ハード　変える
    cmpfi_cancel2();

// sahara
}

int checkCORE()
{
    int i;
    for (i = 0; i < coresize; i++)
    {
        if (data_core[i].state != EMPTY)
        {
            return 1;
        }
    }
    return 0;
}

void initEdge(int id)
{
    head[id]->head = 0;
    head[id]->flag = -1;
    g[id]->head = 0; // idのエッジ数を0に
}

void pushEdge(int id, int to)
{
    if (g[id]->head < MAX_STACK)
    {
        if (g[id]->head == 0)
        {
            g[id]->data = (int *)malloc(MAX_STACK * sizeof(int));
        }
        g[id]->data[g[id]->head] = to; // idに対応するエッジを追加
        g[id]->head++;                 //エッジの数を増やす
    }
}

// リスト用
int deleteEdge(int threadID, int id)
{
    int i;
    int edge_id;
    int ret = -1;
    for (i = 0; i < g[id]->head; i++)
    {
        edge_id = g[id]->data[i];
        while (!__sync_bool_compare_and_swap(&head[edge_id]->flag, -1, threadID))
        {
            _mm_pause();
        } //第一引数のポインタ先が第二と等価なら第三引数を代入
        if (head[edge_id]->head > 0)
        {
            head[edge_id]->head = (head[edge_id]->head) - 1;
        }

        if (head[edge_id]->head == 0)
        {
#ifdef GET_ID
            if (ret == -1)
            {
                ret = edge_id;
            }
            else
            {
#ifndef CHANGE_LIST
                addlist(threadID, edge_id);
#else
                addNodeList(threadID, edge_id);
#endif
            }
#else
#ifndef CHANGE_LIST
            addlist(threadID, edge_id);
#else
            addNodeList(threadID, edge_id);
#endif
#endif
            head[edge_id]->head = -1;
        }
        while (!__sync_bool_compare_and_swap(&head[edge_id]->flag, threadID, -1)); //第一引数のポインタ先が第二と等価なら第三引数を代入
    }
    return ret;
}

// // リングバッファ用
// int deleteEdgeForWorker(int threadID,int id){
//     int i;
//     int edge_id;
//     int ret = -1;
//     for(i=0;i<(g[id]->head);i++){
//         edge_id = g[id]->data[i];
//         while(!__sync_bool_compare_and_swap(&head[edge_id]->flag, -1, threadID)){
//             _mm_pause();
//         }  //第一引数のポインタ先が第二と等価なら第三引数を代入
//         if(head[edge_id]->head>0){
//             // printf("%d -> ",head[edge_id]->head);
//             head[edge_id]->head=head[edge_id]->head-1;
//             // printf("%d\n",head[edge_id]->head);
//         }

//         if(head[edge_id]->head==0){
//             #ifdef GET_ID
//             if(ret==-1){
//                 ret = edge_id;
//             }else{
//                 addNodeList(threadID,edge_id);
//             }
//             #else
//             addNodeList(threadID,edge_id);
//             #endif
//             head[edge_id]->head=-1;
//         }
//         while(!__sync_bool_compare_and_swap(&head[edge_id]->flag, threadID, -1));  //第一引数のポインタ先が第二と等価なら第三引数を代入
//     }
//     return ret;
// }
