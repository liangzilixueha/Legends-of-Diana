/**************************************
-----------------list.h---------------------
product name：list
module name：list
date：2022.03.06
auther：none
file describe: none
***************************************/

#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus // c++ include
extern "C"
#endif // include c++ file
#include <stdio.h>
#include <stdlib.h>
#include "card.h"
    // macro define

    //这个卡牌内容的链表具有一个
    //**空的头指针*
    //双向链表
    struct List
{
    Card val;
    //后继
    struct List *next;
    //前躯
    struct List *prior;
    void Insert(Card);
    void Insert1(Card, Vector2i);
    int Length();
    void print();
};
//卡牌的长度
//初始的长度为0
int List::Length()
{
    List *p = this->next;
    int a = 0;
    while (p)
    {
        p = p->next;
        a++;
    }
    return a;
}
//在链表的*末尾*插入一个卡牌的类型
void List::Insert(Card a)
{
    List *p;
    p = (List *)malloc(sizeof(List));
    p->next = NULL;
    p->prior = NULL;
    p->val = a;
    List *th;
    th = this;
    while (th->next)
    {
        th = th->next;
    }
    th->next = p;
    p->prior = th;
}
void List::Insert1(Card a, Vector2i mousePoint)
{
    List *p;
    p = (List *)malloc(sizeof(List));
    p->next = NULL;
    p->prior = NULL;
    p->val = a;
    List *th;
    th = this;
    // if (th->val.Sprite.getPosition().x > mousePoint.x)
    // {
    //     p->next = th;
    //     th->prior = p;
    //     th = p;
    // }
    // else
    // {
    while (th->next)
    {
        printf("%d %d\n", th->next->val.Sprite.getPosition().x+th->next->val.Sprite.getGlobalBounds().width/2, mousePoint.x);
        if (th->next->val.Sprite.getPosition().x+th->next->val.Sprite.getGlobalBounds().width/2-50 > mousePoint.x)
        {
            printf("ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");
            
            p->next = th->next;
            th->next->prior = p;
            th->next = p;
            p->prior = th;
            th = p;
            return;
        }
        th=th->next;
    }
    th->next = p;
    p->prior = th;
    //}
    // while (th->next)
    // {
    //     th = th->next;
    // }
    // th->next = p;
    // p->prior = th;
}
//输出这个链表的内容用名字
void List::print()
{
    List *p = this->next;
    printf("[");
    while (p)
    {
        printf("\"%s\"", s1);
        if (p->next)
            printf(",");
        p = p->next;
    }
    printf("]\n");
}
#ifdef __cpluscplus
#endif
#endif // end _LIST_H