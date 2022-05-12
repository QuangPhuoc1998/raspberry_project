#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include "main.h"

int Hal_SpiInit(void);
void Hal_SpiDeInit(void);
void Hal_SpiWrite(uint8_t * TxData, uint8_t * RxData, uint8_t len);

#endif // _HAL_SPI_H_