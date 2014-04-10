#include "gameChoice.h"

GameChoice::GameChoice()// constructor
{	
	game = new Game; //create a new instance of game
	data = new FileLoader; //create a new instance of data
}

GameChoice::~GameChoice()// De-constructor
{	
	delete game; //delete the instance of game
	delete data; //delete the instance of data
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

	next = -1;//sets the value of next to be -1 initially
	buttonPressed = -1; //sets the value of button pressed to be -1 initially
	mouseOver;
	page = 0;// sets the value of page to be 0 initially
	level = 1;// sets the value of level to be 1 initially
	fileName;
	numberOfLevels;
	y = 0; // sets the value of y to be 0 initially
	x = 0; // sets the value of x to be 0 initially

	/*LOOP UNTIL NEXT IS NOT EQUAL TO -1************************************************/
	while(next == -1)
	{	
		mouseOver = -1;//reset the value of mouse over to -1
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );// set the background to the buffer

		/*IF PAGE == 0*************************************************************************/
		if (page == 0)
		{
			textprintf_ex(buffer, font, 160, 38, makecol(0,0,0),-1, "CHOOSE THE LEVEL TYPE"); //display the title of the choice to the player
			
			//check if mouse is over PRE-BUILT
			if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 138 && mouse_y <= 188)
			{
				masked_blit( sign, buffer, 0, 50, 147, 138, 347, 50 ); //set the sign to be glowing green
				mouseOver = 1;// set the value of mouse over to be 1
			}
			else
			{
				masked_blit( sign, buffer, 0, 0, 147, 138, 347, 50 );//set the sign to not be glowing green
			}
			textprintf_ex(buffer, font, 257, 148, makecol(0,0,0),-1, "PRE-BUILT"); //set the title of the sign to the buffer

			//check if mouse is over CUSTOM
			if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 248 && mouse_y <= 298)
			{
				masked_blit( sign, buffer, 0, 50, 147, 248, 347, 50 );//set the sign to be glowing green
				mouseOver = 2;// set the value of mouse over to be 2
			}
			else
			{
				masked_blit( sign, buffer, 0, 0, 147, 248, 347, 50 );//set the sign to not be glowing green
			}
			textprintf_ex(buffer, font, 268, 258, makecol(0,0,0),-1, "CUSTOM");//set the title of the sign to the buffer

		}
		/*END OF PAGE 0********************************************************************/

		/*IF PAGE == 1*************************************************************************/
		else
		{
			textprintf_ex(buffer, font, 196, 38, makecol(0,0,0),-1, "CHOOSE THE LEVEL");//display the title of the choice to the player
			y = 160;//set the value of the level choice y position to be 160
			x = 64;//set the value of the level choice x position to be 64

			/*LOOP FOR THE NUMBER OF LEVELS******************************************************/
			for (int i = 1; i <= numberOfLevels; i++)
			{
				//check if the mouse is over the bomb of the current level
				if (mouse_x >= x && mouse_x <= (x + 32) && mouse_y >= y && mouse_y <= (y + 32))
				{
					masked_blit( bomb, buffer, 96, 0, x, y, 32, 32 );//display the most red version of the bomb

					mouseOver = 1;// set the value of mouse over to be 1
					level = i; //set the number of levels
				}
				else
				{
					masked_blit( bomb, buffer, 0, 0, x, y, 32, 32 ); //display the most grey version of the bomb
				}
				textprintf_ex(buffer, font, (x + 8), (y + 6), makecol(0,0,0),-1, "%i", i);//set the number of the level to the buffer
				if (x > 576)// check if the value of x is greater than 576
				{
					//if yes than rest the x position and move to a new line
					x = 64;
					y += 64;
				}
				else
				{
					// if no add 64 to the current position of the bomb
					x += 64;
				}
			}
			/*END THE LOOP FOR THE NUMBER OF LEVELS******************************************************/
		}
		/*END OF PAGE 1********************************************************************/

		//check if mouse is over RETURN
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 400 && mouse_y <= 450)
		{
			masked_blit( sign, buffer, 0, 50, 147, 400, 347, 50 );//set the sign to not be glowing green
			mouseOver = 0;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 400, 347, 50 );//set the sign to not be glowing green
		}

		textprintf_ex(buffer, font, 272, 410, makecol(0,0,0),-1, "RETURN");//set the title of the sign to the buffer

		show_mouse(buffer);//display the mouse to the buffer

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		if(mouseOver == 0) //check if mouse is over RETURN
		{
			if(mouse_b & 1)// if the mouse is pressed then set the value of button pressed to 0
			{
				buttonPressed = 0;
			}
		}

		else if(mouseOver == 1) //check if mouse is over PRE-BUILT or a LEVEL
		{
			if(mouse_b & 1)// if the mouse is pressed then set the value of button pressed to 1
			{
				buttonPressed = 1;
			}
		}

		else if(mouseOver == 2)//check if mouse is over CUSTOM
		{
			if(mouse_b & 1)// if the mouse is pressed then set the value of button pressed to 2
			{
				buttonPressed = 2;
			}
		}
	
		else// if not over any sets the value of the button pressed to be -1
		{
			buttonPressed = -1;
		}

		if (buttonPressed == 0 && !(mouse_b & 1))//check if the mouse is pressed and released over RETRUN
		{
			if (page == 0) //if on page 0 on then set next to 1
			{
				next = 1;
			}
			else// if on page 1 set then page to 0 and reset the button pressed value
			{
				buttonPressed = -1;
				page = 0;
			}
		}

		else if (buttonPressed == 1 && !(mouse_b & 1)) //check if the mouse is pressed and released over PRE-BUILT or a LEVEL
		{
			if (page == 1) //if on page 1 then load the level data to the instance of data and pass this to the instance of game. Then set the value of next to the outcome of the game
			{
				data->loadFile(fileName, level);
				next = game->gameStart(fileName, level);
			}
			else// if on page 0 then set the page to page 1 and set the file name to the location of the pre-built level data then load the number of levels from the file.
			{
				page = 1;
				fileName = "preBuiltLevels.txt";
				numberOfLevels = data->getNumberOfLevels(fileName);
			}
			buttonPressed = -1; //reset the value of button pressed
		}

		else if (buttonPressed == 2 && !(mouse_b & 1)) //check if the mouse is pressed and released over PRE-BUILT or a LEVEL
		{
			// Set the page to page 1 and set the file name to the location of the custom-built level data then load the number of levels from the file.
			page = 1;
			fileName = "customBuiltLevels.txt";
			numberOfLevels = data->getNumberOfLevels(fileName);
			buttonPressed = -1; //reset the value of button pressed
		}
	}
	/*END LOOP IF NEXT IS NOT EQUAL TO -1************************************************/

	/*DESTROY DATA*/
	show_mouse(NULL);
	destroy_font(font);
	destroy_bitmap( sign );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	/*END OF DESTROY DATA*/
	return next;
}