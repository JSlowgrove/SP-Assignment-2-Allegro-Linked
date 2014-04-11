#include "game.h"

Game::Game()//constructor
{	
}

Game::~Game()//De-constructor
{	
}

/*GLOBALS FOR USE WITH TIMERS*/
std::vector<int> animXY; //0 = playerAnimX, 1 = playerAnimY, 2 = pusherAnimX, 3 = pusherAnimY, 4 = bombAnimX, 5 = holeAnimX, 6 = lightAnimX
std::vector<int> direction;//0 = playerDirection, 1 = pusherDirection
int timeLeft;
FileLoader *data;
MoveEntity *move;
void movePlayer32(void);
void holeAnim(void);
SAMPLE *slide;
SAMPLE *win;
std::string fileName;
int level;
int moveInt;
bool axis;
bool winTest;
int winTime;
/*GLOBALS FOR USE WITH TIMERS*/

int Game::gameStart(std::string tempFileName, int tempLevel)
{
	/*LEVEL STARTUP*/
	fileName = tempFileName;
	level = tempLevel;
	data = new FileLoader;
	move = new MoveEntity;
	data->loadFile(fileName, level);
	/*LEVEL STARTUP*/

	/*LOAD ASSETS*/
	slide = load_sample( "slide.wav" );
	win = load_sample( "win.wav" );
	SAMPLE *lose = load_sample( "lose.wav" );
	SAMPLE *countdown = load_sample( "countdownBeep.wav" );
	BITMAP *resetHelp = load_bitmap( "restartHelp.bmp", NULL );
	BITMAP *gameHelp = load_bitmap( "gameHelp.bmp", NULL );
	BITMAP *exitHelp = load_bitmap( "quitHelp.bmp", NULL );
	BITMAP *moveHelp = load_bitmap( "moveHelp.bmp", NULL );
	BITMAP *countdownBack = load_bitmap( "countdown.bmp", NULL );
	BITMAP *light = load_bitmap( "moveLight.bmp", NULL );
	BITMAP *ground = load_bitmap( "floor.bmp", NULL );
	BITMAP *loseGround = load_bitmap( "gameOverBackground.bmp", NULL );
	BITMAP *winGround = load_bitmap( "winBackground.bmp", NULL );
	BITMAP *bomb = load_bitmap( "bomb.bmp", NULL );
	BITMAP *hole = load_bitmap( "hole.bmp", NULL );
	BITMAP *player = load_bitmap( "remotePusher.bmp", NULL );
	BITMAP *pusher  = load_bitmap( "pusher.bmp", NULL );
	BITMAP *girder  = load_bitmap( "girder.bmp", NULL );
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);//used for double buffering
	FONT *font = load_font("karmaticArcade.pcx",NULL,NULL);
	/*END OF LOAD ASSETS*/

	/*SET INITAL DATA*/
	animXY.resize(7);
	animXY[0] = 0;
	animXY[1] = 0;
	animXY[2] = 0;
	animXY[3] = 32;
	animXY[4] = 0;
	animXY[5] = 0;
	animXY[6] = 0;
	direction.resize(2);
	direction[0] = 0;
	direction[1] = 1;
	timeLeft = 30;
	moveInt = 0;
	winTest = false;
	/*END OF SET INITAL DATA*/

	/*START TIMERS*/
	void bombAnim(void);
	void respondToKeyboard(void);
	void movePusherX(void);
	void countingDown(void);
	install_int( bombAnim,100 );
	install_int( respondToKeyboard,10 );
	install_int( movePusherX,10 );
	install_int( countingDown,1000 );
	/*END OF START TIMERS*/

	/*Loop while the escape key is not pressed*********************************************************************/
	while(!key[KEY_ESC])
	{	
		if(timeLeft == 11)//if there is only 10 seconds left play the countdown sound
		{
			play_sample( countdown, 255, 128, 1000, 0 );
		}

		if(timeLeft == 0)//if there is no time left play the loose sound and set the time left to -1
		{
			play_sample( lose, 255, 128, 1000, 0 );
			timeLeft = -1;
		}

		if(timeLeft < 0)//if the time is less than 0, AKA the game has been won or lost
		{

			/*WIN**************************************************************************/
			if (winTest)
			{
				blit( winGround,buffer, 0, 0, 0, 0, 640, 480 );//set the background to the win background
				textprintf_ex(buffer, font, 250, 36, makecol(0,0,0),-1, "SUCCESS!");//display win title
				textprintf_ex(buffer, font, 200, 68, makecol(0,0,0),-1, "TIME REMAINING %i", winTime);//display the score/time taken
			}
			/*WIN**************************************************************************/

			/*LOSE**************************************************************************/
			else
			{
				blit( loseGround,buffer, 0, 0, 0, 0, 640, 480 );//display the lose screen
				textprintf_ex(buffer, font, 250, 36, makecol(0,0,0),-1, "GAME OVER"); // display the lost title
			}
			/*LOSE**************************************************************************/

			masked_blit( resetHelp,buffer, 0, 0, 188, 160, resetHelp->w, resetHelp->h );//display the reset help
			masked_blit( exitHelp,buffer, 0, 0, 188, 224, exitHelp->w, exitHelp->h );//display the exit help
		}

		else // if none of the above then the game is still running and has more than 11 seconds left
		{
			//Test if both the bombs are placed on top of the holes, if they are and move int is not 0 then when the player stops pushing them, they will test true
			if(move->collision(data->getBombs(), data->getHolePositionX(0), data->getHolePositionY(0), 32, 32, 1, 32, 32, *data) != 0 &&
				move->collision(data->getBombs(), data->getHolePositionX(1), data->getHolePositionY(1), 32, 32, 1, 32, 32, *data) != 0 && moveInt == 0)
			{
				animXY[5]+=32;//set the hole animation to the open image

				/*loops for the number of bombs***********************************************************************************************/
				for(int i = 0; i < data->getBombs(); i++) //move the bombs off the screen so it appears they have dropped into the hole
				{
					animXY[6] = 32;//removes the light sprite
					data->setBombPositionX(i,640);
					data->setBombPositionY(i,i*32);
				}
				/*loops for the number of bombs***********************************************************************************************/

				play_sample( win, 128, 128, 1000, 0 );//plays the win sound
				install_int( holeAnim,150 );//animate the bomb drop
			}

			blit( ground,buffer, 0, 0, 0, 0, 640, 480 );//sets the background to the buffer

			/*loops for the number of bombs***********************************************************************************************/
			for (int i = 0;i < data->getBombs(); i++)
			{
				blit( hole,buffer, animXY[5], 0, data->getHolePositionX(i), data->getHolePositionY(i), 32, 32 );//sets the hole to the buffer
			}
			/*loops for the number of bombs***********************************************************************************************/

			/*loops for the number of bombs***********************************************************************************************/
			for (int i = 0;i < data->getBombs(); i++)// loops after holes so that bombs can go over holes
			{
				masked_blit( bomb,buffer, animXY[4], 0, data->getBombPositionX(i), data->getBombPositionY(i), 32, 32 );//sets the bomb to the buffer
				masked_blit( light,buffer, animXY[6], 0, data->getBombPositionX(i), data->getBombPositionY(i), 32, 32 );//sets the light to the buffer
			}
			/*loops for the number of bombs***********************************************************************************************/

			/*loops for the number of girders***********************************************************************************************/
			for (int i = 0;i < data->getGirders(); i++)
			{
				masked_blit( girder,buffer, 0, 0, data->getGirderPositionX(i), data->getGirderPositionY(i), girder->w, girder->h );//sets the girder to the buffer
			}
			/*loops for the number of girders***********************************************************************************************/

			/*loops for the number of pushers***********************************************************************************************/
			for (int i = 0;i < data->getPushers(); i++)
			{
				masked_blit( pusher,buffer, animXY[2], animXY[3], data->getPusherPositionX(i), data->getPusherPositionY(i), 32, 32 );//sets the pusher to the buffer
			}
			/*loops for the number of pushers***********************************************************************************************/

			/*Sets the help icons to the buffer*/
			masked_blit( resetHelp,buffer, 0, 0, 32, 0, resetHelp->w, resetHelp->h );
			masked_blit( exitHelp,buffer, 0, 0, 160, 0, exitHelp->w, exitHelp->h );
			masked_blit( gameHelp,buffer, 0, 0, 352, 0, gameHelp->w, gameHelp->h );
			masked_blit( moveHelp,buffer, 0, 0, 96, 448, moveHelp->w, moveHelp->h );
			/*Sets the help icons to the buffer*/

			masked_blit( player,buffer, animXY[0], animXY[1], data->getPlayerX(), data->getPlayerY(), 32, 32 );//sets the player to the buffer
			
			/*Sets the time left to the buffer*/
			masked_blit( countdownBack,buffer, 0, 0, 288, 0, 64, 32 );
			textprintf_ex(buffer, font, 304, 8, makecol(255,0,0),-1, "%i", timeLeft);
			/*Sets the time left to the buffer*/
		}
		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

	}
	/*End Loop when the escape key is pressed*********************************************************************/

	/*DESTROY DATA*/
	if(moveInt !=0)//check if the movePlayer32 int is running
	{
		remove_int( movePlayer32 );
	}
	remove_int( countingDown );
	remove_int( bombAnim );
	remove_int( movePusherX );
	remove_int( respondToKeyboard );
	animXY.resize(0);
	direction.resize(0);
	destroy_font(font);
	destroy_sample( lose );
	destroy_sample( win );
	destroy_sample( countdown );
	destroy_sample( slide );
	destroy_bitmap( countdownBack );
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
	destroy_bitmap( gameHelp );
	destroy_bitmap( moveHelp );
	destroy_bitmap( resetHelp );
	destroy_bitmap( exitHelp );
	destroy_bitmap( player );
	destroy_bitmap( pusher );
	destroy_bitmap( girder );
	destroy_bitmap( light );
	destroy_bitmap( buffer );
	delete data;
	delete move;
	/*END OF DESTROY DATA*/
	return 1;
}

