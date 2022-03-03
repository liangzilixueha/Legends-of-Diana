#include <SFML/Graphics.hpp>
#include "card.h"
#define WIDTH 1920
#define HEIGHT 1114
using namespace sf;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Legends of Diana");
Img batter;
Card l(2, 3);
Image a;
void Start()
{
    batter.Texture.loadFromFile("img/batter.jpg");
    batter.Sprite.setTexture(batter.Texture);
    batter.Sprite.setScale(2, 2);

    l.Texture.loadFromFile("img/l.png");
    l.Sprite.setTexture(l.Texture);
}
void Draw()
{
    window.draw(batter.Sprite);
    window.draw(l.Sprite);
}
int x=0;
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
                if(l.isHold())
                {
                    if(l.Hold) l.Hold=0;
                    if(!l.Hold) l.Hold=1;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                printf("Right is press\n");
            }
        }
        if(l.Hold) l.Sprite.setPosition(sf::Mouse::getPosition().x-90, sf::Mouse::getPosition().y-70);
        window.clear();
        Draw();
        window.display();
    }
    return 0;
}