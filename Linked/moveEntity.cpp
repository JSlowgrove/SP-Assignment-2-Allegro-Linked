#include "moveEntity.h"

MoveEntity::MoveEntity() //Constructor
{	

}

MoveEntity::~MoveEntity() //De-constructor
{	

}

void MoveEntity::movePlayer(int axis, int direction, FileLoader data)
{
	switch(axis) //checks to see what direction the player is moving
	{
	case false: //RIGHT or LEFT
		data.setPlayerX(data.getPlayerX()+direction); //adds the value of direction to the playerX coordinate stored in data. Direction is either 1 or -1 so will cause the player to move either right or left
		break;
	case true: //UP or DOWN
		data.setPlayerY(data.getPlayerY()+direction);//adds the value of direction to the playerY coordinate stored in data. Direction is either 1 or -1 so will cause the player to move either up or down					
		break;
	}

	if(collision(data.getGirders(),data.getPlayerX(), data.getPlayerY(), 32, 32, 0, 32, 32, data) == 0) //check to see if there has been a collision between the player and any of the girders
	{
		//if 0 then there has been no collision so the player can move in the direction it has been set to
	}
	else
	{
		switch(axis) //checks to see what direction the player is moving
		{
		case false://RIGHT or LEFT
			data.setPlayerX(data.getPlayerX()-direction);// takes away the value of direction from the playerX coordinate, effectively stopping the player from moving
			break;
		case true://UP or DOWN
			data.setPlayerY(data.getPlayerY()-direction);// takes away the value of direction from the playerX coordinate, effectively stopping the player from moving				
			break;
		}
	}

	if(collision(data.getBombs(),data.getPlayerX(), data.getPlayerY(), 32, 32, 1, 32, 32, data) == 0)//check to see if the player has collided with any of the bombs
	{
		lightAnim = 0; //if 0 then there has been no collision so there will be no light animation. As such it is set to 0
	}
	else
	{
		if(boundingBox(data.getPlayerX(), data.getPlayerY(), 32, 32, data.getBombPositionX(0), data.getBombPositionY(0), 32, 32) == 0)//check to which bomb the player has collided
		{
			collidedBomb = 1; //if 0 sets the collided bomb to be 1
		}
		else
		{
			collidedBomb = 0; //if 1 sets the collided bomb to be 0
		}

		/*LOOP THROUGH CHECKING EACH BOMB**********************************************************************************/
		for (int i = 0; i < data.getBombs(); i++) 
		{
			switch(axis)//checks to see what direction the bomb is moving
			{
			case false://RIGHT or LEFT
				data.setBombPositionX(i,data.getBombPositionX(i)+direction);//adds the value of direction to the bombX coordinate stored in data. Direction is either 1 or -1 so will cause the bomb to move either right or left
				switch(direction)
				{
				case -1:// if the direction is left then the light animation will appear on the right side of the bomb
					lightAnim = 96;
					break;
				case 1:// if the direction is right then the light animation will appear on the left side of the bomb
					lightAnim = 128;
					break;
				}
				break;
			case true://UP or DOWN
				data.setBombPositionY(i,data.getBombPositionY(i)+direction);//adds the value of direction to the bombY coordinate stored in data. Direction is either 1 or -1 so will cause the bomb to move either up or down
				switch(direction)
				{
				case -1:// if the direction is up then the light animation will appear on the bottom of the bomb
					lightAnim = 32;
					break;
				case 1:// if the direction is down then the light animation will appear above the bomb
					lightAnim = 64;
					break;
				}
				break;
			}

			if(collision(data.getGirders(),data.getBombPositionX(i), data.getBombPositionY(i), 32, 32, 0, 32, 32, data) == 0)//check if the bomb has collided with any of the girders
			{
				//if 0 then there has been no collision so the bomb can move in the direction it has been set to
			}
			else
			{
				switch(axis)//checks to see what direction the bomb is moving
				{
				case false://RIGHT or LEFT
					data.setBombPositionX(i,data.getBombPositionX(i)-direction);// takes away the value of direction from the bombX coordinate, effectively stopping the bomb from moving
					if (i == collidedBomb) //check if the bomb is the one that the player has collided with
					{
						data.setPlayerX(data.getPlayerX()-direction);// takes away the value of direction from the playerX coordinate, effectively stopping the player from moving
					}
					break;
				case true://UP or DOWN
					data.setBombPositionY(i,data.getBombPositionY(i)-direction);// takes away the value of direction from the bombY coordinate, effectively stopping the bomb from moving
					if (i == collidedBomb)
					{
						data.setPlayerY(data.getPlayerY()-direction);// takes away the value of direction from the playerY coordinate, effectively stopping the player from moving
					}
					break;
				}				
			}
		}
		/*END LOOP THROUGH CHECKING EACH BOMB**********************************************************************************/

		if(collision(1, data.getBombPositionX(1), data.getBombPositionY(1), 32, 32, 1, 32, 32, data) == 0)//check to see if the two bombs have collided
		{
			//if 0 then there has been no collision so the bomb can move in the direction it has been set to
		}
		else
		{
			/*LOOP THROUGH CHECKING EACH BOMB**********************************************************************************/
			for (int i = 0; i < data.getBombs(); i++)
			{	
				switch(axis)//checks to see what direction the entities are moving
				{
				case false: //LEFT or RIGHT
					data.setBombPositionX(i,data.getBombPositionX(i)-direction); // takes away the value of direction from the bombX coordinate, effectively stopping the bomb from moving
					data.setPlayerX(data.getPlayerX()-direction);// takes away the value of direction from the playerX coordinate, effectively stopping the player from moving
					break;
				case true: // UP or DOWN
					data.setBombPositionY(i,data.getBombPositionY(i)-direction); // takes away the value of direction from the bombY coordinate, effectively stopping the bomb from moving
					data.setPlayerY(data.getPlayerY()-direction); // takes away the value of direction from the playerY coordinate, effectively stopping the player from moving
					break;
				}	
			}
			/*END LOOP THROUGH CHECKING EACH BOMB**********************************************************************************/
		}
	}
	bombsXY.resize(data.getBombs());// resizes the vector array for the bombs position
	player.x = data.getPlayerX();// sets the value of x in the player position to the new player x-coordinate
	player.y = data.getPlayerY();// sets the value of y in the player position to the new player y-coordinate

	/*LOOP THROUGH EACH BOMB**********************************************************************************/
	for (int i = 0; i < data.getBombs(); i++)
	{
		bombsXY[i].x = data.getBombPositionX(i);// sets the value of x in the bomb position to the new bomb x-coordinate
		bombsXY[i].y = data.getBombPositionY(i);// sets the value of y in the bomb position to the new bomb y-coordinate
	}
	/*END LOOP THROUGH EACH BOMB**********************************************************************************/
}

int MoveEntity::getPlayerX() //PlayerX Getter
{
	return player.x;
}

int MoveEntity::getPlayerY() //PlayerY Getter
{
	return player.y;
}

int MoveEntity::getBombX(int i) //BombX Getter, it takes in the index for the bomb it will return
{
	return bombsXY[i].x;
}

int MoveEntity::getBombY(int i) //BombY Getter, it takes in the index for the bomb it will return
{
	return bombsXY[i].y;
}

int MoveEntity::getLightAnim() //LightAnim Getter
{
	return lightAnim;
}