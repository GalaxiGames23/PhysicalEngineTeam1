#include "Ground.h"
#include <ofAppRunner.h>


// Pour changer la hauteur du sol
void Ground::change_ground_height(int changeValue)
{
	yCoord += ofGetLastFrameTime() * changeValue * change_speed;
}

