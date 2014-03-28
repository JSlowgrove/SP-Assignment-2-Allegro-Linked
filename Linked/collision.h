#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include "fileLoader.h"
#include <allegro.h>

class Collision
{
	private:

	public:
		Collision();
		int boundingBox(int, int, int, int, int, int, int, int);
		bool collisionCheck(int, int, int, int, int, int, int, int)
};

#endif