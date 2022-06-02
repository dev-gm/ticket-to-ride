#include <stdlib.h>
#include <utils/hmalloc.h>
#include <utils/print.h>

inline void * hmalloc(usize size) {
	void *out = malloc(size);
	if (out == NULL) {
		EPRINTLN("malloc failed");
		exit(1);
	}
	return out;
}

inline void * hcalloc(usize n, usize size) {
	void *out = calloc(n, size);
	if (out == NULL) {
		EPRINTLN("calloc failed");
		exit(1);
	}
	return out;
}

inline void * hrealloc(void *ptr, usize size) {
	ptr = realloc(ptr, size);
	if (ptr == NULL) {
		EPRINTLN("realloc failed");
		exit(1);
	}
	return ptr;
}
