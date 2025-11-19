#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*程序课讨论课要求：
假设你们班有30位同学，本学期有10门课程，请以小组为单位对成绩管理系统进行设计并实现，要求使用链表实现以下功能：
（0）设计自引用结构体，保存每位同学的信息；
（1）使用链表结构组织一个班的学生信息；
（2）能够对链表进行初始化；
（3）能够对链表进行查找，并打印查找结果；
（4）能够对链表进行查找，并修改对应的结点；
（5）能够在链表的某个给定位置上，插入新的节点；
（6）能够在链表的某个给定位置上，删除节点；
（7）能够遍历节点信息；
（8）根据某一个课程的成绩进行排序；
其它相关内容请自行设计和实现。*/
typedef struct stu_inf
{
    char ID[20];
    int chi;
    int math;
    int eng;
    int che;
    int phy;
    int pe;
    int bio;
    int hist;
    int geo;
    int poli;
    struct stu_inf* next;
}stu_inf;
int isempty(stu_inf* head)
{
    return head ==NULL;
}
void input(stu_inf* ans)
{
    printf("请输入学生姓名\n");
    scanf_s("%s",ans->ID,20);
    printf("请依次输入语文，数学，英语，化学，物理，体育，生物，历史，地理，政治成绩\n");
    scanf_s("%d %d %d %d %d %d %d %d %d %d",&ans->chi,&ans->math,&ans->eng,&ans->che,&ans->phy,&ans->pe,&ans->bio,&ans->hist,&ans->geo,&ans->poli);
}
stu_inf* chushihua(int n)
{
    stu_inf* ans = NULL;
    stu_inf* cur = NULL;
    for(int i = 0;i<n;i++)
    {
        if(ans == NULL)
        {
            ans = (stu_inf*)malloc(sizeof(stu_inf));
            input(ans);
            cur = ans;
            cur->next = NULL;
        }
        else 
        {
            cur->next = (stu_inf*)malloc(sizeof(stu_inf));
            cur = cur->next;
            input(cur);
            cur->next = NULL;
        }
    }
    return ans;
}
void printList(stu_inf* m)
{
    printf("姓名：%s",m->ID);
    printf("语文：%d]\n",m->chi);
    printf("数学：%d]\n",m->math);
    printf("英语：%d]\n",m->eng);
    printf("化学:%d\n",m->che);
    printf("物理：%d]\n",m->phy);
    printf("体育：%d]\n",m->pe);
    printf("生物：%d]\n",m->bio);
    printf("历史：%d]\n",m->hist);
    printf("地理：%d]\n",m->geo);
    printf("政治：%d]\n",m->poli);
    printf("-------------------\n");
}
stu_inf* chazhao(stu_inf* head,char ID[])
{
    stu_inf* tp = head;
    if(isempty(head))
    {
        printf("当前链表为空，无法进行查找\n");
        return tp;
    }
    while(tp != NULL)
    {
        if(strcmp(tp->ID,ID) == 0)
        {
            printf("已查询到该学生，各科成绩如下\n");
            printList(tp);
            return tp;
        }
        tp = tp->next;
    }
    printf("未查询到目标学生\n");
    tp = NULL;
    return tp;
}
void insertNode(stu_inf** head)//用二级指针才能让头节点被正确修改(当前head并不能被真正修改,当我们向改变指针的值（具体地址）则亦需指针传递)
{
    printf("请输入你想插入学生的位置(插入位置之前第一个学生的ID按1,若插入头节点按2)\n");
    int j;
    char k[20];
    scanf_s("%d",&j);
    stu_inf* tp = NULL;
    stu_inf* loca = NULL;
    stu_inf* op;
    switch(j)
    {
        case 1:
        printf("莲宝正努力将安排新同学入座.......\n");
        scanf_s("%s",k);
        loca = chazhao(*head,k);
        if(!isempty(loca))
        {
            tp = loca->next;
            loca->next = (stu_inf*) malloc (sizeof(stu_inf));
            input(loca->next);
            loca->next->next = tp;
            printf("插入完成了喵\n");
        }
        else {
        printf("插入位置无效๐·°(৹˃̵﹏˂̵৹)°·๐");
        }
        break;
        case 2:
        printf("莲宝正努力将学生插入头部.......\n");
        op = (stu_inf*)malloc(sizeof(stu_inf));
        input(op);
        op->next = *head;
        *head = op;
        printf("插入完成了喵.。(๑･∀･๑)*.。\n");
    }
}
void modify(stu_inf* head);
stu_inf* delete(stu_inf* head);//删除头部用stu_inf*接受,不删除不接收
void reset(stu_inf* head)
{
    stu_inf* prev = head;
    stu_inf* current = head->next;
    while (current != NULL)
    {
        free(prev);
        prev = current;
        current = current->next;
    }
    free(prev);
}