void respondToKeyboard() // checks the keyaboard input
{
	if(key[KEY_W])
	{	
		/*UP*/
		if (moveInt == 0)
		{
			axis = true;
			direction[0] = -1;
			animXY[1] = 0;
			install_int( movePlayer32, 10 );
		}
		/*END OF UP*/
	}
	if(key[KEY_S])
	{
		/*DOWN*/
		if (moveInt == 0)
		{
			axis = true;
			direction[0] = 1;
			animXY[1] = 96;
			install_int( movePlayer32, 10 );
		}
		/*END OF DOWN*/
	}

	if(key[KEY_A])
	{
		/*LEFT*/
		if (moveInt == 0)
		{
			axis = false;
			direction[0] = -1;
			animXY[1] = 64;
			install_int( movePlayer32,10 );
		}
		/*END OF LEFT*/
	}
	if(key[KEY_D])
	{
		/*RIGHT*/
		if (moveInt == 0)
		{
			axis = false;
			direction[0] = 1;
			animXY[1] = 32;
			install_int( movePlayer32,10 );
		}

		/*END OF RIGHT*/
	}
	if(key[KEY_R])
	{
		/*RESET GAME*/
		data->loadFile(fileName, level);
		animXY[1] = 0;
		animXY[0] = 0;
		animXY[4] = 0;
		animXY[6] = 0;
		moveInt = 0;
		timeLeft = 30;
		/*END OF RESET GAME*/
	}
}

