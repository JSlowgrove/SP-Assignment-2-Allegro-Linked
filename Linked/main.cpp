#include <allegro.h>

void respondToKeyboard(void);

SAMPLE *music;
BITMAP *floor;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;
BITMAP *buffer;//used for double buffering
int playerY;
int playerX;
int playerAnimY;
int playerAnimX;

int main(void)
{
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	music = load_sample( "killingTime.wav" );
	floor = load_bitmap( "floor.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	//play_sample( music, 255, 128, 1000, 1 );
	playerY = 128;
	playerX = 32;
	playerAnimY = 0;
	playerAnimX = 0;
	while(!key[KEY_ESC])
	{
		respondToKeyboard();
		blit( floor,buffer, 0, 0, 0, 0, floor->w, floor->h );
		blit( bomb,buffer, 0, 0, 0, 32, 32, bomb->h );
		blit( hole,buffer, 0, 0, 0, 64, 32, 32 );
		blit( pusher,buffer, 0, 0, 0, 96, 32, 32 );
		blit( girder,buffer, 0, 0, 0, 160, girder->w, girder->h );
		blit( player,buffer, playerAnimX, playerAnimY, playerX, playerY, 32, 32 );
		blit(buffer,screen,0,0,0,0,buffer->w,buffer->h);
	}
	destroy_sample( music );
	destroy_bitmap( floor );
	return 0;
}
END_OF_MAIN()

void respondToKeyboard()
{
	if(key[KEY_W])
	{
		playerY--;
		if(playerY < 32 )
		{
			playerY = 32;
		}
		playerAnimY = 0;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_S])
	{
		playerY++;
		if(playerY > 416 )
		{
			playerY = 416;
		}
		playerAnimY = 96;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}

	if(key[KEY_A])
	{
		playerX--;
		if(playerX < 32 )
		{
			playerX = 32;
		}
		playerAnimY = 64;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_D])
	{
		playerX++;
		if(playerX > 576 )
		{
			playerX = 576;
		}
		playerAnimY = 32;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_R])
	{
		
	}
}
