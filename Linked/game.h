#pragma once
#ifndef GAME_H
#define GAME_H

#include "fileLoader.h"
#include "moveEntity.h"
#include <allegro.h>
#include <vector>
#include <string>

class Game
{
private:
	struct position //structure for coordinates of an entity
	{
		int x;
		int y;
	};
public:
	Game();
	~Game();
	int gameStart(std::string, int);
};

#endif