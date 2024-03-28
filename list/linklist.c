#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    int data;           //结构体的一个成员
    struct node* next;  //结构体指针和本结构体类型一样的结构体指针
    
}linklist_t;            //linklist_t等价于struct node

//头插法
linklist_t * linklist_init(void)
{
    linklist_t* h = (linklist_t *)malloc(sizeof(linklist_t));
    h->data = 0;
    h->next = NULL;
    return h;

}

int linklist_print(linklist_t* h)
{
    linklist_t* p = h->next;//让p指向头节点的下一个节点
    printf("链表的内容为：");
    //如果是空头，头节点下一个为空（NULL)
    //p != NULL表示头节点后面有元素
    while (p != NULL)
    {
        printf("%d",p->data );
        p = p->next;//移动p节点，让p往后移动一个元素
    }
    printf("\n");
    return 0;


}

//h 是一个结构体指针，保存结构体的地址
//value要写入的值
int linklist_insert(linklist_t* h, int value)
{
    linklist_t* p = (linklist_t*)malloc(sizeof(linklist_t));
    p->next = h->next;//步骤1 p的next指向h的头节点
    h->next = p;//步骤2  h的头节点指向p
    p->data = value;//将p的元素赋值

    return 0;
}

//删除结点
//正常删除链表中的一个结点，需要把要删除链表的前一个结点和后一个结点连接
//需要找到要删除结点的前一个结点才可以删除
int linklist_delete(linklist_t* h, int value)
{
    //链表要删除1号结点，必须让p指向要删除结点的前一个结点
    linklist_t* p = h;
    linklist_t* q;//保存要删除的结点


    //链表中第一个元素的前一个结点就是链表的head
    while (p->next != NULL)
    {
        //p->next是链表的第一个结点
        if (p->next->data == value)
        {
            q = p->next;//p->next要删除的结点，q去保存要删除的结点
            p->next = q->next;//链表的前一个结点与后一个结点连接
            free(q);//释放内存

            //释放完内存结点后，要立即退出循环或者返回
            return 0;
        }
        
        
            p = p->next;//移动p结点，让p往后移动一个元素
               
       
    }
}

//修改结点的元素
int linklist_modify(linklist_t* h, int old,int new)
{
    linklist_t* p = h->next;//p指向头结点的下一个结点，就是第一个结点
    
    while (p != NULL)
    {
        if (p->data == old)
        {
            p->data = new;
            //更改后 理解退出循环或者返回

            return 0;
        }
        p = p->next;//移动p结点，让p往后移动一个位置
    }

    
    return 0;

}

//找到返回1
//没找到返回0
int linklist_locate(linklist_t* h, int value)
{
    linklist_t* p = h->next;//p指向头节点的下一个节点，就是第一个节点
    while (p!=NULL)
    {
        if (p->data == value)
        {
            return 1;//返回为真
        }
        p = p->next;//移动p节点，让p往后移动一个元素
    }
    return 0;//返回为假

}


//用指针p指向第一个节点，然后把头设计成空头，然后把p节点插入头的后面，以此类推
//即可实现链表的逆序
int linklist_reverse(linklist_t* h)
{
    linklist_t* p = h->next;//p指向头节点的下一个节点，就是第一个节点
    linklist_t* q;//保存p节点，用于下一次运算
    h->next = NULL;//把头节点置空
    while (p != NULL)
    {
        q = p->next;//保存p节点，用于下一次运算
        p->next = h->next;//头插入的第一步
        h->next = p;//头插入的第二步
        p = q;//让p节点移动到q节点的位置上
        
    }
    return 0;//返回为假

}

int main(int argc, char const* argv[])
{
    linklist_t* H = linklist_init();//H=h
    for (int i = 0;i < 10;i++)
    {
        linklist_insert(H, i + 1);
    }
    linklist_print(H);
    linklist_delete(H, 10);
    linklist_delete(H, 1);
    linklist_delete(H, 5);
    linklist_print(H);
    linklist_modify(H, 9, 99);
    linklist_modify(H, 4, 44);
    linklist_modify(H, 2, 22);
    linklist_print(H);
    if (linklist_locate(H, 99))
    {
        printf("99 found!\n");
    }
    else
    {
        printf("99 not found!\n");
    }

    if (linklist_locate(H, 10))
    {
        printf("10 found!\n");
    }
    else
    {
        printf("10 not found!\n");
    }


    linklist_reverse(H);
    linklist_print(H);
    linklist_reverse(H);
    linklist_print(H);

    return 0;
}
