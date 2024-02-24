#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


//Global Vars
float globalX = 0;
float globalY = 0;
int globalXN = globalX;
int globalYN = globalY;

//Player Vars
float playerX = 150;
float playerY = 50;
float playerSpeed = 100.0f;
int playNX = playerX;
int playNY = playerY;


//TIMER STUFF
float fTargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
float fAccumulatedTime = 0.0f;


//Play Window offset off Global X & Y.
int world[2000][2000]{};

//Future Arrays needed for drawing multiple layers to screen.
//Spells and Weather.
int playField[2000][2000]{};


//What the screen prints.
int screen[200][300]{};


//UI Rects - Print to Screen Direct
class Rect1
{
private:
	int drawSelf(int h, int w, int xb, int yb, int x, int y, int e, int f)
	{
		for (int i = y; i <= (y + (h - 1)); i++)
		{
			for (int l = x; l <= (x + (w - 1)); l++)
			{
				if (i <= (y + yb) || i >= y + (h - (1 + yb)) || l <= (x + xb) || l >= x + (w - (1 + xb)))
				{
					if (screen[i][l] != e)
					{
						screen[i][l] = e;
					}
				}
				else
				{
					//This could be used for collision with a 2d array as bones later.
					if (screen[i][l] != f)
					{
						screen[i][l] = f;
					}
				}


			}

		}

		return 0;
	}
	

public:
	int height = 20;
	int width = 20;
	
	int xBord = 0;
	int yBord = 0;

	int posX = 0;
	int posY = 0;

	int windowEdge = 1;
	int windowFill = 4;

	int showSelf()
	{
		drawSelf(height, width, xBord, yBord, posX, posY, windowEdge, windowFill);
		return 0;
	}


}; 


//World Fill
class Rect2
{
private:
	int drawSelf(int h, int w, int xb, int yb, int x, int y, int e, int f)
	{
		for (int i = y; i <= (y + (h - 1)); i++)
		{
			for (int l = x; l <= (x + (w - 1)); l++)
			{
				if (i <= (y + yb) || i >= y + (h - (1 + yb)) || l <= (x + xb) || l >= x + (w - (1 + xb)))
				{
					if (world[i][l] != e)
					{
						world[i][l] = e;
					}
				}
				else
				{
					//This could be used for collision with a 2d array as bones later.
					if (world[i][l] != f)
					{
						world[i][l] = f;
					}
				}


			}

		}

		return 0;
	}


public:
	int height = 20;
	int width = 20;

	int xBord = 0;
	int yBord = 0;

	int posX = 0;
	int posY = 0;

	int windowEdge = 1;
	int windowFill = 4;

	int showSelf()
	{
		drawSelf(height, width, xBord, yBord, posX, posY, windowEdge, windowFill);
		return 0;
	}


};


//Player Objects
class RectPlayer
{
private:
	int drawSelf(int h, int w, int xb, int yb, int x, int y, int e, int f)
	{
		for (int i = y; i <= (y + (h - 1)); i++)
		{
			for (int l = x; l <= (x + (w - 1)); l++)
			{
				if (i <= (y + yb) || i >= y + (h - (1 + yb)) || l <= (x + xb) || l >= x + (w - (1 + xb)))
				{
					world[i][l] = e;
				}
				else
				{
					//This could be used for collision with a 2d array as bones later.
					world[i][l] = f;
				}


			}

		}

		return 0;
	}


public:
	int height = 20;
	int width = 20;

	int xBord = 0;
	int yBord = 0;

	float posX = playerX;
	float posY = playerY;

	int windowEdge = 1;
	int windowFill = 4;

	int showSelf()
	{
		drawSelf(height, width, xBord, yBord, posX, posY, windowEdge, windowFill);
		return 0;
	}


};
RectPlayer playerSprite;


//Keep Adding Colors inside Cases.
//HOLDS NOTHING YET, PUT PLAYER IN.
class PlayerChar
{
private:
	
	


public:
	

};


//Updated per frame based on the number inside the screen array @ pixel pos.
//Need to add more colors and actually sort them.
//Leave 1 - 10 for ground colors, or maybe 1 - 20.
//Big switch.
int red = 0;
int green = 0;
int blue = 0;
int colorPicker(int i)
{
	switch (i)
	{
	case 1: // Black
		red = 0;
		green = 0;
		blue = 0;
		break;
	case 2: //Grass - Light Green
		red = 130;
		green = 255;
		blue = 92;
		break;
	case 3: //Sky Blue
		red = 87;
		green = 160;
		blue = 212;
		break;
	case 4: //Steel Grey
		red = 100;
		green = 109;
		blue = 115;
		break;
	};



	return 0;
}



