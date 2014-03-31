#include "credits.h"

Credits::Credits()
{	
}

int Credits::creditsStart()
{
	int next = -1;
	int mouseOver;
	/*TEMP------------------------------------------------------------------------------*/
	FONT *font = load_font("pongfont.pcx",NULL,NULL);
	/*TEMP------------------------------------------------------------------------------*/

	/*LOAD ASSETS*/
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	BITMAP *background = load_bitmap( "creditsBackground.bmp", NULL );
	BITMAP *sign = load_bitmap( "sign.bmp", NULL );
	/*END OF LOAD ASSETS*/

	while(next == -1)
	{	
		mouseOver = -1;
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );

		//check if mouse is over RETURN
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 400 && mouse_y <= 450)
		{
			masked_blit( sign, buffer, 0, 50, 147, 400, 347, 50 );
			mouseOver = 0;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 400, 347, 50 );
		}
		

		textprintf_ex(buffer, font, 100, 140, makecol(0,0,0),-1, "Created by Jamie Slowgrove using the Allegro Library");
		textprintf_ex(buffer, font, 100, 160, makecol(0,0,0),-1, "Made for a Bournemouth University Games Programming");
		textprintf_ex(buffer, font, 100, 170, makecol(0,0,0),-1, "Assignment");
		textprintf_ex(buffer, font, 100, 190, makecol(0,0,0),-1, "Music: killingTime by Kevin MacLeod (incompetech.com),"); 
		textprintf_ex(buffer, font, 100, 210, makecol(0,0,0),-1, "Licensed under Creative Commons: By Attribution 3.0,");
		textprintf_ex(buffer, font, 100, 230, makecol(0,0,0),-1, "http://creativecommons.org/licenses/by/3.0/");
		textprintf_ex(buffer, font, 100, 250, makecol(0,0,0),-1, "All other Sounds used fall under the creative commons 0");
		textprintf_ex(buffer, font, 100, 260, makecol(0,0,0),-1, "license,");
		textprintf_ex(buffer, font, 100, 280, makecol(0,0,0),-1, "http://creativecommons.org/publicdomain/zero/1.0/");
		textprintf_ex(buffer, font, 297, 410, makecol(0,0,0),-1, "RETURN");

		show_mouse(buffer);

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		if(mouseOver == 0)
		{
			if(mouse_b & 1)
			{
				next = 1;
			}
		}
	}
	/*DESTROY DATA*/
	show_mouse(NULL);
	destroy_bitmap( sign );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	/*END OF DESTROY DATA*/
	return next;
}
