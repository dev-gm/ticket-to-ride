#include <engine/map.h>
#include <utils/hmalloc.h>

Map map_init(City *cities, usize cities_len) {
	// calloc initializes to NULL
	Path ***paths = hcalloc(cities_len, sizeof(Path **));
	for (usize i = 0; i < cities_len; ++i)
		paths[i] = hcalloc(cities_len, sizeof(Path *));
	Map out = {
		.cities = cities,
		.cities_len = cities_len,
		.paths = paths
	};
	return out;
}

Path *map_get_path(const Map *self, usize city1, usize city2) {
	if (city1 == city2)
		return NULL;
	return city1 > city2
		? self->paths[city1][city2]
		: self->paths[city2][city1];
}

// returns whether it succeeded
Path *map_add_connection(
	const Map *self,
	Path path,
	usize city1,
	usize city2
) {
	if (city1 == city2)
		return NULL;
	Path *path_ptr = map_get_path(self, city1, city2);
	*path_ptr = path;
	return path_ptr;
}

// nonrecursively implemented
bool map_player_has_completed_route(
	const Map *self,
	const Player *player,
	usize city1,
	usize city2
) {
	if (city1 == city2)
		return true; // maybe change this behavior?
	usize start = city1, end = city2;
	while (true) {
		if (start < end) {
			usize temp = start;
			start = end;
			end = temp;
		}
		Path *child_path = map_get_path(self, start, end);
		if (child_path != NULL && child_path->player == player)
			return true;
		for (usize i = 0; i < self->cities_len; ++i) {
			if (i == end)
				continue;
			child_path = map_get_path(self, start, i);
			if (child_path != NULL && child_path->player == player) {
				start = i;
				break;
			}
		}
	}
}

void map_count_player_points(
	const Map *self,
	const Player *player,
	void (calculate)(void *counter, path_length_t length),
	void *counter
) {
	for (usize i = 0; i < self->cities_len; ++i) {
		for (usize j = 0; j < self->cities_len; ++j) {
			if (
				self->paths[i][j] != NULL &&
				self->paths[i][j]->player == player
			) calculate(counter, self->paths[i][j]->length);
		}
	}
}

void map_deinit(Map *self) {
	for (usize i = 0; i < self->cities_len; ++i)
		for (usize j = 0; j < self->cities_len; ++j)
			free(self->paths[i][j]);
}


