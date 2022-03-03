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
{
#endif // include c++ file
#include <stdio.h>
#include <SFML/Graphics.hpp>
    // macro define
    struct Card
    {
        int HP;
        int ATK;
        Card(int x, int y);
        void HP_val();
        void ATK_val();
        int Battlecry;
        int Taunt;
        int Deathrattle;
        int Divien_Shield;
        void isBattlecry();
        void isTaunt();
        void isDeathrattle();
        void isDivien_Shield();
        sf::Texture Texture;
        sf::Sprite Sprite;
        double Width, Height;
        int Hold;
        int isHold();
    };

    // variable
    int Card::isHold()
    {
        Width = Texture.getSize().x;
        Height = Texture.getSize().y;
        double x, y;
        x = sf::Mouse::getPosition().x;
        y = sf::Mouse::getPosition().y;
        if (x - Sprite.getPosition().x < Width && x - Sprite.getPosition().x > 0 && y - Sprite.getPosition().y < Height && y - Sprite.getPosition().y > 0)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    // first is ATK,last is HP;
    Card::Card(int x, int y)
    {
        HP = y;
        ATK = x;
        Battlecry = 0;
        Taunt = 0;
        Deathrattle = 0;
        Divien_Shield = 0;
        Hold=0;
    }
    void Card::ATK_val()
    {
        printf("this's ATK is %d\n", ATK);
    }
    void Card::HP_val()
    {
        printf("this's HP is %d\n", HP);
    }

    struct Img
    {
        sf::Texture Texture;
        sf::Sprite Sprite;
    };
#ifdef __cpluscplus
}
#endif

#endif // end _CARD_H_
}