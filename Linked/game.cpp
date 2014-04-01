#include "fileLoader.h"
#include "collisionDetection.h"
#include "game.h"

Game::Game()
{	
}

struct position
{
	int x;
	int y;
};

void respondToKeyboard(void);
void bombAnim(void);
void holeAnim(void);
void movePlayer32(void);
void movePusherX(void);
void countingDown(void);
void backgroundMusic(void);
SAMPLE *musicPart1;
SAMPLE *musicPart2;
SAMPLE *musicPart3;
SAMPLE *win;
SAMPLE *lose;
SAMPLE *slide;
SAMPLE *countdown;
BITMAP *logo;
BITMAP *light;
BITMAP *ground;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;
BITMAP *buffer;//used for double buffering
FONT *font;

volatile int playerAnimY;
volatile int playerAnimX;
volatile int pusherAnimY;
volatile int pusherAnimX;
volatile int bombAnimX;
volatile int holeAnimX;
volatile int lightAnimX;
FileLoader data;
CollisionDetection collision;
std::string fileName = "preBuiltLevels.txt";
//string fileName = "customBuiltLevels.txt";
int moveInt = 0;
bool axis;
int direction;
int timeLeft = 90;
int currentMusic = 1;
int pusherDirection;

int Game::gameStart()
{
	/*LEVEL STARTUP*/
	data.loadFile(fileName);
	/*LEVEL STARTUP*/

	/*LOAD ASSETS*/
	font = load_font("karmaticArcade.pcx",NULL,NULL);
	buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	musicPart1 = load_sample( "killingTime1.wav" );
	musicPart2 = load_sample( "killingTime2.wav" );
	musicPart3 = load_sample( "killingTime3.wav" );
	lose = load_sample( "lose.wav" );
	win = load_sample( "win.wav" );
	countdown = load_sample( "countdownBeep.wav" );
	slide = load_sample( "slide.wav" );
	ground = load_bitmap( "floor.bmp", NULL );
	logo = load_bitmap( "linkedLogo.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	light = load_bitmap( "moveLight.bmp", NULL );
	/*END OF LOAD ASSETS*/

	/*SET INITAL DATA*/
	playerAnimY = 0;
	playerAnimX = 0;
	pusherAnimY = 32;
	pusherAnimX = 0;
	bombAnimX = 0;
	holeAnimX = 0;
	lightAnimX = 0;
	pusherDirection = 1;
	/*END OF SET INITAL DATA*/

	/*START TIMERS*/
	install_int( bombAnim,100 );
	install_int( respondToKeyboard,10 );
	install_int( movePusherX,10 );
	install_int( countingDown,1000 );
	install_int( backgroundMusic,68023 );
	/*END OF START TIMERS*/

	play_sample( musicPart1, 255, 128, 1000, 0 );

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
			blit( ground,buffer, 0, 0, 0, 0, 640, 480 );		
			for (int i = 0;i < data.getBombs(); i++)
			{
				blit( hole,buffer, holeAnimX, 0, data.getHolePositionX(i), data.getHolePositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getBombs(); i++)
			{
				masked_blit( bomb,buffer, bombAnimX, 0, data.getBombPositionX(i), data.getBombPositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getBombs(); i++)
			{
				masked_blit( light,buffer, lightAnimX, 0, data.getBombPositionX(i), data.getBombPositionY(i), 32, 32 );
			}
			for (int i = 0;i < data.getGirders(); i++)
			{
				masked_blit( girder,buffer, 0, 0, data.getGirderPositionX(i), data.getGirderPositionY(i), girder->w, girder->h );
			}
			for (int i = 0;i < data.getPushers(); i++)
			{
				masked_blit( pusher,buffer, pusherAnimX, pusherAnimY, data.getPusherPositionX(i), data.getPusherPositionY(i), 32, 32 );
			}
			masked_blit( player,buffer, playerAnimX, playerAnimY, data.getPlayerX(), data.getPlayerY(), 32, 32 );
			textprintf_ex(buffer, font, 308, 6, makecol(255,0,0),-1, "%i", timeLeft);
		}
		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
	}

	/*DESTROY DATA*/
	destroy_font(font);
	destroy_sample( lose );
	destroy_sample( win );
	destroy_sample( countdown );
	destroy_sample( slide );
	destroy_sample( musicPart1 );
	destroy_sample( musicPart2 );
	destroy_sample( musicPart3 );
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
	destroy_bitmap( player );
	destroy_bitmap( pusher );
	destroy_bitmap( girder );
	destroy_bitmap( light );
	destroy_bitmap( buffer );
	remove_int( backgroundMusic );
	remove_int( bombAnim );
	remove_int( movePusherX );
	remove_int( respondToKeyboard );	
	/*END OF DESTROY DATA*/
	return 1;
}


	void movePusherX()
{
	for(int i = 0; i < data.getPushers(); i++)
	{
		if (data.getPusherPositionX(i) > (data.getFirstPusherPositionX(i) + data.getPusherRange()))
		{
			pusherDirection = -1;
			pusherAnimY = 64;
		}
		else if (data.getPusherPositionX(i) < data.getFirstPusherPositionX(i))
		{
			pusherDirection = 1;
			pusherAnimY = 32;
		}
		data.setPusherPositionX(i, data.getPusherPositionX(i) + pusherDirection);
		pusherAnimX += 32;
		if(pusherAnimX > 64 )
		{
			pusherAnimX = 0;
		}
	}
}

void movePlayer()
{

	switch(axis)
	{
	case false:
		data.setPlayerX(data.getPlayerX()+direction);
		break;
	case true:
		data.setPlayerY(data.getPlayerY()+direction);					
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
			data.setPlayerX(data.getPlayerX()-direction);
			break;
		case true:
			data.setPlayerY(data.getPlayerY()-direction);				
			break;
		}
	}
	if(collision.collision(data.getBombs(),data.getPlayerX(), data.getPlayerY(), 32, 32, 1, 32, 32, data) == false)//bomb collision check
	{
		lightAnimX = 0;
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			switch(axis)
			{
			case false:
				data.setBombPositionX(i,data.getBombPositionX(i)+direction);
				switch(direction)
				{
				case -1:
					lightAnimX = 96;
					break;
				case 1:
					lightAnimX = 128;
					break;
				}
				break;
			case true:
				data.setBombPositionY(i,data.getBombPositionY(i)+direction);
				switch(direction)
				{
				case -1:
					lightAnimX = 32;
					break;
				case 1:
					lightAnimX = 64;
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
					data.setBombPositionX(i,data.getBombPositionX(i)-direction);
					data.setPlayerX(data.getPlayerX()-direction);
					break;
				case true:
					data.setBombPositionY(i,data.getBombPositionY(i)-direction);
					data.setPlayerY(data.getPlayerY()-direction);
					break;
				}
			}
		}
	}
}