//UI Rects
//Makes all the windows around the screen
//Not printed where Play area is, need to Bool swap if menu key is pressed still.
//Also add style.
int uiConstruct()
{

	//Screen Border
	Rect1 WorldPrint;
	WorldPrint.height = 200;
	WorldPrint.width = 300;
	WorldPrint.xBord = 1;
	WorldPrint.yBord = 1;
	WorldPrint.posX = 0;
	WorldPrint.posY = 0;
	WorldPrint.showSelf();

	//Inner Screen - Play Area
	Rect1 mainScreen;
	mainScreen.height = 140;
	mainScreen.width = 240;
	mainScreen.posX = 10;
	mainScreen.posY = 10;
	mainScreen.windowFill = 2;
	mainScreen.showSelf();

	return 0;
}

//Populates the World Array.
//Need to start adding style.
int worldFill()
{
	Rect2 worldBorder;
	worldBorder.height = 2000;
	worldBorder.width = 2000;
	worldBorder.posX = 0;
	worldBorder.posY = 0;
	worldBorder.xBord = 10;
	worldBorder.yBord = 10;
	worldBorder.windowEdge = 1;
	worldBorder.windowFill = 2;
	worldBorder.showSelf();

	Rect2 building01;
	building01.height = 40;
	building01.width = 40;
	building01.posX = 40;
	building01.posY = 40;
	building01.xBord = 4;
	building01.yBord = 4;
	building01.windowEdge = 1;
	building01.windowFill = 3;
	building01.showSelf();

	Rect2 building02;
	building02.height = 40;
	building02.width = 40;
	building02.posX = 200;
	building02.posY = 70;
	building02.xBord = 4;
	building02.yBord = 4;
	building02.windowEdge = 1;
	building02.windowFill = 3;
	building02.showSelf();



	return 0;
}


//Shout out OLC Pixel Engine.
//Where the magic comes to life.
class olcEngine : public olc::PixelGameEngine
{
public:
	olcEngine()
	{
		sAppName = "Shrike";
	}

public:
	bool OnUserCreate() override
	{

		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{


		//TIMER
		fAccumulatedTime += fElapsedTime;

		//UPDATES FOR DRAWING
		//UPDATES FOR DRAWING
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
			worldFill();
			uiConstruct();
			playerSprite.showSelf();
		}

	
		//Player POS UPDATES
		playerSprite.posX = playerX;
		playerSprite.posY = playerY;
		//Player Float to Int
		int playNX = playerX;
		int playNY = playerY;

		//Global Float to Int
		int globalXN = globalX;
		int globalYN = globalY;


		//Movement Keys - -WASD
		if ((GetKey(olc::Key::A).bHeld) != (GetKey(olc::Key::D).bHeld))
		{
			if (GetKey(olc::Key::A).bHeld)
			{
				if ((world[playNY][playNX - 1] == 2) && world[playNY + playerSprite.height - 1][playNX - 1] == 2)
				{
					playerX -= (playerSpeed * fElapsedTime);
					if ((globalX > 0 && playerX > 50) && playerX < 1920)
					{
						globalX -= (playerSpeed * fElapsedTime);
					}
				}

			}
			else if (GetKey(olc::Key::D).bHeld)
			{
				if ((world[playNY][playNX + 20] == 2) && world[playNY + playerSprite.height - 1][playNX + 20] == 2)
				{
					playerX += (playerSpeed * fElapsedTime);
					if ((globalX < 2000 && playerX < 1920) && playerX > 120)
					{
						globalX += (playerSpeed * fElapsedTime);
					}
				}
			}
		}
		if ((GetKey(olc::Key::W).bHeld) != (GetKey(olc::Key::S).bHeld))
		{
			if (GetKey(olc::Key::W).bHeld)
			{
				if ((world[playNY - 1][playNX] == 2) && world[playNY - 1][playNX + playerSprite.width - 1] == 2)
				{
					playerY -= (playerSpeed * fElapsedTime);
					if ((globalY > 0 && playerY > 50) && playerY < 1930)
					{
						globalY -= (playerSpeed * fElapsedTime);
					}
				}
			}
			else if (GetKey(olc::Key::S).bHeld)
			{
				if ((world[playNY + 20][playNX] == 2) && world[playNY + 20][playNX + playerSprite.width - 1] == 2)
				{
					playerY += (playerSpeed * fElapsedTime);
					if ((globalY < 2000 && playerY < 1920) && playerY > 70)
					{
						globalY += (playerSpeed * fElapsedTime);
					}
				}
			}
		}


		// called once per frame
		//VIDEO OUTPUT
		for (int y = 0; y <= ScreenHeight(); y++)
			for (int x = 0; x <= ScreenWidth(); x++)
			{
				if ((x > ((ScreenWidth() / 2) - 130) / 2 && x < ((ScreenWidth() / 2) + 99)) && (y > ((ScreenHeight() / 2) - 79) / 2 && y < ((ScreenHeight() / 2) + 49)))
				{
					colorPicker(world[(y + globalYN)][(x + globalXN)]);
				}
				else
				{
					colorPicker(screen[y][x]);
				}
				
				Draw(x, y, olc::Pixel(red, green, blue));
			}
		return true;
	}
};


int main()
{
	olcEngine demo;
	if (demo.Construct(300, 200, 4, 4))
		demo.Start();

	return 0;
}