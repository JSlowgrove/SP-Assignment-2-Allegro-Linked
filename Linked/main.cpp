#include "fileLoader.h"
#include <allegro.h>
#include <vector>

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
SAMPLE *music;
BITMAP *light;
BITMAP *ground;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;
BITMAP *buffer;//used for double buffering

/*TEMP------------------------------------------------------------------------------*/
FONT *font;
/*TEMP------------------------------------------------------------------------------*/

volatile position playerXY;
volatile int playerAnimY;
volatile int playerAnimX;
volatile int pusherAnimY;
volatile int pusherAnimX;
volatile int bombAnimX;
volatile int holeAnimX;
volatile int lightAnimX;
std::vector<position> bombPosition;
std::vector<position> pusherPosition;
int	pusherDirection;
FileLoader data;
int moveInt = 0;
bool axis;
int direction;

int main(void)
{
	/*ALLEGRO STARTUP*/
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	install_timer();
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	/*END OF ALLEGRO STARTUP*/

	/*TEMP------------------------------------------------------------------------------*/
	font = load_font("pongfont.pcx",NULL,NULL);
	/*TEMP------------------------------------------------------------------------------*/

	/*LEVEL STARTUP*/
	data.loadFile("preBuiltLevels.txt");
	//data.loadFile("customBuiltLevels.txt");
	bombPosition.resize(data.getBombs());
	pusherPosition.resize(data.getPushers());
	/*LEVEL STARTUP*/

	/*LOAD ASSETS*/
	buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	music = load_sample( "killingTime.wav" );
	ground = load_bitmap( "floor.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	light = load_bitmap( "moveLight.bmp", NULL );
	/*END OF LOAD ASSETS*/

	//play_sample( music, 255, 128, 1000, 1 );

	/*SET INITAL DATA*/
	playerXY.x = data.getPlayerX();
	playerXY.y = data.getPlayerY();
	playerAnimY = 0;
	playerAnimX = 0;
	pusherAnimY = 32;
	pusherAnimX = 0;
	bombAnimX = 0;
	holeAnimX = 0;
	lightAnimX = 0;
	pusherDirection = 1;
	/*END OF SET INITAL DATA*/

	/*SET PUSHER START*/
	for(int i = 0; i < data.getPushers(); i++)
	{
		pusherPosition[i].x = data.getPusherPositionX(i);
		pusherPosition[i].y = data.getPusherPositionY(i);
	}
	/*END SET PUSHER START*/

	/*SET BOMB START*/
	for(int i = 0; i < data.getBombs(); i++)
	{
		bombPosition[i].x = data.getBombPositionX(i);
		bombPosition[i].y = data.getBombPositionY(i);
	}
	/*END SET BOMB START*/

	/*START TIMERS*/
	install_int( bombAnim,100 );
	install_int( respondToKeyboard,10 );
	install_int( movePusherX,10 );
	/*END OF START TIMERS*/

	while(!key[KEY_ESC])
	{	
		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( ground,buffer, 0, 0, 0, 0, 640, 480 );		
		for (int i = 0;i < data.getBombs(); i++)
		{
			blit( hole,buffer, holeAnimX, 0, data.getHolePositionX(i), data.getHolePositionY(i), 32, 32 );
		}
		for (int i = 0;i < data.getBombs(); i++)
		{
			masked_blit( bomb,buffer, bombAnimX, 0, bombPosition[i].x, bombPosition[i].y, 32, 32 );
		}
		for (int i = 0;i < data.getBombs(); i++)
		{
			masked_blit( light,buffer, lightAnimX, 0, bombPosition[i].x, bombPosition[i].y, 32, 32 );
		}
		for (int i = 0;i < data.getGirders(); i++)
		{
			masked_blit( girder,buffer, 0, 0, data.getGirderPositionX(i), data.getGirderPositionY(i), girder->w, girder->h );
		}
		for (int i = 0;i < data.getPushers(); i++)
		{
			masked_blit( pusher,buffer, pusherAnimX, pusherAnimY, pusherPosition[i].x, pusherPosition[i].y, 32, 32 );
		}
		masked_blit( player,buffer, playerAnimX, playerAnimY, playerXY.x, playerXY.y, 32, 32 );

		/*TEMP------------------------------------------------------------------------------*/
		//	textprintf_ex(buffer, font, 200, 200, makecol(0,0,0),-1, "%i", data.getPusherRange());
		/*TEMP------------------------------------------------------------------------------*/

		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		/*ANIMATION*/
		bool test = false; ////test setting off an animation at certain point
		for(int i = 0; i < data.getBombs(); i++)
		{
			if (playerXY.x == data.getHolePositionX(i) && playerXY.y == data.getHolePositionY(i) )
			{
				test = true;
			}
		}
		if (test == true)
		{
			install_int( holeAnim,150 );
		}
		/*END OF ANIMATION*/
	}

	/*DESTROY DATA*/
	destroy_sample( music );
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
	destroy_bitmap( player );
	destroy_bitmap( pusher );
	destroy_bitmap( girder );
	remove_int( bombAnim );
	remove_int( respondToKeyboard );	
	/*END OF DESTROY DATA*/
	return 0;
}
END_OF_MAIN()

int boundingBox(int object1X, int object1Y, int object1Width, int object1Height, int object2X, int object2Y, int object2Width, int object2Height)//made using http://wiki.allegro.cc/index.php?title=Bounding_Box
{ 
    if ((object1X > object2X + object2Width - 1) || // check if object 1 is to the right of object 2
        (object1Y > object2Y + object2Height - 1) || // check if object 1 is under object 2
        (object2X > object1X + object1Width - 1) || // check if object 2 is to the right of object 1
        (object2Y > object1Y + object1Height - 1))   // check if object 2 is under object 1
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

bool collision(int index, int x1, int y1, int w1, int h1, int typeOfCollison, int w2, int h2)
{
	int x2,y2;
	bool crash = false;
	for (int i = 0; i < index; i++)
	{
		switch(typeOfCollison)
		{
		case 0:
			x2 = data.getGirderPositionX(i);
			y2 = data.getGirderPositionY(i);
			break;
		case 1:
			x2 = bombPosition[i].x;
			y2 = bombPosition[i].y;
			break;
		}
		if(boundingBox(x1, y1, w1, h1, x2, y2, w2, h2) == 1)
		{
			crash = true;
		}
	}
	return crash;
}

void movePusherX()
{
	for(int i = 0; i < data.getPushers(); i++)
	{
		if (pusherPosition[i].x > (data.getPusherPositionX(i) + (data.getPusherRange())))
		{
			pusherDirection = -1;
			pusherAnimY = 64;
		}
		else if (pusherPosition[i].x < data.getPusherPositionX(i))
		{
			pusherDirection = 1;
			pusherAnimY = 32;
		}
		pusherPosition[i].x+=pusherDirection;
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
				playerXY.x+=direction;
				break;
			case true:
				playerXY.y+=direction;					
				break;
		}
		if(collision(66,playerXY.x, playerXY.y, 32, 32, 0, 32, 32) == false)
		{
		}
		else
		{
			switch(axis)
			{
				case false:
					playerXY.x-=direction;
					break;
				case true:
					playerXY.y-=direction;					
					break;
			}
		}
		if(collision(2,playerXY.x, playerXY.y, 32, 32, 1, 32, 32) == false)//bomb collision check
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
						bombPosition[i].x+=direction;
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
						bombPosition[i].y+=direction;
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
				if(collision(66,bombPosition[i].x, bombPosition[i].y, 32, 32, 0, 32, 32) == false && collision(1, bombPosition[1].x, bombPosition[1].y, 32, 32, 1, 32, 32) == false) //bomb girder collision check and bomb bomb collision check
				{
				}
				else
				{
					switch(axis)
					{
						case false:
							bombPosition[i].x-=direction;
							playerXY.x-=direction;
							break;
						case true:
							bombPosition[i].y-=direction;
							playerXY.y-=direction;
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
		playerXY.x = data.getPlayerX();
		playerXY.y = data.getPlayerY();
		playerAnimY = 0;
		playerAnimX = 0;
		bombAnimX = 0;
		moveInt = 0;
		for(int i = 0; i < data.getBombs(); i++)
		{
			bombPosition[i].x = data.getBombPositionX(i);
			bombPosition[i].y = data.getBombPositionY(i);
		}
		for(int i = 0; i < data.getPushers(); i++)
		{
			pusherPosition[i].x = data.getPusherPositionX(i);
			pusherPosition[i].y = data.getPusherPositionY(i);
		}
		/*END OF RESET GAME*/
	}
	if(key[KEY_B])
	{
		for(int i = 0; i < data.getBombs(); i++)
		{
			holeAnimX = 32;
			bombPosition[i].x = 640;
			bombPosition[i].y = i*32;
		}
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

