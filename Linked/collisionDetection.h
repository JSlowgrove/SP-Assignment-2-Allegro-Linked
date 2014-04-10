#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "fileLoader.h"

class CollisionDetection
{
private:

public:
	CollisionDetection();
	~CollisionDetection();
	int boundingBox(int, int, int, int, int, int, int, int);//object1 X position, object1 Y position, object 1 Width, object 1 Height, object2 X position, object2 Y position, object2 Width, object2 Height
	int collision(int, int, int, int, int, int, int, int, FileLoader);//index,x position, y position, object1 width, object1 height, type of collision check, object2 width, object2 height, data
};

#endif