#include "fileLoader.h"
#include "collisionDetection.h"
#include "game.h"
#include "mainMenu.h"
#include <allegro.h>

int main(void)
{
	/*ALLEGRO STARTUP*/
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_mouse();//Allow mouse input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	install_timer();
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	/*END OF ALLEGRO STARTUP*/
	Game game;
	MainMenu menu;
	int next = 1;
	while (next != 0)
	{
		if (next == 1)
		{
			next = menu.menuStart();
		}
		else if (next == 2)
		{
			next = game.gameStart();
		}
	}
	return 0;
}
END_OF_MAIN()