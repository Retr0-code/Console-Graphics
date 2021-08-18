#include "pch.h"
#include "Semi-Graphics.h"


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

// Defines text color
void Graphics::setColor(int color, int _fontSize)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = _fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Moves cursor to coordinates (X, Y)
void Graphics::setCursor(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// Calculates middle of screen
int Graphics::calculatePosition(std::string list[], int size)
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

// Creates frame around description
void Graphics::makeFrame(int startX, int startY, int Width, int Height)
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


void Menu::vertical()
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
				setColor(ColorSet[j], fontSize);
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

void Menu::DrawDescription(std::string text)
{
	setCursor(10, 5);

	std::cout << text;
}