#pragma once
#ifndef GAME_CHOICE_H
#define GAME_CHOICE_H

#include "fileLoader.h"
#include "game.h"
#include <allegro.h>
#include <vector>
#include <string>

class GameChoice
{
private:
	int next;
	int buttonPressed;
	int mouseOver;
	int page;
	int level;
	int numberOfLevels;
	std::string fileName;
	FileLoader data;
	Game game;
public:
	GameChoice();
	int gameChoiceStart();
};

#endif