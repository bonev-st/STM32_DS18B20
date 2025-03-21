/**
 ******************************************************************************
 * @file    ds28e36.c
 * @brief   This file includes the HAL/LL driver for DS28E36 1-Wire
 * 		  DeepCover Secure Authenticator
 ******************************************************************************
 */
#include "ds28e36.h"

#include <assert.h>

static uint8_t PageData[W1_MIKROBUS_ID_EEPROM_PAGE_SIZE];

/**
 * @brief  The function is used to check valid DS28E36 ROM
 * @retval Return in OK = 1, Failed = 0
 * @param  ROM		Pointer to ROM number
 */
uint8_t DS28E36_IsValid(const uint8_t *ROM) {
	/* Checks if first byte is equal to DS28E36's family code */
	return (*ROM == DS28E36_FAMILY_CODE) ? 1 : 0;
}

/**
 * @brief  The function is used to initialize the DS28E36, and search
 * 		for all ROM along the line. Store in DS28E36 data structure
 * @retval Rom detect status, OK = 1, No Rom detected = 0
 * @param  DS			DS28E36 HandleTypedef
 * @param  OW			DS28E36 HandleTypedef
 */
uint8_t DS28E36_Init(DS28E36_Drv_t *DS, OneWire_t *OW) {
	/* Initialize OneWire and reset all data */
	OneWire_Init(OW);

	/* Search all OneWire devices ROM */
	while (1) {
		/* Start searching for OneWire devices along the line */
		if (OneWire_Search(OW, ONEWIRE_CMD_SEARCHROM) != 1) {
			break;
		}

		/* Get device ROM */
		OneWire_GetDevRom(OW, DS->DevAddr[OW->RomCnt]);

		OW->RomCnt++;
	}

	return (OW->RomCnt != 0) ? 1 : 0;
}

/**
 * @brief  The function is used as read bit from device and store in selected
 * 		destination
 * @retval status in OK = 1, Failed = 0
 * @param  OW				OneWire HandleTypedef
 * @param  ROM				Pointer to ROM number
 * @param  page				Page numbre
 * @return *data			Page data - 32 bytes
 */
const uint8_t *DS28E36_ReadPage(OneWire_t *OW, const uint8_t *ROM, uint8_t page) {
	/* Check if device is DS28E36 */
	if (!DS28E36_IsValid(ROM)) return 0;

	/* Wait until line is released, then coversion is completed */
	while (!OneWire_ReadBit(OW)) {
	};

	/* Reset line */
	OneWire_Reset(OW);

	/* Select ROM number */
	OneWire_SelectWithPointer(OW, ROM);

	OneWire_WriteByte(OW, W1_MIKROBUS_ID_READ_EEPROM);
	OneWire_WriteByte(OW, page);

	volatile uint8_t crc_rdbuf[2];
	for (uint8_t i = 0; i < 2; i++) {
		/* Read byte by byte */
		crc_rdbuf[i] = OneWire_ReadByte(OW);
	}

	OneWire_WriteByte(OW, W1_MIKROBUS_ID_RELEASE_EEPROM);

	OneWire_DelayMS(10);
	crc_rdbuf[0] = OneWire_ReadByte(OW);
	for (uint8_t i = 0; i < W1_MIKROBUS_ID_EEPROM_PAGE_SIZE; i++) {
		/* Read byte by byte */
		PageData[i] = OneWire_ReadByte(OW);
	}

	for (uint8_t i = 0; i < 2; i++) {
		/* Read byte by byte */
		crc_rdbuf[i] = OneWire_ReadByte(OW);
	}

	return PageData;
}
