#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <allegro.h>

class MainMenu
{
private:
	int barY;
	int barTopX;
	int bTXDirection;
public:
	MainMenu();
	int menuStart();
};

#endif