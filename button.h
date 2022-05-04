#pragma once
#include<SFML/Graphics.hpp>
struct Button{
    sf::Texture Texture;
    sf::Sprite Sprite;
    void setSprite(char*,int x=0,int y=0);
};
//快捷设置你的图片，一键设置你的坐标，默认为0，0
void Button::setSprite(char *path, int x, int y)
{
    Texture.loadFromFile(path);
    Sprite.setTexture(Texture);
    Sprite.setPosition(x,y);
}