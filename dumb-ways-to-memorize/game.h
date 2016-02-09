#ifndef __GAME_H
#define __GAME_H

#define	SCREEN_RES_X	1280
#define	SCREEN_RES_Y	720

#define	JSON_FILE		"GameData.json"		
#define ENTITY_FILE		"Entities.json"

int	mState;
int	Setup();
int Run();
void Shutdown();

extern char **gLevels;
extern char **gSelectedLevels;

#endif