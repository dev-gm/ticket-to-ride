#include <utils/defer.h>
#include <utils/hmalloc.h>
#include <utils/print.h>
#include <utils/types.h>
#include <engine/map.h>

typedef struct Game {
	Map map;
} Game;

int main() {
	City cities[] = {
		{ .name = "New York City" },
		{ .name = "Boston" },
		{ .name = "Miami" }
	};
	DEFER(map_deinit) Map map =
		map_init(cities, sizeof(cities) / sizeof(cities[0]));
	return 0;
}
