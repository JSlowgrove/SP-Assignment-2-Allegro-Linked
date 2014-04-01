#include "mainMenu.h"

/*GLOBALS FOR USE WITH TIMERS*/
int barTopX;
int bTXDirection;
int barY;
/*GLOBALS FOR USE WITH TIMERS*/

MainMenu::MainMenu()
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
	BITMAP *barTop = load_bitmap( "barTop.bmp", NULL );
	BITMAP *barMiddle = load_bitmap( "barMiddle.bmp", NULL );
	BITMAP *barBottom = load_bitmap( "barBottom.bmp", NULL );
	BITMAP *tempSign = load_bitmap( "commingSoon.bmp", NULL );
	/*END OF LOAD ASSETS*/
	
	next = -1;
	buttonPressed = -1;
	mouseOver;
	barY = 137;
	barTopX = 39;
	bTXDirection = 1;
	void animation(void);
	install_int(animation,10);

	while(next == -1)
	{	
		mouseOver = -1;
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );
		masked_blit( barBottom, buffer, 0, 0, 29, 125, 38, 38 );
		masked_blit( barMiddle, buffer, 0, 0, 0, barY, 640, 12 );
		masked_blit( barTop, buffer, 0, 0, barTopX, (barY - 5), 18, 22 );
		masked_blit( logo, buffer, 0, 0, 70, 80, 500, 127 );

		//check if mouse is over PLAY
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 220 && mouse_y <= 270)
		{
			masked_blit( sign, buffer, 0, 50, 147, 220, 347, 50 );
			mouseOver = 0;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 220, 347, 50 );
		}

		//check if mouse is over MAP EDITOR
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 280 && mouse_y <= 330)
		{
			masked_blit( sign, buffer, 0, 50, 147, 280, 347, 50 );
			mouseOver = 1;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 280, 347, 50 );
		}

		//check if mouse is over CREDITS
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 340 && mouse_y <= 390)
		{
			masked_blit( sign, buffer, 0, 50, 147, 340, 347, 50 );
			mouseOver = 2;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 340, 347, 50 );
		}

		//check if mouse is over EXIT
		if (mouse_x >= 147 && mouse_x <= 494 && mouse_y >= 400 && mouse_y <= 450)
		{
			masked_blit( sign, buffer, 0, 50, 147, 400, 347, 50 );
			mouseOver = 3;
		}
		else
		{
			masked_blit( sign, buffer, 0, 0, 147, 400, 347, 50 );
		}
		
		
		textprintf_ex(buffer, font, 289, 230, makecol(0,0,0),-1, "PLAY");
		textprintf_ex(buffer, font, 250, 290, makecol(0,0,0),-1, "MAP EDITOR");
		masked_blit( tempSign, buffer, 0, 0, 147, 280, 347, 50 );
		textprintf_ex(buffer, font, 266, 350, makecol(0,0,0),-1, "CREDITS");
		textprintf_ex(buffer, font, 291, 410, makecol(0,0,0),-1, "EXIT");
		textprintf_ex(buffer, font, 10, 460, makecol(255,255,255),-1, "(c) Jamie Slowgrove 2014");

		show_mouse(buffer);

		/*DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
		/*END OF DISPLAYING IMAGES TO SCREEN USING A DOUBLE BUFFER*/

		switch (mouseOver)
		{
		case 0: // PLAY
			if(mouse_b & 1)
			{
				buttonPressed = 2;
			}
			break;
		case 1: // MAP EDITOR
			if(mouse_b & 1)
			{
				//buttonPressed = 3;
			}
			break;
		case 2: //CREDITS
			if(mouse_b & 1)
			{
				buttonPressed = 4;
			}
			break;
		case 3: //EXIT
			if(mouse_b & 1)
			{
				buttonPressed = 0;
			}
			break;
		default:
			buttonPressed = -1;
			break;
		}
		if (buttonPressed != -1 && !(mouse_b & 1))
		{
			next = buttonPressed;
		}
	}

	/*DESTROY DATA*/
	show_mouse(NULL);
	destroy_font(font);
	destroy_bitmap( tempSign );
	destroy_bitmap( barBottom );
	destroy_bitmap( barMiddle );
	destroy_bitmap( barTop );
	destroy_bitmap( sign );
	destroy_bitmap( logo );
	destroy_bitmap( background );
	destroy_bitmap( buffer );
	remove_int( animation );
	/*END OF DESTROY DATA*/
	return next;
}

void animation()
{
	if(barTopX > 660)
	{
		bTXDirection = -1;
	}
	else if(barTopX < - 20)
	{
		bTXDirection = 1;
	}
	barTopX+=bTXDirection;
}