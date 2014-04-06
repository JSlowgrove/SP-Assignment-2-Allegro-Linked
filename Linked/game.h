#pragma once
#ifndef GAME_H
#define GAME_H

#include "fileLoader.h"
#include "collisionDetection.h"
#include "moveEntity.h"
#include <allegro.h>
#include <vector>
#include <string>

class Game
{
private:
	struct position
	{
		int x;
		int y;
	};
public:
	Game();
	int gameStart(std::string, int);
};

#endif