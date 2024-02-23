#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

int globalX = 0;
int globalY = 0;

//Play Window offset off Global X & Y.
int world[2000][2000]{};

//What the screen prints.
int screen[300][200]{};


//Updated per frame based on the number inside the screen array @ pixel pos.
int red = 0;
int green = 0;
int blue = 0;

//UI Rects - Print to Screen Direct
class Rect1
{
private:
	int drawSelf(int h, int w, int xb, int yb, int x, int y, int e, int f)
	{
		for (int i = y; i <= (y + (w - 1)); i++)
		{
			for (int l = x; l <= (x + (h - 1)); l++)
			{
				if (i <= (y + yb) || i >= y + (w - (1 + yb)) || l <= (x + xb) || l >= x + (h - (1 + xb)))
				{
					screen[i][l] = e;
				}
				else
				{
					//This could be used for collision with a 2d array as bones later.
					screen[i][l] = f;
				}


			}

		}

		return 0;
	}
	

public:
	int width = 20;
	int height = 20;

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

//World Rects - Moved off of the Global X & Y
//NOT YET WORKING.
class Rect2
{
private:
	int drawSelf(int w, int h, int xb, int yb, int x, int y, int e, int f)
	{
		for (int i = y; i <= (y + (w - 1)); i++)
		{
			for (int l = x; l <= (x + (h - 1)); l++)
			{
				if (i <= (y + yb) || i >= y + (w - (1 + yb)) || l <= (x + xb) || l >= x + (h - (1 + xb)))
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
	int width = 20;
	int height = 20;

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


//Keep Adding Colors inside Cases.
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



//UI
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
		uiConstruct();
		// called once per frame
		for (int y = 0; y <= ScreenHeight(); y++)
			for (int x = 0; x <= ScreenWidth(); x++)
			{
				colorPicker(screen[x][y]);
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