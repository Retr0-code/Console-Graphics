#include "Semi-Graphics.h"



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


Graphics::Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize)
{
	defaultColors = _defaultColor.background + _defaultColor.frontground;
	secondaryColors = _secondaryColor.background + _secondaryColor.frontground;


	// Checks does user supply font size
	if (_fontSize != NULL)
	{
		fontSize = _fontSize;
		SetTextProperties(defaultColors, fontSize);
	}
	else
		SetTextProperties(defaultColors);

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);
	windowWidth = resolutionX;
	windowHeight = resolutionY;


	SetCursorPosition(0, 0);
}

Graphics::Graphics(int resolutionX, int resolutionY, int _fontSize)
{

	// Checks does user supply font size
	if (_fontSize != NULL)
	{
		fontSize = _fontSize;
		SetTextProperties(defaultColors, fontSize);
	}
	else
		SetTextProperties(defaultColors);
	
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(GetConsoleWindow(), 0, 0, resolutionX - fontSize * 2, resolutionY - fontSize * 2, TRUE);
	windowWidth = resolutionX;
	windowHeight = resolutionY;

	SetCursorPosition(0, 0);
}


void Graphics::SetTextProperties(int color, int _fontSize)
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

void Graphics::SetCursorPosition(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

int Graphics::CalculatePosition(std::string list[], int size)
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

int* Graphics::FillColorSet(int color, int size)
{
	int* ColorSet = new int[size];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));

	for (int i = 0; i < size; i++)
	{
		ColorSet[i] = Graphics::defaultColors;
	}

	return ColorSet;
}



Frame::Frame(int _originX, int _originY, int _Width, int _Height, frameSegments _segments)
{
	segments.leftTopCorner = _segments.leftTopCorner;
	segments.Horizontal = _segments.Horizontal;
	segments.Vertical = _segments.Vertical;

	originX = _originX;
	originY = _originY;

	Width = _Width;
	Height = _Height;

	if (_segments.leftStop != NULL)
		segments.leftStop = _segments.leftStop;

	if (_segments.rightStop != NULL)
		segments.rightStop = _segments.rightStop;

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

Frame::Frame(int _originX, int _originY, int _Width, int _Height)
{
	originX = _originX;
	originY = _originY;

	Width = _Width;
	Height = _Height;
}

void Frame::SpawnFrame(std::string frameHeader)
{
	SetCursorPosition(originX, originY);


	std::cout << segments.leftTopCorner;
	for (int i = 0; i < Width; i++)
	{
		std::cout << segments.Horizontal;
	}
	std::cout << segments.rightTopCorner;
	std::cout << std::endl;


	for (int i = 1; i < Height; i++)
	{
		SetCursorPosition(originX, originY + i);
		for (int j = 0; j <= Width; j++)
		{
			if (j == 0 || j == Width)
			{
				std::cout << segments.Vertical;
			}
			if (j != Width)
				std::cout << " ";
		}
		std::cout << std::endl;
	}

	SetCursorPosition(originX, originY + Height);
	std::cout << segments.leftDownCorner;

	for (int i = 0; i < Width; i++)
	{
		std::cout << segments.Horizontal;
	}
	std::cout << segments.rightDownCorner;


	if (frameHeader.length() != NULL)
	{
		if (frameHeader.length() % 2 == 0)
		{
			int frameTopCentere = Width / 2 - frameHeader.length();
			SetCursorPosition(originX + frameTopCentere + 2, originY);
			std::cout << segments.leftStop << frameHeader << segments.rightStop;
		}
		else
		{
			int frameTopCentere = Width / 2 - frameHeader.length();
			SetCursorPosition(originX + frameTopCentere, originY);
			std::cout << segments.leftStop << frameHeader << segments.rightStop;
		}
	}
}


Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
{
	X = _X;
	Y = _Y;
	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	menuObject.reserve(size);

	for (int i = 0; i < size; i++)
		menuObject.push_back(_menuObject[i]);
}

void Menu::DrawDescription(std::string text)
{
	SetTextProperties(defaultColors, fontSize);
	SetCursorPosition(descriptionField.originX + 3, descriptionField.originY + 3);

	std::cout << text;
}



vMenu::vMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
{
	fontSize = _Graphics.fontSize;

	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	size = _size;
	descriptionField = _descriptionField;

	menuObject.reserve(size);

	std::string* objNames = new std::string[size];
	SecureZeroMemory(objNames, sizeof(objNames));

	for (int i = 0; i < size; i++)
	{
		menuObject[i] = _menuObject[i];
		objNames[i] = _menuObject[0]->paragraphName;
	}

	X = _Graphics.windowWidth / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
	Y = _Graphics.windowHeight / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames)) - 3;

	delete[] objNames;
}

vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
{
	X = _Frame.Width / 4 + 1;
	Y = _Frame.Height / 2;

	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	menuObject.reserve(size);

	for (int i = 0; i < size; i++)
		menuObject.push_back(_menuObject[i]);
}

BOOL vMenu::SpawnMenu(bool onlyDraw)
{
	int counter = 1;
	char key;

	int * ColorSet = new int[size];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));

	ColorSet = FillColorSet(defaultColors, size);

	std::string hints[3] = { "<- Back", "Enter OK", "TAB Switch/Exit" };

	SetTextProperties(secondaryColors, fontSize);
	SetCursorPosition(4, 0);
	for (int i = 0; i < 3; i++)
	{
		SetCursorPosition((windowWidth / fontSize / 3) * i + hints[i - 1].length() / 2 + 4, 0);
		std::cout << hints[i];
	}

	while (true)
	{
		try
		{
			DrawMenu(ColorSet);

			if (key == '\b' || onlyDraw == true)
			{
				DrawMenu(ColorSet);

				delete[] ColorSet;
				return FALSE;
			}
			else if (key == '	')
			{
				DrawMenu(ColorSet);

				ColorSet[counter - 1] = defaultColors;
				delete[] ColorSet;
				return TRUE;
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
					delete[] ColorSet;
					SetTextProperties(defaultColors, fontSize);
					menuObject[counter - 1]->Execute();
					return FALSE;
				}
			}

			ColorSet = FillColorSet(defaultColors, size);

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

void vMenu::DrawMenu(int _ColorSet[])
{
	for (int j = 0; j < size; j++)
	{
		SetCursorPosition(X, Y + j);
		SetTextProperties(_ColorSet[j], fontSize);
		std::cout << menuObject[j]->paragraphName;
	}
}



hMenu::hMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
{
	fontSize = _Graphics.fontSize;

	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	size = _size;
	descriptionField = _descriptionField;

	menuObject.reserve(size);

	std::string* objNames = new std::string[size];
	SecureZeroMemory(objNames, sizeof(objNames));

	for (int i = 0; i < size; i++)
	{
		menuObject[i] = _menuObject[i];
		objNames[i] = _menuObject[0]->paragraphName;
	}

	X = _Graphics.windowWidth / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
	Y = _Graphics.windowHeight / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames)) - 3;

	delete[] objNames;
}

hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
{
	X = _Frame.originX + _Frame.Width / 2;
	Y = _Frame.originY + _Frame.Height / 2;

	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	menuObject.reserve(size);

	for (int i = 0; i < size; i++)
		menuObject.push_back(_menuObject[i]);
}

BOOL hMenu::SpawnMenu(bool onlyDraw)
{
	int counter = 1;
	char key;

	std::string hints[3] = { "<- Back", "Enter OK", "TAB Switch/Exit" };

	SetTextProperties(secondaryColors, fontSize);
	SetCursorPosition(4, 0);
	for (int i = 0; i < 3; i++)
	{
		SetCursorPosition((windowWidth / fontSize / 3) * i + hints[i - 1].length() / 2 + 4, 0);
		std::cout << hints[i];
	}

	if (size % 2 != 0)
	{
		X = X / size * 2;
		Y = Y - size / 6;
	}
	else
	{
		X = X / (size / 2) - 2;
		Y = Y - size / 6;
	}

	int * ColorSet = new int[size];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));

	ColorSet = FillColorSet(defaultColors, size);

	while (true)
	{
		try
		{
			DrawMenu(ColorSet);

			if (key == '\b' || onlyDraw == true)
			{
				DrawMenu(ColorSet);

				delete ColorSet;
				return FALSE;
			}
			else if (key == '	')
			{
				DrawMenu(ColorSet);

				ColorSet[counter - 1] = defaultColors;
				delete ColorSet;
				return TRUE;
			}

			key = _getch();


			if (key == 75 && (counter > 1 && counter <= size))
			{
				counter--;
			}
			else if (key == 77 && (counter >= 0 && counter < size))
			{
				counter++;
			}

			else if (key == '\r')
			{
				if (counter)
				{
					delete[] ColorSet;
					SetTextProperties(defaultColors, fontSize);
					menuObject[counter - 1]->Execute();
					return FALSE;
				}
			}

			ColorSet = FillColorSet(defaultColors, size);

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

void hMenu::DrawMenu(int _ColorSet[])
{
	for (int j = 0; j < size; j++)
	{
		SetCursorPosition(X + X * j, Y);
		SetTextProperties(_ColorSet[j], fontSize);
		std::cout << menuObject[j]->paragraphName;
	}
}



cMenu::cMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

cMenu::cMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _descriptionField, _Graphics) {}

cMenu::cMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _Frame, _descriptionField, _Graphics) {}

