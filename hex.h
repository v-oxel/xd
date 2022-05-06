#ifndef HEX_H
#define HEX_H

#ifdef __cplusplus
/*
extern "C" {
*/
#endif

#include <stdlib.h>
#include <stdio.h>

#include "int.h"

struct _ByteArray;
typedef struct _ByteArray ByteArray;
typedef ByteArray* lpByteArray;

struct _ByteArray
{
	uint8_t* bytes;
	size_t size;
};

lpByteArray LoadFromFile(const char* fname);


#ifdef __cplusplus
/*
}
*/
#endif

#endif