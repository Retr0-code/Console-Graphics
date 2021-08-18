#pragma once
#include "pch.h"


typedef struct
{
	char leftTopCorner;
	char rightTopCorner;
	char leftDownCorner;
	char rightDownCorner;
	char horizontal;
	char vertical;
} frameSegments;



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


class Graphics
{
protected:
	int defaultColors = 7;
	int secondaryColors = 31;

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

	// Sets default window settings with custom colors and font size E.g. 1920, 1090, 7, 31, 48
	Graphics(int resolutionX, int resolutionY, int _defaultColor, int _secondaryColor, int _fontSize);

	// Sets default window settings without custom colors E.g. 1920, 1090, 48
	Graphics(int resolutionX, int resolutionY, int _fontSize);
};


// Spawns frames
class Frame : protected Graphics
{
public:
	frameSegments segments = { (char)201, (char)187, (char)200, (char)188, (char)205, (char)186 };
	int originX = 0;
	int originY = 0;
	int Width;
	int Height;


	Frame() = default;
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

	// Spawns Vertical Menu
	void vertical();

private:

	// Displays description of functions that is in menu
	void DrawDescription(std::string text);
};