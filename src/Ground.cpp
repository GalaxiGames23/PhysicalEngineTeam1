#include "Ground.h"
#include <ofAppRunner.h>


void Ground::change_ground_height(int changeValue)
{
	yCoord += ofGetLastFrameTime() * changeValue * change_speed;
}

//ofGetLastFrameTime
// renvoie la durée (en secondes) que le système a mis pour générer et afficher le dernier frame graphique