PARAGRAPH** cMenu::SpawnMenu()
{
	int counter = 1;
	char key;

	std::string hints[4] = { "<- Back", "Enter OK", "TAB Switch/Exit", "SPACE Select" };

	SetTextProperties(secondaryColors, fontSize);
	SetCursorPosition(4, 0);
	for (int i = 0; i < 4; i++)
	{
		SetCursorPosition((windowWidth / fontSize / 4) * i + hints[i - 1].length() / 2 + 4, 0);
		std::cout << hints[i];
	}

	PARAGRAPH** selectedPoints = new PARAGRAPH*[size];
	SecureZeroMemory(selectedPoints, sizeof(selectedPoints));

	int * ColorSet = new int[size];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));

	ColorSet = FillColorSet(defaultColors, size);


	for (int j = 0; j < size; j++)
	{
		SetCursorPosition(X - 3, Y + j);
		SetTextProperties(ColorSet[j], fontSize);
		std::cout << '[';
		SetCursorPosition(X - 1, Y + j);
		std::cout << ']';
	}

	while (true)
	{
		try
		{
			DrawMenu(ColorSet);

			key = _getch();


			if (key == 72 && (counter > 1 && counter <= size))
			{
				counter--;
			}
			else if (key == 80 && (counter >= 0 && counter < size))
			{
				counter++;
			}

			else if (key == ' ')
			{
				if (selectedPoints[counter - 1] == NULL)
				{
					selectedPoints[counter - 1] = menuObject[counter - 1];
					SetCursorPosition(X - 2, Y + (counter - 1));
					SetTextProperties(defaultColors, fontSize);
					std::cout << "*";
				}
				else if (selectedPoints[counter - 1] != NULL)
				{
					selectedPoints[counter - 1] = NULL;
					SetCursorPosition(X - 2, Y + (counter - 1));
					SetTextProperties(defaultColors, fontSize);
					std::cout << " ";
				}
			}

			else if (key == '\r')
			{
				delete[] ColorSet;
				SetTextProperties(defaultColors, fontSize);
				return selectedPoints;
			}

			ColorSet = FillColorSet(defaultColors, size);

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


sMenu::sMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

sMenu::sMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _descriptionField, _Graphics) {}

sMenu::sMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _Frame, _descriptionField, _Graphics) {}

void sMenu::SpawnMenu(Menu* menu1, Menu* menu2)
{
	menu1->SpawnMenu(TRUE);
	menu2->SpawnMenu(TRUE);


	BOOL menu2State = FALSE;
	BOOL menu1State = menu2->SpawnMenu(FALSE);

	while (true)
	{
		if (menu1State && !menu2State)
		{
			std::cout << " ";
			menu1State = FALSE;
			menu2State = menu2->SpawnMenu(FALSE);
		}
		else if (menu2State && !menu1State)
		{
			std::cout << " ";
			menu2State = FALSE;
			menu1State = menu1->SpawnMenu(FALSE);
		}
		else if (!menu2State && !menu1State)
		{
			delete menu1, menu2;
			break;
		}
	}
}


dMenu::dMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

dMenu::dMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
{
	fontSize = _Graphics.fontSize;

	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	size = _size;
	descriptionField = _descriptionField;

	menuObject.reserve(size);

	std::string* objNames = new std::string[size];
	SecureZeroMemory(objNames, sizeof(objNames));

	for (int i = 0; i < size; i++)
	{
		menuObject[i] = _menuObject[i];
		objNames[i] = _menuObject[0]->paragraphName;
	}

	X = _Graphics.windowWidth / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames));
	Y = _Graphics.windowHeight / _Graphics.fontSize - CalculatePosition(objNames, sizeof(objNames) / sizeof(*objNames)) - 3;

	delete[] objNames;
}

