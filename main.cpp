#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_frame.h"
#include<stack>
#include<string>
#include <cstdlib>
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
    bool Mouse_Flag=true,focus_Flag=false,stop=false;
    int Hieght=500, Width = 650,x_Pos=200,y_Pos=200;
    
    game_frame frame(Width,Hieght);
    stack <Undo> undo;
    Undo temp;

    sf::RenderWindow window(sf::VideoMode(Width,Hieght), "Soduko game");

    while (window.isOpen())
    {
        sf::Event event;
        Mouse mouse;
        window.setPosition(Vector2i(x_Pos,y_Pos));
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                focus_Flag = true;
                Mouse_Flag = true;
                frame.set_num(mouse.getPosition().x - x_Pos - 23, mouse.getPosition().y - y_Pos - 50);
            }
            if (event.type == Event::TextEntered)
            {
                if(Mouse_Flag)
                if (event.text.unicode < 60)
                {
                    Mouse_Flag = false;
                    focus_Flag = false;
                    if (!stop)
                    {
                        temp.value = frame.get_Text(frame.Focus_Pos.x, frame.Focus_Pos.y).getString()[0];
                        temp.x = frame.Focus_Pos.x;
                        temp.y = frame.Focus_Pos.y;
                        undo.push(temp);
                        stop = true;
                    }
                    temp.value = frame.get_Text(frame.Focus_Pos.x, frame.Focus_Pos.y).getString()[0];
                    frame.set_Text(frame.Focus_Pos.x, frame.Focus_Pos.y, event.text.unicode);
                    
                    temp.x = frame.Focus_Pos.x;
                    temp.y = frame.Focus_Pos.y;
                    undo.push(temp);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
                if (!undo.empty())
                {
                    frame.set_Text(undo.top().x, undo.top().y, undo.top().value);
                    undo.pop();
                }
        }
        window.clear();
        window.draw(frame.get_Num());
        if (focus_Flag)
            window.draw(frame.get_Focus());
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                window.draw(frame.get_Text(j,i));
            }
        }
        
        window.display();
    }

    return 0;
}