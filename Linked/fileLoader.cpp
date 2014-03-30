#include "fileLoader.h"

FileLoader::FileLoader()
{	
	
}

void FileLoader::loadFile(std::string fileName)
{
	//number of levels in file. KEY:none=0/girder=1/playerSpawn=2/pusherSpawn=3/pusherEnd=4/bomb=5/endPoint=6
	numberOfBombs = 0;
	numberOfGirders = 0;
	pusherRange = 0;
	numberOfPushers = 0;
	int tempPusher = 0;
	int tempGirder = 0;
	int tempBomb = 0;
	int tempHole = 0;
	int tempPusherEnd = 0;
	std::ifstream file (fileName);
	std::vector<std::string> line;
	std::vector<position> pusherEnd;
	line.resize(1);
	if (file.is_open())
	{
		int i = 0;
		while ( getline (file,line[i]) )
		{
			i++;
			line.resize(i+1);
		}
		file.close();
		
		numberOfLevels = atoi(line[0].c_str());

		for(int i = 1; i < line.size(); i++)
		{
			for (int a = 0; a < line[i].size(); a++){
				switch (line[i][a])
				{
				case '1':
					numberOfGirders++;
					break;
				case '3':
					numberOfPushers++;
					break;
				case '5':
					numberOfBombs++;
					break;
				default:
					break;
				}
			}
		}
		girderPosition.resize(numberOfGirders);
		pusherPosition.resize(numberOfPushers);
		pusherEnd.resize(numberOfPushers);
		holePosition.resize(numberOfBombs);
		bombPosition.resize(numberOfBombs);
		for(int i = 1; i < line.size(); i++)
		{
			for (int a = 0; a < line[i].size(); a++){
				switch (line[i][a])
				{
				case '1':
					girderPosition[tempGirder].x = a*32;
					girderPosition[tempGirder].y = (i-1)*32;
					tempGirder++;
					break;
				case '2':
					playerXY.x = a*32;
					playerXY.y = (i-1)*32;
					break;
				case '3':
					pusherPosition[tempPusher].x = a*32;
					pusherPosition[tempPusher].y = (i-1)*32;
					tempPusher++;
					break;
				case '4':
					pusherEnd[tempPusherEnd].x = a*32;
					pusherEnd[tempPusherEnd].y = (i-1)*32;
					tempPusherEnd++;
					break;
				case '5':
					bombPosition[tempBomb].x = a*32;
					bombPosition[tempBomb].y = (i-1)*32;
					tempBomb++;
					break;
				case '6':
					holePosition[tempHole].x = a*32;
					holePosition[tempHole].y = (i-1)*32;
					tempHole++;
					break;
				default:
					break;
				}
			}
		} 
		firstPusherPosition.resize(numberOfPushers);
		for (int i = 0; i < numberOfPushers; i++)
		{
			firstPusherPosition[i] = pusherPosition[i].x;
		}
		if (numberOfPushers != 0)
		{
			pusherRange = abs(pusherEnd[0].x - pusherPosition[0].x); //abs = always a positive value
		}
		
	}

	else std::cout << "Unable to open file"; 
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

int FileLoader::getHolePositionX(int i)
{
	return holePosition[i].x;
}

int FileLoader::getHolePositionY(int i)
{
	return holePosition[i].y;
}

int FileLoader::getGirderPositionX(int i)
{
	return girderPosition[i].x;
}

int FileLoader::getGirderPositionY(int i)
{
	return girderPosition[i].y;
}

int FileLoader::getPusherPositionX(int i)
{
	return pusherPosition[i].x;
}

int FileLoader::getPusherPositionY(int i)
{
	return pusherPosition[i].y;
}

int FileLoader::getFirstPusherPositionX(int i)
{
	return firstPusherPosition[i];
}

int FileLoader::getPlayerX()
{
	return playerXY.x;
}

int FileLoader::getPlayerY()
{
	return playerXY.y;
}

int FileLoader::getBombPositionX(int i)
{
	return bombPosition[i].x;
}

int FileLoader::getBombPositionY(int i)
{
	return bombPosition[i].y;
}

int FileLoader::getNumberOfLevels()
{
	return numberOfLevels;
}

void FileLoader::setPlayerX(int x)
{
	playerXY.x = x;
}

void FileLoader::setPlayerY(int y)
{
	playerXY.y = y;
}

void FileLoader::setBombPositionX(int i, int x)
{
	bombPosition[i].x = x;
}

void FileLoader::setBombPositionY(int i, int y)
{
	bombPosition[i].y = y;
}

void FileLoader::setPusherPositionX(int i, int x)
{
	pusherPosition[i].x = x;
}