#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;
using namespace sf;
struct XY
{
	int x;
	int y;
};
class game_frame
{
	Texture boredTex;
	Sprite bored;
	Font font;
	Text nums[9][9];
	RectangleShape Focus;
	
public:
	XY Focus_Pos;
	game_frame(int width, int height);
	Sprite get_Num();
	Text get_Text(int j,int i);
	void set_Text(int j, int i,char c);
	RectangleShape get_Focus();
	void set_num(int x,int y);
	~game_frame();
};

