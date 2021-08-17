#include "pch.h"


#define FONT_SIZE 48
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


// Clears the screen
void cls(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

// Calculates percent from number
int calculatePercent(int digit, int perc)
{
	return (digit * perc) / 100;
}


void A()
{
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Yep ";
}

void B()
{
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Not that ";
}

void C()
{
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Not that one ";
}

void D()
{
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n That a lot more ";
}



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

// ---------- Child classes ------------ //

class firstParagraph : public PARAGRAPH
{
public:
	firstParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		A();
	}
};

class secondParagraph : public PARAGRAPH
{
public:
	secondParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		B();
	}
};

class thirdParagraph : public PARAGRAPH
{
public:
	thirdParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		C();
	}
};

class fourthParagraph : public PARAGRAPH
{
public:
	fourthParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		D();
	}
};




// ----------- Graphics parent class -----------

class Graphics
{
protected:
	int defaultColors = 7;
	int secondaryColors = 31;
	const static int fontSize = 48;

	// Defines text color
	void setColor(int color, int fontSize = fontSize)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = fontSize;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;

		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	// Moves cursor to coordinates (X, Y)
	void setCursor(int x, int y)
	{
		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
	}

	// Calculates middle of screen
	int calculatePosition(std::string list[], int size)
	{
		int lengthMAX = list[0].length();
		for (int i = 0; i < size; i++)
		{
			int lengthMIN = list[i].length();

			if (lengthMAX < lengthMIN)
			{
				lengthMAX = lengthMIN;
			}
		}

		return lengthMAX;
	}

	Graphics() = default;

public:

	// Sets default window settings with custom colors and font size E.g. 1920, 1090, 7, 31, 48
	Graphics(int resolutionX, int resolutionY, int _defaultColor, int _secondaryColor, int _fontSize)
	{
		defaultColors = _defaultColor;
		secondaryColors = _secondaryColor;

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - FONT_SIZE * 2, resolutionY - FONT_SIZE * 2, TRUE);


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
		MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - FONT_SIZE * 2, resolutionY - FONT_SIZE * 2, TRUE);


		// Checks does user supply font size
		if (_fontSize != NULL)
			setColor(defaultColors, _fontSize);
		else
			setColor(defaultColors);

		setCursor(0, 0);
	}

	// Creates frame around description
	void makeFrame(int startX, int startY, int Width, int Height)
	{
		setCursor(startX, startY);


		std::cout << (char)201;
		for (int i = 0; i < Width - 1; i++)
		{
			std::cout << (char)205;
		}
		std::cout << (char)187;
		std::cout << std::endl;


		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				if (j == 0 || j == Width - 1)
				{
					std::cout << (char)186;
				}
				std::cout << " ";
			}
			std::cout << std::endl;
		}
		std::cout << (char)200;


		for (int i = 0; i < Width - 1; i++)
		{
			std::cout << (char)205;
		}
		std::cout << (char)188;
	}
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

		X = WINDOW_WIDTH / FONT_SIZE - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
		Y = WINDOW_HEIGHT / FONT_SIZE - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));

		size = _size;

		for (int i = 0; i < _size; i++)
			menuObject[i] = _menuObject[i];

		SecureZeroMemory(objNames, _size);
	}


	void vertical()
	{
		int counter = 1;
		char key;

		int * ColorSet = new int[size];
		for (int i = 0; i < size; i++)
		{
			ColorSet[i] = defaultColors;
		}

		while (true)
		{
			try
			{
				for (int j = 0; j < size; j++)
				{
					setCursor(X, Y + j);
					setColor(ColorSet[j]);
					std::cout << menuObject[j]->paragraphName;
				}

				key = _getch();


				if (key == 72 && (counter > 1 && counter <= size))
				{
					counter--;
				}
				else if (key == 80 && (counter >= 0 && counter < size))
				{
					counter++;
				}

				else if (key == '\r')
				{
					if (counter)
					{
						menuObject[counter - 1]->Execute();
						break;
					}
				}

				for (int i = 0; i < size; i++)
				{
					ColorSet[i] = defaultColors;
				}

				if (counter)
				{
					ColorSet[counter - 1] = secondaryColors;
				}
				DrawDescription(menuObject[counter - 1]->description);
			}
			catch (...)
			{
				counter = 1;
				continue;
			}
		}
	}

private:
	void DrawDescription(std::string text)
	{
		setCursor(10, 5);

		std::cout << text;
	}
};






int main()
{
	/*
	for (int i = 0; i < 100; i++)
	{
		setColor(i);
		std::cout << "Color - " << i << std::endl;
	}
	*/
	/*for (int i = 0; i < 300; i++)
	{
		std::cout << i << " " << (char)i << std::endl;
	}*/

	Graphics window(WINDOW_WIDTH, WINDOW_HEIGHT, NULL);

	//makeFrame( resolutionX / 10 - calculatePercent((resolutionX / 10), 11), 1080 / 10 - calculatePercent(1080 / 10, 80) );
	window.makeFrame(0, 0, (WINDOW_WIDTH / FONT_SIZE) * 2, WINDOW_HEIGHT / (FONT_SIZE * 2));

	std::string menuNames[4] = { "1 MENU" , "2 HELP", "3 TEST", "4 EXIT" };
	std::string menuDescriptions[4] = { "Displays this menu message", "Displays help message     ", "Displays message with test", "Shuts down the program    " };

	// ----------- Creating paragraphs objects ------------- //

	firstParagraph* fstPar = new firstParagraph(menuNames[0], menuDescriptions[0]);
	secondParagraph* sndPar = new secondParagraph(menuNames[1], menuDescriptions[1]);
	thirdParagraph* trdPar = new thirdParagraph(menuNames[2], menuDescriptions[2]);
	fourthParagraph* frtPar = new fourthParagraph(menuNames[3], menuDescriptions[3]);

	PARAGRAPH* objects[4] = { fstPar, sndPar, trdPar, frtPar };

	// ----------- Initialize Menu ----------- //

	Menu menu(4, objects);

	// Creates vertical menu orientation
	menu.vertical();


	// Removing paragraphs objects to escape memory leak
	delete fstPar, sndPar, trdPar, frtPar, objects;
	SecureZeroMemory(menuNames, 4);
	SecureZeroMemory(menuDescriptions, 4);

	system("pause");

	return 0;
}