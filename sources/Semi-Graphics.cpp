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

// Sets default window settings with custom colors and font size E.g. 1920, 1090, 7, 31, 48
Graphics::Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize)
{
	defaultColors = _defaultColor.background + _defaultColor.frontground;
	secondaryColors = _secondaryColor.background + _secondaryColor.frontground;


	// Checks does user supply font size
	if (_fontSize != NULL)
	{
		fontSize = _fontSize;
		setColor(defaultColors, fontSize);
	}
	else
		setColor(defaultColors);

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);
	windowWidth = resolutionX;
	windowHeight = resolutionY;


	setCursor(0, 0);
}

// Sets default window settings without custom colors E.g. 1920, 1090, 48
Graphics::Graphics(int resolutionX, int resolutionY, int _fontSize)
{

	// Checks does user supply font size
	if (_fontSize != NULL)
	{
		fontSize = _fontSize;
		setColor(defaultColors, fontSize);
	}
	else
		setColor(defaultColors);
	
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);
	windowWidth = resolutionX;
	windowHeight = resolutionY;

	setCursor(0, 0);
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


// Constructs frame with custom segments
Frame::Frame(int _originX, int _originY, int _Width, int _Height, frameSegments _segments)
{
	segments.leftTopCorner = _segments.leftTopCorner;
	segments.horizontal = _segments.horizontal;
	segments.vertical = _segments.vertical;

	originX = _originX;
	originY = _originY;

	Width = _Width;
	Height = _Height;

	if (_segments.rightTopCorner == NULL)
	{
		segments.rightTopCorner = _segments.leftTopCorner;

		if (_segments.leftDownCorner == NULL)
		{
			segments.leftDownCorner = _segments.leftTopCorner;

			if (_segments.rightDownCorner == NULL)
				segments.rightDownCorner = _segments.leftTopCorner;
			else
				segments.rightDownCorner = _segments.rightDownCorner;
		}
		else
			segments.leftDownCorner = _segments.leftDownCorner;
	}
	else
		segments.rightTopCorner = _segments.rightTopCorner;
}

// Constructs frame with default segments
Frame::Frame(int _originX, int _originY, int _Width, int _Height)
{
	originX = _originX;
	originY = _originY;

	Width = _Width;
	Height = _Height;
}


// Creates frame around description
void Frame::spawnFrame()
{
	setCursor(originX, originY);


	std::cout << segments.leftTopCorner;
	for (int i = 0; i < Width; i++)
	{
		std::cout << segments.horizontal;
	}
	std::cout << segments.rightTopCorner;
	std::cout << std::endl;


	for (int i = 1; i < Height; i++)
	{
		setCursor(originX, originY + i);
		for (int j = 0; j <= Width; j++)
		{
			if (j == 0 || j == Width)
			{
				std::cout << segments.vertical;
			}
			if (j != Width)
				std::cout << " ";
		}
		std::cout << std::endl;
	}

	setCursor(originX, originY + Height);
	std::cout << segments.leftDownCorner;

	for (int i = 0; i < Width; i++)
	{
		std::cout << segments.horizontal;
	}
	std::cout << segments.rightDownCorner;
}



// Fixed menu position of paragraphs without custom colors
Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
{
	X = _X;
	Y = _Y;
	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	for (int i = 0; i < _size; i++)
		menuObject[i] = _menuObject[i];
}

// Centered menu position of paragraphs without custom colors
Menu::Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
{
	std::string* objNames = new std::string[_size];
	
	for (int i = 0; i < _size; i++)
	{
		menuObject[i] = _menuObject[i];
		objNames[i] = _menuObject[0]->paragraphName;
	}

	X = _Graphics.windowWidth / _Graphics.fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
	Y = _Graphics.windowHeight / _Graphics.fontSize - calculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
	fontSize = _Graphics.fontSize;

	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	size = _size;
	descriptionField = _descriptionField;

	SecureZeroMemory(objNames, _size);
}

// Creates Menu with fixed position in frame without custom colors
Menu::Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField)
{
	std::string* objNames = new std::string[_size];

	for (int i = 0; i < _size; i++)
	{
		menuObject[i] = _menuObject[i];
		objNames[i] = _menuObject[0]->paragraphName;
	}

	X = _Frame.Width / 4 + 1;
	Y = _Frame.Height / 2;

	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;
}

Menu::~Menu()
{
	delete menuObject;
	setColor(defaultColors, fontSize);
}


// Spawns Vertical Menu
void Menu::vertical()
{
	int counter = 1;
	char key;

	int * ColorSet = new int[size];
	SecureZeroMemory(ColorSet, size);

	for (int i = 0; i < size; i++)
	{
		ColorSet[i] = Graphics::defaultColors;
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
					setColor(defaultColors, fontSize);
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

// Displays description of functions that is in menu
void Menu::DrawDescription(std::string text)
{
	setCursor(descriptionField.originX + 3, descriptionField.originY + 3);

	std::cout << text;
}


// Spawns Dialog box of type that user wants
BOOL MsgBox::Message(MSG_BOX_TYPE container)
{
	int originX = (width / 4) / lfontSize + 2;
	int originY = ((height / 4) / lfontSize) * 3;


	setColor(container.backgroundColor, lfontSize);
	Frame frame((width / 4) / lfontSize, (height / 4) / lfontSize, (width / lfontSize) * 2 - (width / 4) / lfontSize * 2, height / (lfontSize * 2));
	frame.spawnFrame();

	setCursor(frame.originX + 3, frame.originY + 3);
	BOOL state = FALSE;
	char key;

	int ColorSet[2];

	SecureZeroMemory(ColorSet, 2);

	for (int i = 0; i < 2; i++)
	{
		ColorSet[i] = container.deselectColor;
	}

	while (true)
	{
		try
		{
			setColor(container.backgroundColor, lfontSize);
			setCursor(frame.originX + 3, frame.originY + 3);
			std::cout << description;

			setCursor(originX * 2, originY);
			setColor(ColorSet[state], lfontSize);
			std::cout << "  OK  ";


			setCursor(originX * 4, originY);
			setColor(ColorSet[state - 1], lfontSize);
			std::cout << "CANCEL";

			key = _getch();

			if (key == 77 && state == TRUE)
			{
				ColorSet[state] = container.selectColor;
				ColorSet[state - 1] = container.deselectColor;
				state = FALSE;
			}
			else if (key == 75 && state == FALSE)
			{
				ColorSet[state] = container.deselectColor;
				ColorSet[state - 1] = container.selectColor;
				state = TRUE;
			}

			else if (key == '\r')
			{

				setColor(defaultColors, lfontSize);
				return state;
			}
		}
		catch (...)
		{
			state = FALSE;
			continue;
		}
	}
}