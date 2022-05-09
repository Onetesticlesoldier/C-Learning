#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>

//����ѧ���ɼ���ʵ�ֲ��롢ɾ����ͳ�Ƶȹ�����

#define MAXSIZE 100 //���ѧ������100
#define MAX 100 //�ɼ���߷�100
#define MIN 0 //��ͷ�0

const int Math=0,English=1,CProgram=2;

//ѧ���ṹ��
struct Student{
    char name[20]; // ����
    double mark[3]; // mark[0]:Math mark[1]:English mark[2]:CProgram
};
typedef struct Student* PStudent;

//˳���ṹ��
struct SeqList{
    int MAXNUM; // �������ѧ������
    int n; // ��������ѧ������
    PStudent Stu; // Student����ָ��
};
typedef struct SeqList* List;

//����
List CreateEmptyList(int m){ // m:ѧ��������
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

//����(���±�Ϊp��ѧ��֮ǰ����ѧ��s)
void insertPre_indexp(List L,int p,struct Student s){
    if(L->n>=L->MAXNUM){ //ѧ��������
        printf("There is no enough space!\n");
        return;
    }
    if(p<0||p>L->n){ //�������������±�
        printf("index doesn't exist!\n");
        return;
    }
    for(int q=L->n-1;q>=p;q--)
        L->Stu[q+1]=L->Stu[q];
    L->Stu[p]=s;
    L->n++;
    printf("Insert successfully!\n");
}

//����(���±�Ϊp��ѧ��֮�����ѧ��s)
void insertPost_indexp(List L,int p,struct Student s){
    insertPre_indexp(L,p+1,s); // �൱�����±�Ϊp+1��ѧ��֮ǰ����ѧ��s
}

//��ȡ����Ϊc��ѧ���ڱ��е��±�
int find_namec_index(List L,char* c){
    for(int p=0;p<L->n;p++){
        if(strcmp(L->Stu[p].name,c)==0)
            return p;
    }
    return -1; //û�ҵ�����-1
}

//����(������Ϊc��ѧ��֮ǰ����ѧ��s)
void insertPre_namec(List L,char* c,struct Student s){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name dosen't exist!\n");
    else
        insertPre_indexp(L,p,s);
}

//����(������Ϊc��ѧ��֮�����ѧ��s)
void insertPost_namec(List L,char* c,struct Student s){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name dosen't exist!\n");
    else
        insertPost_indexp(L,p,s);
}

//ɾ��(ɾ���±�Ϊp��ѧ��)
void delete_indexp(List L,int p){
    if(p<0||p>L->n){
        printf("p doesn't exist!\n"); //�������������±�
        return;
    }
    for(int q=p;q<L->n-1;q++)
        L->Stu[q]=L->Stu[q+1];
    L->n--;
    printf("Delete successfully!\n"); 
}

//ɾ��(ɾ������Ϊc��ѧ��)
void delete_namec(List L,char* c){
    int p=find_namec_index(L,c);
    if(p==-1)
        printf("name doesn't exist!\n");
    else
        delete_indexp(L,p);
}

//ͳ��(ͳ�Ƹ���ѧ�Ƶ���߷֣���ͷ֣�����)
void count(List L){
    if(L->n==0){
        printf("There is no student to be counted!\n");
        return;
    }
    double Math_Max=MIN,Math_Min=MAX,Math_Sum=0; // ��ѧ��߷֣���ͷ֣��ܷ�
    double English_Max=MIN,English_Min=MAX,English_Sum=0; // Ӣ����߷֣���ͷ֣��ܷ�
    double CProgram_Max=MIN,CProgram_Min=MAX,CProgram_Sum=0; // C������߷֣���ͷ֣��ܷ�
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

//�ڱ�ĩβ���ѧ��
void append(List L,struct Student s){
    insertPre_indexp(L,L->n,s);
}

//����һ��ѧ��
struct Student stu(char* name,double* mark){
    struct Student s;
    strcpy(s.name,name);
    s.mark[Math]=mark[Math];
    s.mark[English]=mark[English];
    s.mark[CProgram]=mark[CProgram];
    return s;
} 

//��ӡѧ����������ѧ������Ϣ
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

//�˵�
void menu(){
    char flag[10]="yes";
    int choice_1,choice_2;
    List L=CreateEmptyList(MAXSIZE);
    struct Student s1;     // �ȷŽ�ȥһ��ѧ��
    strcpy(s1.name,"����");
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