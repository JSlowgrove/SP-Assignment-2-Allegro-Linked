#include "game.h"

Game::Game()
{	
}

/*GLOBALS FOR USE WITH TIMERS*/
std::vector<int> animXY; //0 = playerAnimX, 1 = playerAnimY, 2 = pusherAnimX, 3 = pusherAnimY, 4 = bombAnimX, 5 = holeAnimX, 6 = lightAnimX
std::vector<int> direction;//0 = playerDirection, 1 = pusherDirection
int timeLeft;
FileLoader data;
void movePlayer32(void);
void holeAnim(void);
SAMPLE *slide;
SAMPLE *win;
std::string fileName;
int level;
int moveInt;
bool axis;
CollisionDetection collision;
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
	BITMAP *logo = load_bitmap( "linkedLogo.bmp", NULL );
	BITMAP *light = load_bitmap( "moveLight.bmp", NULL );
	BITMAP *ground = load_bitmap( "floor.bmp", NULL );
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
	timeLeft = 90;
	moveInt = 0;
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
			remove_int( countingDown );
			timeLeft = -1053;//lose
		}
		if(timeLeft < 0)
		{
			remove_int( bombAnim );
			remove_int( movePusherX );
			clear_to_color(buffer, makecol(255,0,0));
			textprintf_ex(buffer, font, 300, 36, makecol(0,0,0),-1, "GAME OVER");
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
			masked_blit( player,buffer, animXY[0], animXY[1], data.getPlayerX(), data.getPlayerY(), 32, 32 );
			textprintf_ex(buffer, font, 308, 6, makecol(255,0,0),-1, "%i", timeLeft);
		}
		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

	}

	/*DESTROY DATA*/
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
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
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
		data.setPusherPositionX(i, data.getPusherPositionX(i) + direction[1]);
		animXY[2] += 32;
		if(animXY[2] > 64 )
		{
			animXY[2] = 0;
		}
	}
}

void movePlayer()
{
	switch(axis)
	{
	case false:
		data.setPlayerX(data.getPlayerX()+direction[0]);
		break;
	case true:
		data.setPlayerY(data.getPlayerY()+direction[0]);					
		break;
	}
	if(collision.collision(data.getGirders(),data.getPlayerX(), data.getPlayerY(), 32, 32, 0, 32, 32, data) == false)
	{
	}
	else
	{
		switch(axis)
		{
		case false:
			data.setPlayerX(data.getPlayerX()-direction[0]);
			break;
		case true:
			data.setPlayerY(data.getPlayerY()-direction[0]);				
			break;
		}
	}
	if(collision.collision(data.getBombs(),data.getPlayerX(), data.getPlayerY(), 32, 32, 1, 32, 32, data) == false)//bomb collision check
	{
		animXY[6] = 0;
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			switch(axis)
			{
			case false:
				data.setBombPositionX(i,data.getBombPositionX(i)+direction[0]);
				switch(direction[0])
				{
				case -1:
					animXY[6] = 96;
					break;
				case 1:
					animXY[6] = 128;
					break;
				}
				break;
			case true:
				data.setBombPositionY(i,data.getBombPositionY(i)+direction[0]);
				switch(direction[0])
				{
				case -1:
					animXY[6] = 32;
					break;
				case 1:
					animXY[6] = 64;
					break;
				}
				break;
			}
			if (moveInt == 0)
			{
				play_sample( slide, 255, 128, 1000, 0 );
			}
			if(collision.collision(data.getGirders(),data.getBombPositionX(1), data.getBombPositionX(1), 32, 32, 0, 32, 32, data) == false && 
				collision.collision(data.getBombs(), data.getBombPositionX(1), data.getBombPositionX(1), 32, 32, 1, 32, 32, data) == false) //bomb girder collision check and bomb bomb collision check
			{
			}
			else
			{
				switch(axis)
				{
				case false:
					data.setBombPositionX(i,data.getBombPositionX(i)-direction[0]);
					data.setPlayerX(data.getPlayerX()-direction[0]);
					break;
				case true:
					data.setBombPositionY(i,data.getBombPositionY(i)-direction[0]);
					data.setPlayerY(data.getPlayerY()-direction[0]);
					break;
				}
			}
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
		timeLeft = 90;
		/*END OF RESET GAME*/
	}
}

void movePlayer32()
{
	movePlayer();
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

