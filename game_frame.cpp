#include "game_frame.h"
game_frame::game_frame(int width,int height)
{
	boredTex.loadFromFile("bored.png");
	bored.setTexture(boredTex);
	bored.setPosition(0,0) ;
	bored.setScale(2, 2);
	font.loadFromFile("consola.ttf");
	
	Focus.setSize(Vector2f(45,48));
	Focus.setFillColor(Color::Green);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			nums[j][i].setFont(font);
			nums[j][i].setFillColor(Color::Blue);
			nums[j][i].setCharacterSize(30);
			nums[j][i].setPosition(46 * i  +32, 46 * j +25 );
			nums[j][i].setString("4");
			nums[j][i].Bold;
		}
	}
}
void game_frame::set_num(int x,int y)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (x+32 > nums[j][i].getPosition().x && x+32 < nums[j][i].getPosition().x + 46)
			{
				if (y+25 > nums[j][i].getPosition().y && y+25 < nums[j][i].getPosition().y + 46)
				{

					Focus_Pos.x = j;
					Focus_Pos.y = i;
					
				}
			}
		}
	}
}
RectangleShape game_frame::get_Focus()
{
	Focus.setPosition(Vector2f(nums[Focus_Pos.x][Focus_Pos.y].getPosition().x-12, nums[Focus_Pos.x][Focus_Pos.y].getPosition().y -8));
	return Focus;
}
void game_frame::set_Text(int j, int i,char c)
{
	nums[j][i].setString(c);
}
Text game_frame::get_Text(int j,int i)
{
	return nums[j][i];
}
Sprite game_frame::get_Num()
{
	return bored;
}
game_frame::~game_frame()
{

}