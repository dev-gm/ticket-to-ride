#ifndef UTILS_HMALLOC_H

#define UTILS_HMALLOC_H

#include "types.h"
#include "print.h"

void * hmalloc(usize size);

void * hcalloc(usize n, usize size);

void * hrealloc(void *ptr, usize size);

#endif
