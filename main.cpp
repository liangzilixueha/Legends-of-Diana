#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "list.h"
#include "card.h"
#include "button.h"
#include <string.h>

#include <sstream>
#include <ctime>

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
// 战斗的背景
Img batter;
// 死亡的链表，敌人和自己公用一个死亡的链表
List *Dead;
// 手中牌链表
List *CardHand;
// 场上的战斗牌链表
List *CardinFight;
// 库中牌链表
List *CardinHouse;
// 敌人的战斗链表
List *EnemyinFight;
// 用来测试的两个无用链表,
List *Head, *Head1;

// 嘉心糖的手牌
Card Base0(1, 2, 3, "0");
Card Base1(2, 2, 3, "1");
Card Base2(2, 2, 3, "2");
Card Base3(2, 2, 3, "3");
Card Base4(2, 2, 3, "4");
Card Base5(2, 2, 3, "5");
Card Base6(1, 2, 3, "6");
Card Base7(1, 2, 3, "7");
// 叔叔的手牌
Card base1(1, 1, 5, "n");
Card shu0(1, 2, 3, "0");
Card shu1(1, 2, 3, "1");
Card shu2(1, 2, 3, "2");
Card shu3(1, 2, 3, "3");
Card shu4(1, 2, 3, "4");
Card shu5(1, 2, 3, "5");
Card shu6(1, 2, 3, "6");
Card shu7(1, 2, 3, "7");

// 亡语卡牌
Card deathcard(1, 1, 2, "n");
// 两张脸
Card enemyface(-99, -99, 10, "chenrui");
Card playerface(-99, -99, 10, "jiaxintang");
int Game_judge; //判断是胜利还是失败的变量
// 游戏回合的摆设
Img YRound, YRound_Down;
Img ERound, ERound_Down;
bool IsYourRound;   //判断是否是您的回合
bool IsRoundChange; //判断是否进行了回合的切换
bool IsPressed;     //按钮是否按了下去
int RoundCount;     // 回合计数

// 游戏提示的大头标
Img YTurn;
Img ETurn;
Img GStart;

//判定游戏的胜负
bool isGameOver;

//法力水晶
Img Crystal;
Img CrystalBG;
Text num_c;
Font font_c;
int CrystalCount; //水晶数量计数

//声音
SoundBuffer startM;
Sound StartM;
SoundBuffer jr0, jr1, jr2, jr3, jr4, jr5, jr6, jr7;
Sound JR0, JR1, JR2, JR3, JR4, JR5, JR6, JR7;
SoundBuffer ss0, ss1;
Sound SS0, SS1;
//抽牌
bool NeedNewCard;

//提示文字代码
// 1.你已经攻击过一次了！
// 2.法力水晶不足！
int alertCode = 0;
char alertText[100];
//声明关键模块

void Draw();
void Input();
void Logic();

// 画线函数,输入起点，目的是到光标
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
// 画线函数
void Line(double x, double y, double targetx, double targety)
{

    double dx = (targetx - x) / 5000;
    double dy = (targety - y) / 5000;
    for (int i = 0; i < 5000; i++)
    {
        sf::CircleShape c(2);
        c.setFillColor(sf::Color::White);
        c.setPosition(x + i * dx, y + i * dy);
        window.draw(c);
    }
}
// 创建一个节点
List *creat(List *list)
{
    Card Q(0, 0, 0);
    list = (List *)malloc(sizeof(List));
    list->next = NULL;
    list->prior = NULL;
    list->val = Q;
    return list;
}
//在线程中的代码无限循环
void Alert()
{
    while (1)
    {
        if (alertCode == 0)
            continue;
        if (alertCode == 1)
        {
            alertCode = 0;
            strcpy(alertText, "YOU haved Attacked before!!!");
            sf::sleep(sf::seconds(1));
            strcpy(alertText, "");
        }
        if (alertCode == 2)
        {
            alertCode = 0;
            strcpy(alertText, "YOU haven't enough Power to user it!!!");
            sf::sleep(sf::seconds(1));
            strcpy(alertText, "");
        }
    }
}
// 决定按钮的状态
void Round()
{
    if (IsYourRound && IsPressed == false)
        window.draw(YRound.Sprite);
    else if (IsYourRound && IsPressed)
        window.draw(YRound_Down.Sprite);
    else
        window.draw(ERound.Sprite);
}

