#ifndef UTILS_PRINT_H

#include <stdio.h>

#define UTILS_PRINT_H

#define PRINT(...) fprintf(stdout, __VA_ARGS__)
#define PRINTLN(...) fprintf(stdout, __VA_ARGS__); \
	putc('\n', stdout)
#define EPRINT(...) fprintf(stderr, __VA_ARGS__)
#define EPRINTLN(...) fprintf(stderr, __VA_ARGS__); \
	putc('\n', stderr)

#endif
