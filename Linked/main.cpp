#include "credits.h"
#include "mainMenu.h"
#include "gameChoice.h"
#include <allegro.h>

/*GLOBALS FOR USE WITH TIMERS*/
SAMPLE *musicPart1;
SAMPLE *musicPart2;
SAMPLE *musicPart3;
int currentMusic;
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

	/*CLASS OBJECT POINTERS*/
	GameChoice *choice; //declares a pointer to a object of the GameChoice class
	MainMenu *menu; //declares a pointer to a object of the MainMenu class
	Credits *creds; //declares a pointer to a object of the Credits class
	/*END OF CLASS OBJECT POINTERS*/

	/*BACKGROUND MUSIC TIMER SETUP*/
	void backgroundMusic(void); //declares the function for the
	musicPart1 = load_sample( "killingTime1.wav" );//due to the length of the background music being greater than a sample can take I have split it into 3 different samples, each the same length. This is the first part.
	musicPart2 = load_sample( "killingTime2.wav" );//This is the second part.
	musicPart3 = load_sample( "killingTime3.wav" );//This is the final part
	currentMusic = 1; // sets the value of the current music playing to 1
	install_int( backgroundMusic,68023 ); //This starts the timer for the Music, it gets called every 68.023 seconds, the length of each sample
	play_sample( musicPart1, 255, 128, 1000, 0 ); // as the timer does not play the music instantly this is to be played first instead, the timer then takes over and plays the rest until the game is shutdown 
	/*BACKGROUND MUSIC TIMER SETUP*/

	int next = 1;// sets the initial value of next to be 1 and as such the first thing to be loaded to be the menu

	/*LOOP UNTIL NEXT IS 0***************************************************************/
	while (next != 0)
	{
		switch(next) // check the value of next
		{
		case 1: // if next == 1 then declare a new instance of the object menu and load the start
			menu = new MainMenu; 
			next = menu->menuStart(); // set the value of next to the returned value of menu
			delete menu;//destroy the instance of menu
			break;
		case 2:// if next == 2 then declare a new instance of the object choice and load the start
			choice = new GameChoice;
			next = choice->gameChoiceStart();// set the value of next to the returned value of choice
			delete choice;//destroy the instance of choice
			break;
		case 3:
			//Will be used for a map editor class in the future
			break;
		case 4:// if next == 4 then declare a new instance of the object creds and load the start
			creds = new Credits;
			next = creds->creditsStart();// set the value of next to the returned value of creds
			delete creds;//destroy the instance of creds
			break;
		}
	}
	/*END LOOP IF NEXT IS 0***************************************************************/

	remove_int( backgroundMusic );//remove the timer
	destroy_sample( musicPart1 );//destroy the sample
	destroy_sample( musicPart2 );//destroy the sample
	destroy_sample( musicPart3 );//destroy the sample
	return 0;
}
END_OF_MAIN()

/*TIMERS*/
void backgroundMusic()// the timer that plays the background music
{
	switch(currentMusic) //checks the value of current music
	{
	case 0:// if 0 play the first part and set the current music to 1
		play_sample( musicPart1, 255, 128, 1000, 0 );
		currentMusic = 1;
		break;
	case 1:// if 1 play the second part and set the current music to 2
		play_sample( musicPart2, 255, 128, 1000, 0 );
		currentMusic = 2;
		break;
	case 2:// if 2 play the last part and set the current music to 0
		play_sample( musicPart3, 255, 128, 1000, 0 );
		currentMusic = 0;
		break;
	}
}
/*END OF TIMERS*/