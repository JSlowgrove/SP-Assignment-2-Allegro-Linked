#include "game.h"

Game::Game()
{	
}

/*GLOBALS FOR USE WITH TIMERS*/
std::vector<int> animXY; //0 = playerAnimX, 1 = playerAnimY, 2 = pusherAnimX, 3 = pusherAnimY, 4 = bombAnimX, 5 = holeAnimX, 6 = lightAnimX
std::vector<int> direction;//0 = playerDirection, 1 = pusherDirection
int timeLeft;
FileLoader data;
MoveEntity move;
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
	data.loadFile(fileName, level);
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

	while(!key[KEY_ESC])
	{	
		if(timeLeft == 11)
		{
			play_sample( countdown, 255, 128, 1000, 0 );
		}
		if(timeLeft == 0)
		{
			play_sample( lose, 255, 128, 1000, 0 );
			timeLeft = -1;
		}
		if(timeLeft < 0)
		{
			if (winTest)
			{
				blit( winGround,buffer, 0, 0, 0, 0, 640, 480 );
				textprintf_ex(buffer, font, 250, 36, makecol(0,0,0),-1, "SUCCESS!");
				textprintf_ex(buffer, font, 200, 68, makecol(0,0,0),-1, "TIME REMAINING %i", winTime);
			}
			else
			{
				blit( loseGround,buffer, 0, 0, 0, 0, 640, 480 );
				textprintf_ex(buffer, font, 250, 36, makecol(0,0,0),-1, "GAME OVER");
			}
			masked_blit( resetHelp,buffer, 0, 0, 188, 160, resetHelp->w, resetHelp->h );
			masked_blit( exitHelp,buffer, 0, 0, 188, 224, exitHelp->w, exitHelp->h );
		}
		else
		{
			if(data.getBombPositionX(0) == data.getHolePositionX(0) && data.getBombPositionY(0) == data.getHolePositionY(0) &&
				data.getBombPositionX(1) == data.getHolePositionX(1) && data.getBombPositionY(1) == data.getHolePositionY(1) ||
				data.getBombPositionX(0) == data.getHolePositionX(0) && data.getBombPositionY(1) == data.getHolePositionY(1) &&
				data.getBombPositionX(1) == data.getHolePositionX(1) && data.getBombPositionY(0) == data.getHolePositionY(0) )
			{
				animXY[5]+=32;
				for(int i = 0; i < data.getBombs(); i++)
				{
					animXY[6] = 32;
					data.setBombPositionX(i,640);
					data.setBombPositionY(i,i*32);
				}
				play_sample( win, 128, 128, 1000, 0 );
				install_int( holeAnim,150 );
			}
			blit( ground,buffer, 0, 0, 0, 0, 640, 480 );		
			for (int i = 0;i < data.getBombs(); i++)
			{
				blit( hole,buffer, animXY[5], 0, data.getHolePositionX(i), data.getHolePositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getBombs(); i++)
			{
				masked_blit( bomb,buffer, animXY[4], 0, data.getBombPositionX(i), data.getBombPositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getBombs(); i++)
			{
				masked_blit( light,buffer, animXY[6], 0, data.getBombPositionX(i), data.getBombPositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getGirders(); i++)
			{
				masked_blit( girder,buffer, 0, 0, data.getGirderPositionX(i), data.getGirderPositionY(i), girder->w, girder->h );
			}
			for (int i = 0;i < data.getPushers(); i++)
			{
				masked_blit( pusher,buffer, animXY[2], animXY[3], data.getPusherPositionX(i), data.getPusherPositionY(i), 32, 32 );
			}
			masked_blit( countdownBack,buffer, 0, 0, 288, 0, 64, 32 );
			masked_blit( resetHelp,buffer, 0, 0, 32, 0, resetHelp->w, resetHelp->h );
			masked_blit( exitHelp,buffer, 0, 0, 160, 0, exitHelp->w, exitHelp->h );
			masked_blit( gameHelp,buffer, 0, 0, 352, 0, gameHelp->w, gameHelp->h );
			masked_blit( moveHelp,buffer, 0, 0, 96, 448, moveHelp->w, moveHelp->h );
			masked_blit( player,buffer, animXY[0], animXY[1], data.getPlayerX(), data.getPlayerY(), 32, 32 );
			textprintf_ex(buffer, font, 304, 8, makecol(255,0,0),-1, "%i", timeLeft);
		}
		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

	}

	/*DESTROY DATA*/
	if(moveInt !=0)
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
	/*END OF DESTROY DATA*/
	return 1;
}


void movePusherX()
{
	for(int i = 0; i < data.getPushers(); i++)
	{
		if (data.getPusherPositionX(i) > (data.getFirstPusherPositionX(i) + data.getPusherRange()))
		{
			direction[1] = -1;
			animXY[3] = 64;
		}
		else if (data.getPusherPositionX(i) < data.getFirstPusherPositionX(i))
		{
			direction[1] = 1;
			animXY[3] = 32;
		}
		int tmp = 0;
		for(int a = 0; a < data.getBombs(); a++)
		{
			if(move.collision(data.getBombs(),data.getPusherPositionX(i), data.getPusherPositionY(i), 32, 32, 1, 32, 32, data) == 1)//bomb collision check
			{
				tmp = a;
			}
		}
		if (tmp !=0)
		{
			int tmp2 = data.getBombPositionX(tmp);
			if (tmp2 != data.getFirstPusherPositionX(i)-32 && tmp2 != (data.getFirstPusherPositionX(i) + data.getPusherRange())+32)
			{
				data.setBombPositionX(tmp, tmp2 + direction[1]);
			}
		}
		data.setPusherPositionX(i, data.getPusherPositionX(i) + direction[1]);
		animXY[2] += 32;
		if(animXY[2] > 64 )
		{
			animXY[2] = 0;
		}
	}
}

void bombAnim()
{
	animXY[4]+=32;
	if(animXY[4]>96)
	{
		animXY[4] = 0;
	}
}

void holeAnim()
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

void respondToKeyboard()
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
		data.loadFile(fileName, level);
		animXY[1] = 0;
		animXY[0] = 0;
		animXY[4] = 0;
		animXY[6] = 0;
		moveInt = 0;
		timeLeft = 30;
		/*END OF RESET GAME*/
	}
}

void movePlayer32()
{
	move.movePlayer(axis, direction[0], data);
	animXY[6] = move.getLightAnim();
	if (animXY[6] != 0 && moveInt == 0)
	{
		play_sample( slide, 255, 128, 1000, 0 );
	}
	data.setPlayerX(move.getPlayerX());
	data.setPlayerY(move.getPlayerY());
	for (int i = 0; i < data.getBombs(); i++)
	{
		data.setBombPositionX(i,move.getBombX(i));
		data.setBombPositionY(i,move.getBombY(i));
	}
	animXY[0] += 32;
	if(animXY[0] > 64 )
	{
		animXY[0] = 0;
	}
	moveInt++;
	if(moveInt==32)
	{
		moveInt = 0;
		remove_int( movePlayer32 );
	}
}

void countingDown()
{
	timeLeft--;
}

