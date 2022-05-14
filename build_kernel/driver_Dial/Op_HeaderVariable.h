#ifndef _OP_HEADER_VARIABLE_H_
#define _OP_HEADER_VARIABLE_H_

#include "main.h"
#include "Op_HeaderDefine.h"

#ifndef GLOBAL_DEFINE
#define HEAER_VARIABLE extern
#else
#define HEAER_VARIABLE
#endif

HEAER_VARIABLE uint8_t g_ubEncoderValue[3];
HEAER_VARIABLE uint8_t g_ubEncoderBuffer[3][2];
HEAER_VARIABLE uint8_t g_ubUpDownMoveValue;
HEAER_VARIABLE uint8_t g_bMoveEncoderCount;
HEAER_VARIABLE uint8_t g_ubEncoderCount;

#endif // _OP_HEADER_VARIABLE_H_