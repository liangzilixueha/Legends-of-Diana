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
double fabs(double a)
{
    if (a <= 0)
        return -a;
    else
        return a;
}
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
sf::Font font;
struct Card
{
    Card() {}
    Card(int xx, int x, int y);
    int HP;
    int ATK;
    int Cost;
    int Battlecry;
    int Taunt;
    int Deathrattle;
    int Divien_Shield;
    // The Img
    sf::Texture Texture;
    // The Img
    sf::Sprite Sprite;
    // Width is the Sprite's width,also the Height;
    double Width, Height;
    int Hold;
    int isInclude();
    void setCardFollowMouse();
    void changeHold();

    int moveFlag;
    void moveTo(double x, double y, double time = 3);
    // state need a specific introduce
    // 0 is in you room
    // 1 is in you hand
    // 2 is in mouse choosing
    // 3 is fight
    // 4 is dead
    int state;

    // Text hp_txt;
    // Text atk_txt;
    // Text brief_txt;
    // Text cost_txt;
    // Text name_txt;
    //这个函数是用来让你的文字
    //跟随！你的卡牌
    //包括卡牌的名字，血量，简介，消耗值，攻击力
    // void txtFollow()
    // {
    //     char s[99];
    //     font.loadFromFile("wryh.ttf");

    //     hp_txt.setFont(font);
    //     // atk_txt.setFont(font);
    //     // brief_txt.setFont(font);
    //     // cost_txt.setFont(font);
    //     // name_txt.setFont(font);

    //     hp_txt.setString(itoa(HP, s, 10));
    //     // atk_txt.setString(itoa(HP, s, 10));
    //     // brief_txt.setString(itoa(HP, s, 10));
    //     // cost_txt.setString(itoa(HP, s, 10));
    //     // name_txt.setString(itoa(HP, s, 10));

    //     hp_txt.setPosition(Sprite.getPosition());
    //     window.draw(hp_txt);
    // }
};
///////////////////////////////
//////////this is function/////
///////////////////////////////

// this first is X,then is Y,the last is moving time,and the time is 0.3s for default
// And 0.3s is 18;
// OK,0.3s is useless ,plz don's use it ,it is not used in this function
void Card::moveTo(double x, double y, double time)
{
    double originalX, originalY;
    originalX = Sprite.getPosition().x;
    originalY = Sprite.getPosition().y;
    double speedX, speedY;
    speedX = (x - originalX);
    speedY = (y - originalY);
    double k = speedY / speedX;
    if (fabs(x - originalX) > 1)
    {
        Sprite.setPosition(originalX + fabs(speedX) / (speedX), originalY + fabs(speedX) / (speedX)*k);
    }
    else
    {
        moveFlag = 0;
    }
}
// 这是一个非常重要的函数
// 这个函数返回的是0/1，判断鼠标的点击是否在卡牌的范围之内
int Card::isInclude()
{
    Width = Texture.getSize().x;
    Height = Texture.getSize().y;
    double x, y;
    x = sf::Mouse::getPosition(window).x;
    y = sf::Mouse::getPosition(window).y;
    if (x - Sprite.getPosition().x < Width && x - Sprite.getPosition().x > 0 && y - Sprite.getPosition().y < Height && y - Sprite.getPosition().y > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// 初始化你的卡牌
Card::Card(int xx, int x, int y)
{
    Cost = xx;
    HP = y;
    ATK = x;
    Battlecry = 0;
    Taunt = 0;
    Deathrattle = 0;
    Divien_Shield = 0;
    Hold = 0;
    moveFlag = 0;
    font.loadFromFile("wryh.ttf");

    // hp_txt.setFont(font);
    // atk_txt.setFont(font);
    // brief_txt.setFont(font);
    // cost_txt.setFont(font);
    // name_txt.setFont(font);
    char s[99];
    // hp_txt.setString(itoa(HP, s, 10));
    // atk_txt.setString(itoa(HP, s, 10));
    // brief_txt.setString(itoa(HP, s, 10));
    // cost_txt.setString(itoa(HP, s, 10));
    // name_txt.setString(itoa(HP, s, 10));

    // hp_txt.setPosition(Sprite.getPosition());

}
// 让你的卡牌跟随你的鼠标
void Card::setCardFollowMouse()
{
    Card::Sprite.setPosition(sf::Mouse::getPosition(window).x - Width / 2, sf::Mouse::getPosition(window).y - Height / 2);
    // printf("%f %f\n", Sprite.getPosition().x, Sprite.getPosition().y);
}
// 只是改变你的Hold值罢了
void Card::changeHold()
{
    if (Hold == 1)
        Hold = 0;
    else
        Hold = 1;
}
struct Img
{
    sf::Texture Texture;
    sf::Sprite Sprite;
};
#ifdef __cpluscplus
#endif
#endif // end _LIST_H
