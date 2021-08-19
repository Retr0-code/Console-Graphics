#pragma once
#include "pch.h"
#include "colors.h"


typedef struct
{
	char leftTopCorner;
	char rightTopCorner;
	char leftDownCorner;
	char rightDownCorner;
	char horizontal;
	char vertical;
} frameSegments;

typedef struct
{
	int frontground;
	int background;
} color;

typedef struct
{
	int selectColor;
	int deselectColor;
	int backgroundColor;
} MSG_BOX_TYPE;

#define BOX_INFO { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_AZURE + FG_WHITE }
#define BOX_ERROR { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_RED + FG_BLACK }
#define BOX_WARNING { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_ORANGE + FG_BLACK }

// Clears the screen
void cls(HANDLE hConsole);

// Calculates percent from number
int calculatePercent(int digit, int perc);


// The parent class for defining a menu paragraphs
class PARAGRAPH
{
public:
	std::string paragraphName;
	std::string description;
	PARAGRAPH(std::string paragraphName, std::string description)
	{
		paragraphName = this->paragraphName;
		description = this->description;
	}

	virtual void Execute() = 0;
};

// Main parent class
class Graphics
{
protected:
	// Defines text color
	void setColor(int color, int _fontSize = 48);

	// Moves cursor to coordinates (X, Y)
	void setCursor(int x, int y);

	// Calculates middle of screen
	int calculatePosition(std::string list[], int size);

	Graphics() = default;

public:
	int fontSize = 48;
	int windowWidth = 1920;
	int windowHeight = 1080;
	int defaultColors = BG_BLACK + FG_WHITE;
	int secondaryColors = BG_BLUE + FG_BLACK;


	// Sets default window settings with custom colors and font size E.g. 1920, 1090, 7, 31, 48
	Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize);

	// Sets default window settings without custom colors E.g. 1920, 1090, 48
	Graphics(int resolutionX, int resolutionY, int _fontSize);
};


// Spawns frames
class Frame : protected Graphics
{
public:
	Frame() = default;
	frameSegments segments = { (char)201, (char)187, (char)200, (char)188, (char)205, (char)186 };
	int originX = 0;
	int originY = 0;
	int Width;
	int Height;


	Frame(int _originX, int _originY, int _Width, int _Height, frameSegments _segments);
	Frame(int _originX, int _originY, int _Width, int _Height);
	
	void spawnFrame();
};


// Displays vertical menu
class Menu : protected Frame
{
private:
	int X, Y;
	int size;
	int fontSize;
	PARAGRAPH** menuObject = new PARAGRAPH*[size];
	Frame descriptionField;

public:
	// Fixed menu position of paragraphs without custom colors
	Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField);

	// Centered menu position of paragraphs without custom colors
	Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField);

	// Creates Menu in frame without custom colors
	Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField);

	~Menu();

	// Spawns Vertical Menu
	void vertical();

private:

	Menu() = default;

	// Displays description of functions that is in menu
	void DrawDescription(std::string text);
};

// Dialog box
class MsgBox : protected Graphics
{
protected:
	std::string description;
	int lfontSize;
	int width;
	int height;

public:
	MsgBox(std::string _description, Graphics _Graphics)
	{
		description = _description;
		lfontSize = _Graphics.fontSize;
		width = _Graphics.windowWidth;
		height = _Graphics.windowHeight;
	}

	BOOL Message(MSG_BOX_TYPE container);
};