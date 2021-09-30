#pragma once

#include "setup.h"


namespace pgi
{
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
		PARAGRAPH(std::string paragraphName, std::string description);

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
		/** \fn SetTextProperties(int color, int _fontSize = 48)
		 *	\brief This method changes color and font size
		 *
		 *	\param color		Gets integer value of color
		 *	\param _fontSize	Gets integer value of font size
		 */
		void SetTextProperties(int color, int _fontSize = 48);

		/** \fn SetCursorPosition(int x, int y)
		 *	\brief This method moves cursor to supplied coordinates.
		 *
		 *	\param x	Integer value of coordinate on X axis.
		 *	\param y	Integer value of coordinate on Y axis.
		 */
		void SetCursorPosition(int x, int y);

		/** \fn CalculateMaxLength(std::string list[], int size)
		 *	\brief This method calculates center of screen for proper menu displaying.
		 *
		 *	\details Method gets on input massive of paragraphs' names and size of massive and return length of the biggest name.
		 *
		 *	\param list[]	Gets massive of names.
		 *	\param size		Gets size of massive.
		 *
		 *	\return Length of the biggest name.
		 */
		int CalculateMaxLength(std::string list[], int size);

		/** \fn Graphics()
		 *	\brief This is default constructor of class 'Graphics' that cannot be reached from outside.
		 */
		Graphics() = default;


		int* FillColorSet(int color, int size);


		std::string* MaskDescriptions(std::string descriptions[], int size);

		bool GetKeyState(KEY_EVENT_RECORD key);

	public:
		int fontSize = 48;			//!< By default font size is 48, you can change it in constructor while creating an object.
		int windowWidth = 1920;		//!< By default window width is 1920, you can change it in constructor while creating an object.
		int windowHeight = 1080;	//!< By default window height is 1080, you can change it in constructor while creating an object.
		int defaultColors = BG_BLACK + FG_WHITE;		//!< Default color is white text on black background, you can change it in constructor while creating an object.
		int secondaryColors = BG_BLUE + FG_BLACK;		//!< Secondary color is black text on blue background, you can change it in constructor while creating an object.
		bool enableMouse = false;

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
		 *	\example DefineWindowsProperties1 Graphics window(1920, 1080, { BG_BLACK, FG_WHITE }, { BG_ORANGE, FG_BLACK }, 48);
		 */
		Graphics(int resolutionX, int resolutionY, color _defaultColor, color _secondaryColor, int _fontSize);

		/** \fn Graphics(int resolutionX, int resolutionY, int _fontSize)
		 *	\brief Public constructor of 'Graphics' class without setting colors ability.
		 *
		 *	\details Public constructor of 'Graphics' class without setting colors ability. Sets default window size and font size
		 *	\param resolutionX		Width of the window.
		 *	\param resolutionY		Height of the window.
		 *	\param _fontSize		Gets integer value for fontSize.
		 *
		 *	\example DefineWindowsProperties2 Graphics window(1920, 1080, 48);
		 */
		Graphics(int resolutionX, int resolutionY, int _fontSize);

