#include "mainMenu.h"

/*GLOBALS FOR USE WITH TIMERS*/
int logoY;
int direction;
/*GLOBALS FOR USE WITH TIMERS*/

MainMenu::MainMenu() //Constructor
{	
}

MainMenu::~MainMenu() //De-constructor
{	
}

int MainMenu::menuStart()
{
	/*LOAD ASSETS*/
	FONT *font = load_font("karmaticArcade.pcx",NULL,NULL);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	BITMAP *background = load_bitmap( "menuBackground.bmp", NULL );
	BITMAP *logo = load_bitmap( "linkedLogo.bmp", NULL );
	BITMAP *sign = load_bitmap( "sign.bmp", NULL );
	BITMAP *tempSign = load_bitmap( "commingSoon.bmp", NULL );
	/*END OF LOAD ASSETS*/
	
	/*INITIALIZE VARIABLES*/
	next = -1;
	buttonPressed = -1;
	mouseOver;
	/*INITIALIZE VARIABLES*/

	/*INITIALIZE VARIABLES FOR TIMERS*/
	logoY = 60;
	void animation(void);
	install_int(animation,50);
	/*INITIALIZE VARIABLES FOR TIMERS*/

	/*Loop while next is equal to -1**********************************************************/
	while(next == -1)
	{	
		mouseOver = -1;//resets mouseOver
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 ); //sets the background to the buffer
		masked_blit( logo, buffer, 0, 0, 70, logoY, 500, 127 );// set the logo to the buffer

		//check if mouse is over PLAY
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 220 && mouse_y <= 270)
		{
			masked_blit( sign, buffer, 0, 50, 147, 220, 347, 50 );//set the sign to glow green
			mouseOver = 0;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 220, 347, 50 ); //set the sign to be grey
		}

		//check if mouse is over MAP EDITOR
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 280 && mouse_y <= 330)
		{
			masked_blit( sign, buffer, 0, 50, 147, 280, 347, 50 );//set the sign to glow green
			mouseOver = 1;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 280, 347, 50 ); //set the sign to be grey
		}

		//check if mouse is over CREDITS
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 340 && mouse_y <= 390) 
		{
			masked_blit( sign, buffer, 0, 50, 147, 340, 347, 50 ); //set the sign to glow green
			mouseOver = 2;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 340, 347, 50 );//set the sign to be grey
		}

		//check if mouse is over EXIT
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 400 && mouse_y <= 450)
		{
			masked_blit( sign, buffer, 0, 50, 147, 400, 347, 50 );//set the sign to glow green
			mouseOver = 3;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 400, 347, 50 );//set the sign to be grey
		}
		
		/*DISPLAY TEXT*/
		textprintf_ex(buffer, font, 289, 230, makecol(0,0,0),-1, "PLAY");
		textprintf_ex(buffer, font, 250, 290, makecol(0,0,0),-1, "MAP EDITOR");
		textprintf_ex(buffer, font, 266, 350, makecol(0,0,0),-1, "CREDITS");
		textprintf_ex(buffer, font, 291, 410, makecol(0,0,0),-1, "EXIT");
		textprintf_ex(buffer, font, 10, 460, makecol(255,255,255),-1, "(c) Jamie Slowgrove 2014");
		/*DISPLAY TEXT*/

		masked_blit( tempSign, buffer, 0, 0, 147, 280, 347, 50 );//display the COMMING SOON sign on top of the map editor button [will be removed when map editor is created]

		show_mouse(buffer);//sets the mouse to display to the screen

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		switch (mouseOver)
		{
		case 0: // if the mouse is over PLAY set button pressed to 2
			if(mouse_b & 1)
			{
				buttonPressed = 2;
			}
			break;
		case 1: // if the mouse is over MAP EDITOR set button pressed to 3
			if(mouse_b & 1)
			{
				//buttonPressed = 3; WILL BE ADDED WHEN MAP EDITOR IS CREATED
			}
			break;
		case 2: // if the mouse is over CREDITS set button pressed to 4
			if(mouse_b & 1)
			{
				buttonPressed = 4;
			}
			break;
		case 3: // if the mouse is over EXIT set button pressed to 0
			if(mouse_b & 1)
			{
				buttonPressed = 0;
			}
			break;
		default://if nothing set buttonPressed to -1
			buttonPressed = -1;
			break;
		}
		if (buttonPressed != -1 && !(mouse_b & 1)) //if the right mouse button is not equal to -1 then set next to the value of button pressed
		{
			next = buttonPressed;
		}
	}
	/*End loop when next is not equal to -1**********************************************************/

	/*DESTROY DATA*/
	remove_int( animation );
	show_mouse(NULL);
	destroy_font(font);
	destroy_bitmap( tempSign );
	destroy_bitmap( sign );
	destroy_bitmap( logo );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	/*END OF DESTROY DATA*/
	return next;
}

void animation()
{
	if(logoY >= 80)//if the y position of the logo is greater or equal to 80 then set the direction to -1
	{
		direction = -1;
	}
	else if(logoY <= 60)//if the y position of the logo is less than or equal to 60 then set the direction to 1
	{
		direction = 1;
	}
	logoY += direction; // the y position of the logo will either increase or decrease depending on whether direction is 1 or -1
}
