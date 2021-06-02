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
	
public:
	void set_solve(string game_diff);
	int check_finish(int sec, string game_diff);
	int save_file(int save_time, string game_diff);
	RectangleShape Focus;
	XY Focus_Pos;
	Text nums[9][9];
	game_frame(int width, int height);
	Sprite get_Num();
	Text get_Text(int j,int i);
	void set_Text(int j, int i, char c, string s, string game_diff);
	void set_Mid();
	void set_Easy();
	void set_Hard();
	string set_Rank();
	RectangleShape get_Focus();
	void set_num(int x,int y);
	~game_frame();
};

