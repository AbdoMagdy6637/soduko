#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Menu.h"
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML WORK!");
	
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Easy button has been pressed" <<"\n\n";
						break;
					case 1:
						std::cout << "Meduim button has been pressed" <<"\n\n";
						break;
					case 2:
						std::cout << "Hard button has been pressed" << "\n\n";
						break;
					case 3:
						std::cout << "Restart button has been pressed "<<"\n\n";
						break;
					case 4:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
		menu.draw(window);
		window.display();
	}
}