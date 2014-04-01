#pragma once
#ifndef CREDITS_H
#define CREDITS_H

#include <allegro.h>

class Credits
{
private:
	int next;
	int buttonPressed;
	int mouseOver;
public:
	Credits();
	int creditsStart();
};

#endif