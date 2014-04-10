#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <allegro.h>
#include <vector>

class MainMenu
{
private:
	int next;
	int buttonPressed;
	int mouseOver;
public:
	MainMenu();
	~MainMenu();
	int menuStart();
};

#endif