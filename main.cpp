#include <SFML/Graphics.hpp>
#include "list.h"
#include "card.h"
using namespace sf;
//***************************//
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
//***************************//

//正在选取卡片
int isChooseCard = 0;
//战斗的背景
Img batter;
//手中牌链表
List *CardHand;
//场上的战斗牌链表
List *CardinFight;
//用来测试的无用链表
List *Head;
//测试例子1
Card l(2, 2, 3, "Diana");
//测试例子2
Card p(1, 2, 3);
//创建一个节点
List *creat(List *list)
{
    Card a(0, 0, 0);
    list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->prior = NULL;
    list->val = a;
    return list;
}
//开始初始化
void Start()
{
    window.setFramerateLimit(60);
    //战斗背景的初始化
    batter.Texture.loadFromFile("img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);
    //卡牌测试1的初始化
    l.Texture.loadFromFile("img/base.png");
    l.Sprite.setTexture(l.Texture);
    //卡牌测试2的初始化
    p.Texture.loadFromFile("img/q.png");
    p.Sprite.setTexture(p.Texture);
    p.Sprite.setPosition(500, 500);
    //手牌的初始化
    CardHand = creat(CardHand);
    CardHand->Insert(l);
    CardHand->Insert(p);
    //战斗卡牌的初始化
    CardinFight = creat(CardinFight);
}
void Draw()
{
    window.draw(batter.Sprite);
    //绘画手牌
    Head = CardHand->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Q.Sprite);
        Q.txtFollow();
        //下一个链表内容
        Head = Head->next;
    }
    //绘画战斗卡牌
    Head = CardinFight->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Q.Sprite);
        Q.txtFollow();
        //下一个链表内容
        Head = Head->next;
    }
    //场景绘画线
    CircleShape c(10);
    for (int i = 0; i < 50; i++)
    {
        c.setPosition(i * WIDTH / 50, HEIGHT / 2);
        window.draw(c);
        c.setPosition(i * WIDTH / 50, HEIGHT * 2 / 3);
        window.draw(c);
    }
    c.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    window.draw(c);
    window.display();
}
int main()
{
    Start();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                printf("Left is press\n");
                Head = CardHand->next;
                CardHand->print();
                Head = CardHand;
                while (Head->next)
                {
                    Head = Head->next;
                }
                if (isChooseCard == 0) //鼠标上没有被抓手牌
                {
                    while (Head)
                    {
                        if (Head->val.isInclude())
                        {
                            Head->val.Hold = 1;
                            break;
                        }
                        Head = Head->prior;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                printf("Right is press\n");
            Head = CardHand->next;
            while (Head)
            {
                if (Head->val.isInclude() && Head->val.Hold)
                {
                    Head->val.changeHold();
                    Head->val.moveFlag = 1;
                }
                Head = Head->next;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            // printf("Left is release\n");
            //当鼠标抓着手牌的时候↓
            Head = CardHand->next;
            while (Head)
            {
                Head->val.Hold = 0;
                // if (sf::Mouse::getPosition().y >= HEIGHT / 2 && sf::Mouse::getPosition().y <= HEIGHT * 2 / 3)
                if (Head->val.Sprite.getPosition().y >= HEIGHT / 2 && Head->val.Sprite.getPosition().y <= HEIGHT * 2 / 3)
                {
                    CardinFight->Insert(Head->val);
                    printf("CardinFight:");
                    CardinFight->print();
                    if (Head->next == NULL)
                    {
                        Head->prior->next = NULL;
                    }
                    else if (Head->next->next == NULL)
                    {
                        Head->val = Head->next->val;
                        Head->next = Head->next->next;
                    }
                    else
                    {
                        Head->val = Head->next->val;
                        Head->next = Head->next->next;
                        Head->next->prior = Head;
                    }
                }
                Head = Head->next;
            }
            //当鼠标抓着手牌的时候↑
        }
    }
    window.clear();

    Head = CardHand->next;
    while (Head)
    {
        if (Head->val.Hold)
        {
            Head->val.setCardFollowMouse();
        }
        Head = Head->next;
    }
    Head = CardHand->next;
    while (Head)
    {
        if (Head->val.moveFlag)
            Head->val.moveTo(500, 300);
        Head = Head->next;
    }
    Draw();
}
