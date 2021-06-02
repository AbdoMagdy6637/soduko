#include "menu.h"
#include<iostream>
#include "SFML/Graphics.hpp"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "hello";
	}

	texture_Square.loadFromFile("square.png");
	btn1.loadFromFile("btn1.png");
	btn2.loadFromFile("btn2.png");
	btn3.loadFromFile("btn3.png");
	btn4.loadFromFile("btn4.png");
	


	texts[0].setFont(font);
	texts[0].setFillColor(sf::Color::White);
	texts[0].setString("Easy");
	texts[0].setPosition(sf::Vector2f(width / 1.24, height / (MAX_NUMBER_OF_ITEMS + 1) * 0.5));

	texts[1].setFont(font);
	texts[1].setFillColor(sf::Color::White);
	texts[1].setString("Meduim");
	texts[1].setPosition(sf::Vector2f(width / 1.29, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.3));

	texts[2].setFont(font);
	texts[2].setFillColor(sf::Color::White);
	texts[2].setString("Hard");
	texts[2].setPosition(sf::Vector2f(width / 1.24, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.1));

	texts[3].setFont(font);
	texts[3].setFillColor(sf::Color::White);
	texts[3].setString("Restart");
	texts[3].setPosition(sf::Vector2f(width / 1.28, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.9));

	texts[4].setFont(font);
	texts[4].setFillColor(sf::Color::White);
	texts[4].setString("Exit");
	texts[4].setPosition(sf::Vector2f(width / 1.24, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.8));



	squares[0].setSize(sf::Vector2f(150, 50));
	squares[0].setPosition(width / 1.35, height / 13);
	squares[0].setTexture(&btn1);

	squares[1].setSize(sf::Vector2f(150, 50));
	squares[1].setPosition(width / 1.35, height / 5);
	squares[1].setTexture(&btn2);

	squares[2].setSize(sf::Vector2f(150, 50));
	squares[2].setPosition(width / 1.35, height / 3);
	squares[2].setTexture(&btn3);

	squares[3].setSize(sf::Vector2f(150, 50));
	squares[3].setPosition(width / 1.35, height / 2.13);
	squares[3].setTexture(&btn4);

	squares[4].setSize(sf::Vector2f(150, 50));
	squares[4].setPosition(width / 1.35, height / 1.62);
	squares[4].setTexture(&texture_Square);
	selectedItemIndex = 0;
}


Menu::~Menu()
{

}


void Menu::draw(sf::RenderWindow& window)
{
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