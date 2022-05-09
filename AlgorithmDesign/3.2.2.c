#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//用队列走迷宫

#define MaxSize 100

//坐标结构体
typedef struct{
    int x,y;
}point;

//队列元素结构体
typedef struct Node{
    point cur;
    int step;
    point post[MaxSize];
}node;

//队列结构体
typedef struct SeqQueue* Queue;
struct SeqQueue{
    int front,rear;
    node* q;
};

//创建空队列
Queue CreateEmptyQueue(int m){
    Queue Q=(Queue)malloc(sizeof(struct SeqQueue));
    Q->q=(node*)malloc(sizeof(node)*m);
    Q->front=Q->rear=0;
    return Q;
}

//判断队列是否为空
int IsEmptyQueue(Queue Q){
    return Q->front==Q->rear;
}

//入队
void Push(Queue Q,node x){
    Q->q[Q->rear++]=x;
}

//出队
void Pop(Queue Q){
    Q->front++;
}

//取队列头部元素
node Top(Queue Q){
    return Q->q[Q->front];
}

//迷宫maze[M][N]中求从入口maze[x1][y1]到出口[x2][y2]的一条路径
//其中1<=x1,x2<=M-2,1<=y1,y2<=N-2
void mazePath(int** maze,int direction[][2],int x1,int y1,int x2,int y2,int M,int N){
    node n0,n1,n2;
    Queue Q=CreateEmptyQueue(M*N);
    maze[x1][y1]=2;
    n0.cur.x=x1;
    n0.cur.y=y1;
    n0.step=0; //初始化
    n0.post[n0.step].x=x1;
    n0.post[n0.step].y=y1;
    Push(Q,n0);
    while(!IsEmptyQueue(Q)){
        n1=Top(Q);
        Pop(Q);
        n2=n1; //这步一定要有
        if(n2.cur.x==x2&&n2.cur.y==y2){
            printf("The path is:\n");
            for(int j=0;j<=n1.step;j++){
                if(j)
                    printf("->");
                printf("(%d,%d)",n1.post[j].x,n1.post[j].y);
            }
            printf("\n");
            free(Q->q);
            free(Q);
            return;            
            }
        for(int i=0;i<4;i++){
            n2.cur.x=n1.cur.x+direction[i][0];
            n2.cur.y=n1.cur.y+direction[i][1];
            if(maze[n2.cur.x][n2.cur.y]==0){
                maze[n2.cur.x][n2.cur.y]=2;
                n2.step=n1.step+1;
                n2.post[n2.step].x=n2.cur.x;
                n2.post[n2.step].y=n2.cur.y;
                Push(Q,n2);
            }
        }
    }
    free(Q->q);
    free(Q);
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