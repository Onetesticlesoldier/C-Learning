#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>

//创建学生成绩表，实现插入、删除和统计等管理功能

#define MAXSIZE 100 //最大学生个数100
#define MAX 100 //成绩最高分100
#define MIN 0 //最低分0

const int Math=0,English=1,CProgram=2;

//学生结构体
struct Student{
    char name[20]; // 姓名
    double mark[3]; // mark[0]:Math mark[1]:English mark[2]:CProgram
};
typedef struct Student* PStudent;

//顺序表结构体
struct SeqList{
    int MAXNUM; // 表中最大学生个数
    int n; // 表中已有学生个数
    PStudent Stu; // Student类型指针
};
typedef struct SeqList* List;

//创建
List CreateEmptyList(int m){ // m:学生最大个数
    List L=(List)malloc(sizeof(struct SeqList));
    if(L!=NULL){
        L->Stu=(PStudent)malloc(sizeof(struct Student)*m);
        if(L->Stu!=NULL){
            L->MAXNUM=m;
            L->n=0;
            return L;
        }
    }
    printf("Out of space!\n");
    return NULL;
}

//插入(在下标为p的学生之前插入学生s)
void insertPre_indexp(List L,int p,struct Student s){
    if(L->n>=L->MAXNUM){ //学生表已满
        printf("There is no enough space!\n");
        return;
    }
    if(p<0||p>L->n){ //不存在这样的下标
        printf("index doesn't exist!\n");
        return;
    }
    for(int q=L->n-1;q>=p;q--)
        L->Stu[q+1]=L->Stu[q];
    L->Stu[p]=s;
    L->n++;
    printf("Insert successfully!\n");
}

//插入(在下标为p的学生之后插入学生s)
void insertPost_indexp(List L,int p,struct Student s){
    insertPre_indexp(L,p+1,s); // 相当于在下标为p+1的学生之前插入学生s
}

//获取姓名为c的学生在表中的下标
int find_namec_index(List L,char* c){
    for(int p=0;p<L->n;p++){
        if(strcmp(L->Stu[p].name,c)==0)
            return p;
    }
    return -1; //没找到返回-1
}

//插入(在姓名为c的学生之前插入学生s)
void insertPre_namec(List L,char* c,struct Student s){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name dosen't exist!\n");
    else
        insertPre_indexp(L,p,s);
}

//插入(在姓名为c的学生之后插入学生s)
void insertPost_namec(List L,char* c,struct Student s){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name dosen't exist!\n");
    else
        insertPost_indexp(L,p,s);
}

//删除(删除下标为p的学生)
void delete_indexp(List L,int p){
    if(p<0||p>L->n){
        printf("p doesn't exist!\n"); //不存在这样的下标
        return;
    }
    for(int q=p;q<L->n-1;q++)
        L->Stu[q]=L->Stu[q+1];
    L->n--;
    printf("Delete successfully!\n"); 
}

//删除(删除姓名为c的学生)
void delete_namec(List L,char* c){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name doesn't exist!\n");
    else
        delete_indexp(L,p);
}

//统计(统计各门学科的最高分，最低分，均分)
void count(List L){
    if(L->n==0){
        printf("There is no student to be counted!\n");
        return;
    }
    double Math_Max=MIN,Math_Min=MAX,Math_Sum=0; // 数学最高分，最低分，总分
    double English_Max=MIN,English_Min=MAX,English_Sum=0; // 英语最高分，最低分，总分
    double CProgram_Max=MIN,CProgram_Min=MAX,CProgram_Sum=0; // C语言最高分，最低分，总分
    for(int p=0;p<L->n;p++){
        Math_Max=fmax(Math_Max,L->Stu[p].mark[Math]);
        Math_Min=fmin(Math_Min,L->Stu[p].mark[Math]);
        Math_Sum+=L->Stu[p].mark[Math];
        English_Max=fmax(English_Max,L->Stu[p].mark[English]);
        English_Min=fmin(English_Min,L->Stu[p].mark[English]);
        English_Sum+=L->Stu[p].mark[English];
        CProgram_Max=fmax(CProgram_Max,L->Stu[p].mark[CProgram]);
        CProgram_Min=fmin(CProgram_Min,L->Stu[p].mark[CProgram]);
        CProgram_Sum+=L->Stu[p].mark[CProgram];
    }
    printf("Statistics as follows: \n");
    printf("Student Number: %d\n",L->n);
    printf("Math: The Highest = %.2lf\tThe Lowest = %.2lf\tThe average = %.2lf\n",Math_Max,Math_Min,Math_Sum/L->n);
    printf("English: The Highest = %.2lf\tThe Lowest = %.2lf\tThe average = %.2lf\n",English_Max,English_Min,English_Sum/L->n);
    printf("CProgram: The Highest = %.2lf\tThe Lowest = %.2lf\tThe average = %.2lf\n",CProgram_Max,CProgram_Min,CProgram_Sum/L->n);
}

