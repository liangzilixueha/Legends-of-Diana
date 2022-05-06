/**************************************
-----------------card.h---------------------
product name：card
module name：card
date：2022.03.02
auther：none
file describe: none
***************************************/
#ifndef _CARD_H_
#define _CARD_H_

#ifdef __cplusplus // c++ include
extern "C"
#endif // include c++ file
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
    using namespace sf;
#define WIDTH 1920
#define HEIGHT 1114
sf::RenderWindow window(VideoMode(WIDTH, HEIGHT), "Legends of Diana");
sf::Event event;
int stringcmp(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}
//编写strcpy函数
void strcpy(char *a, char *b)
{
    int i = 0;
    while (b[i] != '\0')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}
//编写strlen函数
int strlen(char *a)
{
    int i = 0;
    while (a[i] != '\0')
    {
        i++;
    }
    return i;
}
//绝对值函数
double fabs(double a)
{
    if (a <= 0)
        return -a;
    else
        return a;
}
//这个函数是将字符串改为数字
//例如“156”->156
char *itoa(int num, char *str, int radix)
{ /*索引表*/
    char index[] = "0123456789ABCDEF";
    unsigned unum; /*中间变量*/
    int i = 0, j, k;
    /*确定unum的值*/
    if (radix == 10 && num < 0) /*十进制负数*/
    {
        unum = (unsigned)-num;
        str[i++] = '-';
    }
    else
        unum = (unsigned)num; /*其他情况*/
    /*转换*/
    do
    {
        str[i++] = index[unum % (unsigned)radix];
        unum /= radix;
    } while (unum);
    str[i] = '\0';
    /*逆序*/
    if (str[0] == '-')
        k = 1; /*十进制负数*/
    else
        k = 0;

    for (j = k; j <= (i - 1) / 2; j++)
    {
        char temp;
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
    return str;
}
//宏定义的字体类型，可以重复使用
sf::Font font;
//宏定义的文字类型，可以重复使用
sf::Text text;

//卡牌的类
struct Card
{
    //卡牌初始化的空函数
    Card() {}
    Card(int, int, int, char *s = "test");

    int HP;
    int ATK;
    int Cost;
    //战吼：当你使用时的效果
    int Battlecry;
    //嘲讽：必须现攻击具有嘲讽的卡牌
    int Taunt;
    //亡语：卡牌死亡后的效果
    int Deathrattle;
    //圣盾：免疫一次伤害
    int Divien_Shield;

    sf::Texture Texture;
    sf::Sprite Sprite;
    Vector2i mousePoint;
    double Width, Height;
    // Hold是个0/1变量，用于标识卡牌是否被抓住
    int Hold;
    int isInclude();
    void setCardFollowMouse();
    void changeHold();
    // moveFlag是个0/1变量，用于标识卡牌是否正在移动
    // moveTo()函数中会使用此变量来判断移动的结束与否
    int moveFlag;
    void moveTo(double x, double y, double speed = 40);
    // state是一个 卡牌 的状态变量
    // 0 在你的《卡牌库》中
    // 1 在你的《手牌》中
    // 2 在你的《选中》中
    // 3 在你的《战斗》中
    // 4 在你的《死亡》牌库中
    int state;
    char *name;
    void txtFollow();
    void setSprite(char *);

    //攻击次数
    int attackTimes;
};
//由于我们不需要关注纹理的大小和位置，所以我们可以将其设置为默认值
//如此以来，我们只需要设置一次，这样能减少赋值的次数
void Card::setSprite(char *s)
{
    Texture.loadFromFile(s);
    Sprite.setTexture(Texture);
    Width = Texture.getSize().x;
    Height = Texture.getSize().y;
}
//这个函数是用来让你的文字
//跟随！你的卡牌
//包括卡牌的名字，血量，简介，消耗值，攻击力
// 参数：-99意味着绘制对应的文字
// 4.23 让你的真正的图片跟随着主图片
void Card::txtFollow()
{
    Width = Texture.getSize().x * Sprite.getScale().x;
    Height = Texture.getSize().y * Sprite.getScale().y;
    font.loadFromFile("data/ttf/yuanshen.ttf");
    text.setFont(font);
    // 如果是头节点，那就别画画了
    if (Cost == 0 && ATK == 0 && HP == 0)
        return;
    if (stringcmp(name, "chenrui") == 0 || !stringcmp(name, "player"))
        text.setColor(sf::Color::Red);
    else
        text.setColor(sf::Color::White);
    int txtsize = 40;
    char s[99];
    //消耗值
    if (Cost != -99)
    {
        text.setString(itoa(Cost, s, 10));
        text.setPosition(Sprite.getPosition().x + 20, Sprite.getPosition().y + 5);
        text.setCharacterSize(txtsize);
        window.draw(text);
    }
    //攻击力
    if (ATK != -99)
    {
        text.setString(itoa(ATK, s, 10));
        text.setPosition(Sprite.getPosition().x + 20, Sprite.getPosition().y + Height - 50);
        text.setCharacterSize(txtsize);
        window.draw(text);
    }
    //血量
    text.setString(itoa(HP, s, 10));
    text.setPosition(Sprite.getPosition().x + Width - 30, Sprite.getPosition().y + Height - 50);
    text.setCharacterSize(txtsize);
    window.draw(text);
    //名字
    text.setString(name);
    text.setCharacterSize(20);
    text.setPosition(Sprite.getPosition().x + Width / 2 - 25, Sprite.getPosition().y + Height / 2);
    window.draw(text);
}
//这个是移动函数
//其中speed是移动速度，默认为40.数值越大越快
// x是目标坐标X，y是目标坐标Y
//**但是*，该函数依然有不完善的地方
//当合法误差为1，而speed作产生的位移大于1时，就有距离目标的较大误差的结果
//需要完善！！！
void Card::moveTo(double x, double y, double speed)
{
    double originalX, originalY;
    originalX = Sprite.getPosition().x;
    originalY = Sprite.getPosition().y;
    double speedX, speedY;
    speedX = (x - originalX);
    speedY = (y - originalY);
    double k = speedY / speedX;
    //当函数执行时，卡牌速度太快可能跳过判定区间从而无限往复运动
    //为了解决这个问题，用两个为坐标的flag，判定只要有一次正负变化，就停止运动
    int flagX, flagY;
    if (x > originalX)
        flagX = 1;
    else
        flagX = 0;
    if (y > originalY)
        flagY = 1;
    else
        flagY = 0;
    if (fabs(x - originalX) > 0.1)
    {
        Sprite.setPosition(originalX + speed * fabs(speedX) / (speedX), originalY + speed * fabs(speedX) / (speedX)*k);
        if (flagX && x < Sprite.getPosition().x)
            moveFlag = 0;
        if (flagY && y < Sprite.getPosition().y)
            moveFlag = 0;
        if (!flagX && x > Sprite.getPosition().x)
            moveFlag = 0;
        if (!flagY && y > Sprite.getPosition().y)
            moveFlag = 0;
    }
    else
    {
        moveFlag = 0;
    }
}
// 这个函数返回的是0/1，判断鼠标的点击是否在卡牌的范围之内
// 当你使用它之后，记得要改变你的
//**Hold*
//值
int Card::isInclude()
{
    Width = Texture.getSize().x;
    Height = Texture.getSize().y;
    mousePoint = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
    double x = mousePoint.x;
    double y = mousePoint.y;
    if (x - Sprite.getPosition().x < Width && x - Sprite.getPosition().x > 0 && y - Sprite.getPosition().y < Height && y - Sprite.getPosition().y > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// 初始化你的卡牌，参数的顺序是
//费用，攻击力，血量，名字(默认为test)
//注意！名字不能有中文！
//当你的名字为"n"时，便不会绘制名字
Card::Card(int cost, int atk, int hp, char *namee)
{
    Cost = cost;
    HP = hp;
    ATK = atk;
    Battlecry = 0;
    Taunt = 0;
    Deathrattle = 0;
    Divien_Shield = 0;
    Hold = 0;
    moveFlag = 0;
    state = 0;
    attackTimes = 1;
    //将名字赋值给name
    name = new char[strlen(namee) + 1];
    if (namee[0] != 'n')
        strcpy(name, namee);
    else
        strcpy(name, "");
}
// 让你的卡牌跟随你的鼠标
// 但是鼠标会在卡牌的*正中间*
void Card::setCardFollowMouse()
{
    mousePoint = (Vector2i)window.mapPixelToCoords(Mouse::getPosition(window));
    Card::Sprite.setPosition(mousePoint.x - Width / 2, mousePoint.y - Height / 2);
}
// 只是改变你的Hold值罢了
//从0到1，从1到0
void Card::changeHold()
{
    if (Hold == 1)
        Hold = 0;
    else
        Hold = 1;
}
//一个图片的结构体
struct Img
{
    sf::Texture Texture;
    sf::Sprite Sprite;
    void setSprite(char *, int x = 0, int y = 0);
};
//快捷设置你的图片，一键设置你的坐标，默认为0，0
void Img::setSprite(char *path, int x, int y)
{
    Texture.loadFromFile(path);
    Sprite.setTexture(Texture);
    Sprite.setPosition(x, y);
}
#ifdef __cpluscplus
#endif
#endif // end _LIST_H
