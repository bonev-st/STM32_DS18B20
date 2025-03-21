/**
 ******************************************************************************
 * @file    ds28e36.h
 * @brief   This file contains all the constants parameters for the DS28E36
 * 		 1-Wire DeepCover Secure Authenticator
 ******************************************************************************
 * @attention
 * Usage:
 *		Uncomment LL Driver for HAL driver
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DS28E36_H
#define DS28E36_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "OneWire/onewire.h"
#include <stdint.h>

/* Data Structure ------------------------------------------------------------*/
#define DS28E36_MaxCnt 2

/* Register ------------------------------------------------------------------*/
#define W1_MIKROBUS_ID_READ_EEPROM		0x69
#define W1_MIKROBUS_ID_RELEASE_EEPROM	0xAA
#define W1_MIKROBUS_ID_EEPROM_PAGE_SIZE 32

/* Data Structure ------------------------------------------------------------*/
#define DS28E36_FAMILY_CODE 0xCC

typedef struct {
	uint8_t DevAddr[DS28E36_MaxCnt][8];
} DS28E36_Drv_t;

/* External Function ---------------------------------------------------------*/
uint8_t		   DS28E36_Init(DS28E36_Drv_t *DS, OneWire_t *OW);
const uint8_t *DS28E36_ReadPage(OneWire_t *OW, const uint8_t *ROM, uint8_t page);

#ifdef __cplusplus
}
#endif

#endif /* DS28E36_H */
