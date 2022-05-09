#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//给定两个一元多项式，实现两个一元多项式的相加算法

//多项式结构
typedef struct Node* Polynomial;
struct Node{
    int coef; // 系数
    int expon; // ָ指数
    Polynomial next; //指针域
};

//插入多项式尾部
void Attach(int c,int e,Polynomial* PRear){
    Polynomial P=(Polynomial)malloc(sizeof(struct Node));
    P->coef=c;
    P->expon=e;
    P->next=NULL;
    (*PRear)->next=P;
    (*PRear)=P;
}

//简单排序
void sort(int* c,int* e,int N){
    int t1,t2;
    for(int i=0;i<N-1;i++){
        for(int j=0;j<N-i;j++){
            if(e[j]<e[j+1]){
                t1=c[j];
                t2=e[j];
                c[j]=c[j+1];
                e[j]=e[j+1];
                c[j+1]=t1;
                e[j+1]=t2;
            }
        }
    }
}

//读入多项式
Polynomial ReadPoly(){
    Polynomial Phead,PRear,temp;
    Phead=(Polynomial)malloc(sizeof(struct Node));
    Phead->next=NULL;
    PRear=Phead;
    int N;
    printf("Input number of terms: \n");
    scanf("%d",&N);
    printf("Input coef and expon of every term: \n");
    int* c=(int*)malloc(sizeof(int)*N);
    int* e=(int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++)
        scanf("%d %d",&c[i],&e[i]); // 分别输入每项的系数和指数      
    sort(c,e,N);
    for(int i=0;i<N;i++)
        Attach(c[i],e[i],&PRear); 

    temp=Phead;
    Phead=Phead->next;
    free(temp);
    return Phead;
}

//两个多项式相加返回新的多项式
Polynomial Add(Polynomial P1,Polynomial P2){
    int sum;
    Polynomial Phead,PRear,temp,T1,T2;
    Phead=(Polynomial)malloc(sizeof(struct Node));
    Phead->next=NULL;
    PRear=Phead;
    T1=P1;T2=P2;
    while(T1&&T2){
        if(T1->expon==T2->expon){
            sum=T1->coef+T2->coef;
            if(sum) Attach(sum,T1->expon,&PRear);
            T1=T1->next;
            T2=T2->next;
        }
        else if(T1->expon>T2->expon){
            Attach(T1->coef,T1->expon,&PRear);
            T1=T1->next;
        } 
        else{
            Attach(T2->coef,T2->expon,&PRear);
            T2=T2->next;
        }
    }
    while(T1){ 
        Attach(T1->coef,T1->expon,&PRear);
        T1=T1->next;
    }
    while(T2){ 
        Attach(T2->coef,T2->expon,&PRear);
        T2=T2->next;
    }
    temp=Phead;
    Phead=Phead->next;
    free(temp);
    return Phead;
}

//打印多项式
void PrintPoly(Polynomial P){
    int count=0;
    if(!P){
        printf("0 0\n");
        return;
    }
    while(P){
        if(count)
            printf("+");
        printf("%d*X^%d",P->coef,P->expon);
        count++;
        P=P->next;
    }   
    printf("\n");
}

int main(){
    Polynomial P1,P2,PA;
    printf("Input First Polynomial: \n");
    P1=ReadPoly();
    printf("Input Second Polynomial: \n");
    P2=ReadPoly();
    PA=Add(P1,P2);
    printf("First Polynomial: \n");
    PrintPoly(P1);
    printf("Seconde Polynomial: \n");
    PrintPoly(P2);
    printf("Add Result: \n");
    PrintPoly(PA);
    getch();
    return 0;
}