//在表末尾添加学生
void append(List L,struct Student s){
    insertPre_indexp(L,L->n,s);
}

//创建一个学生
struct Student stu(char* name,double* mark){
    struct Student s;
    strcpy(s.name,name);
    s.mark[Math]=mark[Math];
    s.mark[English]=mark[English];
    s.mark[CProgram]=mark[CProgram];
    return s;
} 

//打印学生表中已有学生的信息
void disply(List L){
    if(L->n==0){
        printf("There is no student to be displyed!\n");
        return;
    }
    printf(" \tName\t\tMath\t\tEnglish\t\tCPrograme\n");
    for(int i=0;i<L->n;i++){
        printf("%d:\t%s\t%6.2lf\t\t%6.2lf\t\t%6.2lf\n",i+1,L->Stu[i].name,L->Stu[i].mark[Math],L->Stu[i].mark[English],L->Stu[i].mark[CProgram]);
    }
}

//菜单
void menu(){
    char flag[10]="yes";
    int choice_1,choice_2;
    List L=CreateEmptyList(MAXSIZE);
    struct Student s1;     // 先放进去一个学生
    strcpy(s1.name,"张三");
    s1.mark[Math]=80;
    s1.mark[English]=70;
    s1.mark[CProgram]=60;
    append(L,s1);
    while(strcmp(flag,"yes")==0){
        printf("**********Menu**********\n");
        printf("1.Insert\n");
        printf("2.Delete\n");
        printf("3.Count\n");
        printf("4.Append\n");
        printf("5.Disply\n");
        printf("0.Exit\n");
        printf("Input a number as your choice:");
        scanf("%d",&choice_1);
        getchar();
        printf("\n");
        if(choice_1==1){
            printf("1.Insert student s before index p\n");
            printf("2.Insert student s after index p\n");
            printf("3.Insert student s before student named C\n");
            printf("4.Insert student s after student named C\n");
            printf("Input a number as your choice:");
            scanf("%d",&choice_2);
            getchar();
            char name[20];
            double mark[3];
            printf("Input student s name:");
            gets(name);
            printf("Input student s Math English CProgram marks:");
            scanf("%lf %lf %lf",&mark[Math],&mark[English],&mark[CProgram]);
            getchar();
            struct Student s=stu(name,mark);
            if(choice_2==1||choice_2==2){
                int p;
                printf("Input index p:");
                scanf("%d",&p);
                getchar();
                if(choice_2==1)
                    insertPre_indexp(L,p,s);
                else
                    insertPost_indexp(L,p,s);
            }
            else if(choice_2==3||choice_2==4){
                char c[20];
                printf("Input name c:");
                gets(c);
                if(choice_2==3)
                        insertPre_namec(L,c,s);
                else
                    insertPost_namec(L,c,s);
            }
        }
        else if(choice_1==2){
            printf("1.Delete student by index\n");
            printf("2.Delete student by name c\n");
            printf("Input a number as your choice:");
            scanf("%d",&choice_2);
            getchar();
            if(choice_2==1){
                int p;
                printf("Input index p:");
                scanf("%d",&p);
                getchar();
                delete_indexp(L,p);
            }
            else if(choice_2==2){
                char c[20];
                printf("Input name c:");
                gets(c);
                delete_namec(L,c);
            }
        }
        else if(choice_1==3){
            count(L);
        }
        else if(choice_1==4){
            char name[20]={0};
            double mark[3];
            printf("Input student s name:");
            gets(name);
            printf("Input student s Math English CProgram marks:");
            scanf("%lf %lf %lf",&mark[Math],&mark[English],&mark[CProgram]);
            getchar();
            struct Student s=stu(name,mark);
            append(L,s);
        }
        else if(choice_1==5){
            disply(L);
        }
        else if(choice_1==0){
            break;
        }
        printf("\nCome back to menu?(input yes or no):");
        gets(flag);
        printf("\n");
}
    printf("Menu exits.\n");
}

int main(){
    menu();
    getch();
    return 0;
}