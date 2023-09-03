#include <stdio.h>
#define NMAX 64
#define N 2

void SCAN(double A[N][N], char s[NMAX]){
    FILE *fp;
    
    if((fp = fopen(s,"r"))==NULL)
        printf("ファイルを開けません\n");
    else{
        for(int i=0; i<N; i++){
            double a[N];
            for(int j=0; j<N; j++){
                fscanf(fp,"%lf",&a[j]);
                A[i][j] = a[j];
            }
        }
        fclose(fp);
    }
}

void SHOW_NxN(double A[N][N]){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%f ",A[i][j]);
        }
        printf("\n");
    }
}

void set_L(double L[N][N]){
    for(int i=0; i<N; i++)
        L[i][i] = 1;
}

void u_1k(double U[N][N], double A[N][N]){
    for(int k=0; k<N; k++)
        U[0][k] = A[0][k];
}

void l_j1(double L[N][N], double A[N][N], double U[N][N]){
    for(int j=1; j<N; j++)
        L[j][0] = A[j][0]/U[0][0];
}

void u_jk(double U[N][N], double L[N][N], double A[N][N], int j){
    for(int k=j; k<N; k++){
        double t=0;
        for(int s=0; s<=j-1; s++)
            t += L[j][s]*U[s][k];
        
        U[j][k] = A[j][k] - t;
    }
}

void l_jk(double U[N][N], double L[N][N], double A[N][N], int k){
    for(int j=k+1; j<N; j++){
        double t=0;
        for(int s=0; s<=k-1; s++)
            t += L[j][s]*U[s][k];
        
        L[j][k] = (A[j][k] - t)/U[k][k];
    }
}


int main(int argc, const char * argv[]) {
    char name[NMAX];
    double A[N][N] = {0};
    
    printf("使用するファイルを入力してください:");
    scanf("%s",name);
    
    SCAN(A,"test_lu.txt");
    
    double L[N][N] = {0};
    double U[N][N] = {0};
    set_L(L);
    
    u_1k(U, A);
    
    l_j1(L, A, U);
    
    for(int q=1; q<N; q++){
        
        u_jk(U, L, A, q);
        if(q == N-1){
            break;
        }else{
            l_jk(U, L, A, q);
        }
    }
    
    printf("A\n");
    SHOW_NxN(A);
    printf("L\n");
    SHOW_NxN(L);
    printf("U\n");
    SHOW_NxN(U);

    return 0;
}