		coordinates GetMousePosition();
	};


	class Line : protected Graphics
	{
	public:
		Line(int X, int Y, int _lineLength, char _lineSegment);

		virtual void DrawLine() = 0;

	protected:
		int lineLength;
		int lineStartX, lineStartY;
		char lineSegment;
	};

	class vLine : protected Line
	{
	public:
		vLine(int X, int Y, int _lineLength, char _lineSegment) : Line(X, Y, _lineLength, _lineSegment) {}

		void DrawLine() override;
	};

	class hLine : protected Line
	{
	public:
		hLine(int X, int Y, int _lineLength, char _lineSegment) : Line(X, Y, _lineLength, _lineSegment) {}

		void DrawLine() override;
	};


	/** \class Frame
	 *	\brief This class is used for creating frames.
	 *
	 *	\details This class is used for creating frames. Frames are fields on console that can be used as decoration or as window.
	 */
	class Frame : protected Graphics
	{
	protected:

		frameSegments segments = { (char)201, (char)187, (char)200, (char)188, (char)205, (char)186, (char)185, (char)204 };		//!< Segments of a frame is double line chars.
		int originX = 0;		//!< Coordinate on X axis of a frame origin (beginning)
		int originY = 0;		//!< Coordinate on Y axis of a frame origin (beginning)
		int Width;			//!< Width of a frame
		int Height;			//!< Height of a frame

	public:
		/** \fn Frame()
		 *	\brief Default construcor of the 'Frame' class, user must not use it, because it is used for other classes and not for user's purposes.
		 */
		Frame() = default;

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

		/** \fn SpawnFrame()
		 *	\brief This function spawns frame by using parameters that was passed in constructor.
		 *
		 *	\param frameHeader	Gets text that will be displayed on the top of frame.
		 */
		void SpawnFrame(std::string frameHeader);

		int GetWidth();

		int GetHeight();

		int GetOriginX();

		int GetOriginY();
	};


	/** \class Menu
	 *	\brief This is an inteface (abstract) class for all menus
	 */
	class Menu : protected Graphics
	{
	protected:
		int size;		//!< Contains amount of menu points (paragraphs).
		int fontSize;	//!< Font size of menu text.
		coordinates position;								//!< Structure that contains origin coordinates of a menu
		PARAGRAPH** menuObject;								//!< Contains elements of menu.
		Frame descriptionField;								//!< Contains frame where desription of paragraphs will be displayed.
		std::string* descriptions;
		bool menuEnableMouse;


		Menu() = default;

		/** \fn Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in position that user passed in '_X' and '_Y' arguments.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _X					Gets integer value of menu origin on X axis coordinate.
		 *	\param _Y					Gets integer value of menu origin on Y axis coordinate.
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu::MenuLoop(int switchKey1, int switchKey2, char conditionKey, int colorSet[])
		 *	\brief This main logical function of any menu.
		 *
		 *	\param switchKey1		Gets integer value of key for moving cursor up or left.
		 *	\param switchKey2		Gets integer value of key for moving cursor down or right.
		 *	\param conditionKey		Key that will be flag for starting additional function.
		 *	\param colorSet[]		Array of integer values from which menu objects will be drawn.
		 *
		 *	\return State of menu from enumeration in setup.h.
		 */
		int MenuLoop(int switchKey1, int switchKey2, int conditionKey, int colorSet[]);

		/** \fn Menu::DrawDescription(std::string text)
		 *	\brief This method displays description for element of menu. (is inaccessacle from outside the class)
		 *
		 *	\param text		Gets string that will be displayed in frame.
		 */
		void DrawDescription(std::string text);


		/** \fn Menu::DrawMenu(int _ColorSet[])
		 *	\brief Abstract function for drawing menu.
		 *
		 *	\param colorSet[]		Array of integer values from which menu objects will be drawn.
		 */
		virtual void DrawMenu(int _ColorSet[]) = 0;


		/** \fn Menu::Condition(int counter, int colorSet[])
		 *	\brief Abstract function that executes additional instructions such as check boxes or submenu.
		 *	
		 *	\param counter			Gets integer value of cursor position in menu.
		 *	\param colorSet[]		Array of integer values from which menu objects will be drawn.
		 */
		virtual bool Condition(int counter, int colorSet[]) = 0;


		virtual int MouseCondition(coordinates _mousePosition) = 0;

		virtual coordinates CalculatePositionInFrame(int frameWidth, int frameHeight);

		virtual coordinates CalculateWindowCenter(int windowWidth, int windowHeight, std::string objNames[]);

	public:

		/** \fn Menu::SpawnMenu(bool onlyDraw = false)
		 *	\brief Main abstract function of creating a menu.
		 *
		 *	\param onlyDraw		Gets boolean value for drawing menu. If the value would be true menu will only be renderd and if the value would be false menu will work as shoud to be.
		 *	\return			State of menu from enumeration in setup.h.
		 */
		virtual int SpawnMenu(bool onlyDraw = false) = 0;
	};

	/** \class vMenu
	 *	\brief Class for creating object of a vertical menu.
	 */
	class vMenu : public Menu
	{
	public:
		/** \fn Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in position that user passed in '_X' and '_Y' arguments.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _X					Gets integer value of menu origin on X axis coordinate.
		 *	\param _Y					Gets integer value of menu origin on Y axis coordinate.
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		vMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in center of window.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		vMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn vMenu::vMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in center of Frame.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Frame				Contains Frame object where menu will be spawned.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		vMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics);

		/** \fn vMenu::SpawnMenu(bool onlyDraw = false)
		 *	\brief Main function of creating a vertical menu.
		 *
		 *	\param onlyDraw		Gets boolean value for drawing menu. If the value would be true menu will only be renderd and if the value would be false menu will work as shoud to be.
		 *	\return			State of menu from enumeration in setup.h.
		 */
		int SpawnMenu(bool onlyDraw = false);

	protected:
		/** \fn vMenu::Condition(int counter, int colorSet[])
		 *	\brief Default vertical menu have not got any aditional functionality.
		 */
		virtual bool Condition(int counter, int colorSet[]) override { return false; }

		/** \fn vMenu::DrawMenu(int _ColorSet[])
		 *	\brief Function for drawing vertical menu.
		 *
		 *	\param colorSet[]		Array of integer values from which menu objects will be drawn.
		 */
		void DrawMenu(int _ColorSet[]) override;

		int MouseCondition(coordinates _mousePosition) override;
	};

	/** \class hMenu
	 *	\brief Class for creating object of a horizontal menu.
	 */
	class hMenu : public Menu
	{
	public:
		/** \fn Menu::Menu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in position that user passed in '_X' and '_Y' arguments.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _X					Gets integer value of menu origin on X axis coordinate.
		 *	\param _Y					Gets integer value of menu origin on Y axis coordinate.
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 */
		hMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in center of window.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 */
		hMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn hMenu::hMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics)
		 *	\brief This constructor creates menu in center of Frame.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Frame				Contains Frame object where menu will be spawned.
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 */
		hMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics);

		/** \fn hMenu::SpawnMenu(BOOL onlyDraw = FALSE)
		 *	\brief Spawns Horizontal menu with properties that was supplied in constructor.
		 *
		 *	\param onlyDraw		Gets boolean value which sets flag to only draw menu.
		 *	\return				TRUE if pressed TAB, and FALSE if pressed BACK or flag 'onlyDraw' is TRUE.
		 */
		int SpawnMenu(bool onlyDraw = false);

	private:

		/** \fn vMenu::Condition(int counter, int colorSet[])
		 *	\brief Default horizontal menu have not got any aditional functionality.
		 */
		bool Condition(int counter, int colorSet[]) override { return false; }

		int MouseCondition(coordinates _mousePosition) override;

		/** \fn vMenu::DrawMenu(int _ColorSet[])
		 *	\brief Function for drawing horizontal menu.
		 *
		 *	\param colorSet[]		Array of integer values from which menu objects will be drawn.
		 */
		void DrawMenu(int _ColorSet[]) override;

		coordinates CalculatePositionInFrame(int frameWidth, int frameHeight) override;

		coordinates CalculateWindowCenter(int windowWidth, int windowHeight, std::string objNames[]) override;
	};


	class cMenu : protected vMenu
	{
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
		cMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of window.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		cMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of Frame.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Frame				Contains Frame object where menu will be spawned.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		cMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics);

		/** \fn cMenu::SpawnMenu()
		 *	\brief Spawns vertical menu where user can choose multiple options with properties that was supplied in constructor.
		 *
		 *	\return Massive of objects that was chosen.
		 */
		PARAGRAPH** SpawnMenu();

	private:
		PARAGRAPH** selectedPoints;

		bool Condition(int counter, int colorSet[]) override;
	};


	class sMenu : protected vMenu
	{
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
		sMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of window.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		sMenu(int _size, PARAGRAPH* _menuObject[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of Frame.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Frame				Contains Frame object where menu will be spawned.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		sMenu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Frame _descriptionField, Graphics _Graphics);

		/** \fn SwitchMenu(Menu* meun1, Menu* meun2, BOOL(Menu::*abstractMenu1)(BOOL onlyDraw), BOOL(Menu::*abstractMenu2)(BOOL onlyDraw))
	 *	\brief Spawns two menus by supplied objects and methods.
	 *
	 *	\param menu1			Gets pointer to first Menu object.
	 *	\param menu2			Gets pointer to second Menu object.
	 *	\param *abstractMenu1	Gets pointer to method for spawning first menu.
	 *	\param *abstractMenu2	Gets pointer to method for spawning second menu.
	 *
	 *	\example SwitchMenu menu.SwitchMenu(menu1, menu2, &Menu::Vertical, &Menu::Horizontal);
	 */
		int SpawnMenu(Menu* menu1, Menu* menu2);

	private:
		bool Condition(int counter, int colorSet[]) override { return false; }
	};


	class dMenu : protected Menu
	{
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
		dMenu(int _size, int _X, int _Y, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of window.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		dMenu(int _size, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _descriptionField, Graphics _Graphics);

		/** \fn Menu(int _size, PARAGRAPH* _menuObject[], Frame _Frame, Graphics _Graphics, Frame _descriptionField)
		 *	\brief This constructor creates menu in center of Frame.
		 *
		 *	\param _size				Gets integer value size of menu (amount of points).
		 *	\param _menuObject[]		Contains PARAGRAPH* objects of menu.
		 *	\param _Frame				Contains Frame object where menu will be spawned.
		 *	\param _Graphics			Contains Graphics object with basic parameters (font size, font colors, window size).
		 *	\param _descriptionField	Contains Frame object where description will be displayed.
		 */
		dMenu(int _size, PARAGRAPH* _menuObject[], vMenu* _paragraphs[], Frame _Frame, Frame _descriptionField, Graphics _Graphics);

		int SpawnMenu(bool onlyDraw = false) override;

	private:
		vMenu** paragraphs;
		std::string space;

		bool Condition(int counter, int colorSet[]) override;

		int MouseCondition(coordinates _mousePosition) override;

		void DrawMenu(int _ColorSet[]);
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
		MsgBox(std::string _description, Graphics _Graphics);

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
}