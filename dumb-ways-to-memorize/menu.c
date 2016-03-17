#include "globals.h"
#include "graphics.h"
#include "menu.h"
#include "mystrings.h"
#include <stdio.h>

menu_t *gMenus = NULL;
int gCurrentSelectedItem = 0;


void DeselectItemByNum(menu_t *self, int item)
{
	if(!self)
	{
		printf("Deselect item not given menu");
		return;
	}
	self->mItems[item].State = MENU_ITEM_STATE_NOT_SELECTED;
}

void SelectItemByNum(menu_t *self, int item)
{
	if(!self)
	{
		printf("Select item not given menu");
		return;
	}
	self->mItems[item].State = MENU_ITEM_STATE_SELECTED;
}

//Uses gSelectedItem
void UpdateVerticalMenu(menu_t *self, SDL_GameControllerButton button)
{
	if(!self)
	{
		printf("NULL menu updated \n");
		return;
	}
	switch(button)
	{
	case(SDL_CONTROLLER_BUTTON_DPAD_UP):
		{
			if(!gCurrentSelectedItem)
			{
				break;
			}
			DeselectItemByNum(self, gCurrentSelectedItem);
			if(gCurrentSelectedItem-1 < 0)
			{
				SelectItemByNum(self, gCurrentSelectedItem);
				break;
			}
			gCurrentSelectedItem--;
			SelectItemByNum(self, gCurrentSelectedItem);
			break;
		}
	case(SDL_CONTROLLER_BUTTON_DPAD_DOWN):
		{
			DeselectItemByNum(self, gCurrentSelectedItem);
			if(gCurrentSelectedItem+1 > CountMem(self->mItems, sizeof(menu_item_t)))
			{
				SelectItemByNum(self, gCurrentSelectedItem);
				break;
			}
			gCurrentSelectedItem++;
			SelectItemByNum(self, gCurrentSelectedItem);
			break;
		}
	case(SDL_CONTROLLER_BUTTON_A):
		{
			gGameState = self->mItems[gCurrentSelectedItem].NextState;
			break;
		}
	default:
		{
			break;
		}
	}
}

//Uses mSelectedItem
void UpdatePowerUpMenu(menu_t *self, SDL_GameControllerButton button)
{
	int i, powerUps, selected_power_ups;
	if(!self)
	{
		printf("NULL menu updated \n");
		return;
	}
	switch(button)
	{
	case(SDL_CONTROLLER_BUTTON_DPAD_UP):
		{
			if(self->mSelectedItem+1 < self->mItems+CountMem(self->mItems, sizeof(menu_item_t)))
			{
				break;
			}
			self->mSelectedItem--;
			break;
		}
	case(SDL_CONTROLLER_BUTTON_DPAD_DOWN):
		{
			if(self->mSelectedItem+1 > self->mItems+CountMem(self->mItems, sizeof(menu_item_t)))
			{
				break;
			}
			self->mSelectedItem++;
			break;
		}
	case(SDL_CONTROLLER_BUTTON_A):
		{
			if(!self->mSelectedItem)
			{
				self->mSelectedItem = self->mItems;
			}
			if(self->mSelectedItem->NextState == SPLASH)
			{
				self->mSelectedItem->State = MENU_ITEM_STATE_PICKED;
			} else
			{
				powerUps = CountMem(self->mItems, sizeof(menu_item_t));
				gSelectedPowerUps = (char**) malloc(sizeof(char*)*powerUps);
				selected_power_ups = 0;
				for(i = 0; i < powerUps; i++)
				{
					if(self->mItems[i].State & MENU_ITEM_STATE_PICKED)
					{
						gSelectedPowerUps[selected_power_ups] = self->mItems[i].Name;
						selected_power_ups++;
					}
				}
				if(selected_power_ups != gLevelsPerGame)
				{
					printf("Too many or not enough power_ups selected");
					free(gSelectedPowerUps);
					break;
				}
				gSelectedPowerUps[selected_power_ups] = NULL;
				gGameState = PLAYING;
			}
			break;
		}
	default:
		{
			break;
		}
	}
}

/**
 * Allocate memor for menu system, gMenus is the menu list. 
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */

int InitMenuSystem()
{
	if(gMenus)
	{
		printf("gMenus already initialized");
		return -1;
	}
	gMenus = (menu_t*) malloc(sizeof(menu_t)*MAX_MENUS);
	if(!gMenus)
	{
		printf("Allocate menu error");
		return -1;
	}
	memset(gMenus, 0, sizeof(menu_t)*MAX_MENUS);
	return 0;
}

