#include <SFML/Graphics.hpp>
#include "list.h"
#include "card.h"
using namespace sf;
//***************************//
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
//***************************//

//战斗的背景
Img batter;
//手中牌链表
List *CardHand;
//场上的战斗牌链表
List *CardinFight;
//用来测试的无用链表
List *Head;
//测试例子1
Card l(2, 2, 3);
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

    CardHand=creat(CardHand);
    CardHand->Insert(l);
    CardHand->Insert(p);
    
    CardinFight = creat(CardinFight);
}
void Draw()
{
    window.draw(batter.Sprite);
    Head = CardHand->next;
    //绘画手牌
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
<<<<<<< Updated upstream
                while (Head)
                {
                    if (Head->val.isInclude())
                        Head->val.changeHold();
                    Head = Head->next;
                }
=======
                // while (Head)
                // {
                //     // //如果鼠标在其中
                //     // if (Head->val.isInclude())
                //     // {
                //     //     if (isChooseCard)
                //     //         isChooseCard = 0;
                //     //     else
                //     //         isChooseCard = 1;
                //     //     if (isChooseCard)
                //     //         Head->val.changeHold();
                //     //     //如果卡牌被选中
                //     //     if (Head->val.Hold)
                //     //     {
                //     //         //卡牌的Y坐标
                //     //         double y = Head->val.Sprite.getPosition().y;
                //     //         //如果卡牌位于敌方位置，回去
                //     //         //如果卡牌位于自己的下方，回去
                //     //         // else让卡牌从手牌移除，加入战斗卡牌列表
                //     //         if (y < HEIGHT / 2 || y > HEIGHT * 2 / 3)
                //     //         {
                //     //             Head->val.moveFlag = 1;
                //     //         }
                //     //         else
                //     //         {
                //     //             //插入这个节点到战斗手牌中
                //     //             CardinFight->Insert(Head->val);
                //     //             //删除这个节点
                //     //             Head->prior->next = Head->next;
                //     //         }
                //     //     }
                //     //     //只要鼠标在卡牌的范围内，那每一次点击就必然会拿起一张卡牌或者放下一张卡牌
                //     //     //如果卡牌被选中，那么就放下这张卡牌
                //     //     //如果卡牌没有被选中，那么就拿起这张卡牌
                //     Head = Head->next;
                // }
>>>>>>> Stashed changes
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
    