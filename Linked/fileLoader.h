#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include <allegro.h>
#include <string>
#include <vector>

class FileLoader
{
   private:
	struct position
	{
		int x;
		int y;
	};
	int numberOfBombs;
	int numberOfGirders;
	int pusherRange;
	int numberOfPushers;
	position playerXY;
	std::vector<position> holePosition;
	std::vector<position> girderPosition;
	std::vector<position> originalPusherPosition;
	std::vector<position> bombPosition;
   public:
	FileLoader();
	void loadFile(std::string);
	int getBombs();
	int getGirders();
	int getPusherRange();
	int getPushers();
	int getPlayerX();
	int getPlayerY();
	int getHolePositionX(int);
	int getGirderPositionX(int);
	int getPusherPositionX(int);
	int getHolePositionY(int);
	int getGirderPositionY(int);
	int getPusherPositionY(int);
	int getBombPositionX(int);
	int getBombPositionY(int);
};

#endif