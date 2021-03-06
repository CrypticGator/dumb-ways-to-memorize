#ifndef __GLOBALS_H
#define __GLOBALS_H


#include <jsmn.h>
#define STRING_TYPE(X) (X == sizeof(char) ? "Char"  \
						: (X == sizeof(int) ? "Int"  \
						: (X == sizeof(jsmntok_t) ? "Jsmn" \
						: "Unkown" ) ) ) 
/**< Returns string of the type of size X*/

#define SIGN_BIT 0xF000

/** Defines an alias representing the 2D vector */
typedef struct vec2_s
{
	int x;
	int y;
}vec2_t;


struct cpVect;
cpVect Vec2Cp(vec2_t *vect);
vec2_t CpToVect(cpVect * cp);

typedef struct area_s
{
	float x, y, w, h;
}area_t;

extern vec2_t gZeroVect;

//Address of a value, basically generic typing int*
typedef unsigned int address_t;
//Key Value pair struct
typedef struct KV_Pair_s
{
	char *key;
	address_t value;
}KV_Pair_t;

//#define VEC2_ADD(A, B, C) (C[0] = A[0] + B[0], C[1] = A[1] + B[1]) 
//#define VEC2_SUBTRACT(A, B, C) (C[0] = A[0] - B[0], C[1] = A[1] - B[1])
void Vec2Add(vec2_t *A, vec2_t *B, vec2_t *C);
void Vec2Subtract(vec2_t *First, vec2_t *Second, vec2_t *C);
void Vec2MultiplyScalar(vec2_t *A, int B, vec2_t *C);
extern int LargestDivisor(int num);


/** Defines the enum relating to entity states */
typedef enum
{
	ENTITY_STATE_DEAD,  /**<  entity state dead */
	ENTITY_STATE_ALIVE, /**<  entity state alive option */
	ENTITY_STATE_OTHER  /**<  entity state other, which is used for non-health based entities */
}entity_state_t;

/** Defines the enum which are the collision types for the physics engine */
typedef enum
{
	COLLISION_TYPE_STATIC,  /**<  collision type static - which means it collides, but doesn't move */
	COLLISION_TYPE_INDEPENDENT,
	COLLISION_TYPE_RAGDOLL, /**<  collision type ragdoll - which collides + moves */
	COLLISION_TYPE_CLIP		/**<  collision type clip - which means it doesn't collide , but moves. Should be used for particle entities (maybe) */
}collision_type_t;

typedef enum
{
	UI_NULL,
	UI_ELEMENT_LABEL,
	UI_ELEMENT_IMAGE,
	UI_ELEMENT_BUTTON,
	UI_PANEL,
	UI_MAX
}ui_type_t;

/** Defines the enum for menu item states */
typedef enum
{
	MENU_ITEM_STATE_NULL,
	MENU_ITEM_STATE_SELECTED = 0x1,		/**<  menu item state selected - which means the player is hovering over this now */
	MENU_ITEM_STATE_NOT_SELECTED = 0x2, /**<  menu item state not selected */
	MENU_ITEM_STATE_PICKED = 0x4,		/**<  menu item state picked - which is a option that is checked */
	MENU_ITEM_STATE_MAX = 0x8
}menu_item_state_t;

/** Defines an enum for animation states in mSprites array */
typedef enum
{
	ANIMATION_IDLE,		/**<  idle animation */
	ANIMATION_WALK,		/**<  walk animation*/
	ANIMATION_JUMP,		/**<  jump animation */
	ANIMATION_ATTACK,   /**<  attack animation */
	ANIMATION_HIT,		/**<  hit animation */
	ANIMATION_MAX = 20  /**<  maximum animations */

}animation_state_t;

/** Defines the enum for the game states */
typedef enum
{
	DEBUG =		0x0,
	SPLASH =	0x1,	/**<  splash screen game state */
	START =		0x2,	/**<  start screen game state */
	GUESS =		0x4,	/**<  first time the player chooses the power_ups */
	CHOOSE =	0x8,	/**<  state in which the player selects a power_up from the chosen power ups in guess */
	PLAYING =	0x10,   /**<  playing game state, which is consistent of the level, enemy entities, and the player */
	EDITOR =	0x20,   /**<  editor state, where the player creates a new level */
	END =		0x40,   /**<  player has chosen to quit the game */
	MAX =		0x80,   /**<  maximum states */
}GameState;

extern GameState gGameState;					/**< State of the game */
extern GameState StrToGameState(char *str);		/**< Converts a string into a game state*/
extern char *gGameStateStr[];
extern char *GameStateToStr(GameState game_state);
extern int StrToMenuType(char *str);			/**< Converts a string into a menu type*/

//For Hazards
#define HAZARD_NULL	0x0
#define HAZARD_MAX	(0x1 >> 31)
#define HAZARD_DAMAGE 10
#define HAZARD_STUN_FRAMES 10
extern char **Hazards_str;							/**< The hazards string array which is defined in the gamedata file */
extern int StrToHazard(char *str);					/**< Converts a string into a hazard, using the parsed hazards_str for comparison */

