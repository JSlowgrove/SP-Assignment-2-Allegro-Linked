#pragma once
#ifndef MOVE_ENTITY_H
#define MOVE_ENTITY_H

#include <allegro.h>
#include <vector>
#include "fileLoader.h"
#include "collisionDetection.h"

class MoveEntity:public CollisionDetection
{
private:
	struct position{
		int x;
		int y;
	};
	position player;
	int lightAnim;
	std::vector<position> bombsXY;
public:
	MoveEntity();
	void movePlayer(int, int, FileLoader);
	int getPlayerX();
	int getPlayerY();
	int getBombX(int);
	int getBombY(int);
	int getLightAnim();
};

#endif