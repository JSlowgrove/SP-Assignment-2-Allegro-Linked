#include "moveEntity.h"

MoveEntity::MoveEntity()
{	

}

void MoveEntity::setPlayerXY(int axis, int tmpX, int tmpY, int direction)
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
}

void MoveEntity::setBombs(int i, int tmpX, int tmpY)
{
	bombsXY.resize(i+1);
	bombsXY[i].x = tmpX;
	bombsXY[i].y = tmpY;
}

void MoveEntity::setCollisions(int pG, int pB, int pPu)
{
	collisionPG = pG;
	collisionPB = pB;
	collisionPPu = pPu;
}

void MoveEntity::movePlayer(int axis, int direction)
{
	if(collisionPG == 0)//girder collision check
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			x -= direction;
			break;
		case true:
			y -= direction;			
			break;
		}
	}
	if(collisionPB == 0)//bomb collision check
	{
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			switch(axis)
			{
			case false:
				bombsXY[i].x += direction;
				break;
			case true:
				bombsXY[i].y += direction;			
				break;
			}
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
			x -= direction;
			break;
		case true:
			y -= direction;			
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

int MoveEntity::getBombX(int i)
{
	return bombsXY[i].x;
}

int MoveEntity::getBombY(int i)
{
	return bombsXY[i].y;
}