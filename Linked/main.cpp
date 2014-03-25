#include <allegro.h>

SAMPLE *music;
void respondToKeyboard(void);

int main(void)
{
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0); //Sets the graphics mode
	music = load_sample( "8bitDungeonLevel.wav" );
	play_sample(music, 255, 255, 1000, 1);
	while(!key[KEY_ESC])
	{
		clear_to_color( screen, makecol(0,0,0) ); //Sets the background to black
		respondToKeyboard();
	}

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
}
