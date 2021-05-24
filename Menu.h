#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text texts[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture_Square , texture_Background;
	sf::RectangleShape squares [MAX_NUMBER_OF_ITEMS],background;

};

