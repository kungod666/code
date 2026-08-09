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
void reset(stu_inf** head)
{
    stu_inf* prev = *head;
    stu_inf* current = (*head)->next;
    while (current != NULL)
    {
        free(prev);
        prev = current;
        current = current->next;
    }
    free(prev);
    prev = NULL;
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
    return head;
}
void sortscore(stu_inf* head,int n)
{
stu_inf* tp=head;
printf("请输入你要查询的课程编号：");
printf("(1.语文 2.数学 3.英语 4.化学 5.物理 6.体育 7.生物 8.历史 9.地理 10.政治 )");

int class_num;
    scanf_s("%d",&class_num);
int score1,score2,i=0;
    switch(class_num)
    {
    case 1:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->chi,score2=tp->next->chi;
            }
        if(score2>score1)
        {
            int tempchi;
            char tempid[20];
            tempchi=tp->chi;
            strcpy_s(tempid,20,tp->ID);
            tp->chi=tp->next->chi;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->chi=tempchi;
            strcpy_s(tp->next->ID,20,tempid);
        }

        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->chi);
        tp=tp->next;
        }
        break;
     case 2:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->math,score2=tp->next->math;
            }
        if(score2>score1)
        {
            int tempmath;
            char tempid[20];
            tempmath=tp->math;
            strcpy_s(tempid,20,tp->ID);
            tp->math=tp->next->math;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->math=tempmath;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->math);
        tp=tp->next;
        }
        break;
            case 3:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->eng,score2=tp->next->eng;
            }
        if(score2>score1)
        {
            int tempeng;
            char tempid[20];
            tempeng=tp->eng;
            strcpy_s(tempid,20,tp->ID);
            tp->eng=tp->next->eng;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->eng=tempeng;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->eng);
        tp=tp->next;
        }
        break;
            case 4:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->che,score2=tp->next->che;
            }
        if(score2>score1)
        {
            int tempche;
            char tempid[20];
            tempche=tp->che;
            strcpy_s(tempid,20,tp->ID);
            tp->che=tp->next->che;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->che=tempche;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->che);
        tp=tp->next;
        }
        break;
            case 5:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<30;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->phy,score2=tp->next->phy;
            }
        if(score2>score1)
        {
            int tempphy;
            char tempid[20];
            tempphy=tp->phy;
            strcpy_s(tempid,20,tp->ID);
            tp->phy=tp->next->phy;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->phy=tempphy;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<30;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->phy);
        tp=tp->next;
        }
        break;
            case 6:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->pe,score2=tp->next->pe;
            }
        if(score2>score1)
        {
            int temppe;
            char tempid[20];
            temppe=tp->pe;
            strcpy_s(tempid,20,tp->ID);
            tp->pe=tp->next->pe;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->pe=temppe;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<30;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->pe);
        tp=tp->next;
        }
        break;
            case 7:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->bio,score2=tp->next->bio;
            }
        if(score2>score1)
        {
            int tempbio;
            char tempid[20];
            tempbio=tp->bio;
            strcpy_s(tempid,20,tp->ID);
            tp->bio=tp->next->bio;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->bio=tempbio;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->bio);
        tp=tp->next;
        }
        break;
            case 8:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->hist,score2=tp->next->hist;
            }
        if(score2>score1)
        {
            int temphist;
            char tempid[20];
            temphist=tp->hist;
            strcpy_s(tempid,20,tp->ID);
            tp->hist=tp->next->hist;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->hist=temphist;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->hist);
        tp=tp->next;
        }
        break;
            case 9:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->geo,score2=tp->next->geo;
            }
        if(score2>score1)
        {
            int tempgeo;
            char tempid[20];
            tempgeo=tp->geo;
            strcpy_s(tempid,20,tp->ID);
            tp->geo=tp->next->geo;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->geo=tempgeo;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->geo);
        tp=tp->next;
        }
        break;
            case 10:
    if(tp==NULL||tp->next==NULL)
    {
        return;
    }
    for(int b=0;b<n;b++)
    {
        for(int a=0;a<n;a++)
        {
            if(tp->next!=NULL)
            {
        score1=tp->poli,score2=tp->next->poli;
            }
        if(score2>score1)
        {
            int temppoli;
            char tempid[20];
            temppoli=tp->poli;
            strcpy_s(tempid,20,tp->ID);
            tp->poli=tp->next->poli;
            strcpy_s(tp->ID,20,tp->next->ID);
            tp->next->poli=temppoli;
            strcpy_s(tp->next->ID,20,tempid);
        }
        tp=tp->next;
        }
    }
    tp=head;
        printf("学号:\t\t\t成绩:\n");
        for(int c=0;c<n;c++)
        {
        printf("%s\t\t\t\t\t%d\n",tp->ID,tp->poli);
        tp=tp->next;
        }
        break;
    }
}
int main()
{
    printf("欢迎来到由菲比揪比主教大人赞助的学生成绩信息管理系统\n");
    printf("先把成绩录入进去吧\n");
    int n;
    scanf_s("%d",&n);
    stu_inf* head = chushihua(n);
    printf("请输入您想做的操作\n");
    int choice;
    while(1)
    {
        printf("1.查找对象并打印结果\n");
        printf("2.查找并修改对象\n");
        printf("3.选择位置并插入新的同学信息\n");
        printf("4.删除给定位置同学信息\n");
        printf("5.遍历节点信息\n");
        printf("6.选择想要排序成绩的课程并将排序后结果打印\n");
        printf("7.链表清零");
        printf("0.退出系统");
        scanf_s("%d",&choice);
        char ankle[20];
        stu_inf* rece = NULL;
        int branch;
        switch(choice)
        {
            case 1:
            printf("请输入想查找的学生姓名\n");
            scanf_s("%s",ankle,20);
            rece = chazhao(head,ankle);
            if(isempty(rece))
            {
                break;
            }
            printList(rece);
            break;

            case 2:
            modify(head);
            break;

            case 3:
            insertNode(&head);
            break;

            case 4:
            head = delete(head);
            break;

            case 5:
            print_all_students(head);
            break;
            
            case 6:
            sortscore(head,n);
            break;

            case 7:
            reset(&head);
            printf("是否还要对清零后链表初始化?(想要初始化请按1)\n");
            scanf_s("%d",&branch);
            if(branch == 1)
            {
                head = chushihua(30);
            }
            break;
            
            case 0:
            return 0;
        }
    }
}