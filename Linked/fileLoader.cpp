#include "fileLoader.h"

FileLoader::FileLoader()//constructor
{	
	
}

FileLoader::~FileLoader()//De-constuctor
{	

}

void FileLoader::loadFile(std::string fileName, int level)
{
	//first line of text file = number of levels in file. KEY:none=0/girder=1/playerSpawn=2/pusherSpawn=3/pusherEnd=4/bomb=5/endPoint=6

	/*VARIABLE INITIALIZATION*/
	numberOfBombs = 0;
	numberOfGirders = 0;
	pusherRange = 0;
	numberOfPushers = 0;
	int tempPusher = 0;
	int tempGirder = 0;
	int tempBomb = 0;
	int tempHole = 0;
	int tempPusherEnd = 0;
	std::vector<position> pusherEnd;
	/*VARIABLE INITIALIZATION*/

	/*FILE READ IN VARIABLES*/
	std::ifstream file (fileName);//creates a input file stream called file using the value of fileName
	std::vector<std::string> line; //creates a vector of strings for the lines in the file
	/*FILE READ IN VARIABLES*/

	if (file.is_open())//if the file successfully opens
	{
		/*FILE READ IN*/
		int i = -1, count = 0;
		std::string temp;
		while ( getline (file,temp) ) //while there are still lines to be read in from the file
		{
			count++;
			if (count >= ( (level - 1) * 15 ) + level && count <= ( (level - 1) * 15 ) + (15 + level)) //if the count is at the position in the file with the correct level data in it store the lines to the temp varible
			{
				i++;
				line.resize(i+1);
				line[i] = temp;
			}
		}
		file.close();
		/*FILE READ IN*/

		/*Loop for the number of lines in the line array***********************************************/
		for(int i = 0; i < line.size(); i++)
		{
			/*loop for the number of characters in a single line***************************************/
			for (int a = 0; a < line[i].size(); a++){ 
				switch (line[i][a])//check the character at this position in the array
				{
				case '1': //if 1 add 1 to the value of the number of girders in the file
					numberOfGirders++;
					break;
				case '3': //if 3 add 1 to the value of the number of pushers in the file
					numberOfPushers++;
					break;
				case '5': //if 5 add 1 to the value of the number of bombs in the file
					numberOfBombs++;
					break;
				default: //if not any of thesee then do nothing
					break;
				}
			}
			/*End loop for the number of characters in a single line***************************************/
		}
		/*End loop for the number of lines in the line array***********************************************/

		/*RESIZE ARRAYS USING NUMBERS COLLECTED*/
		girderPosition.resize(numberOfGirders);
		pusherPosition.resize(numberOfPushers);
		pusherEnd.resize(numberOfPushers);
		holePosition.resize(numberOfBombs);
		bombPosition.resize(numberOfBombs);
		/*RESIZE ARRAYS USING NUMBERS COLLECTED*/

		/*Loop for the number of lines in the line array***********************************************/
		for(int i = 0; i < line.size(); i++)
		{
			/*loop for the number of characters in a single line***************************************/
			for (int a = 0; a < line[i].size(); a++){
				switch (line[i][a])//check the character at this position in the array
				{
				case '1':// if 1 set the position using the loop variables in the girders vector array and add one to the value of temp girder
					girderPosition[tempGirder].x = a*32;
					girderPosition[tempGirder].y = (i-1)*32;
					tempGirder++;
					break;
				case '2':// if 2 set the position using the loop variables in the playerXY variable
					playerXY.x = a*32;
					playerXY.y = (i-1)*32;
					break;
				case '3':// if 3 set the position using the loop variables in the pushers vector array and add one to the value of temp pusher
					pusherPosition[tempPusher].x = a*32;
					pusherPosition[tempPusher].y = (i-1)*32;
					tempPusher++;
					break;
				case '4':// if 4 set the position using the loop variables in the pushers end vector array and add one to the value of temp pusher end
					pusherEnd[tempPusherEnd].x = a*32;
					pusherEnd[tempPusherEnd].y = (i-1)*32;
					tempPusherEnd++;
					break;
				case '5':// if 5 set the position using the loop variables in the bomb vector array and add one to the value of temp bomb
					bombPosition[tempBomb].x = a*32;
					bombPosition[tempBomb].y = (i-1)*32;
					tempBomb++;
					break;
				case '6':// if 6 set the position using the loop variables in the hole vector array and add one to the value of temp hole
					holePosition[tempHole].x = a*32;
					holePosition[tempHole].y = (i-1)*32;
					tempHole++;
					break;
				default: //else do nothing
					break;
				}
			}
			/*End loop for the number of characters in a single line***************************************/
		} 
		/*End loop for the number of lines in the line array***********************************************/

		firstPusherPosition.resize(numberOfPushers);//resize the first pusher position vector array

		/*Loop for the number of pushers*******************************************************************/
		for (int i = 0; i < numberOfPushers; i++)
		{
			firstPusherPosition[i] = pusherPosition[i].x;// set the contents of the pusher array to the first pusher array
		}
		if (numberOfPushers != 0) // if the number of pushers is not 0 then work out the range of the pushers movement using the end and start positions
		{
			pusherRange = abs(pusherEnd[0].x - pusherPosition[0].x); //abs = always a positive value
		}
		/*End loop for the number of pushers*******************************************************************/
	}

	else //if the file could be opened then output error message
	{
		std::cout << "Unable to open file"; 
	}
}

