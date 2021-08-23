#pragma once
#include "colors.h"

#include <string>
#include <conio.h>
#include <iostream>
#include <windows.h>


/** \struct frameSegments
 *  \brief This structure used to pass segments of a frame as arguments (leftTopCorner, rightTopCorner, leftDownCorner, rightDownCorner, horizontal, vertical).
 *  \var frameSegments::leftTopCorner
 *  Field 'leftTopCorner' contains segment of left top corner. If you use only one corner segment, you can supply only this field and other would be filled later.
 *  \var frameSegments::rightTopCorner
 *  Field 'rightTopCorner' contains segment of right top corner.
 *	\var frameSegments::leftDownCorner
 *  Field 'leftDownCorner' contains segment of left down corner.
 *	\var frameSegments::rightDownCorner
 *  Field 'rightDownCorner' contains segment of right down corner.
 *	\var frameSegments::horizontal
 *	Field 'rightDownCorner' contains segment of horizontal segment.
 *	\var frameSegments::vertical
 *	Field 'rightDownCorner' contains segment of vertical segment.
 */
typedef struct
{
	char leftTopCorner;
	char rightTopCorner;
	char leftDownCorner;
	char rightDownCorner;
	char horizontal;
	char vertical;
} frameSegments;

/** \struct color
 *	\brief This structure contains background and frontground colors (frontground color, background color).
 *	\var color::frontground
 *	Field 'frontground' contains integer value of frontground color
 *	\var color::background
 *	Field 'background' contains integer value of frontground color
 */
typedef struct
{
	int frontground;
	int background;
} color;

/** \struct MSG_BOX_TYPE
 *	\brief This structure defines properties of dialog box (selection color, deselection color, background color).
 *	\var MSG_BOX_TYPE::selectColor
 *	Field 'selectColor' contains integer value of selection color
 *	\var MSG_BOX_TYPE::deselectColor
 *	Field 'deselectColor' contains integer value of deselection color
 *	\var MSG_BOX_TYPE::backgroundColor
 *	Field 'backgroundColor' contains integer value of background color of dialog box
 */
typedef struct
{
	int selectColor;
	int deselectColor;
	int backgroundColor;
} MSG_BOX_TYPE;


/** \def BOX_INFO
 *	Defines dialog box type as information box
 *	(selection color black on white, deselection color white on black, dialog box color white on azure)
 */
#define BOX_INFO { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_AZURE + FG_WHITE }

/** \def BOX_ERROR
 *	Defines dialog box type as information box
 *	(selection color black on white, deselection color white on black, dialog box color black on red)
 */
#define BOX_ERROR { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_RED + FG_BLACK }

/** \def BOX_WARNING
 *	Defines dialog box type as information box
 *	(selection color black on white, deselection color white on black, dialog box color black on orange)
 */
#define BOX_WARNING { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_ORANGE + FG_BLACK }


/** \fn cls(HANDLE hConsole)
 *	\brief This function clears the screen
 *
 *	\param hConsole		Gets handle of console
 *
 *	\example clear cls(GetStdHandle(STD_OUTPUT_HANDLE));
 */
void cls(HANDLE hConsole);


/** \class PARAGRAPH
 *	\brief The parent class for defining a menu paragraphs
 *	
 *	\details This class is this class is used to create custom menu items and paragraphs. Accordingly, the user must create a class that inherits from this class and override the 'Execute' method.
 *	\var PARAGRAPH::paragraphName
 *	Field 'paragraphName' contains name of point in menu
 *	\var PARAGRAPH::description
 *	Field 'description' contains description of menu point (paragraph)
 */
class PARAGRAPH
{
public:
	std::string paragraphName;
	std::string description;


	/** Construcor of PARAGRAPH
	 *	\brief Sets name and description of paragraphs
	 *
	 *	\details Each inherited class must contains constructor that sets fields in parent class.
	 */
	PARAGRAPH(std::string paragraphName, std::string description)
	{
		paragraphName = this->paragraphName;
		description = this->description;
	}

	/**
	 *	Virtual method Execute must be overrided in heired class
	 */
	virtual void Execute() = 0;
};

/** \class Graphics
 *	\brief Parent class of all graphical elements.
 *	
 *	\details Class 'Graphics' contains parameters for graphical elements as menus, dialog boxes and frames.
 */
class Graphics
{
protected:
	/** \fn setTextProperties(int color, int _fontSize = 48)
	 *	\brief This method changes color and font size
	 *	
	 *	\param color		Gets integer value of color
	 *	\param _fontSize	Gets integer value of font size
	 */
	void setTextProperties(int color, int _fontSize = 48);

	/** \fn setCursor(int x, int y)
	 *	\brief This method moves cursor to supplied coordinates.
	 *
	 *	\param x	Integer value of coordinate on X axis.
	 *	\param y	Integer value of coordinate on Y axis.
	 */
	void setCursor(int x, int y);