//Draw Function through gCurrentSelectedItm
void DrawMenuByNum(menu_t *self)
{
	int i, itemCount;
	SDL_Rect selection_rect = {0,0,10,10};

	if(!self)
	{
		printf("Null menu tried to be drawn \n");
		return;
	}

	if(self->mBackground)
	{
		DrawSprite(self->mBackground, NULL, gRenderer);
	}

	itemCount = CountMem(self->mItems, sizeof(menu_item_t));
	for(i = 0; i < itemCount; i++)
	{
		if(i == gCurrentSelectedItem)
		{
			DrawSprite(self->mItems[i].Image, &self->mItems[i].Position, gRenderer);
			selection_rect.x = self->mItems[i].Position.x;
			selection_rect.y = self->mItems[i].Position.y;
			SDL_RenderDrawRect(gRenderer, &selection_rect);
		} else {
			DrawSprite(self->mItems[i].Image, &self->mItems[i].Position, gRenderer);
		}
	}

}

//Draw Function through mItem State
void DrawMenuByState(menu_t *self)
{
	int i, itemCount;
	SDL_Rect selection_rect = {0,0,10,10};

	if(!self)
	{
		printf("Null menu tried to be drawn \n");
		return;
	}

	if(self->mBackground)
	{
		DrawSprite(self->mBackground, NULL, gRenderer);
	}

	itemCount = CountMem(self->mItems, sizeof(menu_item_t));
	for(i = 0; i < itemCount; i++)
	{
		if(self->mItems[i].State & (MENU_ITEM_STATE_SELECTED | MENU_ITEM_STATE_PICKED))
		{
			DrawSprite(self->mItems[i].Image, &self->mItems[i].Position, gRenderer);
			selection_rect.x = self->mItems[i].Position.x;
			selection_rect.y = self->mItems[i].Position.y;
			SDL_RenderDrawRect(gRenderer, &selection_rect);
		} else
		{
			DrawSprite(self->mItems[i].Image, &self->mItems[i].Position, gRenderer);
		}
	}

}
/**
 * Sets the positions of the menu items based on the type of layout.
 *
 * @param [in,out]	items	If non-null, the items.
 * @param	type		 	The type.
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */

void ProcessMenuItemsByType(menu_item_t *items,menu_type_t type)
{
	SDL_Rect format;
	int itemCount, i, width, height;
	itemCount = CountMem(items, sizeof(menu_item_t));

	width = gScreenWidth ? gScreenWidth : SCREEN_RES_W;
	height = gScreenHeight ? gScreenHeight : SCREEN_RES_H;


	switch(type)
	{
	case(MENU_TYPE_H):
		{
			SDL_SetRect(&format, 0, height*.33, 0, 0);
			break;
		}
	case(MENU_TYPE_V) : 
		{
			SDL_SetRect(&format, width*.33, 0, 0, 0);
			break;
		}
	case(MENU_TYPE_GRID):
		{
			SDL_SetRect(&format, 0, 0, 0, 0);
			break;
		}
	case(MENU_TYPE_POWER):
		{
			SDL_SetRect(&format, width*.1, height*.1, 0, 0);
			break;
		}
	default:
		{
			SDL_SetRect(&format, 0, height*.33, 0, 0);
			break;
		}
	}
	
	for(i = 0; i < itemCount; i++)
	{
		if(type & (MENU_TYPE_H | MENU_TYPE_V))
		{
			items[i].Position.x = format.x * i;
			items[i].Position.y = format.y * i;
		}
		if(type & MENU_TYPE_GRID)
		{
			items[i].Position.x = format.x * i;
			items[i].Position.y = format.y * i;
		}
		if(type & MENU_TYPE_POWER)
		{
			items[i].Position.x = format.x * i * 3.14;
			items[i].Position.y = format.y * i * 3.14;
		}
	}

	
}


/**
 * Loads a menu.
 *
 * @param [in,out]	object 	If non-null, the object menu was parsed to.
 * @param [in,out]	g_str 	If non-null, the string.
 * @param	currState	  	State to assign the menu.
 * @param	previous_state	State before this menu.
 *
 * @return	0 if loads correctly, -1 if it doesn't.
 *
 * @author	Anthony Rios
 * @date	3/16/2016
 */

