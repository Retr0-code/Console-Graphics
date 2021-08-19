#include "pch.h"
#include "Semi-Graphics.h"

#define FONT_SIZE 42
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

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

class fifthParagraph : public PARAGRAPH
{
public:
	fifthParagraph(std::string _paragraphName, std::string _description) : PARAGRAPH(_paragraphName, _description)
	{
		paragraphName = _paragraphName;
		description = _description;
	}

	void Execute() override
	{
		cls(GetStdHandle(STD_OUTPUT_HANDLE));
		std::cout << "HHMMMMMMMMMMMMMMMMMMMMMMMM\n";
	}
};

int main()
{
	Graphics window(WINDOW_WIDTH, WINDOW_HEIGHT, { BG_BLACK, FG_WHITE }, { BG_ORANGE, FG_BLACK }, FONT_SIZE);

	//window.makeFrame(0, 0, WINDOW_WIDTH / 10 - calculatePercent((WINDOW_WIDTH / 10), 11), WINDOW_HEIGHT / 10 - calculatePercent(WINDOW_HEIGHT / 10, 80) );
	Frame frame(0, 0, (WINDOW_WIDTH / FONT_SIZE) * 2 - 2, WINDOW_HEIGHT / (FONT_SIZE * 2) - 2);
	frame.spawnFrame();

	std::string menuNames[5] = { "1 MENU" , "2 HELP", "3 TEST", "4 EXIT", "5 HMMM" };
	std::string menuDescriptions[5] = { "Displays this menu message", "Displays help message     ", "Displays message with test", "Shuts down the program    ", "                         " };

	// ----------- Creating paragraphs objects ------------- //

	firstParagraph* fstPar = new firstParagraph(menuNames[0], menuDescriptions[0]);
	secondParagraph* sndPar = new secondParagraph(menuNames[1], menuDescriptions[1]);
	thirdParagraph* trdPar = new thirdParagraph(menuNames[2], menuDescriptions[2]);
	fourthParagraph* frtPar = new fourthParagraph(menuNames[3], menuDescriptions[3]);
	fifthParagraph* ftfPar = new fifthParagraph(menuNames[4], menuDescriptions[4]);

	PARAGRAPH* objects[5] = { fstPar, sndPar, trdPar, frtPar, ftfPar };

	// ----------- Initialize Menu ----------- //

	//Menu menu(4, 5, 20, objects, window, frame);
	Menu menu(5, objects, window, frame);

	// Creates vertical menu orientation
	menu.horizontal();
	//menu.vertical();


	// Removing paragraphs objects to escape memory leak
	delete fstPar, sndPar, trdPar, frtPar, ftfPar, objects;
	SecureZeroMemory(menuNames, 4);
	SecureZeroMemory(menuDescriptions, 4);

	system("pause");

	return 0;
}