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
	const static int fontSize = 48;
	const int windowWidth = 1920;
	const int windowHeight = 1080;

	// Defines text color
	void setColor(int color, int _fontSize = fontSize);

	// Moves cursor to coordinates (X, Y)
	void setCursor(int x, int y);

	// Calculates middle of screen
	int calculatePosition(std::string list[], int size);

	Graphics() = default;

public:

	// Sets default window settings with custom colors and font size E.g. 1920, 1090, 7, 31, 48
	Graphics(int resolutionX, int resolutionY, int _defaultColor, int _secondaryColor, int _fontSize)
	{
		defaultColors = _defaultColor;
		secondaryColors = _secondaryColor;

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);


		// Checks does user supply font size
		if (_fontSize != NULL)
			setColor(_defaultColor, _fontSize);
		else
			setColor(_defaultColor);

		setCursor(0, 0);
	}

	// Sets default window settings without custom colors E.g. 1920, 1090, 48
	Graphics(int resolutionX, int resolutionY, int _fontSize)
	{
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);


		// Checks does user supply font size
		if (_fontSize != NULL)
			setColor(defaultColors, _fontSize);
		else
			setColor(defaultColors);

		setCursor(0, 0);
	}

	// Creates frame around description
	void makeFrame(int startX, int startY, int Width, int Height);
};


// Displays vertical menu
class Menu : protected Graphics
{
private:
	int X, Y;
	int size;
	PARAGRAPH** menuObject = new PARAGRAPH*[size];

public:
	// Fixed menu position of paragraphs without custom colors
	Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[])
	{
		X = _X;
		Y = _Y;
		size = _size;

		for (int i = 0; i < _size; i++)
			menuObject[i] = _menuObject[i];
	}

	// Centered menu position of paragraphs without custom colors
	Menu(int _size, PARAGRAPH* _menuObject[])
	{
		std::string objNames[4] = { _menuObject[0]->paragraphName, _menuObject[1]->paragraphName, _menuObject[2]->paragraphName, _menuObject[3]->paragraphName };

		X = windowWidth / fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
		Y = windowHeight / fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));

		size = _size;

		for (int i = 0; i < _size; i++)
			menuObject[i] = _menuObject[i];

		SecureZeroMemory(objNames, _size);
	}


	void vertical();

private:
	void DrawDescription(std::string text);
};