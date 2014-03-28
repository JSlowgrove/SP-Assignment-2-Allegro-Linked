#include "fileLoader.h"
#include <allegro.h>
#include <string>

FileLoader::FileLoader()
{	
}

void loadFile(std::string fileName)
{
}

void FileLoader::setArrays()
{
}

void FileLoader::setNumbers()
{
	numberOfBombs = 2;
	numberOfGirders = 66;
	pusherRange = 6;
	numberOfPushers = 1;
}

int FileLoader::getBombs()
{
	return numberOfBombs;
}
int FileLoader::getGirders()
{
	return numberOfGirders;
}
int FileLoader::getPusherRange()
{
	return pusherRange;
}
int FileLoader::getPushers()
{
	return numberOfPushers;
}