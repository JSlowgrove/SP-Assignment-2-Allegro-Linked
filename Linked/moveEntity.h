#pragma once
#ifndef MOVE_ENTITY_H
#define MOVE_ENTITY_H

#include <allegro.h>

class MoveEntity
{
private:
	int x;
	int y;
public:
	MoveEntity();
	void movePlayer(int, int, int, int, int, int, int);
	int getPlayerX();
	int getPlayerY();
};

#endif