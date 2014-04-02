#include "mainMenu.h"

/*GLOBALS FOR USE WITH TIMERS*/
int barTopX;
int barTopAnim;
int barY;
std::vector<int> barBotX;
std::vector<int> barBotY;
std::vector<int> barBotAnim;
std::vector<int> directions;
void pickupAnim(int);
void moveBotAnim(int i,int dir);
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
	directions.resize(4);
	directions[0] = 1;//top X Direction
	directions[1] = 0;//bottom X Direction
	directions[2] = 0;//bar Y Direction
	directions[3] = 1;//forwards/reverse
	barBotX.resize(3);
	barBotX[0] = 29;
	barBotX[1] = 573;
	barBotX[2] = 29;
	barBotY.resize(3);
	barBotY[0] = 125;
	barBotY[1] = 221;
	barBotY[2] = 317;
	barBotAnim.resize(3);
	barBotAnim[0] = 0;
	barBotAnim[1] = 0;
	barBotAnim[2] = 0;
	barTopX = 39;
	barTopAnim = 0;
	void animation(void);
	install_int(animation,10);

	while(next == -1)
	{	
		mouseOver = -1;
		masked_blit( background, buffer, 0, 0, 0, 0, 640, 480 );
		for (int i = 0; i<3; i++)
		{
			masked_blit( barBottom, buffer, barBotAnim[i], 0, barBotX[i], barBotY[i], 38, 38 );
		}
		masked_blit( barMiddle, buffer, 0, 0, 0, barY, 640, 12 );
		masked_blit( barTop, buffer, barTopAnim, 0, barTopX, (barY - 5), 18, 22 );
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
				//buttonPressed = 4;
			}
			break;
		case 2: //CREDITS
			if(mouse_b & 1)
			{
				buttonPressed = 5;
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
	remove_int( animation );
	directions.resize(0);
	barBotX.resize(0);
	barBotY.resize(0);
	barBotAnim.resize(0);
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
	/*END OF DESTROY DATA*/
	return next;
}

void animation()
{
	if(directions[1] == 0 && barY == 137)
	{
		pickupAnim(0);
	}
	else if (directions[1] == 1 && barY == 137)
	{
		moveBotAnim(0,-1);
	}
	else if (directions[0] == -1 && barY <= 233 && barTopX > 39)
	{
		barY+=directions[2];
		barTopX+=directions[0];
		if (barY == 233)
		{
			directions[2] = 0;
		}
	}
	else if(barY == 233 && barTopX == 39 && directions[0] == -1)
	{
		directions[2] = 0;
		directions[0] = 0;
	}
	else if(barY == 233 && barTopX == 39 && directions[0] == 0 && directions[1] != 1)
	{
		pickupAnim(1);
	}
	else if (directions[1] == 1 && barY == 233)
	{
		moveBotAnim(1,-1);
	}
	else if(barY == 329 && barTopX == 39 && directions[0] == -1)
	{
		directions[2] = 0;
		directions[0] = 0;
	}
	else if(barY == 329 && barTopX == 39 && directions[0] == 0 && directions[1] != 1)
	{
		pickupAnim(2);
	}
	else if (directions[1] == 1 && barY == 329)
	{
		moveBotAnim(2,-1);
	}
}

void pickupAnim(int i)
{
	if (barTopAnim != 36 && barBotAnim[i] != 76)
	{
		barTopAnim+=18;
	}
	else if (barBotAnim[i] != 76)
	{
		barBotAnim[i]+=38;
	}
	else if (barTopAnim != 0 && barBotAnim[i] == 76)
	{
		barTopAnim-=18;
	}
	else
	{
		directions[1] = 1;
	}
}

void moveBotAnim(int i,int dir)
{
	if(barTopX > 660)
	{
		directions[0] = dir;
		directions[1] = 0;
		if (barY == 329)
		{
			directions[2] = dir;
		}
		else
		{
			directions[2] = -dir;
		}
		barY+=directions[2];
	}
	else if(barTopX == 39)
	{
		directions[0] = -dir;
		directions[1] = -dir;
	}
	barTopX+=directions[0]*directions[3];
	barBotX[i]+=directions[1]*directions[3];
}