#include "score.h"
bool paused = false;

score::score() {
	
}

void score::pause()
{
    paused = true;
    time.pause();
	
}
void score::resume()
{
    paused = false;
    time.resume();
}

score::~score()
{

}