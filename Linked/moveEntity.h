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
	int collisionPG;
	int collisionPB;
	int collisionPPu;
	int collisionBB;
	int lightAnim;
	std::vector<position> bombsXY;
	std::vector<int> collisionBG;
	std::vector<int> collisionBPu;
	void moveBombs(int, int);
public:
	MoveEntity();
	void setPlayerXY(int,int,int,int);
	void setBombs(int, int, int);
	void setCollisions(FileLoader);
	void movePlayer(int, int);
	int getPlayerX();
	int getPlayerY();
	int getBombX(int);
	int getBombY(int);
	int getLightAnim();
};

#endif