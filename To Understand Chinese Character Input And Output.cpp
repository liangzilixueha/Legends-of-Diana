#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(500,500),"test");
	sf::String buffer;
	Text t;
	Font f;
	f.loadFromFile("simsun.ttc");
	t.setFont(f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
				window.close();
				break;
			case sf::Event::EventType::TextEntered:
				if (event.text.unicode != 8 && event.text.unicode != 13)
				{
					window.clear();
					buffer += event.text.unicode;
					t.setPosition(0, 0);
					t.setString(buffer);
					window.draw(t);
					window.display();
				}
				break;
			case sf::Event::EventType::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::Return)
				{
					std::basic_ofstream<Uint8> out;
					std::basic_ifstream<Uint8> in;
					std::basic_string<Uint8> s;
					s = buffer.toUtf8();
					// out.open("text.txt");
					// out << s;
					// out.close();
					in.open("text.txt");
					in >> s;
					in.close();
			
					window.clear();
					t.setPosition(0, 0);
					buffer.clear();
					buffer = String::fromUtf8(s.begin(), s.end());
					t.setString(buffer);
					window.draw(t);
					window.display();

					std::cout << "Enter Pressed" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Key::BackSpace)
				{
					window.clear();
					if (buffer.getSize() != 0)
						buffer.erase(buffer.getSize() - 1, 1);
					t.setPosition(0, 0);
					t.setString(buffer);
					
					window.draw(t);
					window.display();

					std::cout << "BackSpace Pressed" << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
	return 0;
}