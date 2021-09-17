#include <conio.h>
#include <iostream>
#include <Windows.h>


#include "../sources/Semi-Graphics.h"

#define FONT_SIZE 36
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


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
		D();
	}
};

int main()
{
	pgi::Graphics window(WINDOW_WIDTH, WINDOW_HEIGHT, { BG_BLACK, FG_WHITE }, { BG_ORANGE, FG_BLACK }, FONT_SIZE);

	//window.makeFrame(0, 0, WINDOW_WIDTH / 10 - calculatePercent((WINDOW_WIDTH / 10), 11), WINDOW_HEIGHT / 10 - calculatePercent(WINDOW_HEIGHT / 10, 80) );
	pgi::Frame frame(0, 1, (WINDOW_WIDTH / FONT_SIZE) * 2 - 3, WINDOW_HEIGHT / (FONT_SIZE * 2) - 2);
	frame.SpawnFrame("");

	std::string menuNames[5] = { "1 MENU" , "2 HELP", "3 TEST", "4 EXIT", "5 HMMM" };
	std::string menuDescriptions[5] = { "Displays this menu message", "Displays help message     ", "Displays message with test", "Shuts down the program    ", "                         " };

	// ----------- Creating paragraphs objects ------------- //

	firstParagraph* fstPar = new firstParagraph(menuNames[0], menuDescriptions[0]);
	secondParagraph* sndPar = new secondParagraph(menuNames[1], menuDescriptions[1]);
	thirdParagraph* trdPar = new thirdParagraph(menuNames[2], menuDescriptions[2]);
	fourthParagraph* frtPar = new fourthParagraph(menuNames[3], menuDescriptions[3]);
	fifthParagraph* ftfPar = new fifthParagraph(menuNames[4], menuDescriptions[4]);

	pgi::PARAGRAPH* objects[5] = { fstPar, sndPar, trdPar, frtPar, ftfPar };

	// ----------- Initialize Menu ----------- //

	//Menu menu(4, 5, 20, objects, window, frame);
	pgi::hMenu menu(5, objects, frame, window);

	// Creates horizontal menu orientation
	menu.SpawnMenu();


	// Removing paragraphs objects to escape memory leak
	delete fstPar, sndPar, trdPar, frtPar, ftfPar, objects;
	SecureZeroMemory(menuNames, sizeof(menuNames));
	SecureZeroMemory(menuDescriptions, sizeof(menuNames));

	_getch();

	return 0;
}