// ONLY WORKS IN GCC
#ifndef UTILS_DEFER_H

#define UTILS_DEFER_H

// GCC ONLY, nested functions
// #define DEFER_NO_ARGS(func) \
// 	void _cleanup ## func(void **value) { func(); } \
// 	__attribute__((cleanup(_cleanup ## func)))
// 
// #define DEFER(func) \
// 	void _cleanup ## func(void **value) { func (*value); } \
// 	__attribute__((cleanup(_cleanup ## func)))
// 
// #define DEFER_PTR(func) \
// 	__attribute__((cleanup( func )))
// 

#define DEFER(func) __attribute__((cleanup(func)))

#endif
