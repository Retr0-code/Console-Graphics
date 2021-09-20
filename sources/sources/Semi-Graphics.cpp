#include <string>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <functional>

#include "Semi-Graphics.h"


namespace pgi
{
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


	PARAGRAPH::PARAGRAPH(std::string paragraphName, std::string description)
	{
		paragraphName = this->paragraphName;
		description = this->description;
	}



	// --------------| Main setup class |--------------

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

	int Graphics::CalculateMaxLength(std::string list[], int size)
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

	std::string* Graphics::MaskDescriptions(std::string descriptions[], int size)
	{
		int maxLength = CalculateMaxLength(descriptions, size);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < maxLength - descriptions[i].length(); j++)
			{
				descriptions[i] += " ";
			}
		}
		return descriptions;
	}


	// --------------| Line class |--------------

	Line::Line(int X, int Y, int _lineLength, char _lineSegment)
	{
		lineStartX = X;
		lineStartY = Y;
		lineLength = _lineLength;
		lineSegment = _lineSegment;
	};


	void vLine::DrawLine()
	{
		SetCursorPosition(lineStartX, lineStartY);

		for (int i = 0; i < lineLength; i++)
			std::cout << lineSegment << std::endl;
	}

	void hLine::DrawLine()
	{
		SetCursorPosition(lineStartX, lineStartY);

		for (int i = 0; i < lineLength; i++)
			std::cout << lineSegment;
	}


	// --------------| Frame class |--------------

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

	int Frame::GetWidth()
	{
		return Width;
	}

	int Frame::GetHeight()
	{
		return Height;
	}

	int Frame::GetOriginX()
	{
		return originX;
	}

	int Frame::GetOriginY()
	{
		return originY;
	}


	// --------------| Menu interface class |--------------

	Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
	{
		position.X = _X;
		position.Y = _Y;
		fontSize = _Graphics.fontSize;
		size = _size;
		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;
		descriptionField = _descriptionField;

		descriptions = new std::string[size];

		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
			menuObject[i] = _menuObject[i];
	}

	int Menu::MenuLoop(int switchKey1, int switchKey2, char conditionKey, int colorSet[])
	{
		int counter = 1;
		char key;

		while (true)
		{
			try
			{
				DrawMenu(colorSet);
				DrawDescription(descriptions[counter - 1]);

				if (key == BACKSPACE)
				{
					colorSet = FillColorSet(defaultColors, size);
					DrawMenu(colorSet);

					delete[] colorSet;
					return MENU_EXIT;
				}
				else if (key == TAB)
				{
					DrawMenu(colorSet);

					colorSet[counter - 1] = defaultColors;
					delete[] colorSet;
					return MENU_SWITCH;
				}


				key = _getch();


				if (key == switchKey1 && (counter > 1 && counter <= size))
				{
					counter--;
				}
				else if (key == switchKey2 && (counter >= 0 && counter < size))
				{
					counter++;
				}
				else if (key == conditionKey)
				{
					if (this->Condition(counter, colorSet))
					{
						return MENU_DONE;
					}
				}
				else if (key == ENTER)
				{
					if (counter)
					{
						delete[] colorSet;
						SetTextProperties(defaultColors, fontSize);
						menuObject[counter - 1]->Execute();
						return MENU_DONE;
					}
				}

				colorSet = FillColorSet(defaultColors, size);
				if (counter)
				{
					colorSet[counter - 1] = secondaryColors;
				}
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
		SetTextProperties(defaultColors, fontSize);
		SetCursorPosition(descriptionField.GetOriginX() + 3, descriptionField.GetOriginY() + 3);

		std::cout << text;
	}

	coordinates Menu::CalculatePositionInFrame(int frameWidth, int frameHeight)
	{
		return {
			frameWidth / 4 + 1,
			frameHeight / 2
		};
	}

	coordinates Menu::CalculateWindowCenter(int windowWidth, int windowHeight, std::string objNames[])
	{
		return {
			windowWidth / fontSize - CalculateMaxLength(objNames, sizeof(objNames) / sizeof(*objNames)),
			windowHeight / fontSize - CalculateMaxLength(objNames, sizeof(objNames) / sizeof(*objNames)) - 3
		};
	}



	// --------------| Vertical menu |--------------

	vMenu::vMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

	vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
	{
		fontSize = _Graphics.fontSize;

		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;

		size = _size;
		descriptionField = _descriptionField;

		std::string* objNames = new std::string[size];
		SecureZeroMemory(objNames, sizeof(objNames));

		descriptions = new std::string[size];		
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);
		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
		{
			menuObject[i] = _menuObject[i];
			objNames[i] = _menuObject[0]->paragraphName;
		}

		position = CalculateWindowCenter(_Graphics.windowWidth, _Graphics.windowHeight, objNames);
		
		delete[] objNames;
	}

	vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
	{
		position = CalculatePositionInFrame(_Frame.GetWidth(), _Frame.GetHeight());

		fontSize = _Graphics.fontSize;
		size = _size;
		descriptionField = _descriptionField;
		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;

		descriptions = new std::string[size];

		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
			menuObject[i] = _menuObject[i];
	}

	int vMenu::SpawnMenu(bool onlyDraw)
	{
		int * colorSet = new int[size];
		SecureZeroMemory(colorSet, sizeof(colorSet));
		colorSet = FillColorSet(defaultColors, size);

		if (onlyDraw)
		{
			colorSet = FillColorSet(defaultColors, size);
			DrawMenu(colorSet);

			delete[] colorSet;
			return MENU_EXIT;
		}

		return MenuLoop(ARROW_UP, ARROW_DOWN, '\0', colorSet);
	}

	void vMenu::DrawMenu(int _ColorSet[])
	{
		for (int j = 0; j < size; j++)
		{
			SetCursorPosition(position.X, position.Y + j);
			SetTextProperties(_ColorSet[j], fontSize);
			std::cout << menuObject[j]->paragraphName;
		}
	}




	// --------------| Horizontal menu |--------------

	hMenu::hMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

	hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
	{
		fontSize = _Graphics.fontSize;

		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;

		size = _size;
		descriptionField = _descriptionField;

		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		std::string* objNames = new std::string[size];
		SecureZeroMemory(objNames, sizeof(objNames));

		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
		{
			menuObject[i] = _menuObject[i];
			objNames[i] = _menuObject[0]->paragraphName;
		}

		position = CalculateWindowCenter(_Graphics.windowWidth, _Graphics.windowHeight, objNames);

		delete[] objNames;
	}

	hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
	{
		fontSize = _Graphics.fontSize;
		size = _size;
		descriptionField = _descriptionField;
		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;

		position = CalculatePositionInFrame(_Frame.GetWidth(), _Frame.GetHeight());
		position.Y += _Frame.GetOriginY();
		
		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
			menuObject[i] = _menuObject[i];
	}

	int hMenu::SpawnMenu(bool onlyDraw)
	{
		int * colorSet = new int[size];
		SecureZeroMemory(colorSet, sizeof(colorSet));

		colorSet = FillColorSet(defaultColors, size);

		if (onlyDraw)
		{
			colorSet = FillColorSet(defaultColors, size);
			DrawMenu(colorSet);

			delete[] colorSet;
			return MENU_EXIT;
		}

		return MenuLoop(ARROW_LEFT, ARROW_RIGHT, '\0', colorSet);
	}

	void hMenu::DrawMenu(int _ColorSet[])
	{
		for (int j = 0; j < size; j++)
		{
			SetCursorPosition(position.X + position.X * j, position.Y);
			SetTextProperties(_ColorSet[j], fontSize);
			std::cout << menuObject[j]->paragraphName;
		}
	}

	coordinates hMenu::CalculatePositionInFrame(int frameWidth, int frameHeight)
	{
		int X = frameWidth / (size + 1);
		int Y = frameHeight / 2;

		return { X, Y };
	}

	coordinates hMenu::CalculateWindowCenter(int windowWidth, int windowHeight, std::string objNames[])
	{
		if (size % 2 == 0)
		{
			return {
			(windowWidth / fontSize * 2) / (size + size / 2),
			(windowHeight / fontSize) / 2 + 3
			};
		}
		else
		{
			return {
				(windowWidth / fontSize * 2) / (size + 1),
				(windowHeight / fontSize) / 2 + 3
			};
		}
	}


	// --------------| CheckBox menu |--------------

	cMenu::cMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics)
	{
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		selectedPoints = new PARAGRAPH*[size];
	}

	cMenu::cMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _descriptionField, _Graphics)
	{
		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		selectedPoints = new PARAGRAPH*[size];
	}

	cMenu::cMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _Frame, _descriptionField, _Graphics)
	{
		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		selectedPoints = new PARAGRAPH*[size];
	}

	PARAGRAPH** cMenu::SpawnMenu()
	{
		selectedPoints = new PARAGRAPH*[size];
		SecureZeroMemory(selectedPoints, sizeof(selectedPoints));

		int * colorSet = new int[size];
		SecureZeroMemory(colorSet, sizeof(colorSet));

		colorSet = FillColorSet(defaultColors, size);


		for (int j = 0; j < size; j++)
		{
			SetCursorPosition(position.X - 3, position.Y + j);
			SetTextProperties(colorSet[j], fontSize);
			std::cout << '[';
			SetCursorPosition(position.X - 1, position.Y + j);
			std::cout << ']';
		}

		MenuLoop(ARROW_UP, ARROW_DOWN, SPACE, colorSet);
		return selectedPoints;
	}

	bool cMenu::Condition(int counter, int colorSet[])
	{
		if (selectedPoints[counter - 1] == NULL)
		{
			selectedPoints[counter - 1] = menuObject[counter - 1];
			SetCursorPosition(position.X - 2, position.Y + (counter - 1));
			SetTextProperties(defaultColors, fontSize);
			std::cout << "*";
		}
		else if (selectedPoints[counter - 1] != NULL)
		{
			selectedPoints[counter - 1] = NULL;
			SetCursorPosition(position.X - 2, position.Y + (counter - 1));
			SetTextProperties(defaultColors, fontSize);
			std::cout << " ";
		}
		return false;
	}


	// --------------| Double (switch) menu |--------------

	sMenu::sMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics) {}

	sMenu::sMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _descriptionField, _Graphics) {}

	sMenu::sMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics) : vMenu(_size, _menuObject, _Frame, _descriptionField, _Graphics) {}

	int sMenu::SpawnMenu(Menu* menu1, Menu* menu2)
	{
		menu1->SpawnMenu(TRUE);
		menu2->SpawnMenu(TRUE);


		BOOL menu2State = MENU_SWITCH;
		BOOL menu1State = MENU_EXIT;

		while (true)
		{
			if (menu1State == MENU_SWITCH && menu2State == MENU_EXIT)
			{
				std::cout << " ";
				menu1State = MENU_EXIT;
				menu2State = menu2->SpawnMenu(FALSE);
			}
			else if (menu2State == MENU_SWITCH && menu1State == MENU_EXIT)
			{
				std::cout << " ";
				menu2State = MENU_EXIT;
				menu1State = menu1->SpawnMenu(FALSE);
			}
			else if (menu2State == MENU_DONE || menu1State == MENU_DONE)
			{
				return MENU_DONE;
			}
			else if (menu1State == MENU_EXIT && menu2State == MENU_EXIT)
			{
				return MENU_EXIT;
			}
		}
	}



	// --------------| Frop-down menu |--------------

	dMenu::dMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _descriptionField, Graphics _Graphics) : Menu(_size, _X, _Y, _menuObject, _descriptionField, _Graphics)
	{
		std::string* paragraphNames = new std::string[_size];
		paragraphs = _paragraphs;

		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		for (int i = 0; i < _size; i++)
			paragraphNames[i] = _menuObject[i]->paragraphName;

		int lengthOfSpace = CalculateMaxLength(paragraphNames, _size);

		for (int i = 0; i < lengthOfSpace; i++)
			space += " ";
	}

	dMenu::dMenu(int _size, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _descriptionField, Graphics _Graphics)
	{
		fontSize = _Graphics.fontSize;

		size = _size;
		descriptionField = _descriptionField;
		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;

		paragraphs = _paragraphs;

		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		menuObject = new PARAGRAPH*[size];

		std::string* objNames = new std::string[size];
		SecureZeroMemory(objNames, sizeof(objNames));

		for (int i = 0; i < size; i++)
		{
			menuObject[i] = _menuObject[i];
			objNames[i] = _menuObject[0]->paragraphName;
		}

		position = CalculateWindowCenter(_Graphics.windowWidth, _Graphics.windowHeight, objNames);


		int lengthOfSpace = CalculateMaxLength(objNames, _size);

		for (int i = 0; i < lengthOfSpace; i++)
			space += " ";

		delete[] objNames;
	}

	dMenu::dMenu(int _size, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
	{
		fontSize = _Graphics.fontSize;
		size = _size;
		descriptionField = _descriptionField;
		defaultColors = _Graphics.defaultColors;
		secondaryColors = _Graphics.secondaryColors;
		position = CalculatePositionInFrame(_Frame.GetWidth(), _Frame.GetHeight());

		paragraphs = _paragraphs;

		descriptions = new std::string[size];
		for (int i = 0; i < size; i++)
			descriptions[i] = _menuObject[i]->description;

		descriptions = MaskDescriptions(descriptions, size);

		menuObject = new PARAGRAPH*[size];

		for (int i = 0; i < size; i++)
			menuObject[i] = _menuObject[i];

		std::string* paragraphNames = new std::string[_size];

		for (int i = 0; i < _size; i++)
			paragraphNames[i] = _menuObject[i]->paragraphName;

		int lengthOfSpace = CalculateMaxLength(paragraphNames, _size);

		for (int i = 0; i < lengthOfSpace; i++)
			space += " ";
	}

	int dMenu::SpawnMenu(bool onlyDraw)
	{
		int * colorSet = new int[size];
		SecureZeroMemory(colorSet, sizeof(colorSet));
		colorSet = FillColorSet(defaultColors, size);

		if (onlyDraw)
		{
			colorSet = FillColorSet(defaultColors, size);
			DrawMenu(colorSet);

			delete[] colorSet;
			return MENU_EXIT;
		}

		return MenuLoop(ARROW_UP, ARROW_DOWN, ' ', colorSet);
	}

	bool dMenu::Condition(int counter, int colorSet[])
	{
		colorSet = FillColorSet(defaultColors, size);
		(paragraphs[counter - 1]->*&dMenu::position).Y += counter;
		(paragraphs[counter - 1]->*&dMenu::position).X += 1;

		position.Y += (paragraphs[counter - 1]->*&dMenu::size);
		DrawMenu(colorSet);

		for (int j = 0; j < size; j++)
		{
			SetCursorPosition(position.X, (paragraphs[counter - 1]->*&dMenu::position).Y + j);
			SetTextProperties(colorSet[j], fontSize);
			std::cout << " " << space << " ";
		}

		if (paragraphs[counter - 1]->SpawnMenu() == MENU_DONE)
		{
			return true;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				SetCursorPosition(position.X, position.Y + i);
				std::cout << space << " ";
			}

			(paragraphs[counter - 1]->*&dMenu::position).Y -= counter;
			(paragraphs[counter - 1]->*&dMenu::position).X -= 1;

			position.Y -= (paragraphs[counter - 1]->*&dMenu::size);

			for (int j = 0; j < size; j++)
			{
				SetCursorPosition(position.X, position.Y + j);
				SetTextProperties(colorSet[j], fontSize);
				std::cout << " " << space << " ";
			}

			DrawMenu(colorSet);
			return false;
		}
	}

	void dMenu::DrawMenu(int _ColorSet[])
	{
		for (int j = 0; j < size; j++)
		{
			SetCursorPosition(position.X, position.Y + j);
			SetTextProperties(_ColorSet[j], fontSize);
			std::cout << menuObject[j]->paragraphName;
		}
	}


	// --------------| Dialog box spawner |--------------

	MsgBox::MsgBox(std::string _description, Graphics _Graphics)
	{
		description = _description;
		lfontSize = _Graphics.fontSize;
		width = _Graphics.windowWidth;
		height = _Graphics.windowHeight;
	}

	BOOL MsgBox::Message(MSG_BOX_TYPE container)
	{
		int originX = (width / 4) / lfontSize + 2;
		int originY = ((height / 4) / lfontSize) * 3;


		SetTextProperties(container.backgroundColor, lfontSize);
		Frame frame((width / 4) / lfontSize, (height / 4) / lfontSize, (width / lfontSize) * 2 - (width / 4) / lfontSize * 2, height / (lfontSize * 2));
		frame.SpawnFrame(container.boxHeader);

		SetCursorPosition(frame.GetOriginX() + 3, frame.GetOriginY() + 3);
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
				SetCursorPosition(frame.GetOriginX() + 3, frame.GetOriginY() + 3);
				std::cout << description;

				SetCursorPosition(originX * 2, originY);
				SetTextProperties(ColorSet[state], lfontSize);
				std::cout << "  OK  ";


				SetCursorPosition(originX * 4, originY);
				SetTextProperties(ColorSet[state - 1], lfontSize);
				std::cout << "CANCEL";

				key = _getch();

				if (key == ARROW_RIGHT && state == TRUE)
				{
					ColorSet[state] = container.selectColor;
					ColorSet[state - 1] = container.deselectColor;
					state = FALSE;
				}
				else if (key == ARROW_LEFT && state == FALSE)
				{
					ColorSet[state] = container.deselectColor;
					ColorSet[state - 1] = container.selectColor;
					state = TRUE;
				}

				else if (key == ENTER)
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
}