#include "globals.h"
#include "parsepowerup.h"
#include "entity.h"
#include "player.h"
#include "parselevel.h"
#include <stdio.h>

char *gPlayerName = PLAYER_NAME;
entity_t *gPlayer = NULL;
int gPlayerLives = 0;

void InitPlayer()
{
	if(!gPlayer)
	{
		gPlayer = InitNewEntity();
	}

	if(!gPlayer)
	{
		printf("Could not Init Player");
		exitRequest = 1;
		return;
	}
	memcpy(gPlayer,FindCachedEntity("Player"), sizeof(entity_t));
	if(!gPlayerLives)
	{
		PLAYER_LIVES;
	}
	gPlayer->Draw = DrawGeneric;
	gPlayer->Think = ThinkPlayer;
	gPlayer->Touch = TouchPlayer;
	gPlayer->PowerUp = gPowerUps ? UsePower : NULL;
	gPlayer->mPosition = gCurrentLevel ? gCurrentLevel->mSpawnPoint : gZeroPos;
	gPlayer->mHealth = 100;
	gPlayer->mWeight = 1;
	gPlayer->mNextThink = gCurrentTime + 2*FRAME_DELAY;
}

void DecrementPlayerLives()
{
	gPlayerLives--;
}