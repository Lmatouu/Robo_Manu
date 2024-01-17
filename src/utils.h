#include <stdio.h>
#ifndef UTILS_H
#define UTILS_H

#ifndef NDEBUG
#define TRACE(fmt, ...) do {fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); fflush (stderr); } while(0);   

#else
#define TRACE(fmt, ...) 
#endif // NDEBUG

#endif // UTILS_H