int FileLoader::getNumberOfLevels(std::string fileName) //gets the number of levels in the file
{
	/*FILE READ IN VARIABLES*/
	std::ifstream file (fileName);
	std::string temp;
	/*FILE READ IN VARIABLES*/

	/*FILE READ IN*/
	if (file.is_open())
	{
		getline (file,temp);//read the first line
		file.close();
	}
	/*FILE READ IN*/

	numberOfLevels = atoi(temp.c_str()); // convert the value of temp to an integer and fill it in to the number of levels variable
	return numberOfLevels; //return the number of levels
}

int FileLoader::getBombs() //Number of Bombs Getter
{
	return numberOfBombs;
}

int FileLoader::getGirders() //Number of Girders Getter
{
	return numberOfGirders;
}

int FileLoader::getPusherRange() //Pusher range Getter
{
	return pusherRange;
}

int FileLoader::getPushers() //Number of Pushers Getter
{
	return numberOfPushers;
}

int FileLoader::getHolePositionX(int i) //Hole x position Getter, takes the index of the hole wanted
{
	return holePosition[i].x;
}

int FileLoader::getHolePositionY(int i)//Hole y position Getter, takes the index of the hole wanted
{
	return holePosition[i].y;
}

int FileLoader::getGirderPositionX(int i) //Girder x position Getter, takes the index of the girder wanted
{
	return girderPosition[i].x;
}

int FileLoader::getGirderPositionY(int i) //Girder y position Getter, takes the index of the girder wanted
{
	return girderPosition[i].y;
}

int FileLoader::getPusherPositionX(int i) //Pusher x position Getter, takes the index of the pusher wanted
{
	return pusherPosition[i].x;
}

int FileLoader::getPusherPositionY(int i) //Pusher y position Getter, takes the index of the pusher wanted
{
	return pusherPosition[i].y;
}

int FileLoader::getFirstPusherPositionX(int i) //First Pusher x position Getter, takes the index of the pusher wanted
{
	return firstPusherPosition[i];
}

int FileLoader::getPlayerX() //Player x position Getter
{
	return playerXY.x;
}

int FileLoader::getPlayerY() //Player y position Getter
{
	return playerXY.y;
}

int FileLoader::getBombPositionX(int i) //Bomb x position Getter, takes the index of the bomb wanted
{
	return bombPosition[i].x;
}

int FileLoader::getBombPositionY(int i) //bomb y position Getter, takes the index of the bomb wanted
{
	return bombPosition[i].y;
}

void FileLoader::setPlayerX(int x) //Player x position Setter, takes the new value to be set
{
	playerXY.x = x;
}

void FileLoader::setPlayerY(int y) //Player y position Setter, takes the new value to be set
{
	playerXY.y = y;
}

void FileLoader::setBombPositionX(int i, int x) //bomb x position Setter, takes the index of the bomb wanted and the new value to be set
{
	bombPosition[i].x = x;
}

void FileLoader::setBombPositionY(int i, int y) //bomb y position Setter, takes the index of the bomb wanted and the new value to be set
{
	bombPosition[i].y = y;
}

void FileLoader::setPusherPositionX(int i, int x) //pusher x position Setter, takes the index of the pusher wanted and the new value to be set
{
	pusherPosition[i].x = x;
}