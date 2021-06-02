#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	void drawTime(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text texts[MAX_NUMBER_OF_ITEMS];
	sf::Text timeText;
	sf::Texture texture_Square;
	sf::Texture btn1;
	sf::Texture btn2;
	sf::Texture btn3;
	sf::Texture btn4;
	sf::RectangleShape squares[MAX_NUMBER_OF_ITEMS];

};