menu_t *LoadMenu(object_t* object, char *g_str ,GameState curr_state, GameState previous_state)
{
	menu_t *menu;
	jsmntok_t *temp_tok, *type_tok;
	object_t *temp_obj;
	char *temp_str, *type_str;
	int i, temp_i, value_pos;

	//Check Vars given
	if(!object || !g_str)
	{
		printf("No object / str given to load menu \n");
		return NULL;
	}

	//Check menu type
	temp_str = FindValueFromKey(object->keys, MENU_TYPE, g_str);
	if(!temp_str)
	{
		printf("No menu type in menu found: %s \n", object->name);
		return NULL;
	}

	//Look for free menu slot
	menu = FindFreeMenu();
	if(!menu)
	{
		printf("Could not find free menu \n");
		return NULL;
	}

	menu->mPreviousState = previous_state;
	menu->mCurrentState = curr_state;

	temp_obj = FindObject(object, MENU_ITEMS);
	if(!temp_obj)
	{
		printf("No items in menu %s \n", object->name);
		return NULL;
	}

	//Load Background
	temp_tok = FindKey(object->keys, MENU_BACKGROUND, g_str);
	if(!temp_tok)
	{
		printf("No background loaded for menu %s \n", object->name);
	} else 
	{
		temp_i = (temp_tok - object->keys);
		temp_str = JsmnToString(&object->values[temp_i], g_str);
		menu->mBackground = LoadSprite(temp_str, 0);
	}

	//Load Items
	temp_i = CountObjectChildren(temp_obj);
	if(temp_i >= MENU_ITEM_MAX)
	{
		printf("Max menu items for menu %s \n", object->name);
		temp_i = MENU_ITEM_MAX -1;
	}
	for(i = 0; i < temp_i; i++)
	{
		temp_tok = FindKey(temp_obj->children[i].keys, MENU_ITEM_SPRITE, g_str);
		if(temp_tok)
		{
			value_pos = (temp_tok - temp_obj->children[i].keys);
			temp_str = JsmnToString(&temp_obj->children[i].values[value_pos], g_str);
			menu->mItems[i].Image = LoadSprite(temp_str, 0);
		}
		temp_tok = FindKey(temp_obj->children[i].keys, MENU_ITEM_TEXT, g_str);
		if(temp_tok)
		{
			value_pos = (temp_tok - temp_obj->children[i].keys);
			temp_str = JsmnToString(&temp_obj->children[i].values[value_pos], g_str);
			menu->mItems[i].Name = temp_str;
		}
		menu->mItems[i].State = MENU_ITEM_STATE_NOT_SELECTED;
		temp_tok = FindKey(temp_obj->children[i].keys, MENU_ITEM_LINK, g_str);
		if(temp_tok)
		{
			value_pos = (temp_tok - temp_obj->children[i].keys);
			temp_str = JsmnToString(&temp_obj->children[i].values[value_pos], g_str);
			menu->mItems[i].NextState = StrToGameState(temp_str);
			free(temp_str);
		} else
		{
			menu->mItems[i].NextState = SPLASH;
		}
		menu->mItems[i].Info = NULL;
			
	}
		
	//Calculate Menu Item Positions
	type_tok = FindKey(object->keys, MENU_TYPE, g_str);
	if(!type_tok)
	{
		printf("Not found menu layout type for %s. Switching to default vertical layout", object->name);
		type_str = strdup(MENU_TYPE_STRING_V);
	}
	value_pos = (type_tok - object->keys);
	type_str = JsmnToString(&object->values[value_pos], g_str);
	ProcessMenuItemsByType(menu->mItems, (menu_type_t) StrToMenuType(type_str));
	menu->mSelectedItem = menu->mItems;
	gCurrentSelectedItem = 0;

	//Set Up Different Menu Types
	if(!strcmp(type_str, MENU_TYPE_STRING_V))
	{
		menu->Update = UpdateVerticalMenu;
		menu->Draw = DrawMenuByNum;
	} else if(!strcmp(type_str, MENU_TYPE_STRING_POWER))
	{
		menu->Update = UpdatePowerUpMenu;
		menu->Draw = DrawMenuByState;
	} else
	{
		menu->Update = UpdateVerticalMenu;
		menu->Draw = DrawMenuByNum;
	}

	return menu;

}

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

menu_t* FindMenuFromGameState(GameState curr_state)
{
	int i;
	if(!gMenus)
	{
		printf("Menu Sys not Initialized");
		return NULL;
	}
	for(i = 0; i < MAX_MENUS; i++)
	{
		if(!gMenus[i].Update)
		{
			continue;
		}
		if(gMenus[i].mCurrentState == curr_state)
		{
			return &gMenus[i];
		}
	}
}

menu_t* FindFreeMenu()
{
	int i, *menuCmp;
	if(!gMenus)
	{
		printf("Menu System not initialized");
		return NULL;
	}
	menuCmp = (int*) malloc(sizeof(menu_t));
	memset(menuCmp, 0, sizeof(menu_t));
	for(i = 0; i < MAX_MENUS; i++)
	{
		if(!memcmp(menuCmp, &gMenus[i], sizeof(menu_t)))
		{
			return &gMenus[i];
		}
	}
	return NULL;
}


int StrToMenuType(char *str)
{
	if(strcmp(str, MENU_TYPE_STRING_H))
	{
		return MENU_TYPE_H;
	}
	if(strcmp(str, MENU_TYPE_STRING_V))
	{
		return MENU_TYPE_V;
	}
	if(strcmp(str, MENU_TYPE_STRING_GRID))
	{
		return MENU_TYPE_GRID;
	}
	if(strcmp(str, MENU_TYPE_STRING_POWER))
	{
		return MENU_TYPE_POWER;
	}
	return MENU_TYPE_NULL;
}