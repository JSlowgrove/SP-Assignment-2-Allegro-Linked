#include "collisionDetection.h"

CollisionDetection::CollisionDetection() //Constructor
{	

}

CollisionDetection::~CollisionDetection() //De-constructor
{	

}

int CollisionDetection::boundingBox(int object1X, int object1Y, int object1Width, int object1Height, int object2X, int object2Y, int object2Width, int object2Height)//made using http://wiki.allegro.cc/index.php?title=Bounding_Box
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

int CollisionDetection::collision(int index, int x1, int y1, int w1, int h1, int typeOfCollison, int w2, int h2, FileLoader data)
{
	int x2,y2;

	/*Loop for the index passed in*****************************************************/
	for (int i = 0; i < index; i++)
	{
		switch(typeOfCollison)//check the value passed into typeOfCollison
		{
		case 0://if 0 the check is against girders so set the value of x2, and y2 to the position of the girder with the current index
			x2 = data.getGirderPositionX(i);
			y2 = data.getGirderPositionY(i);
			break;
		case 1://if 1 the check is against bombs so set the value of x2, and y2 to the position of the bomb with the current index
			x2 = data.getBombPositionX(i);
			y2 = data.getBombPositionY(i);
			break;
		case 2://if 0 the check is against pushers so set the value of x2, and y2 to the position of the pusher with the current index
			x2 = data.getPusherPositionX(i);
			y2 = data.getPusherPositionY(i);
			break;
		}

		if(boundingBox(x1, y1, w1, h1, x2, y2, w2, h2) == 1)//check if the loaded object is colliding with the original object, if so end the function with the returned value of 1
		{
			return 1;
		}
	}
	/*End loop for the index passed in*****************************************************/

	return 0;//no collision
}
