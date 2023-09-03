#include "gmpfi.h"
#include <time.h>
extern volatile int thread_flag[CORE_SIZE];//ワーカの生死

int sub_thread = 0;//ワーカを作るか否かのフラグ
int count = 0;//ノードの通し番号設定の際に使う
int isWrite = 0;// dfgに使うデータ？のmaloc
int *log_node = NULL;
int id = -1;//ノードの通し番号が後々代入される
int data_count_copy=0;//queueに最初に入っている数のコピー
int coresize =CORE_SIZE;//core_jump //ワーカ数
int size = 3;
//#ifdef div //分割実行使ってるか否か
extern int Nlog;//分割数//sahara
//#endif
head_t *head = NULL;//各ノード番号の上付きのエッジ数
head_t *head2 = NULL;//保存用sahara
int *op = NULL;//各ノードの数字か演算子かが入っている配列
int *op2 =NULL;//保存用 動的確保
extern int *node_list2;//保存用 //実質キュー？を保存するもの
extern int entrypoint;
extern int endpoint; 
int entrypoint_copy=0;
int endpoint_copy=0;
//int g2[10000];//保存用
edge_t *g = NULL;
edge_t *g2 = NULL;//保存用
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
    op2 = (int *)malloc(MAX_STACK * sizeof(int));
    if (op2 == NULL)
    {
        printf("op2 malloc error\n");
    }
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
    g2 = (edge_t *)malloc(MAX_STACK * sizeof(edge_t));
    if (g2 == NULL)
    {
        printf("g malloc error\n");
    }
    initList();
#ifdef VER12
    initTmp();
#endif
    return 0;
}

int cmpfi_malloc2()
{
    
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
    free(g2);
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
    cancelThread_end();
    cmpfi_free();
    sub_thread = 0;
    isWrite = 0;
    return 1;
}

int cmpfi_end()
{
    cancelThread_end();//fight
    cmpfi_free();
    sub_thread = 0;
    isWrite = 0;
    return 1;
}

int cmpfi_cancel2()
{
    cancelThread_for_worker(); // sahara
    // cmpfi_free2();
    //sub_thread = 0;
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
    //printf("queueの最初の個数=%d,entrypoint=%d,end=%d\n",data_count,entrypoint,endpoint);

    ////再利用のためのコード開始
    int i = 0;
    int id = -1;//node番号定義
    int k=0;//初期化用反復変数
    
    if(split==0){
       for(k=0;k<count;k++){
        
		    op2[k]=op[k];
            g2[k]->head=g[k]->head;
            node_list2[k]=node_list[k];
            //printf("g2[%d]=%d\n",k,g2[k]->head);
	    }
        data_count_copy=data_count;//キューの最初の個数保存
    }
    
   
   
    /*for(k=0;k<CORE_SIZE;k++){
        if(k<CORE_SIZE)thread_flag[k]=1;
    }*///jumps   
            ////初期化のためのコード終了

    //int as = node_list[0];
    
    
    //////////////////////////

    
    
    //printf("sub_th=%d\n",sub_thread);
    if (sub_thread == 0)
    {
        //printf("split=%d\n",split);

#ifdef VER12
        init_storeData(thread_acc);//jump4
#endif
       
        createThread(coresize);
        //printf("thread生成しました\n");
        sub_thread = 1;
    }else{
        emptyThread();
    }
   // if(checkCORE()==1){printf("まだ働いてる\nミス");exit(1);}
     //無理やりIDを先に取得
     /*
    while(id==-1||id==0){
        id = atomicGetList(coresize);
        printf("id=%d\n",id);
        i++;
           if(i>20){
              printf("id取得失敗\n");
              exit(1);
            }
    }
    printf("無理やりmain_threadがnodeID=%dを取得\n",id);
    */
   for(i = 0; i < coresize; i++){
        thread_flag[i] = 1;
    }
    while (1){
       // printf("最初=%d",checkCORE());
        if (id == -1){   
            id = atomicGetList(coresize);//getNodeList jump
            //printf("Getlist_id=%d\n",id);
            if (id != -1){
                //printf("1id=%d\n",id);
                mpfi_cal2(coresize, id);
                //printf("1後");
                id = atomicAddList(coresize, id);
            }
        #ifndef CHANGE_LIST
            else if ((wait_h == NULL && checkCORE() == 0))
            // sahara {
        #else//これに加えて、count MAXまでやったかの判定
            else if (data_count == 0 && checkCORE() == 0 )//&& atomicGetList(coresize)==-1)
            {
        #endif
                //printf("break前check==%d\n",checkCORE());     
                break;
            }
        }
        else
        {
            mpfi_cal2(coresize, id);
            //printf("2id=%d\n",id);
            id = atomicAddList(coresize, id);
            
            //printf("後2id=%d\n",id);
        }
    }
    //while(thread_flag[0]==1){printf("他スレッド稼働中");}

    /*
    int jyouken=0;
    while(jyouken==0){
        jyouken=cmpfi_cancel2();
    }*/
    
    cmpfi_cancel2();
    
    //struct timespec req={0,1};
    while(checkCORE2()!=0){
       //nanosleep(&req,NULL);
       //printf("a");
    }///jump_flag//usleep();
    if(split==Nlog-1){
        //printf("aaaa");
        //cmpfi_end();
    }
    //printf("thread_killed\n");
    
    //entrypoint=entrypoint_copy;
    //endpoint = endpoint_copy;
    //sahara ハード　変える
if(split<(Nlog-1)){
    for(k=0;k<count;k++){
			op[k]=op2[k];
			head[k]->head=head2[k]->head;
			head[k]->flag = -1;
            g[k]->head=g2[k]->head;//g[]保存
            node_list[k]=node_list2[k];
		} 
        data_count=data_count_copy;//要素は絶対ある//絶対変えるdata_count
    }
    //printf("saaa");
 
    
    /*if(data_count==0){
        printf("おかしい");
        exit(0);}*/

    
    

    //printf("check_c=%d\n",checkCORE());
    //printf("終了時id=%d\n",id);
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
//全ワーカがpthread_exit();呼ばれていたら０。いきているワーカがいたら1を返す
volatile int check_worker; 
int checkCORE2()
{
    
    for ( check_worker= 0; check_worker < coresize; check_worker++)
    {
        if (thread_flag[check_worker] != 0)
        {
            //printf("alive_thread[%d].state=%d\n",i,thread_flag[i]);
            return 1;
        }
    }
    //printf("全スレッド死亡\n");
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
    //printf("delete_Edge,threadID=%d,id=%d\n",threadID,id);
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
