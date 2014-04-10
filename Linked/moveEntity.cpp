#include "moveEntity.h"

MoveEntity::MoveEntity()
{	

}

void MoveEntity::movePlayer(int axis, int direction, FileLoader data)
{
	switch(axis)
	{
	case false:
		data.setPlayerX(data.getPlayerX()+direction);
		break;
	case true:
		data.setPlayerY(data.getPlayerY()+direction);					
		break;
	}
	if(collision(data.getGirders(),data.getPlayerX(), data.getPlayerY(), 32, 32, 0, 32, 32, data) == 0)
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			data.setPlayerX(data.getPlayerX()-direction);
			break;
		case true:
			data.setPlayerY(data.getPlayerY()-direction);				
			break;
		}
	}
	if(collision(data.getBombs(),data.getPlayerX(), data.getPlayerY(), 32, 32, 1, 32, 32, data) == 0)//bomb collision check
	{
		lightAnim = 0;
	}
	else
	{
		for (int i = 0; i < data.getBombs(); i++)
		{
			switch(axis)
			{
			case false:
			data.setBombPositionX(i,data.getBombPositionX(i)+direction);
				switch(direction)
				{
				case -1:
					lightAnim = 96;
					break;
				case 1:
					lightAnim = 128;
					break;
				}
				break;
			case true:
				data.setBombPositionY(i,data.getBombPositionY(i)+direction);
				switch(direction)
				{
				case -1:
					lightAnim = 32;
					break;
				case 1:
					lightAnim = 64;
					break;
				}
				break;
			}
			if(collision(data.getGirders(),data.getBombPositionX(i), data.getBombPositionY(i), 32, 32, 0, 32, 32, data) == 0 &&
				collision(1, data.getBombPositionX(1), data.getBombPositionY(1), 32, 32, 1, 32, 32, data) == 0)//bomb girder collision check and bomb bomb collision check
			{
			}
			else
			{
				switch(axis)
				{
				case false:
					data.setBombPositionX(i,data.getBombPositionX(i)-direction);
					data.setPlayerX(data.getPlayerX()-direction);
					break;
				case true:
					data.setBombPositionY(i,data.getBombPositionY(i)-direction);
					data.setPlayerY(data.getPlayerY()-direction);
					break;
				}					
			}
		}
	}
	bombsXY.resize(data.getBombs());
	switch(axis)
	{
	case false:
		player.x = data.getPlayerX();
		player.y = data.getPlayerY();
		break;
	case true:
		player.x = data.getPlayerX();
		player.y = data.getPlayerY();					
		break;
	}
	for (int i = 0; i < 2; i++)
	{
		bombsXY[i].x = data.getBombPositionX(i);
		bombsXY[i].y = data.getBombPositionY(i);
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