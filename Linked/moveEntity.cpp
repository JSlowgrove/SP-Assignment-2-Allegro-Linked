#include "moveEntity.h"

MoveEntity::MoveEntity()
{	

}

void MoveEntity::setPlayerXY(int axis, int tmpX, int tmpY, int direction)
{
	switch(axis)
	{
	case false:
		player.x = tmpX + direction;
		player.y = tmpY;
		break;
	case true:
		player.x = tmpX;
		player.y = tmpY + direction;	
		break;
	}
}

void MoveEntity::setBombs(int i, int tmpX, int tmpY)
{
	bombsXY.resize(i+1);
	bombsXY[i].x = tmpX;
	bombsXY[i].y = tmpY;
}

void MoveEntity::setCollisions(FileLoader data)
{
	collisionPG = CollisionDetection::collision(data.getGirders(),player.x, player.y, 32, 32, 0, 32, 32, data);
	collisionPB = CollisionDetection::collision(data.getBombs(), player.x, player.y, 32, 32, 1, 32, 32, data);
	collisionPPu = CollisionDetection::collision(data.getPushers(), player.x, player.y, 32, 32, 2, 32, 32, data);
	collisionBB = CollisionDetection::collision(1, data.getBombPositionX(1), data.getBombPositionY(1), 32, 32, 1, 32, 32, data);
	collisionBG.resize(data.getBombs());
	collisionBPu.resize(data.getBombs());
	for (int i = 0; i < data.getBombs(); i++)
	{
		collisionBG[i] = CollisionDetection::collision(data.getGirders(), data.getBombPositionX(i), data.getBombPositionY(i), 32, 32, 0, 32, 32, data);
		collisionBPu[i] = CollisionDetection::collision(data.getPushers(), data.getBombPositionX(i), data.getBombPositionY(i), 32, 32, 2, 32, 32, data);
	}
}

void MoveEntity::movePlayer(int axis, int direction)
{
	if(collisionPG == 0)//girder collision check
	{
		lightAnim = 0;
	}
	else
	{
		switch(axis)
		{
		case false:
			player.x -= direction;
			break;
		case true:
			player.y -= direction;			
			break;
		}
	}
	if(collisionPB == 0)//bomb collision check
	{
	}
	else
	{
		if (direction == -1 && axis == false)
		{
			lightAnim = 96;
		}
		else if (direction == 1 && axis == false)
		{
			lightAnim = 128;
		}
		if (direction == -1 && axis == true)
		{
			lightAnim = 32;
		}
		else if (direction == 1 && axis == true)
		{
			lightAnim = 64;
		}
		moveBombs(axis,direction);
	}
	if(collisionPPu == 0)//pusher collision check
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			player.x -= direction;
			break;
		case true:
			player.y -= direction;			
			break;
		}
	}
}

void MoveEntity::moveBombs(int axis, int direction)
{
	for (int i = 0; i < 2; i++)//( sizeof(collisionBB) / sizeof(collisionBB[0])); i++)
	{
		switch(axis)//initial move
		{
		case false:
			bombsXY[i].x += direction;
			break;
		case true:
			bombsXY[i].y += direction;
			break;
		}
		if(collisionBG[i] == 0)//girder collision check
		{
		}
		else
		{
			switch(axis)
			{
			case false:
				bombsXY[i].x -= direction;
				player.x -= direction;
				break;
			case true:
				bombsXY[i].y -= direction;	
				player.y -= direction;
				break;
			}
		}
		if(collisionBB == 0)//bomb collision check
		{
		}
		else
		{
			switch(axis)
			{
			case false:
				bombsXY[i].x -= direction;
				player.x -= direction;
				break;
			case true:
				bombsXY[i].y -= direction;
				player.y -= direction;
				break;
			}
		}
		if(collisionBPu[i] == 0)//pusher collision check
		{
		}
		else
		{
			switch(axis)
			{
			case false:
				bombsXY[i].x -= direction;
				break;
			case true:
				bombsXY[i].y -= direction;			
				break;
			}
		}
	}
}

int MoveEntity::getPlayerX()
{
	return player.x;
}

int MoveEntity::getPlayerY()
{
	return player.y;
}

int MoveEntity::getBombX(int i)
{
	return bombsXY[i].x;
}

int MoveEntity::getBombY(int i)
{
	return bombsXY[i].y;
}

int MoveEntity::getLightAnim()
{
	return lightAnim;
}