void modify(stu_inf* head)
{
    char target[20];
    printf("请输入您想修改的学生姓名\n");
    scanf_s("%s",target);
    stu_inf* mc = chazhao(head,target);
    if(!isempty(mc))
    {
    while(1)
    {
    printf("你想对该学生做出的操作：\n1.修改所有信息\n2.修改某个信息\n0.取消操作\n");
    int n = 0;
    scanf_s("%d", &n);
    switch (n)
    {
    case 1:
        printf("请按照顺序输入信息：\n语文 数学 英语 化学 物理 体育 生物 历史 地理 政治\n");
        if ((scanf_s(" %d %d %d %d %d %d %d %d %d %d", &mc->chi, &mc->math, &mc->eng, &mc->che,
            &mc->phy, &mc->pe, &mc->bio, &mc->hist, &mc->geo, &mc->poli)) != 10)
        {
            printf("输入错误，请重新输入\n");
            break;
        }
        else
        {
            printf("修改成功 还需要对该学生进行其他操作吗？\n");
            break;
        }
        break;
    case 2:
        printf("你要修改什么信息呢？\n1.语文\n2.数学\n3.英语\n4.化学\n5.物理\n6.体育\n7.生物\n8.历史\n9.地理\n10.政治\n");
        int grade = 0;
        int n = 0;
        scanf_s("%d", &n);
        printf("输入该学科的信息\n");
        scanf_s("%d", &grade);
        switch (n)
        {
        case 1:
            mc->chi = grade;
            break;
        case 2:
            mc->math = grade;
            break;
        case 3:
            mc->eng = grade;
            break;
        case 4:
            mc->che = grade;
            break;
        case 5:
            mc->phy = grade;
            break;
        case 6:
            mc->pe = grade;
            break;
        case 7:
            mc->bio = grade;
            break;
        case 8:
            mc->hist = grade;
            break;
        case 9:
            mc->geo = grade;
            break;
        case 10:
            mc->poli = grade;
            break;
        }
        printf("修改成功 还需要对该学生进行其他操作吗？\n");
        modify(head);
        break;
    case 0:
        return;
    }
}
}
}
// 遍历链表并打印所有学生信息
void print_all_students(struct stu_inf *head) {
    if (head == NULL) {
        printf("链表为空，没有学生信息。\n");
        return;
    }

    printf("\n========== 开始遍历所有学生信息 ==========\n");
    printf("学号\t\t语文\t数学\t英文\t化学\t物理\t体育\t生物\t历史\t地理\t政治\n");
    printf("------------------------------------------------------------------------------------------------\n");

    struct stu_inf *current = head;  // 从头节点开始

    int index = 1;  // 用于显示第几个学生，可选

    while (current != NULL) {
        printf("学生%d ", index++);
        printf("学号: %s\t", current->ID);
        printf("语文: %d\t", current->chi);
        printf("数学: %d\t", current->math);
        printf("英文: %d\t", current->eng);
        printf("化学: %d\t", current->che);
        printf("物理: %d\t", current->phy);
        printf("体育: %d\t", current->pe);
        printf("生物: %d\t", current->bio);
        printf("历史: %d\t", current->hist);
        printf("地理: %d\t", current->geo);
        printf("政治: %d\n", current->poli);

        current = current->next;  // 移动到下一个节点
    }

    printf("========== 遍历结束 ==========\n\n");
}
stu_inf* delete(stu_inf* head)
{
    stu_inf* tp = head;
    char ys[20];
    printf("请输入您要删除的学生姓名\n");
    scanf_s("%s",ys,20);
    stu_inf* cur = chazhao(tp,ys);
    if(!isempty(cur))
    {
        if(tp == cur)
        {
            stu_inf* oj = tp->next;
            free(tp);
            return oj;
        }
        else 
        {
            while(tp->next != cur)
            {
                tp = tp->next;
            }
            tp->next = cur->next;
            free(cur);
        }
    }
    return NULL;
}
int main()
{

}