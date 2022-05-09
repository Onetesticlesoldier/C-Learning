#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//用栈走迷宫

//坐标结构体
typedef struct{
    int x,y,d;
}Point;

//栈结构体
typedef struct SeqStack* Stack;
struct SeqStack{
    int MAXNUM;
    int top;
    Point* s;
};

//创建空栈
Stack create(int m){
    Stack S=(Stack)malloc(sizeof(struct SeqStack));
    if(S!=NULL){
        S->s=(Point*)malloc(sizeof(Point)*m);
        if(S->s!=NULL){
            S->MAXNUM=m;
            S->top=-1;
            return S;
        }
    }
    printf("Out of space!\n");
    return NULL;
}

//判断栈是否为空
int isEmpty(Stack S){
    return S->top==-1;
}

//入栈
void push(Stack S,Point p){
    if(S->top>=S->MAXNUM-1)
        printf("Overflow!\n");
    else
        S->s[++S->top]=p;
}

//出栈
void pop(Stack S){
    if(S->top==-1)
        printf("Underflow!\n");
    else
        S->top--;
}

//取栈顶元素
Point top(Stack S){
    if(S->top==-1)
        printf("Empty!\n");
    else
        return S->s[S->top];
}

//迷宫maze[M][N]中求从入口maze[x1][y1]到出口[x2][y2]的一条路径
//其中1<=x1,x2<=M-2,1<=y1,y2<=N-2
void mazePath(int** maze,int direction[][2],int x1,int y1,int x2,int y2,int M,int N){
    int i,j,k,g,h;
    Point p;
    Stack S1=create(M*N);
    Stack S2=create(M*N);
    maze[x1][y1]=2;
    p.x=x1;
    p.y=y1;
    p.d=-1;
    push(S1,p);
    while(!isEmpty(S1)){
        p=top(S1);
        pop(S1);
        i=p.x;
        j=p.y;
        k=p.d+1;
        while(k<=3){
            g=i+direction[k][0];
            h=j+direction[k][1];
            if(g==x2&&h==y2&&maze[g][h]==0){ //走到出口
                printf("The path is:\n");
                while(!isEmpty(S1)){
                    p=top(S1);
                    push(S2,p);
                    pop(S1);
                }
                while(!isEmpty(S2)){
                    p=top(S2);
                    pop(S2);
                    printf("(%d,%d)->",p.x,p.y);
                }
                printf("(%d,%d)->",i,j);
                printf("(%d,%d)\n",g,h);
                free(S1);
                free(S2);
                return;
            }
            if(maze[g][h]==0){
                maze[g][h]=2;
                p.x=i;
                p.y=j;
                p.d=k;
                push(S1,p);
                i=g;
                j=h;
                k=-1;
            }
            k++;
        }
    }
    free(S1);
    free(S2);
    printf("The path has not been found.\n");
}

//打印迷宫
void print_maze(int** maze,int M,int N){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            printf("%d\t",maze[i][j]);
        }
        printf("\n");
    }
}

int main(){ //maze[i][j]= 0:通道 1:墙 2:已走过
    int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; // direction[1]:向右 d[2]:向下 d[3]:向左 d[4]:向上
    int maze[8][11]={{1,1,1,1,1,1,1,1,1,1,1},{1,0,1,0,0,1,1,1,0,0,1},{1,0,0,0,0,0,1,0,0,1,1},{1,0,1,1,1,0,0,0,1,1,1},{1,0,0,0,1,0,1,1,0,1,1},{1,1,0,0,1,0,1,1,0,0,1},{1,1,1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1,1}};
    int M=8,N=11;
    int x1=1,y1=1,x2=6,y2=9;
    int** p=(int**)malloc(sizeof(int*)*M);
    for(int i=0;i<M;i++)
        p[i]=maze[i];
    printf("The maze is:\n");
    print_maze(p,M,N); //直接传maze会出错
    mazePath(p,direction,x1,y1,x2,y2,M,N);
    getch();
    return 0;
}