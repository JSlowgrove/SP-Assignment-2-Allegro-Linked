#pragma once
#ifndef CREDITS_H
#define CREDITS_H

#include <allegro.h>

class Credits
{
private:
	int next;
	int mouseOver;
public:
	Credits();
	int creditsStart();
};

#endif