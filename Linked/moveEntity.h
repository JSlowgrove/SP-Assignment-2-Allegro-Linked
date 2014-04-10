#pragma once
#ifndef MOVE_ENTITY_H
#define MOVE_ENTITY_H

#include <vector>
#include "fileLoader.h"
#include "collisionDetection.h"

class MoveEntity:public CollisionDetection // inherits the collisionDetection class
{
private:
	struct position{ //creates a structure for the coordinates of the entity
		int x;
		int y;
	};
	int collidedBomb;
	position player;
	int lightAnim;
	std::vector<position> bombsXY;
public:
	MoveEntity();
	~MoveEntity();
	void movePlayer(int, int, FileLoader);
	int getPlayerX();
	int getPlayerY();
	int getBombX(int);
	int getBombY(int);
	int getLightAnim();
};

#endif