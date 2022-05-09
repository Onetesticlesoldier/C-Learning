#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//二叉搜索树并线索化

#define MaxSize 50

//二叉树结构体
typedef struct TreeNode* PTreeNode;
struct TreeNode{
    int info,ltag,rtag;
    PTreeNode left;
    PTreeNode right;
};

//栈结构体
typedef struct SeqStack* Stack;
struct SeqStack{
    int MAXNUM;
    int top;
    PTreeNode* s;
};

//创建空栈
Stack create(int m){
    Stack S=(Stack)malloc(sizeof(struct SeqStack));
    if(S!=NULL){
        S->s=(PTreeNode*)malloc(sizeof(struct TreeNode)*m);
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
void push(Stack S,PTreeNode T){
    if(S->top>=S->MAXNUM-1)
        printf("Overflow!\n");
    else
        S->s[++S->top]=T;
}

//出栈
void pop(Stack S){
    if(S->top==-1)
        printf("Underflow!\n");
    else
        S->top--;
}

//取栈顶元素
PTreeNode top(Stack S){
    if(S->top==-1)
        printf("Empty!\n");
    else
        return S->s[S->top];
}
//创建二叉树
PTreeNode Insert(PTreeNode root,int x){
    if(root==NULL){
        root=(PTreeNode)malloc(sizeof(struct TreeNode));
        root->info=x;
        root->ltag=root->rtag=0;
        root->left=root->right=NULL;
    }
    else{
        if(x<root->info)
            root->left=Insert(root->left,x);
        else if(x>root->info)
            root->right=Insert(root->right,x);
    }
    return root;
}

//中序线索化二叉树
void Thread(PTreeNode root){
    PTreeNode P,PR;
    Stack S=create(MaxSize);
    if(root==NULL) return;
    P=root;PR=NULL;
    do{
        while(P!=NULL){
            push(S,P);
            P=P->left;
        }
        P=top(S);
        pop(S);
        if(PR!=NULL){
            if(PR->right==NULL){
                PR->right=P;
                PR->rtag=1;
            }
            if(P->left==NULL){
                P->left=PR;
                P->ltag=1;
            }
        }
        PR=P;P=P->right;
    }while(!isEmpty(S)||P!=NULL);
}

//中序遍历
void InOrderTraverse(PTreeNode root){
    PTreeNode P=root;
    if(P==NULL) return;
    while(P->left!=NULL&&P->ltag==0) P=P->left;
    while(P!=NULL){
        printf("%4d\t",P->info);
        if(P->right!=NULL&&P->rtag==0){
            P=P->right;
            while(P->left!=NULL&&P->ltag==0) P=P->left;
        }
        else
            P=P->right;
    }
}

int main(){
    PTreeNode root=NULL;
    int N,x;
    printf("Input TreeNode Number:");
    scanf("%d",&N);
    printf("Input N numbers:");
    while(N--){
        scanf("%d",&x);
        root=Insert(root,x);
    }
    Thread(root);
    printf("InOrderTravel: ");
    InOrderTraverse(root);
    getch();
    return 0;
}