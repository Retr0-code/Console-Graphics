#pragma once
#include "pch.h"

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

	// Creates frame around description
	void makeFrame(int startX, int startY, int Width, int Height);
};


// Displays vertical menu
class Menu : protected Graphics
{
private:
	int X, Y;
	int size;
	int fontSize;
	PARAGRAPH** menuObject = new PARAGRAPH*[size];

public:
	// Fixed menu position of paragraphs without custom colors
	Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Graphics _Graphics)
	{
		X = _X;
		Y = _Y;
		fontSize = _Graphics.fontSize;
		size = _size;

		for (int i = 0; i < _size; i++)
			menuObject[i] = _menuObject[i];
	}

	// Centered menu position of paragraphs without custom colors
	Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics)
	{
		std::string objNames[4] = { _menuObject[0]->paragraphName, _menuObject[1]->paragraphName, _menuObject[2]->paragraphName, _menuObject[3]->paragraphName };

		X = _Graphics.windowWidth / _Graphics.fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
		Y = _Graphics.windowHeight / _Graphics.fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
		fontSize = _Graphics.fontSize;

		size = _size;

		for (int i = 0; i < _size; i++)
			menuObject[i] = _menuObject[i];

		SecureZeroMemory(objNames, _size);
	}


	void vertical();

private:
	void DrawDescription(std::string text);
};