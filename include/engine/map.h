#ifndef ENGINE_MAP_H

#define ENGINE_MAP_H

#include <stdlib.h>
#include <utils/types.h>
#include "path.h"

typedef struct {
	char *name;
} City;

typedef struct {
	City *cities;
	usize cities_len;
	Path ***paths; // cell == NULL if no path
} Map;

Map map_init(City *cities, usize cities_len);

Path *map_get_path(const Map *self, usize city1, usize city2);

// returns pointer to path, or NULL if unsuccessful
Path *map_add_connection(
	const Map *self,
	Path path,
	usize city1,
	usize city2
);

bool map_player_has_completed_route(
	const Map *self,
	const Player *player,
	usize city1,
	usize city2
);

void map_count_player_points(
	const Map *self,
	const Player *player,
	void (calculate)(void *counter, path_length_t length),
	void *counter
);

// it is the caller's responsibility to free cities
void map_deinit(Map *self);

#endif