// 开始初始化
void Start()
{
    window.setFramerateLimit(60);
    // 战斗背景的初始化
    batter.Texture.loadFromFile("data/img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);
    // 初始化Button图标
    YRound.setSprite("data/img/img_discord/YRound.PNG", 1462, 380);
    YRound_Down.setSprite("data/img/img_discord/YRound_Down.PNG", 1462, 380);
    ERound.setSprite("data/img/img_discord/ERound.PNG", 1462, 380);
    // 初始化Round 开场动画
    YTurn.setSprite("data/img/img_discord/YTurn.png", 710, 400);
    YTurn.Sprite.setScale(2, 2);
    ETurn.setSprite("data/img/img_discord/ETurn.png", 710, 400);
    ETurn.Sprite.setScale(2, 2);
    GStart.setSprite("data/img/img_discord/GStart.png", 710, 400);
    GStart.Sprite.setScale(2, 2);

    //嘉心糖手牌的初始化
    Base0.setSprite("data/img/img_card/base0.png");
    Base1.setSprite("data/img/img_card/base1.png");
    Base2.setSprite("data/img/img_card/base2.png");
    Base3.setSprite("data/img/img_card/base3.png");
    Base4.setSprite("data/img/img_card/base4.png");
    Base5.setSprite("data/img/img_card/base5.png");
    Base6.setSprite("data/img/img_card/base6.png");
    Base7.setSprite("data/img/img_card/base7.png");
    //叔叔手牌的初始化
    shu0.setSprite("data/img/cardsforCR/dinpin.png");
    shu1.setSprite("data/img/cardsforCR/he.png");
    shu2.setSprite("data/img/cardsforCR/LEX.png");
    shu3.setSprite("data/img/cardsforCR/LV0.png");
    shu4.setSprite("data/img/cardsforCR/mengguren.png");
    shu5.setSprite("data/img/cardsforCR/nanami.png");
    shu6.setSprite("data/img/cardsforCR/vox.png");
    shu7.setSprite("data/img/cardsforCR/vvip.png");

    // 音效的初始化
    // 开场音效
    startM.loadFromFile("data/music/start/welcome.wav");
    StartM.setBuffer(startM);
    // 嘉然音效
    jr0.loadFromFile("data/music/owner/jiaran1.wav");
    JR0.setBuffer(jr0);
    jr1.loadFromFile("data/music/owner/jiaran2.wav");
    JR1.setBuffer(jr1);
    jr2.loadFromFile("data/music/owner/jiaran3.wav");
    JR2.setBuffer(jr2);
    jr3.loadFromFile("data/music/owner/jiaran4.wav");
    JR3.setBuffer(jr3);
    jr4.loadFromFile("data/music/owner/jiaran5.wav");
    JR4.setBuffer(jr4);
    jr5.loadFromFile("data/music/owner/nanami1.wav");
    JR5.setBuffer(jr5);
    jr6.loadFromFile("data/music/owner/nanami2.wav");
    JR6.setBuffer(jr6);
    jr7.loadFromFile("data/music/owner/ko no dio da.wav");
    JR7.setBuffer(jr7);
    // 叔叔音效
    ss0.loadFromFile("data/music/enemy/CR1.wav");
    SS0.setBuffer(ss0);
    ss1.loadFromFile("data/music/enemy/CR2.wav");
    SS1.setBuffer(ss1);

    // 牌库的初始化
    CardinHouse = creat(CardinHouse);
    srand((unsigned int)(time(NULL)));
    int no;
    for (int i = 0; i < 40; i++)
    {
        no = rand() % 7;
        switch (no)
        {
        case 0:
            CardinHouse->Insert(Base0);
            break;
        case 1:
            CardinHouse->Insert(Base1);
            break;
        case 2:
            CardinHouse->Insert(Base2);
            break;
        case 3:
            CardinHouse->Insert(Base3);
            break;
        case 4:
            CardinHouse->Insert(Base4);
            break;
        case 5:
            CardinHouse->Insert(Base5);
            break;
        case 6:
            CardinHouse->Insert(Base6);
            break;
        case 7:
            CardinHouse->Insert(Base7);
            break;
        default:
            break;
        }
    }
    // 手牌的初始化
    CardHand = creat(CardHand);
    CardHand->Insert(Base7);
    // 战斗卡牌的初始化
    CardinFight = creat(CardinFight);

    // 敌人的木人桩
    EnemyinFight = creat(EnemyinFight);
    //EnemyinFight->Insert(shu0);
    //EnemyinFight->Insert(shu1);

    // 死亡链表
    Dead = creat(Dead);
    deathcard.setSprite("data/img/img_card/base2.png");

    //初始化布尔参数
    IsYourRound = true;
    IsRoundChange = true;
    IsPressed = false;
    isGameOver = false;
    NeedNewCard = false;

    //回合计数初始化
    RoundCount = 1;

    // 画两个脸(参数控制)
    enemyface.setSprite("data/img/img_card/chengrui.png");
    enemyface.Sprite.setScale(1, 1);
    enemyface.Sprite.setPosition(WIDTH / 2 - enemyface.Width / 2 + 10, 110);
    playerface.setSprite("data/img/img_card/player.png");
    playerface.Sprite.setPosition(WIDTH / 2 - playerface.Width / 2 + 5,
                                  HEIGHT - playerface.Height * 2 - 10);

    // 法力水晶
    Crystal.setSprite("data/img/img_discord/power.png");
    Crystal.Sprite.setScale(0.7, 0.7);
    CrystalBG.setSprite("data/img/img_discord/crystal_bg.png", 1208, 966);
    CrystalBG.Sprite.setScale(2, 2);
    CrystalCount = 1;

    // 法力文字
    font_c.loadFromFile("data/ttf/yuanshen.ttf");
    std::stringstream ss;
    ss << CrystalCount << " / " << RoundCount;
    num_c.setString(ss.str());
    num_c.setFont(font);
    num_c.setCharacterSize(20);
    num_c.setColor(sf::Color::White);
    num_c.setPosition(1251, 1017);
}
// 绘制基本场景
void Initial_Draw()
{
    // 绘制背景
    window.draw(batter.Sprite);
    Round();
    // 画两个脸
    window.draw(enemyface.Sprite);
    window.draw(playerface.Sprite);
    // enemyface.txtFollow();
    // playerface.txtFollow();
    window.draw(GStart.Sprite);
    // 画法力水晶背景
    window.draw(CrystalBG.Sprite);
    window.draw(num_c);
    // 画法力水晶
    Crystal.Sprite.setPosition(1323, 1017);
    window.draw(Crystal.Sprite);

    StartM.play();

    // 绘制鼠标点，让你看的清楚
    CircleShape d(10);
    //绘制我的血量背景，不要被卡牌挡住了
    d.setRadius(70);
    d.setOrigin(d.getGlobalBounds().width / 2, d.getGlobalBounds().height / 2);
    d.setPosition(1145, 850);
    window.draw(d);
    //绘制叔叔的血量背景，不要被卡牌挡住了
    d.setRadius(70);
    d.setOrigin(d.getGlobalBounds().width / 2, d.getGlobalBounds().height / 2);
    d.setPosition(1145, 240);
    window.draw(d);
    char test1[100];

    window.display();
    // 睡个1秒钟
    sf::sleep(sf::seconds(2));
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
        window.draw(ERound.Sprite); // 用于修复按钮显示Bug
        window.display();
    }
    IsRoundChange = false;
    sf::sleep(sf::seconds(1));
    Draw();
    // 用于修复按钮显示Bug
    if (!IsYourRound)
    {
        window.draw(ERound.Sprite);
        window.display();
    }
    else
    {
        window.draw(YRound.Sprite);
        window.display();
    }
}

