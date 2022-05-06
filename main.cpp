#include <SFML/Graphics.hpp>
#include "list.h"
#include <iostream>
#include "card.h"
using namespace sf;
//***************************//
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
//***************************//
Vector2i mousePoint1;
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
Card l(1, 2, 3);
//测试例子2
Card p(2, 2, 3);
//测试例子3
Card q(3, 2, 3);
//测试例子4
Card r(4, 2, 3);
//测试例子5
Card s(5, 2, 3);
//测试例子6
Card t(6, 2, 3);
//测试例子7
Card u(7, 2, 3);
//战斗区卡牌数量
int FightCardNum = 0;
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
    //卡牌测试3的初始化
    q.Texture.loadFromFile("img/base.png");
    q.Sprite.setTexture(l.Texture);
    q.Sprite.setPosition(100, 100);
    //卡牌测试4的初始化
    r.Texture.loadFromFile("img/base.png");
    r.Sprite.setTexture(l.Texture);
    r.Sprite.setPosition(200, 200);
    //卡牌测试5的初始化
    s.Texture.loadFromFile("img/base.png");
    s.Sprite.setTexture(l.Texture);
    s.Sprite.setPosition(300, 300);
    //卡牌测试6的初始化
    t.Texture.loadFromFile("img/base.png");
    t.Sprite.setTexture(l.Texture);
    t.Sprite.setPosition(400, 400);
    //卡牌测试7的初始化
    u.Texture.loadFromFile("img/base.png");
    u.Sprite.setTexture(l.Texture);
    u.Sprite.setPosition(700, 500);
    //手牌的初始化
    CardHand = creat(CardHand);
    CardHand->Insert(l);
    CardHand->Insert(p);
    CardHand->Insert(q);
    CardHand->Insert(r);
    CardHand->Insert(s);
    CardHand->Insert(t);
    CardHand->Insert(u);

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

        for (int i = 1; i <= FightCardNum; i++)
        {
            CircleShape c(10);
            Card Q(0, 0, 0);
            Q = Head->val;
            std::cout << FightCardNum << std::endl;
            std::cout << "SPRITE" << Q.Sprite.getGlobalBounds().width << Q.Sprite.getGlobalBounds().height << std::endl;

            if (FightCardNum % 2 == 0)
            {
                Q.Sprite.setPosition(WIDTH / 2 - 210 * (FightCardNum / 2) - 10 + (i - 1) * 210, HEIGHT / 2);
            }
            else
            {
                Q.Sprite.setPosition(WIDTH / 2 - (FightCardNum / 2) * 210 - 95 + (i - 1) * 210, HEIGHT / 2);
            }
            c.setPosition(Q.Sprite.getPosition().x + Q.Sprite.getGlobalBounds().width / 2-50, HEIGHT / 2);
            window.draw(c);
            // Q.Sprite.setPosition(WIDTH/2, HEIGHT/2);
            window.draw(Q.Sprite);
            Q.txtFollow();
            //下一个链表内容
            Head = Head->next;
        }
    }
    //场景绘画线
    CircleShape c(3);
    for (int i = 0; i < 50; i++)
    {
        c.setPosition(i * WIDTH / 50, HEIGHT / 2);
        window.draw(c);
        c.setPosition(i * WIDTH / 50, HEIGHT * 2 / 3);
        window.draw(c);
    }
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    // Map Pixel to Coords:
    sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
    c.setPosition(mouse_world);
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
            if (event.type == sf::Event::EventType::TextEntered)
            {
                s1 += event.text.unicode;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // printf("Left is press\n");
                //最后一个head
                printf("CardHand: ");
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

                // std::basic_ifstream<sf::Uint8> in;
                // std::basic_fstream<sf::Uint8> out("1234.txt");
                // std::basic_ofstream<sf::Uint8> out("1234.txt");
                // if (!out.is_open())
                // {
                //     printf("open error\n");
                // }
                // else
                // {
                //     printf("open success\n");
                // }
                // s2 = sf::String::toUtf8(s1);
                // out.open("1234.txt");
                // printf("s2  %s\n", s2.c_str());
                // out.write(s2.c_str(), s2.length());
                // out >> s3;
                // sprintf("next%s__%s\n", s2, s3);
                // printf("next%s\n", s3);
                // out.close();
                // out.close();
                // system("pause");
                // return 0;
                // printf("s2  %s\n", s2);
                // in.open("a.txt");
                // if(!in.is_open())
                // {
                //     printf("open error\n");
                // }
                // in >> s2;
                // in.close();
                // printf("next%s\n", s2);
                // system("pause");
                // s2.clear();
                // s1=sf::String::fromUtf8(s2.begin(), s2.end());
                // printf("s1%s\n", s1);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
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
                        mousePoint1 = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));

                        CardinFight->Insert1(Head->val, mousePoint1);
                        FightCardNum++;
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
}
