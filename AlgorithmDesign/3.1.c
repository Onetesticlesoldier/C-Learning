#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//用栈判断表达式中的圆括号是否匹配

#define MaxSize 50

//栈结构体
typedef struct SeqStack* Stack;
struct SeqStack{
    int MAXNUM;
    int top;
    char* s;
};

//创建空栈
Stack CreateEmptyStack(int m){
    Stack S=(Stack)malloc(sizeof(struct SeqStack));
    S->s=(char*)malloc(sizeof(char)*m);
    S->MAXNUM=m;
    S->top=-1;
    return S;
}

//判断栈为空
int IsEmptyStack(Stack S){
    return S->top==-1;
}

//入栈
void Push(Stack S,char c){
    S->s[++S->top]=c;
}

//出栈
void Pop(Stack S){
    S->top--;
}

//栈顶元素
char Top(Stack S){
    return S->s[S->top];
}

//判断是否匹配
int IsValid(char* exp){
    Stack S=CreateEmptyStack(MaxSize);
    int len=strlen(exp);
    for(int i=0;i<len;i++){
        if(exp[i]==')'){
            while(!IsEmptyStack(S)&&Top(S)!='(') 
                Pop(S);
            if(IsEmptyStack(S)) //没有找到对应的'(',匹配失败
                return 0; 
            else //找到对应的'(',把'('弹出
                Pop(S); 
        }
        else
            Push(S,exp[i]);
    }
    while(!IsEmptyStack(S)&&Top(S)!='(') //把剩余所有元素出栈,判断有没有多余的'('
        Pop(S);
    if(IsEmptyStack(S)){ //没有多余的'(',匹配成功
        free(S);
        return 1;
    } 
    else{ //有多余的'('，匹配失败
        free(S);
        return 0;
    }
}

int main(){
    char exp[MaxSize]={0};
    printf("Please Input Expression:");
    gets(exp);
    if(IsValid(exp))
        printf("Yes\n");
    else
        printf("No\n");
    getch();
    return 0;
}