#include <allegro.h>
#include <vector>

struct position
{
	int x;
	int y;
};

void respondToKeyboard(void);
void bombAnim(void);
void movePusherX(void);
bool girderCollision();
SAMPLE *music;
BITMAP *ground;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;
BITMAP *buffer;//used for double buffering
volatile position playerXY;
volatile int playerAnimY;
volatile int playerAnimX;
volatile int bombAnimX;
std::vector<position> girderPosition;
std::vector<position> bombPosition;
std::vector<position> originalPusherPosition;
std::vector<position> pusherPosition;
int pusherRange = 6;
int numberOfPushers = 1;
int	pusherDirection = 1;

int main(void)
{
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	install_timer();
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	int numberOfBombs = 2;
	int numberOfGirders = 66;
	girderPosition.resize(numberOfGirders);
	bombPosition.resize(numberOfBombs);
	pusherPosition.resize(numberOfPushers);
	originalPusherPosition.resize(numberOfPushers);
	buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	music = load_sample( "killingTime.wav" );
	ground = load_bitmap( "floor.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	//play_sample( music, 255, 128, 1000, 1 );
	pusherPosition[0].x = 32;
	pusherPosition[0].y = 96;
	playerXY.x = 32;
	playerXY.y = 32;
	playerAnimY = 0;
	playerAnimX = 0;
	bombAnimX = 2;
	girderPosition.resize(numberOfGirders);
	bombPosition.resize(numberOfBombs);
	pusherPosition.resize(numberOfPushers);
	originalPusherPosition.resize(numberOfPushers);
	for(int i = 0; i < numberOfPushers; i++)
	{
		originalPusherPosition[i].x = pusherPosition[i].x;
		originalPusherPosition[i].y = pusherPosition[i].y;
	}
	int a = 0;
	for (int i = 0;i < 20; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 0;
		a++;
	}
	a = 0;
	for (int i = 20;i < 40; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 448;
		a++;
	}
	a = 1;
	for (int i = 40; i < 53; i++)
	{
		girderPosition[i].x = 0;
		girderPosition[i].y = (a*32);
		a++;
	}
	a = 1;
	for (int i = 53;i < 66; i++)
	{
		girderPosition[i].x = 608;
		girderPosition[i].y = (a*32);
		a++;
	}
	bombPosition[0].x = 64;
	bombPosition[0].y = 64;
	bombPosition[1].x = 128;
	bombPosition[1].y = 128;
	install_int( bombAnim,100 );
	install_int( respondToKeyboard,10 );
	install_int( movePusherX,10 );
	while(!key[KEY_ESC])
	{	
		blit( ground,buffer, 0, 0, 0, 0, 640, 480 );		
		masked_blit( hole,buffer, 0, 0, 32, 64, 32, 32 );
		for (int i = 0;i < numberOfBombs; i++)
		{
			masked_blit( bomb,buffer, bombAnimX, 2, bombPosition[i].x, bombPosition[i].y, 28, 28 );
		}
		for (int i = 0;i < numberOfGirders; i++)
		{
			masked_blit( girder,buffer, 0, 0, girderPosition[i].x, girderPosition[i].y, girder->w, girder->h );
		}
		for (int i = 0;i < numberOfPushers; i++)
		{
			masked_blit( pusher,buffer, 0, 0, pusherPosition[i].x, pusherPosition[i].y, 32, 32 );
		}
		masked_blit( player,buffer, playerAnimX, playerAnimY, playerXY.x, playerXY.y, 32, 32 );
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
	}
	destroy_sample( music );
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
	destroy_bitmap( player );
	destroy_bitmap( pusher );
	destroy_bitmap( girder );
	remove_int( bombAnim );
	remove_int( respondToKeyboard );
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
			x2 = girderPosition[i].x;
			y2 = girderPosition[i].y;
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
	for(int i = 0; i < numberOfPushers; i++)
	{
		if (pusherPosition[i].x > (originalPusherPosition[i].x + (pusherRange*32)))
		{
			pusherDirection = -1;
		}
		else if (pusherPosition[i].x < originalPusherPosition[i].x)
		{
			pusherDirection = 1;
		}
		pusherPosition[i].x+=pusherDirection;
	}
}

void movePlayer(bool axis, int direction)
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
		if(collision(2,playerXY.x, playerXY.y, 32, 32, 1, 28, 28) == false)//bomb collision check
		{
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				switch(axis)
				{
					case false:
						bombPosition[i].x+=direction;
						break;
					case true:
						bombPosition[i].y+=direction;					
						break;
				}
				if(collision(66,bombPosition[i].x, bombPosition[i].y, 28, 28, 0, 32, 32) == false && collision(1, bombPosition[1].x, bombPosition[1].y, 28, 28, 1, 28, 28) == false) //bomb girder collision check and bomb bomb collision check
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
	switch(bombAnimX)
	{
	case 2:
		bombAnimX = 34;
		break;
	case 34:
		bombAnimX = 66;
		break;
	case 66:
		bombAnimX = 98;
		break;
	case 98:
		bombAnimX = 2;
	break;
	}
}

void respondToKeyboard()
{
	if(key[KEY_W])
	{	
		movePlayer(true, -1);
		playerAnimY = 0;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_S])
	{
		movePlayer(true, 1);
		playerAnimY = 96;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}

	if(key[KEY_A])
	{
		movePlayer(false, -1);
		playerAnimY = 64;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_D])
	{
		movePlayer(false, 1);
		playerAnimY = 32;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_R])
	{
		playerXY.x = 32;
		playerXY.y = 32;
		playerAnimY = 0;
		playerAnimX = 0;
		bombAnimX = 2;
		bombPosition[0].x = 64;
		bombPosition[0].y = 64;
		bombPosition[1].x = 128;
		bombPosition[1].y = 128;
	}
}