void bombAnim()
{
	bombAnimX+=32;
	if(bombAnimX>96)
	{
		bombAnimX = 0;
	}
}

void holeAnim()
{
	holeAnimX+=32;
	if(holeAnimX>224)
	{
		holeAnimX = 0;
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
			direction = -1;
			playerAnimY = 0;
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
			direction = 1;
			playerAnimY = 96;
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
			direction = -1;
			playerAnimY = 64;
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
			direction = 1;
			playerAnimY = 32;
			install_int( movePlayer32,10 );
		}

		/*END OF RIGHT*/
	}
	if(key[KEY_R])
	{
		/*RESET GAME*/
		data.loadFile(fileName);
		playerAnimY = 0;
		playerAnimX = 0;
		bombAnimX = 0;
		lightAnimX = 0;
		moveInt = 0;
		timeLeft = 90;
		/*END OF RESET GAME*/
	}
	if(key[KEY_B])
	{
		for(int i = 0; i < data.getBombs(); i++)
		{
			holeAnimX = 32;
			data.setBombPositionX(i,640);
			data.setBombPositionY(i,i*32);
		}
		play_sample( win, 128, 128, 1000, 0 );
		install_int( holeAnim,150 );
	}
}

void movePlayer32()
{
	movePlayer();
	playerAnimX += 32;
	if(playerAnimX > 64 )
	{
		playerAnimX = 0;
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

void backgroundMusic()
{
	switch(currentMusic)
	{
	case 0:
		play_sample( musicPart1, 255, 128, 1000, 0 );
		currentMusic = 1;
		break;
	case 1:
		play_sample( musicPart2, 255, 128, 1000, 0 );
		currentMusic = 2;
		break;
	case 2:
		play_sample( musicPart3, 255, 128, 1000, 0 );
		currentMusic = 0;
		break;
	}
}