//For EntParsing
#define ENTITIES_FILE_STR	"Entities"
extern char *gEntitiesFile;							/**< The name of the entities file */
extern char *Collisions_str[];						/**< The collisions type strings for parsing */
extern char *EntityStates_str[];					/**< The entity state strings for parsing */
collision_type_t StrToCollisionType(char *str);		/**< Converts a string into a entity collision type */
entity_state_t StrToEntityState(char *str);			/**< Converts a string into an entity state */
int StrToSpriteType(char *str);

//For PowerUps
#define POWER_UPS_STR	"PowerUps"
extern char *gPowerUpsFile;							/**< The name of the power ups file */
extern vec2_t *mousePos;							/**< The mouse position */
extern int *keyPower;								/**< The key press related to using the power */
extern char **gSelectedPowerUps;					/**< The power ups the player selects */
extern char **gUsedPowerUps;						/**< The used power ups for this game run */
extern char *gCurrentPowerUpName;					/**< The current power up name */

//For Levels
extern char **gLevels;								/**< The level names */
extern char **gSelectedLevels;						/**< The selected levels to load */
int SelectLevels();
int LoadSelectedLevel(int level);
void RandomizeSelectedLevels();

extern void *gWorld;
extern void *gMouse;

//Game Globals

#define G_NAME_STR		"Name"
#define LOC_NAME_STR	"name"
#define	UPDATE_FRAME_DELAY		13
#define DRAW_FRAME_DELAY		20
#define DIR_LEFT				1
#define DIR_RIGHT				0
#define PHYSICS_LIMITER 2
extern int gPlayerLives;			/**< The lives of the player */
extern int gLevelsPerGame;			/**< The levels per game */
extern int gScreenWidth;			/**< The set Width of the screen */
extern int gScreenHeight;			/**< Te set Height of the screen */
extern unsigned int gCurrentTime;   /**< The current time , updated from last update call*/
extern float gDeltaTime;		/**< The time since last runs */
extern vec2_t gGravity;				/**< The gravity which affects all the assets */

extern void ResetGame();
extern void ResetRun();
extern void GameNextLevel();

extern int exitRequest;				/**< The integer to be changed to exit */

//Memory Functions
/**
 * Counts the memory of type size_type, given that the final address is null.
 *
 * @param [in,out]	src	If non-null, source of memory.
 * @param			size_type  	Size of the type.
 *
 * @return	The total number of memory, if src is null 0 is returned.
 *
 * @author	Anthony Rios
 * @date	2/1/2016
 */
extern int CountMem(void *src, int size_type);

/**
 * Allocate memory and copy over src into it. Adds Null to end.
 * Returns NULL on size 0
 * 
 * @param [in,out]	dst	If non-null, destination for the allocation.
 * @param [in,out]	src	If non-null, source for the adding.
 * @param	size_type  	Size of the type.
 * @param	size	   	The size.
 *
 * @return	0 on success, -1 on error.
 *
 * @author	Anthony Rios
 * @date	2/1/2016
 */
extern int AllocateDynamic(void **dst, void *src, int size_type, int size);

/**
 * Compare memory to memory array.
 *
 * @param [in,out]	mem		 	If non-null, the memory.
 * @param [in,out]	mem_array	If non-null, array of memories.
 * @param	size_type		 	Size of type, via sizeof() function.
 * @param	size_array		 	Size of Array.
 *
 * @return	0 if equal, -1 if not.
 *
 * @author	Anthony Rios
 * @date	1/31/2016
 */
extern int CompareMemToMemArray(void *mem, void *mem_array, int size_type, int size_array);

//Foward dec of object_s for global objects & functions
struct object_s;
/**
 * Parse given obj/str to vector 2.
 *
 * @param [in,out]	object	If non-null, the object.
 * @param [in,out]	str   	If non-null, the string.
 *
 * @return	null if it fails, else a pointer to a vec2_t.
 *
 * @author	Anthony Rios
 * @date	3/29/2016
 */
extern vec2_t *ParseToVec2(struct object_s *object, char* str);

/**
 * Parse obj/data to string array.
 *
 * @param [in,out]	object	If non-null, the object.
 * @param [in,out]	str   	If non-null, the string.
 *
 * @return	null if it fails, else a handle to a char.
 *
 * @author	Anthony Rios
 * @date	3/29/2016
 */
extern char **ParseToStringArray(struct object_s *object, char* str);

//Prepoccessor defed LINKS and STRICT_MODE
//JSON Parser
extern jsmn_parser gParser;								/**< The global jsmn parser */
extern jsmntok_t *gGameTokens;							/**< Tokens for GameData */
extern struct object_s *gGameObject;					/**< The game object */
extern jsmntok_t *gEntityTokens;						/**< The entity jsmn tokens */
extern struct object_s *gEntityObject;					/**< The entity object */
extern jsmntok_t *gLevelTokens;							/**< The level jsmn tokens */
extern struct object_s *gLevelObject;					/**< The current level object */
extern char *gGameData;									/**< Game Data File - holding the contents of file via string*/
extern char *gEntityData;								/**< The current parsed string of the entity file */
extern char *gLevelData;								/**< Information describing the current level */

#endif