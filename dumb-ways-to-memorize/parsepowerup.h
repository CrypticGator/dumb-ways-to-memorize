#ifndef __PARSE_POWER_UP_H
#define __PARSE_POWER_UP_H

#include "parseobject.h"
#include "entity.h"

enum use_type_t
{
	INFINITE = -2,
	STATIC
};

typedef enum 
{
	INFO_NONE	= 0x0,
	INFO_BUTTON = 0x1,
	INFO_MOUSE	= 0x2,
	INFO_BOTH	= INFO_MOUSE | INFO_BUTTON

}info_type_t;

typedef struct power_s power_t;

struct power_s
{
	entity_t *target;
	char *name;
	void (*GetInfo)(info_type_t info);
	void (*GetTarg)(entity_t *self, entity_t **targ);
	void (*Update)(power_t *power);
	int uses;
	info_type_t info_type;

};
//Power Specific
void CallInfo(info_type_t info);
void UpdateNormal(power_t *power);
void UpdateInfinite(power_t *power);
int GetUseType(const char *var, int *useType);

power_t *ParseToPowerUp(object_t *power, char *str);

//Interactions
void Move();
void Destroy();
void Spawn(object_t *object, char *g_str);
void Edit(void *args, ...);
void Nullify();

//Interactions Array
extern char *InteractionNames[];
extern void (*InteractionSymbols[]);

#endif