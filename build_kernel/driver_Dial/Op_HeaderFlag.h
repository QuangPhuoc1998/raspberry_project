#ifndef _OP_HEADER_FLAG_H_
#define _OP_HEADER_FLAG_H_

#include "main.h"

#ifdef GLOBAL_DEFINE
#define HEADER_FLAG
#else
#define HEADER_FLAG extern
#endif

typedef struct
{
	uint8_t bit0 : 1;
	uint8_t bit1 : 1;
	uint8_t bit2 : 1;
	uint8_t bit3 : 1;
	uint8_t bit4 : 1;
	uint8_t bit5 : 1;
	uint8_t bit6 : 1;
	uint8_t bit7 : 1;
} BYTE_T;

typedef union
{
	uint8_t origin;
	BYTE_T member;
} BYTE_FIELD_T;

#endif // _OP_HEADER_FLAG_H_