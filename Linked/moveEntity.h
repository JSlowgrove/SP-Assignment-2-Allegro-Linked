#pragma once
#ifndef MOVE_ENTITY_H
#define MOVE_ENTITY_H

#include <allegro.h>
#include <vector>

class MoveEntity
{
private:
	struct position{
		int x;
		int y;
	};
	std::vector<position> bombsXY;
	int x;
	int y;
	int collisionPG;
	int collisionPB;
	int collisionPPu;
public:
	MoveEntity();
	void setPlayerXY(int,int,int,int);
	void setBombs(int, int, int);
	void setCollisions(int,int,int);
	void movePlayer(int, int);
	int getPlayerX();
	int getPlayerY();
	int getBombX(int);
	int getBombY(int);
};

#endif