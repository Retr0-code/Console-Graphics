#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "../sources/Semi-Graphics.h"

#define FONT_SIZE 36
#define WINDOW_WIDTH 1650
#define WINDOW_HEIGHT 1050


int main()
{
	pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
	pgi::Graphics window(WINDOW_WIDTH, WINDOW_HEIGHT, { BG_BLACK, FG_WHITE }, { BG_ORANGE, FG_BLACK }, FONT_SIZE);

	// ----------- Initialize MessageBox ----------- //
	pgi::MsgBox Dialog("TEST", window);

	// Default themes
	//int value = Dialog.Message(BOX_INFO);
	//int value = Dialog.Message(BOX_WARNING);
	int value = Dialog.Message(BOX_ERROR);

	// Custom theme
	//int value = Dialog.Message({BG_BLUE + FG_BLACK, BG_WHITE + FG_RED, BG_GREEN + FG_RED});
	//int value = Dialog.Message({BG_BLUE + FG_BLACK, BG_WHITE + FG_RED, BG_GREEN + FG_RED, "LMAO"});
	
	if (value)
	{
		pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
		std::cout << value << std::endl;
	}
	else
		return 0;

	_getch();

	return 0;
}