// 敌人的操作
void Enemy_Action()
{
    // 以下操作为敌人的操作
    // 从库中抽取牌
    if (RoundCount % 2 == 0)
    {
        Head = CardinHouse->next;
        Head1 = EnemyinFight;
        // 将这个卡牌插入到手牌当中
        if (Head1->length() < 7)
        {
            Head1->Insert(Head->val);
            // 下面这一串都是为了将这个节点从牌库中删除
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
            Head = Head->next;
            // 随机播放音频
            int suijishu = rand() * 2;
            if (suijishu == 0)
                SS1.play();
            else
                SS0.play();
        }
    }

    List *p = EnemyinFight->next;
    while (p)
    {
        srand((unsigned int)(time(NULL)));
        //随机一个数字，指定对方的，也就是自己的受害者
        Head1 = CardinFight->next;
        int r;
        //场上为空则直接攻击脸
        if (CardinFight->length() == 0)
            r = CardinFight->length();
        else
            r = rand() % (CardinFight->length() + 1);
        //如果生成overflow，则正好攻击我方的脸
        if (r == CardinFight->length())
        {
            playerface.HP -= p->val.ATK;
            Draw();
            Line(p->val.Sprite.getPosition().x + p->val.Width / 2,
                 p->val.Sprite.getPosition().y + p->val.Height / 2,
                 playerface.Sprite.getPosition().x + playerface.Width / 2,
                 playerface.Sprite.getPosition().y + playerface.Height / 2);
            window.display();
            p = p->next;
            sf::sleep(sf::milliseconds(700));
            continue;
        }
        //循环找到这个受害
        for (int i = 0; i < r; i++)
            Head1 = Head1->next;
        p->val.HP -= Head1->val.ATK;
        Head1->val.HP -= p->val.ATK;
        Draw();
        Line(p->val.Sprite.getPosition().x + p->val.Width / 2,
             p->val.Sprite.getPosition().y + p->val.Height / 2,
             Head1->val.Sprite.getPosition().x + Head1->val.Width / 2,
             Head1->val.Sprite.getPosition().y + Head1->val.Height / 2);
        window.display();
        sf::sleep(sf::milliseconds(700));
        p = p->next;
    }

    IsYourRound = true;
    IsRoundChange = true;
    //回合切换后，更新你的战斗次数
    Head = CardinFight;
    while (Head)
    {
        Head->val.attackTimes = 1;
        Head = Head->next;
    }
}

