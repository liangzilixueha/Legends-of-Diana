#include <SFML/Graphics.hpp>
#include <windows.h>
#include "list.h"
#include "card.h"
#include <string.h>

using namespace sf;
//***************************//
//完成上牌，抽牌，取消选取，牌死亡
//完成牌的攻击判定，动画
//卡牌的效果
//***************************//
//如何添加一张卡牌->在全局初始化Card->在Start()中初始化卡牌的资源->插入卡牌

//正在选取卡片
// 参数说明：
// 1：卡牌在手中被选取
// 2：卡牌在战斗中被选取
int isChooseCard = 0;
//战斗的背景
Img batter;
//死亡的链表，敌人和自己公用一个死亡的链表
List *Dead;
//手中牌链表
List *CardHand;
//场上的战斗牌链表
List *CardinFight;
//敌人的战斗链表
List *EnemyinFight;
//用来测试的两个无用链表,
List *Head, *Head1;
//测试例子1
Card l(2, 2, 3, "Diana");
//测试例子2
Card Base0(1, 2, 3, "n");
Card Base1(1, 2, 3, "n");
Card Base2(1, 2, 3, "n");
Card Base3(1, 2, 3, "nasacasc");
Card Base4(1, 2, 3, "n");
Card Base5(1, 2, 3, "n");
Card Base6(1, 2, 3, "n");
Card Base7(1, 2, 3, "n");
//敌人木人桩
Card Tree(1000, 1, 1000, "n");
Card base1(1, 1, 5, "n");
//亡语卡牌
Card deathcard(1, 1, 2, "n");
//两张脸
Card enemyface(-99, -99, 10, "chenrui");
Card playerface(-99, -99, 9, "player");

//游戏回合的摆设
Img YRound, YRound_Down;
Img ERound, ERound_Down;
int IsYourRound = 1;       //判断是否是您的回合
bool IsRoundChange = true; //判断是否进行了回合的切换
bool IsPressed = false;    //按钮是否按了下去
Img YTurn;
Img ETurn;
Img GStart;

