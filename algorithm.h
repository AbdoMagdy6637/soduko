#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class algorithm
{
public:
	int i;
	algorithm();
	bool win(int arr[9][9]);
	bool lineValide(int m[9][9], int line, int val);
	bool columnValide(int m[9][9], int column, int val);
	bool boxValide(int m[9][9], int line, int column, int val);
	void change(Text arr[9][9], int arr2[9][9]);

};