void movePlayer32()//moves the player in sets of 32, this is to give the feeling of a tile based game as all of the objects are 32X32
{
	move->movePlayer(axis, direction[0], *data);//loads the movePlayer function in the moveEntity class to set the new positions

	/*get the new values for data from the getters in moveEntity class*/
	animXY[6] = move->getLightAnim();
	if (animXY[6] != 0 && moveInt == 0)
	{
		play_sample( slide, 255, 128, 1000, 0 );
	}
	data->setPlayerX(move->getPlayerX());
	data->setPlayerY(move->getPlayerY());
	for (int i = 0; i < data->getBombs(); i++)
	{
		data->setBombPositionX(i,move->getBombX(i));
		data->setBombPositionY(i,move->getBombY(i));
	}
	/*get the new values for data from the getters in moveEntity class*/

	//animate the player
	animXY[0] += 32;
	if(animXY[0] > 64 )
	{
		animXY[0] = 0;
	}
	moveInt++;
	if(moveInt==32) //if 32 runs of this timer has been done then stop the timer
	{
		moveInt = 0;
		remove_int( movePlayer32 );
	}
}

void movePusherX()// moves the enemy pusher constantly
{
	/*loop for the number of pushers*************************************************************/
	for(int i = 0; i < data->getPushers(); i++)
	{
		if (data->getPusherPositionX(i) >= (data->getFirstPusherPositionX(i) + data->getPusherRange())) //check if the pusher is greater then or equal to the maximum point the pusher can go to
		{
			direction[1] = -1;//if yes set the direction to -1 and the pusher y animation to 64
			animXY[3] = 64;
		}
		else if (data->getPusherPositionX(i) <= data->getFirstPusherPositionX(i))// if no check if the pusher is greater then or equal to the minimum point the pusher can go to
		{
			direction[1] = 1;//if yes set the direction to 1 and the pusher y animation to 32
			animXY[3] = 32;
		}

		int tmp = 0;
		
		/*loop for the number of bombs**********************************************************************************/
		for(int a = 0; a < data->getBombs(); a++)
		{
			if(move->collision(data->getBombs(),data->getPusherPositionX(i), data->getPusherPositionY(i), 32, 32, 1, 32, 32, *data) == 1)//bomb collision check
			{
				tmp = a;// if true set tmp to a
			}
		}
		/*loop for the number of bombs**********************************************************************************/

		if (tmp !=0)// if tmp is not equal to 0 then the pusher collided with a bomb
		{
			int tmp2 = data->getBombPositionX(tmp);//get the position of the collided bomb
			if (tmp2 != data->getFirstPusherPositionX(i)-32 && tmp2 != (data->getFirstPusherPositionX(i) + data->getPusherRange())+32)// if the bomb is inside the path of the pusher then move the bomb with the pusher
			{
				data->setBombPositionX(tmp, tmp2 + direction[1]);
			}
		}

		data->setPusherPositionX(i, data->getPusherPositionX(i) + direction[1]);// move the pusher

		//animate pusher
		animXY[2] += 32;
		if(animXY[2] > 64 )
		{
			animXY[2] = 0;
		}
	}
	/*loop for the number of pushers*************************************************************/
}

void bombAnim()//animates the bombs
{
	animXY[4]+=32;
	if(animXY[4]>96)
	{
		animXY[4] = 0;
	}
}

void holeAnim()//animates the holes, when the animation has finished then the player wins
{
	animXY[5]+=32;
	if(animXY[5]>224)
	{
		animXY[5] = 0;
		remove_int( holeAnim );
		winTime = timeLeft;
		timeLeft = -1;
		winTest  = true;
	}
}

void countingDown()//counts down the time left
{
	timeLeft--;
}

