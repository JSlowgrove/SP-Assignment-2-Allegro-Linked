#include <allegro.h>

void respondToKeyboard(void);

SAMPLE *music;
BITMAP *floor;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;

int main(void)
{
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	music = load_sample( "killingTime.wav" );
	floor = load_bitmap( "floor.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	//play_sample( music, 255, 128, 1000, 1 );
	blit( floor,screen, 0, 0, 0, 0, floor->w, floor->h );
	blit( bomb,screen, 0, 0, 0, 32, 32, bomb->h );
	blit( hole,screen, 0, 0, 0, 64, 32, 32 );
	blit( pusher,screen, 0, 0, 0, 96, 32, pusher->h );
	blit( player,screen, 0, 0, 0, 128, 32, player->h );
	blit( girder,screen, 0, 0, 0, 160, girder->w, girder->h );
	while(!key[KEY_ESC])
	{
		respondToKeyboard();
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
		
	}
	if(key[KEY_S])
	{
		
	}

	if(key[KEY_A])
	{
		
	}
	if(key[KEY_D])
	{
		
	}
	if(key[KEY_R])
	{
		
	}
}
