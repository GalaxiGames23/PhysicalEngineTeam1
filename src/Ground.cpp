#include "Ground.h"
#include <ofAppRunner.h>


void Ground::change_ground_height(int changeValue)
{
	yCoord += ofGetLastFrameTime() * changeValue * change_speed;
}

//ofGetLastFrameTime
// renvoie la dur�e (en secondes) que le syst�me a mis pour g�n�rer et afficher le dernier frame graphique