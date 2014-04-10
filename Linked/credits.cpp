#include "credits.h"

Credits::Credits()//constructor
{	
}

Credits::~Credits()//De-constructor
{	
}

int Credits::creditsStart()
{
	/*LOAD ASSETS*/
	FONT *font = load_font("karmaticArcade.pcx",NULL,NULL);
	FONT *fontSmall = load_font("karmaticArcadeSmall.pcx",NULL,NULL);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	BITMAP *background = load_bitmap( "creditsBackground.bmp", NULL );
	BITMAP *sign = load_bitmap( "sign.bmp", NULL );
	/*END OF LOAD ASSETS*/
	
	/*INITIALISE VARIABLES*/
	next = -1;
	buttonPressed = -1;
	mouseOver;
	/*INITIALISE VARIABLES*/
	
	/*LOOP WHILE NEXT IS EQUAL TO -1*/
	while(next == -1)
	{	
		mouseOver = -1;// reset mouseOver
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );//set background to the buffer

		//check if mouse is over RETURN
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 400 && mouse_y <= 450)
		{
			masked_blit( sign, buffer, 0, 50, 147, 400, 347, 50 );//display sign that glows green
			mouseOver = 0;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 400, 347, 50 ); //display grey sign
		}
		
		/*CREDITS TO BUFFER*/
		textprintf_ex(buffer, fontSmall, 100, 130, makecol(0,0,0),-1, "Created by Jamie Slowgrove using the");
		textprintf_ex(buffer, fontSmall, 100, 140, makecol(0,0,0),-1, "Allegro Library");
		textprintf_ex(buffer, fontSmall, 100, 160, makecol(0,0,0),-1, "Made for a Bournemouth University Games");
		textprintf_ex(buffer, fontSmall, 100, 170, makecol(0,0,0),-1, "Programming First Year Assignment");
		textprintf_ex(buffer, fontSmall, 100, 190, makecol(0,0,0),-1, "Music- killingTime by Kevin MacLeod");
		textprintf_ex(buffer, fontSmall, 100, 200, makecol(0,0,0),-1, "(incompetech.com),"); 
		textprintf_ex(buffer, fontSmall, 100, 210, makecol(0,0,0),-1, "Licensed under Creative Commons: By");
		textprintf_ex(buffer, fontSmall, 100, 220, makecol(0,0,0),-1, "Attribution 3.0,");
		textprintf_ex(buffer, fontSmall, 100, 230, makecol(0,0,0),-1, "http://creativecommons.org/licenses/by/3.0/");
		textprintf_ex(buffer, fontSmall, 100, 250, makecol(0,0,0),-1, "All other Sounds used fall under the");
		textprintf_ex(buffer, fontSmall, 100, 260, makecol(0,0,0),-1, "creative commons 0 license,");
		textprintf_ex(buffer, fontSmall, 100, 270, makecol(0,0,0),-1, "http://creativecommons.org/publicdomain/zero/1.0/");
		textprintf_ex(buffer, fontSmall, 100, 290, makecol(0,0,0),-1, "Font- Karmatic Arcade by Vic Fieger");
		textprintf_ex(buffer, fontSmall, 100, 300, makecol(0,0,0),-1, "http://www.1001freefonts.com/karmatic_arcade.font");
		textprintf_ex(buffer, font, 272, 410, makecol(0,0,0),-1, "RETURN");
		/*CREDITS TO BUFFER*/

		show_mouse(buffer);//display the mouse to the buffer

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		if(mouseOver == 0)//check if the mouse is over RETURN
		{
			if(mouse_b & 1)//if the left mouse button is pressed set the value of button pressed to be 1
			{
				buttonPressed = 1;
			}
		}
		else //if not set the value of button pressed to -1
		{
			buttonPressed = -1;
		}

		if (buttonPressed != -1 && !(mouse_b & 1)) //If mouse is over RETURN and the mouse is pressed and released set the value of next to 1
		{
			next = buttonPressed;
		}
	}
	/*END LOOP WHILE NEXT IS NOT EQUAL TO -1*/

	/*DESTROY DATA*/
	show_mouse(NULL);
	destroy_font(font);
	destroy_font(fontSmall);
	destroy_bitmap( sign );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	/*END OF DESTROY DATA*/
	return next;
}