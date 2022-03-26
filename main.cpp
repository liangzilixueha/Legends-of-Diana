#include <SFML/Graphics.hpp>
#include "list.h"
#include "card.h"
using namespace sf;
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
Img batter;
List *CardHand, *CardinFight, *Head;
Card l(2, 2, 3);
Card p(1, 2, 3);
List *creat(List *list)
{
    Card a(0, 0, 0);
    list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->prior = NULL;
    list->val = a;
    return list;
}
void Start()
{
    batter.Texture.loadFromFile("img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);
    l.Texture.loadFromFile("img/base.png");
    l.Sprite.setTexture(l.Texture);

    p.Texture.loadFromFile("img/q.png");
    p.Sprite.setTexture(p.Texture);
    p.Sprite.setPosition(500, 500);

    Card a(0,0,0);
    CardHand=creat(CardHand);
    CardHand->Insert(l);
    CardHand->Insert(p);
    CardinFight = creat(CardinFight);
}
void Draw()
{
    window.draw(batter.Sprite);
    Head = CardHand->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Q.Sprite);
        //画HP
        // Q.txtFollow();
        //下一个链表内容 
        Head = Head->next;
    }
    Head = CardinFight->next;
    while (Head)
    {
        Card Q(0, 0, 0);
        Q = Head->val;
        window.draw(Head->val.Sprite);
        Head = Head->next;
    }

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
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                printf("Left is press\n");
                Head = CardHand->next;
                while (Head)
                {
                    if (Head->val.isInclude())
                        Head->val.changeHold();
                    Head = Head->next;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                printf("Right is press\n");
                Head = CardHand->next;
                while (Head)
                {
                    if (Head->val.isInclude() && Head->val.Hold)
                        Head->val.changeHold();
                    Head = Head->next;
                }
                Head = CardHand->next;
            }
        }
        window.clear();
        Head = CardHand->next;
        while (Head)
        {
            if (Head->val.Hold)
                Head->val.setCardFollowMouse();
            Head = Head->next;
        }
        Draw();
    }
}
    