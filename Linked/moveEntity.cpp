#include "moveEntity.h"

MoveEntity::MoveEntity()
{	

}

void MoveEntity::movePlayer(int axis, int direction, int tmpX, int tmpY, int collisionPG, int collisionPB, int collisionPPu)
{
	switch(axis)
	{
	case false:
		x = tmpX + direction;
		y = tmpY;
		break;
	case true:
		x = tmpX;
		y = tmpY + direction;	
		break;
	}
	if(collisionPG == 0)//girder collision check
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			x = x - direction;
			break;
		case true:
			y = y - direction;			
			break;
		}
	}
	if(collisionPB == 0)//bomb collision check
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			x = x - direction;
			break;
		case true:
			y = y - direction;			
			break;
		}
	}
	if(collisionPPu == 0)//pusher collision check
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			x = x - direction;
			break;
		case true:
			y = y - direction;			
			break;
		}
	}
}

int MoveEntity::getPlayerX()
{
	return x;
}

int MoveEntity::getPlayerY()
{
	return y;
}