#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

// ���������ַ����е�������Ӵ�(�����ַ���������ַ�������ʵ��˳�������ַ���)

#define MAXSIZE 100

//kmpƥ��(�ж�s2�ǲ���s1���Ӵ�)
int KMP_Match(char* s1,char* s2,int s1_len,int s2_len,int *next){  
    int i=0,j=0;
    while(i<s2_len&&j<s1_len){
        if(i==-1||s2[i]==s1[j]){
            i++;
            j++;
        }
        else
            i=next[i];
    }
    if(i==s2_len)
        return 1; // ƥ��ɹ�����1
    else
        return 0; // ʧ�ܷ���0
}

//���ַ���s��next����
void make_next(char* s,int s_len,int* next){
    int i=0,k=-1;
    next[0]=-1;
    while(i<s_len-1){
        if(k==-1||s[i]==s[k]){
            i++;k++;
            if(s[i]!=s[k])
                next[i]=k;
            else
                next[i]=next[k];
        }
        else
            k=next[k];
    }
}

//DFS���ˣ�Ӧ��BFS
//��s1Ϊĸ����s2�±�i-j���ַ���Ϊ�Ӵ�����ƥ��
int solve(char* s1,int s1_len,char* s2,int i,int j){
    if(i>j) return 0;
    char s[MAXSIZE];
    int s_len=0;
    for(int k=i;k<=j;k++)
        s[s_len++]=s2[k];
    int* next=(int*)malloc(sizeof(int)*(j-i+1));
    make_next(s,s_len,next);
    if(KMP_Match(s1,s,s1_len,s_len,next)){
        printf("The longest common substring of s1 and s2 is: %s\n ",s);
        return 1;
    }
    else    
        return solve(s1,s1_len,s2,i,j-1)||solve(s1,s1_len,s2,i+1,j); 
}

int main(){
    char s1[MAXSIZE];
    char s2[MAXSIZE];
    int s1_len,s2_len;
    printf("Input First String: \n");
    gets(s1);
    printf("Input Seconde String: \n");
    gets(s2);
    s1_len=strlen(s1);
    s2_len=strlen(s2);
    if(s1_len>s2_len){
        if(!solve(s1,s1_len,s2,0,s2_len-1))
            printf("The longest common substring of s1 and s2 doesn't exist!\n");
    }
    else{
        if(!solve(s2,s2_len,s1,0,s1_len-1))
            printf("The longest common substring of s1 and s2 doesn't exist!\n");
    }
    getch();
    return 0;
}