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
	BITMAP *bomb = load_bitmap( "bomb.bmp", NULL );
	/*END OF LOAD ASSETS*/

	next = -1;
	buttonPressed = -1;
	mouseOver;
	page = 0;
	level = 1;
	fileName;
	numberOfLevels;
	y = 0;
	x = 0;

	while(next == -1)
	{	
		mouseOver = -1;
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );

		/*PAGE 0*************************************************************************/
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
		/*END OF PAGE 0********************************************************************/

		/*PAGE 1*************************************************************************/
		else
		{
			textprintf_ex(buffer, font, 196, 38, makecol(0,0,0),-1, "CHOOSE THE LEVEL");
			y = 160;
			x = 64;
			for (int i = 1; i <= numberOfLevels; i++)
			{
				if (mouse_x >= x && mouse_x <= (x + 32) && mouse_y >= y && mouse_y <= (y + 32))
				{
					masked_blit( bomb, buffer, 96, 0, x, y, 32, 32 );

					mouseOver = 1;
					level = i;
				}
				else
				{
					masked_blit( bomb, buffer, 0, 0, x, y, 32, 32 );
				}
				textprintf_ex(buffer, font, (x + 8), (y + 6), makecol(0,0,0),-1, "%i", i);
				if (y > 576)
				{
					x = 64;
					y += 64;
				}
				else
				{
					x += 64;
				}
			}
			
		}
		/*END OF PAGE 1********************************************************************/

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
				numberOfLevels = data.getNumberOfLevels(fileName);
			}
		}

		else if(mouseOver == 2 && page == 0)
		{
			if(mouse_b & 1)
			{
				page = 1;
				fileName = "customBuiltLevels.txt";
				numberOfLevels = data.getNumberOfLevels(fileName);
			}
		}

		else if(mouseOver == 1 && page == 1)
		{
			if(mouse_b & 1)
			{
				buttonPressed = 2;
			}
		}
	
		else
		{
			buttonPressed = -1;
		}

		if (buttonPressed == 1 && !(mouse_b & 1))
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

		if (buttonPressed == 2 && !(mouse_b & 1))
		{
			data.loadFile(fileName, level);
			next = game.gameStart(fileName, level);
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