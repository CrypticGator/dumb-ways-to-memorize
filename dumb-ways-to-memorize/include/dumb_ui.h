#ifndef __DUMB_UI
#define __DUMB_UI

#include "globals.h"
#include "graphics.h"

typedef struct element_s element_t;
typedef struct window_s window_t;

//Hard-coding some shit
#define	MENU_ITEM_MAX	20
#define MAX_MENUS		10
#define MENU_BACKGROUND "Background"
#define MENU_ITEMS		"Items"
#define MENU_ITEM_SPRITE "sprite"
#define MENU_ITEM_TEXT	"text"
#define MENU_ITEM_LINK	"link"
#define MENU_ITEM_EXTRA "extra"
#define MENU_TYPE		"Type"
#define MENU_TYPE_STR_POWER	"power_select"
#define MENU_TYPE_STR_CHOOSE "choose_power"
#define MENU_TYPE_STR_H		"horizontal"
#define MENU_TYPE_STR_V		"vertical"
#define MENU_TYPE_STR_GRID	"grid"

#define MENU_EXTRA_LOAD_LEVEL	"Load Level"

#define UI_PLAYER_STATUS "UI_Lives"

/**
 * An element of the UI for the game.
 *
 * @author	Anthony Rios
 * @date	4/27/2016
 */

struct element_s
{
	menu_item_state_t mState;
	ui_type_t mType;
	area_t mPosition;   /**< The position/size of the element on a percentage of the area its assigned to */
	sprite_t *mSprite;
	void *mData;	/**< The data necessary to use this element.
					 *	This is based on type what will be there.
					 *	If the type is panel : entity list with NULL end is expected.
					 *  Label : char* to text
					 *  Button : func* to a more specific function
					 *  Image : none
					 */
	char *mName;

	void (*Draw)(element_t *self);
	void (*Think)(element_t *self);
};

struct window_s
{
	window_t *mParent;
	area_t mPosition;   /**< The position/size of the window in percentage of parents position */
	element_t *elements;
};

enum
{
	MENU_START,
	MENU_GUESS,
	MENU_CHOOSE
};

/** Defines the enum for what type of menu it is */
typedef enum
{
	MENU_TYPE_NULL = 0x0,
	MENU_TYPE_H = 0x1,		/**<  menu type - horizontal */
	MENU_TYPE_V = 0x2,		/**<  menu type - vertical */
	MENU_TYPE_GRID = 0x4,   /**<  menu type - grid */
	MENU_TYPE_POWER = 0x8,  /**<  menu type - half circle for power selection*/
	MENU_TYPE_CHOOSE = 0x10,	/**<  menu - same as power, but used to differ the menu operations */
	MENU_TYPE_MAX = 0x20

}menu_type_t;


typedef struct menu_item_s menu_item_t;
typedef struct menu_s menu_t;

/**
 * A menu item structure, used to define the items in the menu.
 *
 * @author	Anthony Rios
 * @date	3/30/2016
 */

struct menu_item_s
{
	menu_item_state_t	State;		/**< The state of the menu item */
	GameState			NextState;  /**< State of the next gamestate this item links to */
	vec2_t				Position;   /**< The position of the item */
	char				*Name;		/**< The name of the menu item */
	sprite_t			*Image;		/**< The image of the menu item */
	void				*Info;		/**< The information specific to this menu */
};

/**
 * A menu structure which controls updateing, drawing, and connecting menu states.
 *
 * @author	Anthony Rios
 * @date	3/30/2016
 */

struct menu_s
{
	menu_item_t mItems[MENU_ITEM_MAX];		/**< The items this menu contains */
	menu_item_t *mSelectedItem;				/**< The currently selected item */
	sprite_t *mBackground;					/**< The background image for the menu */
	GameState mCurrentState;				/**< The current game state the menu is drawing in */
	GameState mPreviousState;				/**< State before this got loaded*/
	int mItemCount;							/**< Number of items in this menu */
	void (*Update)(menu_t *self, SDL_GameControllerButton button);	/**< The update function, which takes input and updates global variables*/
	void (*Draw)(menu_t *self);				/**The draw function for the menu*/
};

extern menu_t *gMenus;

/**
 * Allocate memor for menu system, gMenus is the menu list. 
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */
int InitMenuSystem();

/**
 * Loads a menu.
 *
 * @param [in,out]	object 	If non-null, the object menu was parsed to.
 * @param [in,out]	g_str 	If non-null, the string.
 * @param	curr_state	  	State to assign the menu.
 * @param	previous_state	State before this menu.
 *
 * @return	0 if loads correctly, -1 if it doesn't.
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */
menu_t *LoadMenu(object_t *object, char *g_str, GameState curr_state, GameState previous_state );

/**
 * Searches for the first menu from game state in gMenus.
 *
 * @param	curr_state	State of the curr.
 *
 * @return	null if it fails, else the found menu from game state.
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */
menu_t *FindMenuFromGameState(GameState curr_state);

/**
 * Searches for the first free menu slot in gMenus, used for loading new menus.
 *
 * @return	null if it fails, else the found free menu.
 *
 * @author	Anthony Rios
 * @date	3/30/2016
 */
menu_t *FindFreeMenu();

/**
 * Searches for the first menu item, with name of str given.
 *
 * @param [in,out]	menu	If non-null, the menu.
 * @param [in,out]	item	If non-null, the item.
 *
 * @return	null if it fails, else the found menu item.
 *
 * @author	Anthony Rios
 * @date	3/30/2016
 */
menu_item_t *FindMenuItem(menu_t *menu, char *item);

void FreeMenu(menu_t *menu);
int InitGUI();
void ShutdownGUI();

void LoadGUIforGameState(GameState game_state);
void DrawUI();

extern sprite_t *gUI_Sprite_Health;
extern vec2_t gUI_Health_Pos;
extern vec2_t gUI_Power_Pos;


#endif
