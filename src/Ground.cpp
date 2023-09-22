#include "Ground.h"
#include <ofAppRunner.h>


void Ground::change_ground_height(int changeValue)
{
	yCoord += ofGetLastFrameTime() * changeValue * change_speed;
}