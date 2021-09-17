#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "../sources/Semi-Graphics.h"

#define FONT_SIZE 36
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 820

void A()
{
	pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Yep ";
}

void B()
{
	pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Not that ";
}

void C()
{
	pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n Not that one ";
}

void D()
{
	pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
	std::cout << "\n That a lot more ";
}



// ---------- Child classes ------------ //

class firstParagraph : public pgi::PARAGRAPH
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

class secondParagraph : public pgi::PARAGRAPH
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

class thirdParagraph : public pgi::PARAGRAPH
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

class fourthParagraph : public pgi::PARAGRAPH
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

class fifthParagraph : public pgi::PARAGRAPH
{
public:
	fifthParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		pgi::cls(GetStdHandle(STD_OUTPUT_HANDLE));
		std::cout << "HHMMMMMMMMMMMMMMMMMMMMMMMM\n";
	}
};

int main()
{
	pgi::Graphics window(WINDOW_WIDTH, WINDOW_HEIGHT, FONT_SIZE);

	pgi::Frame frame1(0, 12, WINDOW_WIDTH / (48 / 2) + 14, 6, { '+', NULL, NULL, NULL, '-', '|' });
	pgi::Frame frame2(0, 1, WINDOW_WIDTH / (48 / 2) + 14, 10);

	frame1.SpawnFrame("");
	frame2.SpawnFrame("");

	std::string menuNames[4] = { "1 MENU" , "2 HELP", "3 TEST", "4 EXIT" };
	std::string menuDescriptions[4] = { "Displays this menu message", "Displays help message     ", "Displays message with test", "Shuts down the program    " };

	// ----------- Creating paragraphs objects ------------- //

	firstParagraph* fstPar = new firstParagraph(menuNames[0], menuDescriptions[0]);
	secondParagraph* sndPar = new secondParagraph(menuNames[1], menuDescriptions[1]);
	thirdParagraph* trdPar = new thirdParagraph(menuNames[2], menuDescriptions[2]);
	fourthParagraph* frtPar = new fourthParagraph(menuNames[3], menuDescriptions[3]);

	pgi::PARAGRAPH* objects[4] = { fstPar, sndPar, trdPar, frtPar };

	// ----------- Initialize Menu ----------- //

	pgi::hMenu menu(4, objects, frame1, frame2, window);

	// Creates vertical menu orientation
	menu.SpawnMenu();

	// Removing paragraphs objects to escape memory leak
	delete fstPar, sndPar, trdPar, frtPar, objects;
	SecureZeroMemory(menuNames, sizeof(menuNames));
	SecureZeroMemory(menuDescriptions, sizeof(menuNames));

	_getch();

	return 0;
}