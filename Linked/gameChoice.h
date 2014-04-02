#pragma once
#ifndef GAME_CHOICE_H
#define GAME_CHOICE_H

#include "fileLoader.h"
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
	std::string fileName;
public:
	GameChoice();
	int gameChoiceStart();
};

#endif