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
	int y;
	int x;
	std::string fileName;
	FileLoader *data;//declares a pointer to an instance of the FileLoader class
	Game *game;//declares a pointer to an instance of the Game class
public:
	GameChoice();
	~GameChoice();
	int gameChoiceStart();
};

#endif