	/** \fn calculatePosition(std::string list[], int size)
	 *	\brief This method calculates center of screen for proper menu displaying.
	 *
	 *	\details Method gets on input massive of paragraphs' names and size of massive and return length of the biggest name.
	 *
	 *	\param list[]	Gets massive of names.
	 *	\param size		Gets size of massive.
	 *
	 *	\return Length of the biggest name.
	 */
	int calculatePosition(std::string list[], int size);

	/** \fn Graphics()
	 *	\brief This is default constructor of class 'Graphics' that cannot be reached from outside.
	 */
	Graphics() = default;

public:
	int fontSize = 48;			//!< By default font size is 48, you can change it in constructor while creating an object.
	int windowWidth = 1920;		//!< By default window width is 1920, you can change it in constructor while creating an object.
	int windowHeight = 1080;	//!< By default window height is 1080, you can change it in constructor while creating an object.
	int defaultColors = BG_BLACK + FG_WHITE;		//!< Default color is white text on black background, you can change it in constructor while creating an object.
	int secondaryColors = BG_BLUE + FG_BLACK;		//!< Secondary color is black text on blue background, you can change it in constructor while creating an object.


	/** \fn Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize)
	 *	\brief Public constructor of 'Graphics' class with the biggest amount of options.
	 *
	 *	\details Public constructor of 'Graphics' class with the biggest amount of options. Sets default window size with custom colors and font size
	 *
	 *	\param resolutionX		Width of the window.
	 *	\param resolutionY		Height of the window.
	 *	\param _defaultColor	Gets color structure for defaultColors.
	 *	\param _secondaryColor	Gets color structure for secondaryColors.
	 *	\param _fontSize		Gets integer value for fontSize.
	 *	
	 *	\exmample Graphics window(1920, 1080, { BG_BLACK, FG_WHITE }, { BG_ORANGE, FG_BLACK }, 48);
	 */
	Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize);

	/** \fn Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize)
	 *	\brief Public constructor of 'Graphics' class without setting colors ability.
	 *
	 *	\details Public constructor of 'Graphics' class without setting colors ability. Sets default window size and font size
	 *	\param resolutionX		Width of the window.
	 *	\param resolutionY		Height of the window.
	 *	\param _fontSize		Gets integer value for fontSize.
	 *
	 *	\exmample Graphics window(1920, 1080, 48);
	 */
	Graphics(int resolutionX, int resolutionY, int _fontSize);
};


/** \class Frame
 *	\brief This class is used for creating frames.
 *
 *	\details This class is used for creating frames. Frames are fields on console that can be used as decoration or as window.
 */
class Frame : protected Graphics
{
public:

	/** \fn Frame()
	 *	\brief Default construcor of the 'Frame' class, user must not use it, because it is used for other classes and not for user's purposes.
	 */
	Frame() = default;

	frameSegments segments = { (char)201, (char)187, (char)200, (char)188, (char)205, (char)186 };		//!< Segments of a frame is double line chars.
	int originX = 0;		//!< Coordinate on X axis of a frame origin (beginning)
	int originY = 0;		//!< Coordinate on Y axis of a frame origin (beginning)
	int Width;			//!< Width of a frame
	int Height;			//!< Height of a frame

	/** \fn Frame(int _originX, int _originY, int _Width, int _Height, frameSegments _segments)
	 *	\brief In this constructor user can supply own chars as frame segments.
	 *
	 *	\details In this constructor user can supply own chars as frame segments. Frame segments can be passed as argument as 'frameSegments' structure.
	 *
	 *	\param _originX		Gets integer value of X axis coordinate.
	 *	\param _originY		Gets integer value of Y axis coordinate.
	 *	\param _Width		Gets integer value of frame width.
	 *	\param _Height		Gets integer value of frame haight.
	 *	\param _segments	Gets 'frameSegments' structure of chars.
	 *
	 *	\example CustomFrame Frame frame(0, 0, 10, 1080 / 48 - 4, { '+', NULL, NULL, NULL, '-', '|' });
	 */
	Frame(int _originX, int _originY, int _Width, int _Height, frameSegments _segments);

	/** \fn Frame(int _originX, int _originY, int _Width, int _Height)
	 *	\brief In this constructor user cannot supply own chars as frame segments.
	 *
	 *	\param _originX		Gets integer value of X axis coordinate.
	 *	\param _originY		Gets integer value of Y axis coordinate.
	 *	\param _Width		Gets integer value of frame width.
	 *	\param _Height		Gets integer value of frame haight.
	 *
	 *	\example NonCustomFrame Frame frame(0, 0, 10, 1080 / 48 - 4);
	 */
	Frame(int _originX, int _originY, int _Width, int _Height);
	
	/** \fn spawnFrame()
	 *	\brief This function spawns frame by using parameters that was passed in constructor.
	 */
	void spawnFrame();
};


/** \class Menu
 *	\brief This class is used to spawn different kinds of menus (vertical, horizontal, checkbox)
 */
class Menu : protected Frame
{
private:
	int X;			//!< Contains menu origin coordiante on X axis.
	int Y;			//!< Contains menu origin coordiante on Y axis.
	int size;		//!< Contains amount of menu points (paragraphs).
	int fontSize;	//!< Font size of menu text.
	PARAGRAPH** menuObject = new PARAGRAPH*[size];		//!< Contains elements of menu.
	Frame descriptionField;								//!< Contains frame where desription of paragraphs will be displayed.

public:

	/** \fn Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
	 *	\brief This constructor creates menu in position that user passed in '_X' and '_Y' arguments.
	 *
	 *	\param _size				Gets integer value size of menu (amount of points).
	 *	\param _X					Gets integer value of X axis coordinate.
	 *	\param _Y					Gets integer value of Y axis coordinate.
	 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
	 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
	 *	\param _descriptionField	Contains Frame object where description will be displayed.
	 */
	Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField);

	/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
	 *	\brief This constructor creates menu in center of window.
	 *
	 *	\param _size				Gets integer value size of menu (amount of points).
	 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
	 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
	 *	\param _descriptionField	Contains Frame object where description will be displayed.
	 */
	Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField);

	/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField)
	 *	\brief This constructor creates menu in center of Frame.
	 *
	 *	\param _size				Gets integer value size of menu (amount of points).
	 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
	 *	\param _Frame				Contains Frame object where menu will be spawned.
	 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
	 *	\param _descriptionField	Contains Frame object where description will be displayed.
	 */
	Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField);


	/** \fn vertical(BOOL onlyDraw = FALSE)
	 *	\brief Spawns vertical menu with properties that was supplied in constructor.
	 *
	 *	\param onlyDraw		Gets boolean value which sets flag to only draw menu.
	 *	\return				TRUE if pressed TAB, and FALSE if pressed BACK or flag 'onlyDraw' is TRUE.
	 */
	BOOL vertical(BOOL onlyDraw = FALSE);

	/** \fn horizontal(BOOL onlyDraw = FALSE)
	 *	\brief Spawns horizontal menu with properties that was supplied in constructor.
	 *
	 *	\param onlyDraw		Gets boolean value which sets flag to only draw menu.
	 *	\return				TRUE if pressed TAB, and FALSE if pressed BACK or flag 'onlyDraw' is TRUE.
	 */
	BOOL horizontal(BOOL onlyDraw = FALSE);

	/** \fn checkBox()
	 *	\brief Spawns vertical menu where user can choose multiple options with properties that was supplied in constructor.
	 *
	 *	\return Massive of objects that was chosen.
	 */
	PARAGRAPH** checkBox();

	/** \fn switchMenu(Menu* meun1, Menu* meun2, BOOL(Menu::*abstractMenu1)(BOOL onlyDraw), BOOL(Menu::*abstractMenu2)(BOOL onlyDraw))
	 *	\brief Spawns two menus by supplied objects and methods.
	 *
	 *	\param menu1			Gets pointer to first Menu object.
	 *	\param menu2			Gets pointer to second Menu object.
	 *	\param *abstractMenu1	Gets pointer to method for spawning first menu.
	 *	\param *abstractMenu2	Gets pointer to method for spawning second menu.
	 *
	 *	\example switchMenu menu.switchMenu(menu1, menu2, &Menu::vertical, &Menu::horizontal);
	 */
	void switchMenu(Menu* menu1, Menu* menu2, BOOL(Menu::*abstractMenu1)(BOOL onlyDraw), BOOL(Menu::*abstractMenu2)(BOOL onlyDraw));

private:
	Menu() = default;

	/** \fn DrawDescription(std::string text)
	 *	\brief This method displays description for element of menu. (is inaccessacle from outside the class)
	 *
	 *	\param text		Gets string that will be displayed in frame.
	 */
	void DrawDescription(std::string text);
};

/** \class MsgBox
 *	\brief This class is used for creating dialog boxes.
 */
class MsgBox : protected Graphics
{
protected:
	std::string description;	//!< Contains text that will be displayed in dialog box.
	int lfontSize;			//!< Contains font size.
	int width;			//!< Contains width of dialog box.
	int height;			//!< Contains height of dialog box.

public:

	/** \fn MsgBox(std::string _description, Graphics _Graphics)
	 *	\brief Constructor that sets basic properties of dialog box (description, font size, width, height)
	 *
	 *	\param _description		Gets description that will be displayed in dialog box.
	 *	\param _Graphics		Gets Graphics object to get basic settings.
	 */
	MsgBox(std::string _description, Graphics _Graphics)
	{
		description = _description;
		lfontSize = _Graphics.fontSize;
		width = _Graphics.windowWidth;
		height = _Graphics.windowHeight;
	}

	/** \fn Message(MSG_BOX_TYPE container)
	 *	\brief This method displays dialog (message) box.
	 *
	 *	\param container	Gets color which will be used in dialog box.
	 *
	 *	\return TRUE as OK and FALSE as CANCEL.
	 *
	 *	\example DialogBox1 Dialog.Message({BG_BLUE + FG_BLACK, BG_WHITE + FG_RED, BG_GREEN + FG_RED});
	 *	\example DialogBox2 Dialog.Message(BOX_INFO);
	 */
	BOOL Message(MSG_BOX_TYPE container);
};