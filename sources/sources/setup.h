#pragma once

#define FG_BLACK	0
#define FG_BLUE		1
#define FG_GREEN	2
#define FG_lBLUE	3
#define FG_RED		4
#define FG_PURPLE	5
#define FG_ORANGE	6
#define FG_lGREY	7
#define FG_GREY		8
#define FG_AZURE	9
#define FG_LIME		10
#define FG_CYAN		11
#define FG_PINK		12
#define FG_VIOLET	13
#define FG_YELLOW	14
#define FG_WHITE	15

#define BG_BLACK	0
#define BG_BLUE		16
#define BG_GREEN	32
#define BG_lBLUE	48
#define BG_RED		64
#define BG_PURPLE	80
#define BG_ORANGE	96
#define BG_lGREY	112
#define BG_GREY		128
#define BG_AZURE	144
#define BG_LIME		160
#define BG_CYAN		176
#define BG_PINK		192
#define BG_VIOLET	208
#define BG_YELLOW	224
#define BG_WHITE	240

enum MenuReturnValues : int
{
	MENU_DONE = -1,
	MENU_SWITCH = 0,
	MENU_EXIT = 1
};

enum keys
{
	ARROW_UP = 72,
	ARROW_DOWN = 80,
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77,
	SPACE = ' ',
	ENTER = '\r',
	BACKSPACE = '\b',
	TAB	= '\t'
};


/** \struct frameSegments
 *  \brief This structure used to pass segments of a frame as arguments (leftTopCorner, rightTopCorner, leftDownCorner, rightDownCorner, Horizontal, Vertical).
 *  \var frameSegments::leftTopCorner
 *  Field 'leftTopCorner' contains segment of left top corner. If you use only one corner segment, you can supply only this field and other would be filled later.
 *  \var frameSegments::rightTopCorner
 *  Field 'rightTopCorner' contains segment of right top corner.
 *	\var frameSegments::leftDownCorner
 *  Field 'leftDownCorner' contains segment of left down corner.
 *	\var frameSegments::rightDownCorner
 *  Field 'rightDownCorner' contains segment of right down corner.
 *	\var frameSegments::Horizontal
 *	Field 'rightDownCorner' contains segment of Horizontal segment.
 *	\var frameSegments::Vertical
 *	Field 'rightDownCorner' contains segment of Vertical segment.
 *	\var frameSegments::leftStop
 *	Field 'leftStop' contains plug char for the left side.
 *	\var frameSegments::rightStop
 *	Field 'rightStop' contains plug char for the rigth side (between left and rigth plugs will be displayed header of frame).
 */
typedef struct
{
	char leftTopCorner;
	char rightTopCorner;
	char leftDownCorner;
	char rightDownCorner;
	char Horizontal;
	char Vertical;
	char leftStop;
	char rightStop;
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
	std::string boxHeader;
} MSG_BOX_TYPE;


/** \def BOX_INFO
 *	Defines dialog box type as information box
 *	(selection color black on white, deselection color white on black, dialog box color white on azure)
 */
#define BOX_INFO { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_AZURE + FG_WHITE, "INFO" }

 /** \def BOX_ERROR
  *	Defines dialog box type as information box
  *	(selection color black on white, deselection color white on black, dialog box color black on red)
  */
#define BOX_ERROR { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_RED + FG_BLACK, "ERROR" }

  /** \def BOX_WARNING
   *	Defines dialog box type as information box
   *	(selection color black on white, deselection color white on black, dialog box color black on orange)
   */
#define BOX_WARNING { BG_WHITE + FG_BLACK, BG_BLACK + FG_WHITE, BG_ORANGE + FG_BLACK, "WARNING" }

