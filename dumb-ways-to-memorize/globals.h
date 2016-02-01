#ifndef __GLOBALS_H
#define __GLOBALS_H

#define SIZE_OF_JSMN_TOK_T 20
#define SIZE_OF_OBJECT_T 20
#define RETURN_TYPE(X, Y) (X == sizeof(char) ? (char*)Y  \
						: (X == sizeof(int) ? (int*)Y  \
						: (X == SIZE_OF_JSMN_TOK_T ? (jsmntok_t*)Y \
						: (int*)Y ) ) ) 
/**< Returns pointer to Y based on X size | default (int*) */

#define	FRAME_DELAY		17
#define LEVELS_PER_GAME	6

extern int exitRequest;

extern int AllocateDynamic(void *dst, void *src, int size_type, int size);
extern int CompareMemToMemArray(void *mem, void *mem_array, int size_type, int size_array);

//Prepoccessor defed LINKS and STRICT_MODE
//JSON Parser
#include <jsmn.h>
extern jsmn_parser gParser;
extern jsmntok_t *gTokens;
extern char *gGameData;

#endif