// 绘画
void Draw()
{
    // 绘制背景
    window.draw(batter.Sprite);

    // 判定按钮状态
    Round();

    // 画两个脸
    window.draw(enemyface.Sprite);
    window.draw(playerface.Sprite);
    // enemyface.txtFollow();
    // playerface.txtFollow();

    // 画法力水晶背景
    window.draw(CrystalBG.Sprite);
    window.draw(num_c);

    //画法力水晶
    for (int i = 0; i < CrystalCount; i++)
    {
        Crystal.Sprite.setPosition(1323 + i * 32, 1017);
        window.draw(Crystal.Sprite);
    }

    // 绘画手牌
    // 同时，规范手牌的位置
    Head = CardHand->next;
    while (Head)
    {
        if (isChooseCard == 1)
            break;
        for (int i = 1; i <= CardHand->length(); i++)
        {
            if (CardHand->length() % 2 == 0)
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (CardHand->length() / 2) + (i - 1) * 155,
                                             HEIGHT / 1.25);
            }
            else
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (CardHand->length() / 2) - 75 + (i - 1) * 155,
                                             HEIGHT / 1.25);
            }
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            // 下一个链表内容
            Head = Head->next;
        }
    }
    if (isChooseCard == 1)
    {
        for (int i = 1; i <= CardHand->length(); i++)
        {
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            // 下一个链表内容
            Head = Head->next;
        }
    }
    // 绘画战斗卡牌
    // 同时，规范战斗卡牌的位置
    Head = CardinFight->next;
    while (Head)
    {
        for (int i = 1; i <= CardinFight->length(); i++)
        {
            if (CardinFight->length() % 2 == 0)
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (CardinFight->length() / 2) + (i - 1) * 155,
                                             HEIGHT / 2.2);
            }
            else
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (CardinFight->length() / 2) - 75 + (i - 1) * 155,
                                             HEIGHT / 2.2);
            }
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            // 下一个链表内容
            Head = Head->next;
        }
    }
    // 绘画敌人卡牌
    // 同时，规范敌人卡牌的位置
    Head = EnemyinFight->next;
    while (Head)
    {
        for (int i = 1; i <= EnemyinFight->length(); i++)
        {
            if (EnemyinFight->length() % 2 == 0)
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (EnemyinFight->length() / 2) + 155 * (i - 1),
                                             HEIGHT / 4);
            }
            else
            {
                Head->val.Sprite.setPosition(WIDTH / 2 - 155 * (EnemyinFight->length() / 2) - 75 + 155 * (i - 1),
                                             HEIGHT / 4);
            }
            Card Q = Head->val;
            window.draw(Q.Sprite);
            Head->val.txtFollow();
            // 下一个链表内容
            Head = Head->next;
        }
    }
    // 画点直线，为了战斗卡牌攻击对方服务，我们不会做特效
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.Hold)
            LineTo(Head->val.Sprite.getPosition().x + Head->val.Width / 2, Head->val.Sprite.getPosition().y + Head->val.Height / 2);
        Head = Head->next;
    }
    // 绘制鼠标点，让你看的清楚
    CircleShape c(10);
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
    c.setPosition(mouse_world);
    window.draw(c);
    //绘制提醒文字
    Text txt(alertText, font, 100);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(WIDTH / 2, HEIGHT / 2);
    window.draw(txt);

    //绘制我的血量，不要被卡牌挡住了
    c.setRadius(70);
    c.setOrigin(c.getGlobalBounds().width / 2, c.getGlobalBounds().height / 2);
    c.setPosition(1145, 850);
    window.draw(c);
    char test[100];
    txt.setString(itoa(playerface.HP, test, 10));
    txt.setColor(sf::Color::Red);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(c.getPosition());
    window.draw(txt);
    //绘制叔叔的血量，不要被卡牌挡住了
    c.setRadius(70);
    c.setOrigin(c.getGlobalBounds().width / 2, c.getGlobalBounds().height / 2);
    c.setPosition(1145, 240);
    window.draw(c);
    char test1[100];
    txt.setString(itoa(enemyface.HP, test, 10));
    txt.setColor(sf::Color::Red);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(c.getPosition());
    window.draw(txt);

    //绘制游戏结束画面
    if (isGameOver)
    {
        if (Game_judge == 1)
        {
            Font font;
            font.loadFromFile("data/ttf/yuanshen.ttf");
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
        else
        {
            Font font;
            font.loadFromFile("data/ttf/yuanshen.ttf");
            Text win;
            win.setString("You Lose!");
            win.setFont(font);
            win.setCharacterSize(400);
            win.setColor(sf::Color::Red);
            window.draw(win);
            window.display();
            sf::sleep(sf::seconds(10));
            window.clear();
        }
    }

    // 判定回合改变
    if (IsRoundChange)
        Draw_Round();

    window.display();
}

