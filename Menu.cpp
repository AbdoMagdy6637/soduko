#include "Menu.h"
#include<iostream>
#include "SFML/Graphics.hpp"
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "hello";
	}

	texture_Background.loadFromFile("backgroundimage.png");
	texture_Square.loadFromFile("square.png");

	texts[0].setFont(font);
	texts[0].setFillColor(sf::Color::White);
	texts[0].setString("Easy");
	texts[0].setPosition(sf::Vector2f(width /1.17, height / (MAX_NUMBER_OF_ITEMS + 1) * 0.5));

	texts[1].setFont(font);
	texts[1].setFillColor(sf::Color::White);
	texts[1].setString("Meduim");
	texts[1].setPosition(sf::Vector2f(width / 1.21, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	texts[2].setFont(font);
	texts[2].setFillColor(sf::Color::White);
	texts[2].setString("Hard");
	texts[2].setPosition(sf::Vector2f(width / 1.17, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));

	texts[3].setFont(font);
	texts[3].setFillColor(sf::Color::White);
	texts[3].setString("Restart");
	texts[3].setPosition(sf::Vector2f(width / 1.20, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	texts[4].setFont(font);
	texts[4].setFillColor(sf::Color::White);
	texts[4].setString("Exit");
	texts[4].setPosition(sf::Vector2f(width / 1.17, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));



	squares[0].setSize(sf::Vector2f(150, 50));
	squares[0].setPosition( width / 1.25, height / 13);
	squares[0].setTexture(&texture_Square);

	squares[1].setSize(sf::Vector2f(150, 50));
	squares[1].setPosition(width / 1.25, height / 6.3);
	squares[1].setTexture(&texture_Square);

	squares[2].setSize(sf::Vector2f(150, 50));
	squares[2].setPosition(width / 1.25, height / 4.1);
	squares[2].setTexture(&texture_Square);

	squares[3].setSize(sf::Vector2f(150, 50));
	squares[3].setPosition(width / 1.25, height / 3.1);
	squares[3].setTexture(&texture_Square);

	squares[4].setSize(sf::Vector2f(150, 50));
	squares[4].setPosition(width / 1.25, height / 2.45);
	squares[4].setTexture(&texture_Square);

	background.setSize(sf::Vector2f(width, height));
	background.setPosition(0, 0);
	background.setTexture(&texture_Background);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{

		window.draw(squares[i]);

	}
	
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		
		window.draw(texts[i]);
		
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		texts[selectedItemIndex].setFillColor(sf::Color::Black);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		texts[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		texts[selectedItemIndex].setFillColor(sf::Color::Black);
	}
}