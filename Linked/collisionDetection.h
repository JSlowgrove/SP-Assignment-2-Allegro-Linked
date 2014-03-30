#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include <allegro.h>
#include "fileLoader.h"

class CollisionDetection
{
private:

public:
	CollisionDetection();
	int boundingBox(int, int, int, int, int, int, int, int);
	int collision(int, int, int, int, int, int, int, int, FileLoader);
};

#endif