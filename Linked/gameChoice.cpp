#include "gameChoice.h"

GameChoice::GameChoice()
{	
}

int GameChoice::gameChoiceStart()
{
	/*LOAD ASSETS*/
	FONT *font = load_font("karmaticArcade.pcx",NULL,NULL);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	BITMAP *background = load_bitmap( "background.bmp", NULL );
	BITMAP *sign = load_bitmap( "sign.bmp", NULL );
	/*END OF LOAD ASSETS*/

	next = -1;
	buttonPressed = -1;
	mouseOver;
	page = 0;
	level = 1;
	fileName;
	FileLoader data;

	while(next == -1)
	{	
		mouseOver = -1;
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );

		if (page == 0)
		{
			textprintf_ex(buffer, font, 160, 38, makecol(0,0,0),-1, "CHOOSE THE LEVEL TYPE");
			
			//check if mouse is over PRE-BUILT
			if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 138 && mouse_y <= 188)
			{
				masked_blit( sign, buffer, 0, 50, 147, 138, 347, 50 );
				mouseOver = 1;
			}
			else
			{
				masked_blit( sign, buffer, 0, 0, 147, 138, 347, 50 );
			}
			textprintf_ex(buffer, font, 257, 148, makecol(0,0,0),-1, "PRE-BUILT");

			//check if mouse is over CUSTOM
			if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 248 && mouse_y <= 298)
			{
				masked_blit( sign, buffer, 0, 50, 147, 248, 347, 50 );
				mouseOver = 2;
			}
			else
			{
				masked_blit( sign, buffer, 0, 0, 147, 248, 347, 50 );
			}
			textprintf_ex(buffer, font, 268, 258, makecol(0,0,0),-1, "CUSTOM");

		}
		else
		{
			textprintf_ex(buffer, font, 196, 38, makecol(0,0,0),-1, "CHOOSE THE LEVEL");

			data.getNumberOfLevels(fileName);
			data.loadFile(fileName, level);
		}

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

		textprintf_ex(buffer, font, 272, 410, makecol(0,0,0),-1, "RETURN");

		show_mouse(buffer);

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		if(mouseOver == 0)
		{
			if(mouse_b & 1)
			{
				buttonPressed = 1;
			}
		}

		else if(mouseOver == 1 && page == 0)
		{
			if(mouse_b & 1)
			{
				page = 1;
				fileName = "preBuiltLevels.txt";
			}
		}

		else if(mouseOver == 2 && page == 0)
		{
			if(mouse_b & 1)
			{
				page = 1;
				fileName = "customBuiltLevels.txt";
			}
		}
	
		else
		{
			buttonPressed = -1;
		}

		if (buttonPressed != -1 && !(mouse_b & 1))
		{
			if (page == 0)
			{
				next = buttonPressed;
			}
			else
			{
				buttonPressed = -1;
				page = 0;
			}
		}
	}
	/*DESTROY DATA*/
	show_mouse(NULL);
	destroy_font(font);
	destroy_bitmap( sign );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	/*END OF DESTROY DATA*/
	return next;
}