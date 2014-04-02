#include "game.h"
#include "credits.h"
#include "mainMenu.h"
#include "gameChoice.h"
#include <allegro.h>

/*GLOBALS FOR USE WITH TIMERS*/
SAMPLE *musicPart1;
SAMPLE *musicPart2;
SAMPLE *musicPart3;
int currentMusic = 1;
/*GLOBALS FOR USE WITH TIMERS*/

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
	GameChoice choice;
	MainMenu menu;
	Credits creds;
	void backgroundMusic(void);
	musicPart1 = load_sample( "killingTime1.wav" );
	musicPart2 = load_sample( "killingTime2.wav" );
	musicPart3 = load_sample( "killingTime3.wav" );
	install_int( backgroundMusic,68023 );
	play_sample( musicPart1, 255, 128, 1000, 0 );
	int next = 1;
	while (next != 0)
	{
		switch(next)
		{
		case 1:
			next = menu.menuStart();
			break;
		case 2:
			next = choice.gameChoiceStart();
			break;
		case 3:
			next = game.gameStart();
			break;
		case 4:
			break;
		case 5:
			next = creds.creditsStart();
			break;
		}
	}
	destroy_sample( musicPart1 );
	destroy_sample( musicPart2 );
	destroy_sample( musicPart3 );
	remove_int( backgroundMusic );
	return 0;
}
END_OF_MAIN()

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