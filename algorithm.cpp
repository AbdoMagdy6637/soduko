#include "algorithm.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
algorithm::algorithm() 
{ 
	i = 0;
}

bool algorithm::win(int arr[9][9])
{
	bool num[9] = {};
	bool flag = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			num[x] = 0;
		}
		for (int j = 0; j < 9; j++)
		{
			for (int x = 0; x < 9; x++)
			{

				if (arr[i][j] == x + 1)
					num[x] = 1;
			}
		}
		for (int x = 0; x < 9; x++)
		{
			if (num[x] == 0)
				flag = 0;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int x = 0; x < 9; x++)
		{
			num[x] = 0;
		}
		for (int j = 0; j < 9; j++)
		{
			for (int x = 0; x < 9; x++)
			{
				if (arr[j][i] == x + 1)
					num[x] = 1;
			}
		}
		for (int x = 0; x < 9; x++)
		{
			if (num[x] == 0)
				flag = 0;
		}
	}
	for (int i = 0; i < 7; i += 3)
	{
		for (int j = 0; j < 7; j += 3)
		{
			for (int x = 0; x < 9; x++)
			{
				num[x] = 0;
			}
			for (int a = i; a < i + 3; a++)
			{
				for (int b = j; b < j + 3; b++)
				{
					for (int x = 0; x < 9; x++)
					{
						if (arr[i][j] == x + 1)
							num[x] = 1;

					}
				}
			}
			for (int x = 0; x < 9; x++)
			{
				if (num[x] == 0)
					flag = 0;
			}
		}
	}
	return flag;
}

bool algorithm::lineValide(int m[9][9], int line, int val)
{
	for (int i = 0; i < 9; i++)
	{
		if (m[line][i] == val)
		{
			return false;
		}
	}
	return true;
}
bool algorithm::columnValide(int m[9][9], int column, int val)
{
	for (int i = 0; i < 9; i++)
	{
		if (m[i][column] == val)
		{
			return false;
		}
	}
	return true;
}
bool algorithm::boxValide(int m[9][9], int line, int column, int val)
{
	int y = line / 3;
	int x = column / 3;
	y = y * 3;
	x = x * 3;

	for (int i = y; i < y + 3; i++) {
		for (int j = x; j < x + 3; j++) {
			if (m[i][j] == val)
			{
				return false;
			}
		}
	}
	return true;

}

void algorithm::change(Text arr[9][9], int arr2[9][9]) {
	string s;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			s = arr[i][j].getString();
			arr2[i][j] = atoi(s.c_str());
		}
	}

}