dMenu::dMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
{
	X = _Frame.Width / 4 + 1;
	Y = _Frame.Height / 2;

	fontSize = _Graphics.fontSize;
	size = _size;
	descriptionField = _descriptionField;
	defaultColors = _Graphics.defaultColors;
	secondaryColors = _Graphics.secondaryColors;

	menuObject.reserve(size);

	for (int i = 0; i < size; i++)
		menuObject.push_back(_menuObject[i]);
}

BOOL dMenu::SpawnMenu(vMenu* paragraphs[], bool onlyDraw)
{
	int counter = 1;
	char key;

	int * ColorSet = new int[size];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));

	ColorSet = FillColorSet(defaultColors, size);

	std::string hints[3] = { "<- Back", "Enter OK", "TAB Switch/Exit" };

	SetTextProperties(secondaryColors, fontSize);
	SetCursorPosition(4, 0);

	for (int i = 0; i < 3; i++)
	{
		SetCursorPosition((windowWidth / fontSize / 3) * i + hints[i - 1].length() / 2 + 4, 0);
		std::cout << hints[i];
	}

	while (true)
	{
		try
		{
			DrawMenu(ColorSet);

			if (key == '\b' || onlyDraw == TRUE)
			{
				DrawMenu(ColorSet);
				delete[] ColorSet;
				return FALSE;
			}
			else if (key == '	')
			{
				DrawMenu(ColorSet);

				ColorSet[counter - 1] = defaultColors;
				delete[] ColorSet;
				return TRUE;
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

			else if (key == ' ')
			{
				if (counter)
				{
					SetTextProperties(defaultColors, fontSize);
					(paragraphs[counter - 1]->*&dMenu::Y) += counter;
					(paragraphs[counter - 1]->*&dMenu::X) += 1;

					Y += (paragraphs[counter - 1]->*&dMenu::size);
					DrawMenu(ColorSet);

					paragraphs[counter - 1]->SpawnMenu();

					for (int i = 0; i < size; i++)
					{
						SetCursorPosition(X, Y + i);
						std::cout << "        ";
					}

					(paragraphs[counter - 1]->*&dMenu::Y) -= counter;
					(paragraphs[counter - 1]->*&dMenu::X) -= 1;

					Y -= (paragraphs[counter - 1]->*&dMenu::size);
					DrawMenu(ColorSet);
				}
			}

			else if (key == '\r')
			{
				if (counter)
				{
					delete[] ColorSet;
					SetTextProperties(defaultColors, fontSize);
					menuObject[counter - 1]->Execute();
					return FALSE;
				}
			}

			ColorSet = FillColorSet(defaultColors, size);

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

void dMenu::DrawMenu(int _ColorSet[])
{
	for (int j = 0; j < size; j++)
	{
		SetCursorPosition(X, Y + j);
		SetTextProperties(_ColorSet[j], fontSize);
		std::cout << menuObject[j]->paragraphName;
	}
}




BOOL MsgBox::Message(MSG_BOX_TYPE container)
{
	int originX = (width / 4) / lfontSize + 2;
	int originY = ((height / 4) / lfontSize) * 3;


	SetTextProperties(container.backgroundColor, lfontSize);
	Frame frame((width / 4) / lfontSize, (height / 4) / lfontSize, (width / lfontSize) * 2 - (width / 4) / lfontSize * 2, height / (lfontSize * 2));
	frame.SpawnFrame(container.boxHeader);

	SetCursorPosition(frame.originX + 3, frame.originY + 3);
	BOOL state = FALSE;
	char key;

	int* ColorSet = new int[2];
	SecureZeroMemory(ColorSet, sizeof(ColorSet));
	ColorSet = FillColorSet(container.deselectColor, 2);

	while (true)
	{
		try
		{
			SetTextProperties(container.backgroundColor, lfontSize);
			SetCursorPosition(frame.originX + 3, frame.originY + 3);
			std::cout << description;

			SetCursorPosition(originX * 2, originY);
			SetTextProperties(ColorSet[state], lfontSize);
			std::cout << "  OK  ";


			SetCursorPosition(originX * 4, originY);
			SetTextProperties(ColorSet[state - 1], lfontSize);
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

				SetTextProperties(defaultColors, lfontSize);
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