#include <SFML/Graphics.hpp>
using namespace sf;
class algorithm
{
	
public:
	int m[9][9];
	algorithm();
	bool win(int arr[9][9]);
	bool lineValide( int line, int column, int val);
	bool columnValide(int line ,int column, int val);
	bool boxValide( int line, int column, int val);
	bool valid(int line, int column, int val);
	void change(Text arr[9][9]);

};