// 逻辑判断函数
void Logic()
{
    // 更新法力水晶计数
    std::stringstream ss;
    if (RoundCount >= 10)
        ss << CrystalCount << " / " << 10;
    else
        ss << CrystalCount << " / " << RoundCount;
    num_c.setString(ss.str());

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

    // 运行敌人的操作和增加回合计数
    if (!IsYourRound && !IsPressed)
    {
        Enemy_Action();
        RoundCount++;
        NeedNewCard = true;
        if (RoundCount <= 10) // 法力水晶的总数小于10！！！
            CrystalCount = RoundCount;
    }

    // 抽取新的牌
    if (NeedNewCard)
    {
        // 从库中抽取牌
        Head = CardinHouse->next;
        while (Head && NeedNewCard)
        {
            // 将这个卡牌插入到手牌当中
            if (CardHand->length() >= 7)
                break;
            CardHand->Insert(Head->val);
            // 下面这一串都是为了将这个节点从牌库中删除
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
            NeedNewCard = false;
        }
        Head = Head->next;
    }

    // 判定游戏胜负
    //判定胜利 即为对方血量为空
    if (enemyface.HP <= 0)
    {
        isGameOver = true;
        Game_judge = 1;
    }
    //判定失败 即为自身血量为空
    if (playerface.HP <= 0)
    {
        isGameOver = true;
        Game_judge = 2;
    }
    // 判断*双方*卡牌死亡的问题
    Head = CardinFight;
    while (Head)
    {
        // 小心把头节点给删除了
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
        // 小心把头节点给删除了
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
}

// 左键单击
void LeftPress()
{
    // 回合切换
    if (YRound.isInclude() && IsYourRound == true)
        IsPressed = true;
    // 确保你只能选择一个卡牌，且是最上面的卡牌
    // 最上面的卡牌：即最后绘制的卡牌
    Head = CardHand;
    while (Head->next)
    {
        Head = Head->next;
    }
    if (isChooseCard == 0) // 鼠标上没有被抓手牌
    {
        while (Head)
        {
            if (Head->val.isInclude())
            {
                Head->val.Hold = 1;
                isChooseCard = 1;
                break;
            }
            Head = Head->prior;
        }
    }
    // 战斗卡牌点击后，产生面对敌方的预攻击直线
    // 这里Hold=1之后会在Draw()里面调用LineTo()函数
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.isInclude())
        {
            if (Head->val.attackTimes == 0)
            {
                //弹出文字，你已经攻击过一次了！！！
                alertCode = 1;
                Head = Head->next;
                continue;
            }
            Head->val.Hold = 1;
            break;
        }
        Head = Head->next;
    }
}
// 左键释放
void LeftReleased()
{
    //回合切换
    if (YRound_Down.isInclude() && IsYourRound == true)
    {
        IsPressed = false;
        IsYourRound = false;
        IsRoundChange = true;
    }
    // 当鼠标抓着手牌的时候↓
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
            if (CrystalCount - Head->val.Cost < 0)
            {
                alertCode = 2;
                break;
            }
            else
            {
                CrystalCount -= Head->val.Cost;
                if (Head->val.Order == '0')
                    JR0.play();
                if (Head->val.Order == '1')
                    JR1.play();
                if (Head->val.Order == '2')
                    JR2.play();
                if (Head->val.Order == '3')
                    JR3.play();
                if (Head->val.Order == '4')
                    JR4.play();
                if (Head->val.Order == '5')
                    JR5.play();
                if (Head->val.Order == '6')
                    JR6.play();
                if (Head->val.Order == '7')
                    JR7.play();
            }
            CardinFight->InsertBetween(Head->val);
            // 下面这一串都是为了将这个节点从手牌中删除
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
            //减少你的攻击次数
            --Head1->val.attackTimes;
            break;
        }
        Head = Head->next;
    }
    // 打脸！！！
    if (enemyface.isInclude() && isChooseCard == 2)
    {
        enemyface.HP -= Head1->val.ATK;
        --Head1->val.attackTimes;
    }
    // 当鼠标抓着手牌的时候↑
    Head = CardinFight;
    while (Head)
    {
        if (Head->val.Hold == 1)
            Head->val.Hold = 0;
        Head = Head->next;
    }

    isChooseCard = 0;
}
// 右键单击
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

// 输入函数
void Input()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            LeftPress();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            RightPress();
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            LeftReleased();
    }
}

int main()
{
    sf::Thread thread(&Alert);
    thread.launch();
    Start();
    Initial_Draw();

    // 游戏主循环
    while (window.isOpen() && isGameOver == false)
    {
        window.clear();

        Input();
        Logic();
        Draw();
    }
}
