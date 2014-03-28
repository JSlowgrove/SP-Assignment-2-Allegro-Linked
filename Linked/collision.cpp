#include "collision.h"
#include "fileLoader.h"
#include <allegro.h>

Collision::Collision()
{	
}

int Collision::boundingBox(int object1X, int object1Y, int object1Width, int object1Height, int object2X, int object2Y, int object2Width, int object2Height)//made using http://wiki.allegro.cc/index.php?title=Bounding_Box
{ 
    if ((object1X > object2X + object2Width - 1) || // check if object 1 is to the right of object 2
        (object1Y > object2Y + object2Height - 1) || // check if object 1 is under object 2
        (object2X > object1X + object1Width - 1) || // check if object 2 is to the right of object 1
        (object2Y > object1Y + object1Height - 1))   // check if object 2 is under object 1
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

bool Collision::collisionCheck(int index, int x1, int y1, int w1, int h1, int typeOfCollison, int w2, int h2)
{
	int x2,y2;
	bool crash = false;
	for (int i = 0; i < index; i++)
	{
		switch(typeOfCollison)
		{
		case 0:
			x2 = data.getGirderPositionX(i);
			y2 = data.getGirderPositionY(i);
			break;
		case 1:
			x2 = bombPosition[i].x;
			y2 = bombPosition[i].y;
			break;
		}
		if(boundingBox(x1, y1, w1, h1, x2, y2, w2, h2) == 1)
		{
			crash = true;
		}
	}
	return crash;
}