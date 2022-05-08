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
    void InsertBetween(Card);
    int length();
    void print();
    int isIncludeTaunt();
};
//卡牌的长度
//初始的长度为0
int List::length()
{
    List *p = this->next;
    int a = 0;
    while (p)
    {
        p = p->next;
        ++a;
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
//只能用在战斗卡牌（CardinFight）中！！！！
//根据卡牌的位置在卡牌的中间插入一个卡牌
//只能用在战斗卡牌（CardinFight）中！！！！
void List::InsertBetween(Card a)
{
    List *p;
    p = (List *)malloc(sizeof(List));
    p->next = p->prior = NULL;
    p->val = a;
    List *th = this;
    while (th->next)
    {
        if (th->next->val.Sprite.getPosition().x > a.Sprite.getPosition().x)
        {
            p->next = th->next;
            th->next->prior = p;
            th->next = p;
            p->prior = th;
            th = p;
            return;
        }
        th = th->next;
    }
    this->Insert(a);
}
//输出这个链表的内容用名字
void List::print()
{
    List *p = this->next;
    printf("[");
    while (p)
    {
        printf("\"%s\"", p->val.name);
        if (p->next)
            printf(",");
        p = p->next;
    }
    printf("]\n");
}
//该链表的卡牌下包含嘲讽么？
//如果包含，则返回1，否则返回0
int List::isIncludeTaunt(){
    List *p=this;
    while(p){
        if(p->val.Taunt){
            return 1;
        }
        p=p->next;
    }
    return 0;
}
#ifdef __cpluscplus
#endif
#endif // end _LIST_H