//画线函数,输入起点，目的是到光标
void LineTo(double x, double y)
{
    isChooseCard = 2;
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
    double mouseX = mouse_world.x;
    double mouseY = mouse_world.y;
    double dx = (mouseX - x) / 5000;
    double dy = (mouseY - y) / 5000;
    for (int i = 0; i < 5000; i++)
    {
        sf::CircleShape c(2);
        c.setFillColor(sf::Color::White);
        c.setPosition(x + i * dx, y + i * dy);
        window.draw(c);
    }
    return;
}
//创建一个节点
List *creat(List *list)
{
    Card Q(0, 0, 0);
    list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->prior = NULL;
    list->val = Q;
    return list;
}
void Round(int IsYourRound)
{
    if (IsYourRound && IsPressed == false)
        window.draw(YRound.Sprite);
    else if (IsYourRound && IsPressed)
        window.draw(YRound_Down.Sprite);
    else
        window.draw(ERound.Sprite);
}
//开始初始化
void Start()
{
    window.setFramerateLimit(60);
    //战斗背景的初始化
    batter.Texture.loadFromFile("data/img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);

    // 初始化 Round 图标
    YRound.Texture.loadFromFile("data/img/img_discord/YRound.PNG");
    YRound.Sprite.setTexture(YRound.Texture);
    YRound.Sprite.setPosition(1462, 380);
    YRound_Down.Texture.loadFromFile("data/img/img_discord/YRound_Down.PNG");
    YRound_Down.Sprite.setTexture(YRound_Down.Texture);
    YRound_Down.Sprite.setPosition(1462, 380);
    ERound.Texture.loadFromFile("data/img/img_discord/ERound.PNG");
    ERound.Sprite.setTexture(ERound.Texture);
    ERound.Sprite.setPosition(1462, 380);
    // 初始化Round 开场动画
    YTurn.Texture.loadFromFile("data/img/img_discord/YTurn.png");
    YTurn.Sprite.setTexture(YTurn.Texture);
    YTurn.Sprite.setPosition(710, 400);
    YTurn.Sprite.setScale(2, 2);
    ETurn.Texture.loadFromFile("data/img/img_discord/ETurn.png");
    ETurn.Sprite.setTexture(ETurn.Texture);
    ETurn.Sprite.setPosition(710, 400);
    ETurn.Sprite.setScale(2, 2);
    GStart.Texture.loadFromFile("data/img/img_discord/GStart.png");
    GStart.Sprite.setTexture(GStart.Texture);
    GStart.Sprite.setPosition(710, 400);
    GStart.Sprite.setScale(2, 2);

    //卡牌测试1的初始化
    l.Texture.loadFromFile("data/img/base.png");
    l.Sprite.setTexture(l.Texture);
    //木人桩的初始化
    Tree.setSprite("data/img/img_card/base0.png");
    base1.setSprite("data/img/img_card/base1.png");

    Base0.setSprite("data/img/img_card/base0.png");
    Base1.setSprite("data/img/img_card/base1.png");
    Base2.setSprite("data/img/img_card/base2.png");
    Base3.setSprite("data/img/img_card/base3.png");
    Base4.setSprite("data/img/img_card/base4.png");
    Base5.setSprite("data/img/img_card/base5.png");
    Base6.setSprite("data/img/img_card/base6.png");
    Base7.setSprite("data/img/img_card/base7.png");
    //手牌的初始化
    CardHand = creat(CardHand);
    CardHand->Insert(Base0);
    CardHand->Insert(Base1);
    CardHand->Insert(Base2);
    CardHand->Insert(Base3);
    CardHand->Insert(Base4);
    CardHand->Insert(Base5);
    CardHand->Insert(Base6);
    CardHand->Insert(Base7);
    //战斗卡牌的初始化
    CardinFight = creat(CardinFight);

    //敌人的木人桩
    EnemyinFight = creat(EnemyinFight);
    EnemyinFight->Insert(Tree);
    EnemyinFight->Insert(base1);

    //死亡链表
    Dead = creat(Dead);
    deathcard.setSprite("data/img/img_card/base2.png");

    //画两个脸
    enemyface.setSprite("data/img/img_card/chengrui.png");
    enemyface.Sprite.setScale(1, 1);
    enemyface.Sprite.setPosition(WIDTH / 2 - enemyface.Width / 2 + 10, 110);
    playerface.setSprite("data/img/img_card/player.png");
    playerface.Sprite.setPosition(WIDTH / 2 - playerface.Width / 2 + 5, HEIGHT - playerface.Height * 2 - 10);
}
// 绘制基本场景
void Initial_Draw()
{
    //绘制背景
    window.draw(batter.Sprite);
    Round(IsYourRound);
    //画两个脸
    window.draw(enemyface.Sprite);
    window.draw(playerface.Sprite);
    enemyface.txtFollow();
    playerface.txtFollow();
    window.draw(GStart.Sprite);
    window.display();
    Sleep(3000);
}
// 改变回合方的提醒
void Draw_Round()
{
    if (IsYourRound)
    {
        window.draw(YTurn.Sprite);
        window.display();
    }
    else
    {
        window.draw(ETurn.Sprite);
        window.display();
    }
    Sleep(1500);
    IsRoundChange = false;
}

//绘画
void Draw()
{
    //绘制背景
    window.draw(batter.Sprite);
    Round(IsYourRound);
    //画两个脸
    window.draw(enemyface.Sprite);
    window.draw(playerface.Sprite);
    enemyface.txtFollow();
    playerface.txtFollow();
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
    //同时，规范战斗卡牌的位置
    Head = CardinFight->next;
    while (Head)
    {
        for (int i = 1; i <= CardinFight->length(); i++)
        {
            if (CardinFight->length() % 2 == 0)
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 210 * (CardinFight->length() / 2) - 10 + (i - 1) * 210, HEIGHT / 2);
            }
            else
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - (CardinFight->length() / 2) * 210 - 95 + (i - 1) * 210, HEIGHT / 2);
            }
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            //下一个链表内容
            Head = Head->next;
        }
    }
    //绘画敌人卡牌
    //同时，规范敌人卡牌的位置
    Head = EnemyinFight->next;
    while (Head)
    {
        for (int i = 1; i <= EnemyinFight->length(); i++)
        {
            if (EnemyinFight->length() % 2 == 0)
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 210 * (EnemyinFight->length() / 2) - 10 + (i - 1) * 210, HEIGHT / 4);
            }
            else
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - (EnemyinFight->length() / 2) * 210 - 95 + (i - 1) * 210, HEIGHT / 4);
            }
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            //下一个链表内容
            Head = Head->next;
        }
    }
    //画点直线，为了战斗卡牌攻击对方服务，我们不会做特效
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.Hold)
            LineTo(Head->val.Sprite.getPosition().x + Head->val.Width / 2, Head->val.Sprite.getPosition().y + Head->val.Height / 2);
        Head = Head->next;
    }
    //绘制鼠标点，让你看的清楚
    CircleShape c(10);
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
    c.setPosition(mouse_world);
    window.draw(c);

    window.display();
}
//左键单击
void LeftPress()
{
    //确保你只能选择一个卡牌，且是最上面的卡牌
    //最上面的卡牌：即最后绘制的卡牌
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
    //战斗卡牌点击后，产生面对敌方的预攻击直线
    //这里Hold=1之后会在Draw()里面调用LineTo()函数
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.isInclude())
        {
            Head->val.Hold = 1;
            break;
        }
        Head = Head->next;
    }
}
//左键释放
void LeftReleased()
{
    //当鼠标抓着手牌的时候↓
    Head = CardHand->next;
    while (Head)
    {
        Head->val.Hold = 0;
        // 如果卡牌的位置处于战斗区域，那么
        // 1.删除手牌中的卡牌
        // 2.将这个卡牌插入到战斗卡牌当中
        if (Head->val.Sprite.getPosition().y >= HEIGHT / 2 && Head->val.Sprite.getPosition().y <= HEIGHT * 2 / 3)
        {
            if (CardinFight->length() >= 7)
                break;
            CardinFight->Insert(Head->val);
            //下面这一串都是为了将这个节点从手牌中删除
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
    // 找到我们的谁攻击的，也就是先前被抓住的
    // 然后选取对方的敌人，随后扣除相应的血量
    Head1 = CardinFight;
    while (Head1)
    {
        if (Head1->val.Hold == 1)
            break;
        Head1 = Head1->next;
    }
    Head = EnemyinFight;
    while (Head && Head1)
    {
        if (Head->val.isInclude())
        {
            // ATKfunAnime();
            Head->val.HP -= Head1->val.ATK;
            Head1->val.HP -= Head->val.ATK;
            break;
        }
        Head = Head->next;
    }
    //打脸！！！
    if (enemyface.isInclude() && isChooseCard == 2)
        enemyface.HP -= Head1->val.ATK;
    if (enemyface.HP <= 0)
    {
        Font font;
        font.loadFromFile("./data/ttf/yuanshen.ttf");
        Text win;
        win.setString("You Win!");
        win.setFont(font);
        win.setCharacterSize(400);
        win.setColor(sf::Color::Red);
        window.draw(win);
        window.display();
        sf::sleep(sf::seconds(10));
        window.clear();
    }
    //判断*双方*卡牌死亡的问题
    Head = CardinFight;
    while (Head)
    {
        //小心把头节点给删除了
        if (Head->val.HP <= 0 && Head->val.Cost > 0)
        {
            if (strcmp(Head->val.name, "fff") == 0)
            {
                CardinFight->Insert(deathcard);
                CardinFight->Insert(deathcard);
            }

            Dead->Insert(Head->val);
            if (Head->next == NULL)
                Head->prior->next = Head->next;
            else
            {
                Head->next->prior = Head->prior;
                Head->prior->next = Head->next;
            }
        }
        Head = Head->next;
    }
    Head = EnemyinFight;
    while (Head)
    {
        //小心把头节点给删除了
        if (Head->val.HP <= 0 && Head->val.Cost > 0)
        {
            Dead->Insert(Head->val);
            if (Head->next == NULL)
                Head->prior->next = Head->next;
            else
            {
                Head->next->prior = Head->prior;
                Head->prior->next = Head->next;
            }
        }
        Head = Head->next;
    }
    //当鼠标抓着手牌的时候↑
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.Hold == 1)
            Head->val.Hold = 0;
        Head = Head->next;
    }
    isChooseCard = 0;
}
//右键单击
void RightPress()
{
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
int main()
{
    Start();
    Initial_Draw();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (event.mouseButton.x > 1470 && event.mouseButton.y > 390 &&
                    event.mouseButton.x < 1800 && event.mouseButton.y < 600 && IsYourRound == 1)
                    IsPressed = true;
                LeftPress();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                RightPress();
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {

                if (event.mouseButton.x > 1480 && event.mouseButton.y > 390 &&
                    event.mouseButton.x < 1800 && event.mouseButton.y < 600 && IsYourRound == 1)
                {
                    IsPressed = false;
                    IsYourRound = 0;
                    IsRoundChange = true;
                }
                LeftReleased();
            }
        }
        window.clear();
        //点击的函数，当你的Hold为1的时候
        //让你的卡牌跟着你的鼠标
        Head = CardHand->next;
        while (Head)
        {
            if (Head->val.Hold)
            {
                Head->val.setCardFollowMouse();
            }
            Head = Head->next;
        }
        //卡牌移动函数的测试
        //但是远远没有完善
        Head = CardHand->next;
        while (Head)
        {
            if (Head->val.moveFlag)
                Head->val.moveTo(500, 300);
            Head = Head->next;
        }
        Draw();
        if (IsRoundChange)
            Draw_Round();
    }
}