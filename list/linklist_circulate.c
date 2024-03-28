#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;           //结构体的一个成员
    struct node* next;  //结构体指针和本结构体类型一样的结构体指针

}linklist_t;

linklist_t* cyclist_init(void)
{
    linklist_t* h = (linklist_t*)malloc(sizeof(linklist_t));
    h->data = 0;//循环链表的特点是，头节点也要参与运算
    h->next = h;//头节点的下一个节点指向头部
    return h;

}

int cyclist_insert(linklist_t* h, int value)
{
    linklist_t* p = (linklist_t*)malloc(sizeof(linklist_t));
    p->next = h->next;//步骤1 p的next指向h的头节点
    h->next = p;//步骤2  h的头节点指向p
    p->data = value;//将p的元素赋值

    return 0;
}

int cyclist_print(linklist_t* h)
{
    linklist_t* p = h->next;//让p指向头节点的下一个节点
    printf("链表的内容为：");
    //p == h 说明链表循环一周
    //p != h 可以遍历循环链表一圈少一次 
    while (p != h)
    {
        printf("%d ", p->data);
        p = p->next;//移动p节点，让p往后移动一个元素
    }

    if (p == h)//p指向了h，作为循环表的最后一个元素
    {
        printf("%d ", p->data);
    }

    printf("\n");
    return 0;
}

//删除结点
//正常删除链表中的一个结点，需要把要删除链表的前一个结点和后一个结点连接
//需要找到要删除结点的前一个结点才可以删除
linklist_t* cyclist_delete(linklist_t* h, int value)
{
    //链表要删除1号结点，必须让p指向要删除结点的前一个结点
    linklist_t* p = h;
    linklist_t* q;//保存要删除的结点


    //链表中第一个元素的前一个结点就是链表的head
    while (p->next != h)
    {
        //p->next是链表的第一个结点
        if (p->next->data == value)
        {
            q = p->next;//p->next要删除的结点，q去保存要删除的结点
            p->next = q->next;//链表的前一个结点与后一个结点连接
            free(q);//释放内存

            //释放完内存结点后，要立即退出循环或者返回
            return h;//删除的不是头节点，不需要更新头节点
        }
        p = p->next;//移动p结点，让p往后移动一个元素
    }
    if (p->next == h)//移动到头节点的上一个节点，正好循环一周
    {

        if (p->next->data == value)//匹配成功，说明要删除头节点
        {
            q = p->next;//p->next要删除的结点，q去保存要删除的结点
            p->next = q->next;//链表的前一个结点与后一个结点连接
            free(q);//释放内存

            //释放完内存结点后，要立即退出循环或者返回
            return p;//删除的是头节点，需要更新头节点，把p作为新的头节点
        }
    }
    return h;
}

//修改结点的元素
int cyclist_modify(linklist_t* h, int old, int new)
{
    linklist_t* p = h->next;//p指向头结点的下一个结点，就是第一个结点

    while (p != h)
    {
        if (p->data == old)
        {
            p->data = new;
            //更改后 理解退出循环或者返回

            return 0;
        }
        p = p->next;//移动p结点，让p往后移动一个位置
    }
    if (p == h)//链表循环一周
    {
        if (p->data == old)
        {
            p->data = new;
            //更改后 理解退出循环或者返回

            return 0;
        }
    }

    return 0;

}

int cyclist_locate(linklist_t* h, int value)
{
    linklist_t* p = h->next;//p指向头节点的下一个节点，就是第一个节点
    while (p != h)
    {
        if (p->data == value)
        {
            return 1;//返回为真
        }
        p = p->next;//移动p节点，让p往后移动一个元素
    }
    if (p == h)//链表循环一周
    {
        if (p->data == value)
        {
            return 1;//返回为真
        }
    }
    return 0;//返回为假


}

//用指针p指向第一个节点，然后把头设计成空头，然后把p节点插入头的后面，以此类推
//即可实现链表的逆序
linklist_t* cyclist_reverse(linklist_t* h)
{
    linklist_t* p = h->next;//p指向头节点的下一个节点，就是第一个节点
    linklist_t* q;//保存p节点，用于下一次运算
    h->next = h;//把头节点置空
    while (p != h)
    {
        q = p->next;//保存p节点，用于下一次运算
        p->next = h->next;//头插入的第一步
        h->next = p;//头插入的第二步
        p = q;//让p节点移动到q节点的位置上
        
    }
    //处理最后一个节点，把头节点往后移动一个位置
    //要找到头节点的前一个位置
    p = h;
    while (p->next != h)
    {
        p = p->next;
    }
    if (p->next == h)//定位到头节点的前一个节点
    {
        return p;
    }
}

int main(int argc, char const* argv[])
{
    linklist_t* H = cyclist_init();
    for (int i = 0;i < 10;i++)
    {
        cyclist_insert(H, i + 1);
    }
    cyclist_print(H);

    //需要更新
    H = cyclist_delete(H, 10);
    H = cyclist_delete(H, 0);
    H = cyclist_delete(H, 5);
    cyclist_print(H);


    cyclist_modify(H, 9, 99);
    cyclist_modify(H, 4, 44);
    cyclist_modify(H, 2, 22);
    cyclist_print(H);


     if (cyclist_locate(H, 99))
    {
        printf("99 found!\n");
    }
    else
    {
        printf("99 not found!\n");
    }

    if (cyclist_locate(H, 10))
    {
        printf("10 found!\n");
    }
    else
    {
        printf("10 not found!\n");
    }

    H = cyclist_reverse(H);
    cyclist_print(H);
    H = cyclist_reverse(H);
    cyclist_print(H);

    return 0;
}
