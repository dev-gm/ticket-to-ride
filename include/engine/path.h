#ifndef ENGINE_PATH_H

#define ENGINE_PATH_H

#include <utils/types.h>
#include "player.h"

typedef u32 path_length_t;

typedef struct {
	Player *player;
	path_length_t length;
} Path;

#endif
