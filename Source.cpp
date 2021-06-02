#include <SFML/Graphics.hpp>
#include <iostream>
#include<stack>
#include<string>
#include <cstdlib>
#include "game_frame.h"
#include "Menu.h"
#include"algorithm.h"
#include"score.h"
using namespace std;
using namespace sf;

struct Undo
{
	char value;
	int x;
	int y;
};

int main()
{
	bool Mouse_Flag = true, focus_Flag = false, stop = false, stop_save = false, valid = true;
	int Hieght = 500, Width = 650, x_Pos = 200, y_Pos = 200, def = 0;

	int restartButtonPressed = 0;

	game_frame frame(Width, Hieght);
	algorithm algo;
	stack <Undo> undo;
	stack <Undo> redo;
	Undo temp;
	//abdo
	score save_score;
	string gameTime;
	string game_diff;
	//abdo

	sf::RenderWindow window(sf::VideoMode(Width, Hieght), "Soduko game");

	Menu menu(window.getSize().x, window.getSize().y);

	Texture texture_Background;
	RectangleShape background;
	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setPosition(0, 0);
	background.setTexture(&texture_Background);
	texture_Background.loadFromFile("full_background.png");


	while (window.isOpen())
	{
		sf::Event event;
		Mouse mouse;
		window.setPosition(Vector2i(x_Pos, y_Pos));
		//abdo save_score
		Font font;
		font.loadFromFile("consola.ttf");

		Text timeText = Text(save_score.time.getElapsedTime() + " sec", font, 25);
		timeText.setFillColor(Color::White);
		timeText.setPosition({ 500, 400 });

		Text rank = Text("rank : "+frame.set_Rank(), font, 25);
		rank.setFillColor(Color::White);
		rank.setPosition({ 500, 450 });

		Text diff = Text(game_diff + " game", font, 25);
		diff.setFillColor(Color::White);
		diff.setPosition({ 50, 450 });
		
		//abdo save_score
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				focus_Flag = true;
				Mouse_Flag = true;
				valid = true;
				frame.set_num(mouse.getPosition().x - x_Pos - 23, mouse.getPosition().y - y_Pos - 50);

			}
			if (event.type == Event::TextEntered)
			{
				if (Mouse_Flag)
					if (event.text.unicode < 60)
					{
						Mouse_Flag = false;
						focus_Flag = false;

						temp.value = frame.get_Text(frame.Focus_Pos.x, frame.Focus_Pos.y).getString()[0];
						temp.x = frame.Focus_Pos.x;
						temp.y = frame.Focus_Pos.y;
						undo.push(temp);

						frame.set_Text(frame.Focus_Pos.x, frame.Focus_Pos.y, event.text.unicode, save_score.time.getElapsedTime(), game_diff);
						temp.value = frame.get_Text(frame.Focus_Pos.x, frame.Focus_Pos.y).getString()[0];
						if (!redo.empty())
							redo.pop();
						redo.push(temp);
						string s = frame.get_Text(frame.Focus_Pos.x, frame.Focus_Pos.y).getString();

						algo.change(frame.nums);
						valid = algo.valid(frame.Focus_Pos.x, frame.Focus_Pos.y, atoi(s.c_str()));
					}
			}
			switch (event.type)
			{
			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Up:

					menu.MoveUp();
					break;

				case sf::Keyboard::Down:

					menu.MoveDown();
					break;
				case sf::Keyboard::U:
					if (!undo.empty())
					{
						temp.value = frame.get_Text(undo.top().x, undo.top().y).getString()[0];
						temp.x = undo.top().x;
						temp.y = undo.top().y;
						frame.set_Text(undo.top().x, undo.top().y, undo.top().value, save_score.time.getElapsedTime(), game_diff);//abdo save_score
						std::cout << undo.top().x << " " << undo.top().y << " " << undo.top().value;
						redo.push(temp);
						undo.pop();
					}
					break;
				case sf::Keyboard::Y:
					if (!redo.empty())
					{
						temp.value = frame.get_Text(redo.top().x, redo.top().y).getString()[0];
						temp.x = redo.top().x;
						temp.y = redo.top().y;
						frame.set_Text(redo.top().x, redo.top().y, redo.top().value, save_score.time.getElapsedTime(), game_diff);//abdo save_score
						undo.push(temp);
						redo.pop();

					}
					break;
				case sf::Keyboard::Return:

					switch (menu.GetPressedItem())
					{
					case 0://Easy
						std::cout << "Easy button has been pressed" << "\n\n";
						game_diff = "easy";//abdo save_score
						frame.set_Easy();
						def = 1;
						save_score.time.reset();//abdo save_score
						stop_save = 0;//abdo save_score
						break;
					case 1://Meduim
						std::cout << "Meduim button has been pressed" << "\n\n";
						game_diff = "medium";//abdo save_score
						frame.set_Mid();
						def = 2;
						save_score.time.reset();//abdo save_score
						stop_save = 0;//abdo save_score
						break;
					case 2://Hard
						std::cout << "Hard button has been pressed" << "\n\n";
						game_diff = "hard";//abdo save_score
						frame.set_Hard();
						def = 3;
						save_score.time.reset();//abdo save_score
						stop_save = 0;//abdo save_score
						break;
					case 3://Restart
						restartButtonPressed = 1;
						break;
					case 4://Exit
						window.close();
						break;
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Return) && restartButtonPressed == 1)
		{
			if (!undo.empty())
			{
				frame.set_Text(undo.top().x, undo.top().y, undo.top().value, save_score.time.getElapsedTime(), game_diff);
				undo.pop();
			}
		}
		//abdo save_score
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			frame.set_solve(game_diff);
			if (stop_save == 0) {
				stop_save = true;
				frame.check_finish(stoi(save_score.time.getElapsedTime()), game_diff);
			}
			save_score.time.pause();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::P))
		{
			save_score.time.pause();

		}
		if (Keyboard::isKeyPressed(Keyboard::Key::R))
		{
			save_score.time.resume();
		}

		//abdo save_score
		window.clear();

		window.draw(background);
		window.draw(frame.get_Num());
		if (focus_Flag)
			window.draw(frame.get_Focus());
		if (!valid && def < 3)
		{
			frame.Focus.setFillColor(Color::Red);
			window.draw(frame.get_Focus());
		}
		else
			frame.Focus.setFillColor(Color::Green);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				window.draw(frame.get_Text(j, i));
			}
		}

		menu.draw(window);
		window.draw(diff);//abdo save_score
		window.draw(rank);//abdo save_score
		window.draw(timeText);//abdo save_score
		window.display();
	}

	return 0;
}