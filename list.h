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
    struct List
{
    Card val;
    //后继
    struct List *next;
    //前躯
    struct List *prior;
    void Insert(Card);
    int Length();
};
//卡牌的长度
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
void List::Insert(Card a)
{
    List *p;
    sf::Font font;
    font.loadFromFile("wryh.ttf");
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
}


#ifdef __cpluscplus
#endif
#endif // end _LIST_H