#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

struct timer
{
	sf::Clock mC;
	float runTime;
	bool bPaused;
	timer()
	{
		bPaused = false;
		runTime = 0;
		mC.restart();
	}

    void reset()
    {
        mC.restart();
        runTime = 0;
        bPaused = false;
    }
    // Resumes the clock
    void resume()
    {
        if (bPaused)
        {
            mC.restart();
        }
        bPaused = false;
    }
    //Pauses the clock
    void pause()
    {
        if (!bPaused)
        {
            runTime += mC.getElapsedTime().asSeconds();
        }
        bPaused = true;
    }
    // Returns the elapsed seconds
    float getElapsedSeconds()
    {
        if (!bPaused)
        {
            return runTime + mC.getElapsedTime().asSeconds();
        }
        return runTime;
    }
    //Return a string representation of the elapsed time
    string getElapsedTime()
    {
        string time;
        int seconds = int(getElapsedSeconds());
        time = to_string(seconds);

        return time;
    }

};

class score
{

public:
    	
	void resume();
	void pause();
	timer time;
	Text nums[9][9];
	

    score();
	~score();
};

