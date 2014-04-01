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
	int next;
	int mouseOver;
public:
	MainMenu();
	int menuStart();
	void animation();
	void mousePress();
};

#endif