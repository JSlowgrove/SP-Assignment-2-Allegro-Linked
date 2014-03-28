#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include <allegro.h>
#include <string>

class FileLoader
{
   private:
	int numberOfBombs;
	int numberOfGirders;
	int pusherRange;
	int numberOfPushers;
   public:
	FileLoader();
	void loadFile(std::string);
	void setArrays();
	void setNumbers();
	int getBombs();
	int getGirders();
	int getPusherRange();
	int getPushers();
};

#endif