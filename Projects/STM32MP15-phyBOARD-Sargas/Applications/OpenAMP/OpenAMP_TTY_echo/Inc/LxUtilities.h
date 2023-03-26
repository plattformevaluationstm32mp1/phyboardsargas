/**************************************************************************************************/
/**
 * @file        LxUtilities.h
 *
 * @brief       Contains the definition of the module.
 *
 * @remarks     See @ref LxUtilities for module description.
 *
 ***************************************************************************************************
 * @copyright
 *
 * <h2><center>&copy; COPYRIGHT 2021 blum</center></h2>
 **************************************************************************************************/
#ifndef LXUTILITIES_H
#define LXUTILITIES_H

/** \cond */
#include "stdint.h"
#include "stdbool.h"
/** \endcond */

#ifdef LXASSERT_ENABLE
    #include "L0Assert.h"
#else
    #define L0ASSERT_vERROR(expr)
    #define L0ASSERT_vWARNING(expr)
#endif


/** @addtogroup SD_BaseLx
  * @{
  */

/** @addtogroup SD_BaseLx_Libraries  Libraries
  * @{
  */

/** @addtogroup LxUtilities
  * @{
  *
  * @brief      Common used utilities.
  *
  * @remarks    Dieses modul stellt diverse Hilfsfunktionen zur verfügung. Die wichtigsten
  *             Funktionsgruppen sind:
  *             - Bitoperationen auf Variablen (Bits setzten, löschen, lesen, invertieren,
  *               Bitreihenfolge spiegeln MSB <-> LSB, Schiebeoperationen).
  *             - einzelne Bytes / Nibbels aus einer Variable lesen / schreiben bzw. die Reihenfolge
  *               umtauschen.
  *             - Bool zu string konvertieren.
  *             - Aufsplitten einer uint32_t Variable in Array von uint8_t Variablen.
  *             - Konvertierung von uint8_t zu hex.
  *             - Hilfsmakros für das Arbeiten mit Arrays (Anzahl Elemente bestimmen, Element setzten / lesen)
  */

/************************************ public defines **********************************************/
/************************************ public typedef **********************************************/
typedef struct {
    uint8_t u8Digits[2u];
} LxUtilities_Hex8Struct_t;

/************************************ public macros ***********************************************/
#define LXUTILITIES_u32ARRAYENTRIES(array) \
    ((uint32_t)(sizeof(array) / sizeof(array[0u])))      /**< Determines the number of array elements */

#ifndef UNIT_TEST  
#define LXUTILITIES_GETELEMENT(array, index, valuePtr) \
    /*lint -save -e685 -e587 -e568*/\
    _Pragma("diag_suppress 186") \
    {L0ASSERT_vERROR(index >= 0 && (uint32_t)index < LXUTILITIES_u32ARRAYENTRIES(array)); \
    _Pragma("diag_default 186") \
    /*lint -restore*/\
    *valuePtr = array[index];} 
    /**< set array element with bounds check */
#else    /**< get array element with bounds check */
#define LXUTILITIES_GETELEMENT(array, index, valuePtr) {*valuePtr = array[index];}  
#ifndef UNIT_TEST
#warning LXUTILITIES_GETELEMENT bounds check deactivated.
#endif
#endif
    
#ifndef UNIT_TEST    
#define LXUTILITIES_SETELEMENT(array, index, valuePtr) \
    /*lint -save -e685 -e587 -e568*/\
    _Pragma("diag_suppress 186") \
    {L0ASSERT_vERROR(index >= 0 && (uint32_t)index < LXUTILITIES_u32ARRAYENTRIES(array)); \
    _Pragma("diag_default 186") \
    /*lint -restore*/\
    array[index] = valuePtr;}   
    /**< set array element with bounds check */
#else
#define LXUTILITIES_SETELEMENT(array, index, valuePtr) {array[index] = valuePtr;}  
#ifndef UNIT_TEST
#warning LXUTILITIES_SETELEMENT bounds check deactivated.
#endif
#endif

/************************************ public const ************************************************/
/************************************ public variables ********************************************/
/************************************ public function declaration *********************************/

const char *LxUtilities_pcBoolToString(bool bValue);
const char *LxUtilities_pcBoolToOkString(bool bValue);
const char *LxUtilities_pcBoolToLevelString(bool bValue);
const char *LxUtilities_pcBoolToNumberString(bool bValue);
const char *LxUtilities_pcBoolToDecisionString(bool bValue);
const char *LxUtilities_pcBoolToStatusString(bool bValue);

/*Konvertierung hex to uint8_t, uint8_t to hex*/
bool LxUtilities_bHexToUint8(const LxUtilities_Hex8Struct_t stHex8Input, uint8_t *const pu8Result);
void LxUtilities_vUint8ToHex(uint8_t u8Input, LxUtilities_Hex8Struct_t *const pstHex8Result);

bool LxUtilities_bHexToUint8Array(const LxUtilities_Hex8Struct_t astHex8Input[], uint8_t au8Result[], uint32_t u32ArrayLength);
void LxUtilities_vUint8ArrayToHex(const uint8_t au8Input[], LxUtilities_Hex8Struct_t astHex8Result[], uint32_t u32ArrayLength);

void LxUtilities_vUint32ToArray(uint32_t u32Value, uint8_t au8Result[], uint8_t u8ArrayLength);
uint32_t LxUtilities_u32ArrayToUint32(uint8_t *pu8Data, uint8_t u8ArrayLength);

bool LxUtilities_bSelfTest(void);
                                                       
/*****************************************************/
/* Reading Operations                                */
/*****************************************************/
/* Reading Bits */
__forceinline  uint8_t LxUtilities_u8GetBit(uint8_t u8FlagField, uint8_t u8BitNumber);
__forceinline  uint16_t LxUtilities_u16GetBit(uint16_t u16FlagField, uint8_t u8BitNumber);
__forceinline  uint32_t LxUtilities_u32GetBit(uint32_t u32FlagField, uint8_t u8BitNumber);

__forceinline  uint8_t LxUtilities_u8GetBits(uint8_t u8FlagField, uint8_t u8BitMask);
__forceinline  uint16_t LxUtilities_u16GetBits(uint16_t u16FlagField, uint16_t u16BitMask);
__forceinline  uint32_t LxUtilities_u32GetBits(uint32_t u32FlagField, uint32_t u32BitMask);

/* Reading nibble, byte and word*/
__forceinline  uint8_t LxUtilities_u8GetHighNibble(uint8_t u8FlagField);
__forceinline  uint8_t LxUtilities_u8GetHighByte(uint16_t u16FlagField);
__forceinline  uint16_t LxUtilities_u16GetHighWord(uint32_t u32FlagField);

__forceinline  uint8_t LxUtilities_u8GetLowNibble(uint8_t u8FlagField);
__forceinline  uint8_t LxUtilities_u8GetLowByte(uint16_t u16FlagField);
__forceinline  uint16_t LxUtilities_u16GetLowWord(uint32_t u32FlagField);

/*****************************************************/
/* Modifying Operations                              */
/*****************************************************/
/* Setting  bits */
__forceinline void LxUtilities_vSetBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber);
__forceinline void LxUtilities_vSetBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber);
__forceinline void LxUtilities_vSetBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber);

__forceinline void LxUtilities_vSetBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask);
__forceinline void LxUtilities_vSetBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask);
__forceinline void LxUtilities_vSetBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask);

/* Clearing bits */
__forceinline void LxUtilities_vClearBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber);
__forceinline void LxUtilities_vClearBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber);
__forceinline void LxUtilities_vClearBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber);

__forceinline void LxUtilities_vClearBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask);
__forceinline void LxUtilities_vClearBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask);
__forceinline void LxUtilities_vClearBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask);

/* Toggling bits */
__forceinline  void LxUtilities_vInvertBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber);
__forceinline  void LxUtilities_vInvertBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber);
__forceinline  void LxUtilities_vInvertBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber);

__forceinline  void LxUtilities_vInvertBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask);
__forceinline  void LxUtilities_vInvertBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask);
__forceinline  void LxUtilities_vInvertBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask);

/*  Writing true or false to a single bit  */
void LxUtilities_vSetBitStateU8(uint8_t *pu8FlagField, uint8_t u8BitNumber, bool bBitValue);
void LxUtilities_vSetBitStateU16(uint16_t *pu16FlagField, uint8_t u8BitNumber, bool bBitValue);
void LxUtilities_vSetBitStateU32(uint32_t *pu32FlagField, uint8_t u8BitNumber, bool bBitValue);

/* Writing nibbles, bytes and words */
__forceinline void LxUtilities_vSetLowByte(uint16_t *pu16FlagField, uint8_t u8LowByte);
__forceinline void LxUtilities_vSetHighByte(uint16_t *pu16FlagField, uint8_t u8HighByte);
__forceinline void LxUtilities_vSetLowWord(uint32_t *pu32FlagField, uint16_t u16LowWord);
__forceinline void LxUtilities_vSetHighWord(uint32_t *pu32FlagField, uint16_t u16HighWord);

/* Shifting operations */
__forceinline void LxUtilities_vShiftRightU8(uint8_t *pu8FlagField, uint8_t u8Positions);
__forceinline void LxUtilities_vShiftRightU16(uint16_t *pu16FlagField, uint8_t u8Positions);
__forceinline void LxUtilities_vShiftRightU32(uint32_t *pu32FlagField, uint8_t u8Positions);

__forceinline void LxUtilities_vShiftLeftU8(uint8_t *pu8FlagField, uint8_t u8Positions);
__forceinline void LxUtilities_vShiftLeftU16(uint16_t *pu16FlagField, uint8_t u8Positions);
__forceinline void LxUtilities_vShiftLeftU32(uint32_t *pu32FlagField, uint8_t u8Positions);

/* Changing bit, byte and word order */
void LxUtilities_vMirrorBitsU8(uint8_t *pu8FlagField);
void LxUtilities_vMirrorBitsU16(uint16_t *pu16FlagField);
void LxUtilities_vMirrorBitsU32(uint32_t *pu32FlagField);
void LxUtilities_vMirrorBitsU64(uint64_t *pu64FlagField);

__forceinline void LxUtilities_vSwapBytesU16(uint16_t *pu16FlagField);
__forceinline void LxUtilities_vSwapBytesU32(uint32_t *pu32FlagField);
__forceinline void LxUtilities_vSwapBytesU64(uint64_t *pu64FlagField);

__forceinline void LxUtilities_vSwapWordsU32(uint32_t *pu32FlagField);
__forceinline void LxUtilities_vSwapWordsU64(uint64_t *pu64FlagField);

/*****************************************************/
/* Combined operations: read and then modify         */
/*****************************************************/
__forceinline uint8_t LxUtilities_u8GetAndClearBit(uint8_t *pu8FlagField, uint8_t u8BitNumber);
__forceinline uint16_t LxUtilities_u16GetAndClearBit(uint16_t *pu16FlagField, uint8_t u8BitNumber);
__forceinline uint32_t LxUtilities_u32GetAndClearBit(uint32_t *pu32FlagField, uint8_t u8BitNumber);

__forceinline uint8_t LxUtilities_u8GetAndClearBits(uint8_t *pu8FlagField, uint8_t u8BitMask);
__forceinline uint16_t LxUtilities_u16GetAndClearBits(uint16_t *pu16FlagField, uint16_t u16BitMask);
__forceinline uint32_t LxUtilities_u32GetAndClearBits(uint32_t *pu32FlagField, uint32_t u32BitMask);

/**************************************************************************************************/
/********************************* public inline function definition ******************************/
/**************************************************************************************************/
/*lint -save -e695*/
/**************************************************************************************************/
/**
 * @brief           Get the low nibble (4bit) of a 8bit value.
 *
 * @remarks         Example: 0xBE --> 0x0E
 *
 * @param[in]       u8FlagField: 8bit value to get the low nibble from.
 *                  \n [Range: 0..255]
 *
 * @return          Low nibble of the 8bit value.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetLowNibble(uint8_t u8FlagField) {

    return (uint8_t)(0x0Fu & u8FlagField);
}

/**************************************************************************************************/
/**
 * @brief           Get the high nibble (4bit) of a 8bit value.
 *
 * @remarks         Example: 0xBE --> 0x0B
 *
 * @param[in]       u8FlagField: 8bit value to get the high nibble from.
 *                  \n [Range: 0..255]
 *
 * @return          High nibble of the 8bit value.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetHighNibble(uint8_t u8FlagField) {

    return (uint8_t)(0x0Fu & (u8FlagField >> 4u));
}

/**************************************************************************************************/
/**
 * @brief           Get the low byte of a 16bit value.
 *
 * @remarks         Example: 0xBEEF --> 0xEF
 *
 * @param[in]       u16FlagField: 16bit value to get the low byte from.
 *                  \n [Range: 0..65535]
 *
 * @return          Low byte of the 16bit value.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetLowByte(uint16_t u16FlagField) {

    return (uint8_t)(0x00FFu & u16FlagField);
}

/**************************************************************************************************/
/**
 * @brief           Set the low byte of a 16bit value.
 *
 * @remarks         Example: 0xBE55, 0xEF --> 0xBEEF
 *
 * @param[in]       pu16FlagField: pointer to 16bit value to set the low byte to.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u8LowByte: Byte to set at the low byte position.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetLowByteU16(uint16_t *pu16FlagField, uint8_t u8LowByte) {

    *pu16FlagField = ((*pu16FlagField & 0xFF00u) | (uint16_t)u8LowByte);
}

/**************************************************************************************************/
/**
 * @brief           Get the high byte of a 16bit value.
 *
 * @remarks         Example: 0xBEEF --> 0xBE
 *
 * @param[in]       u16FlagField: 16bit value to get the high byte from.
 *                  \n [Range: 0..65535]
 *
 * @return          High byte of the 16bit value.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetHighByte(uint16_t u16FlagField) {

    return (uint8_t)(0x00FFu & (u16FlagField >> 8u));
}

/**************************************************************************************************/
/**
 * @brief           Set the high byte of a 16bit value.
 *
 * @remarks         Example: 0x55EF, 0xBE --> 0xBEEF
 *
 * @param[in,out]   pu16FlagField: 16bit value to set the high byte to.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u8HighByte: Byte to set at the high byte position.
 *                  \n [Range: 0..255]
 *
 * @return          16bit value with set high byte.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetHighByteU16(uint16_t *pu16FlagField, uint8_t u8HighByte) {

    *pu16FlagField = (uint16_t)((*pu16FlagField & 0x00FFu) | (((uint16_t)u8HighByte << 8u) & 0xFF00u));
}

/**************************************************************************************************/
/**
 * @brief           Get the low word of a 32bit value.
 *
 * @remarks         Example: 0xDEADBEEF --> 0xBEEF
 *
 * @param[in]       u32FlagField: 32bit value to get the low word from.
 *                  \n [Range: 0..4294967295]
 *
 * @return          Low word of the 32bit value.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetLowWord(uint32_t u32FlagField) {

    return (uint16_t)(0x0000FFFFu & u32FlagField);
}

/**************************************************************************************************/
/**
 * @brief           Set the low word of a 32bit value.
 *
 * @remarks         Example: 0xDEAD5555, 0xBEEF --> 0xDEADBEEF
 *
 * @param[in,out]   pu32FlagField: 32bit value to set the low word to.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u16LowWord: Word to set at the low word position.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetLowWord(uint32_t *pu32FlagField, uint16_t u16LowWord) {

    *pu32FlagField = ((*pu32FlagField & 0xFFFF0000u) | (uint32_t)u16LowWord);
}

/**************************************************************************************************/
/**
 * @brief           Get the high word of a 32bit value.
 *
 * @remarks         Example: 0xDEADBEEF --> 0xDEAD
 *
 * @param[in]       u32FlagField: 32bit value to get the high word from.
 *                  \n [Range: 0..4294967295]
 *
 * @return          High word of the 32bit value.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetHighWord(uint32_t u32FlagField) {

    return (uint16_t)(0x0000FFFFu & (u32FlagField >> 16u));
}

/**************************************************************************************************/
/**
 * @brief           Set the high word of a 32bit value.
 *
 * @remarks         Example: 0x5555BEEF, 0xDEAD --> 0xDEADBEEF
 *
 * @param[in]       pu32FlagField: 32bit value to set the high word to.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u16HighWord: Word to set at the high word position.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetHighWord(uint32_t *pu32FlagField, uint16_t u16HighWord) {

    *pu32FlagField = (*pu32FlagField & 0x0000FFFFu) | (((uint32_t)u16HighWord << 16u) & 0xFFFF0000u);
}

/**************************************************************************************************/
/**
 * @brief           Swaps the two bytes of a 16Bit value.
 *                  \n Byte order: 21 --> 12
 *
 * @remarks         Example: 0xFECA --> 0xCAFE
 *
 * @param[in,out]   pu16FlagField: 16Bit value to swap.
 *                  \n [Range: 0..65535]
 *
 * @return          16Bit value with swapped bytes.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSwapBytesU16(uint16_t *pu16FlagField) {

    *pu16FlagField = (uint16_t)(((*pu16FlagField << 8u) & (uint16_t)0xFF00u) | ((*pu16FlagField >> 8u) & (uint16_t)0x00FFu));
}

/**************************************************************************************************/
/**
 * @brief           Swaps the four bytes of a 32Bit value.
 *                  \n Byte order: 4321 --> 1234
 *
 * @remarks         Example: 0xEFBEADDE --> 0xDEADBEEF
 *
 * @param[in]       pu32FlagField: pointer 32Bit value to swap order.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSwapBytesU32(uint32_t *pu32FlagField) {
    uint32_t u32Temp = 0u;

    u32Temp = ((*pu32FlagField << 8u) & 0xFF00FF00u) | ((*pu32FlagField >> 8u) & 0x00FF00FFu);
    *pu32FlagField = ((u32Temp << 16u) & 0xFFFF0000u) | ((u32Temp >> 16u) & 0x0000FFFFu);
}

/**************************************************************************************************/
/**
 * @brief           Swaps the eight bytes of a 64Bit value.
 *                  \n Byte order: 87654321 --> 12345678
 *
 * @remarks         Example: 0xFE11D5AD1AC0CAC0 --> 0xC0CAC01AADD511FE
 *
 * @param[in,out]   pu64FlagField: 64Bit value to swap.
 *                  \n [Range: 0..18446744073709551615]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSwapBytesU64(uint64_t *pu64FlagField) {
    uint64_t u64Temp = 0u;

    u64Temp = ((*pu64FlagField << 8u) & 0xFF00FF00FF00FF00uLL) | ((*pu64FlagField >> 8u) & 0x00FF00FF00FF00FFuLL);
    u64Temp = ((u64Temp << 16u) & 0xFFFF0000FFFF0000uLL) | ((u64Temp >> 16u) & 0x0000FFFF0000FFFFuLL);
    *pu64FlagField = ((u64Temp << 32u) & 0xFFFFFFFF00000000uLL) | ((u64Temp >> 32u) & 0x00000000FFFFFFFFuLL);
}

/**************************************************************************************************/
/**
 * @brief           Swaps the two words of a 32Bit value.
 *                  \n Byte order: 4321 --> 2143
 *
 * @remark          Example: 0xBEEFDEAD --> 0xDEADBEEF
 *
 * @param[in]       pu32FlagField: 32Bit value to swap.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSwapWordsU32(uint32_t *pu32FlagField) {

    *pu32FlagField = ((*pu32FlagField << 16u) & 0xFFFF0000u) | ((*pu32FlagField >> 16u) & 0x0000FFFFu);
}

/**************************************************************************************************/
/**
 * @brief           Swaps the four words of a 64Bit value.
 *                  \n Byte order: 87654321 --> 21436587
 *
 * @remarks         Example: 0x11FEADD5C01AC0CA --> 0xC0CAC01AADD511FE
 *
 * @param[in,out]   pu64FlagField: 64Bit value to swap.
 *                  \n [Range: 0..18446744073709551615]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSwapWordsU64(uint64_t *pu64FlagField) {
    uint64_t u64Temp = 0u;

    u64Temp = ((*pu64FlagField << 16u) & 0xFFFF0000FFFF0000uLL) | ((*pu64FlagField >> 16u) & 0x0000FFFF0000FFFFuLL);
    *pu64FlagField = ((u64Temp << 32u) & 0xFFFFFFFF00000000uLL) | ((u64Temp >> 32u) & 0x00000000FFFFFFFFuLL);
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number.
 *
 * @remarks         -
 *
 * @param[in]       u8FlagField: Value to get bit from.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitNumber: number of bit to get
 *                  \n [Range: 0..7]
 *
 * @return          Value of single bit.
 *                  \n [Range: 0x00..0x80]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetBit(uint8_t u8FlagField, uint8_t u8BitNumber) {

    return (u8FlagField & (0x01u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number and clear it.
 *
 * @param[in,out]   pu8FlagField: pointer to value.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitNumber: number of bit to get
 *                  \n [Range: 0..7]
 *
 * @return          Value of single bit. Other Bits are 0.
 *                  \n [Range: 0x00..0x80]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetAndClearBit(uint8_t *pu8FlagField, uint8_t u8BitNumber) {

    uint8_t u8tmp   = ((*pu8FlagField) & (0x01u << u8BitNumber));
    *pu8FlagField  &= ~(0x01u << u8BitNumber);

    return (u8tmp);
}

/**************************************************************************************************/
/**
 * @brief           Inverts bit selected by a bit number.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: bit values.
 *                  \n [Range: 0x00..0xFF]
 *
 * @param[in]       u8BitNumber: number of bit to inverter
 *                  \n [Range: 0..7]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber) {

    *pu8FlagField = (*pu8FlagField ^ (0x01u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set a specific bit of given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: Value to set bit.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitNumber: Number of bit to be set.
 *                  \n [Range: 0..7]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber) {

    *pu8FlagField = (*pu8FlagField | (1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Clear a specific bit of a given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: Value to clear bit.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitNumber: number of bit to be cleared.
 *                  \n [Range: 0..7]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitU8(uint8_t *pu8FlagField, uint8_t u8BitNumber) {

    *pu8FlagField = (*pu8FlagField & ~(1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: Value to set bits.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitMask: Set bit mask.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask) {

    *pu8FlagField  = (*pu8FlagField | u8BitMask);
}

/**************************************************************************************************/
/**
 * @brief           Clear bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: Value to clear bits.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitMask: Clear bit mask.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask) {

    *pu8FlagField = (*pu8FlagField & ~u8BitMask);
}

/**************************************************************************************************/
/**
 * @brief           Invert bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in]       pu8FlagField: Value to invert bits.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitMask: Invert bit mask.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitsU8(uint8_t *pu8FlagField, uint8_t u8BitMask) {

    *pu8FlagField = *pu8FlagField ^ u8BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   u8FlagField: Value to get bits.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitMask: Get bit mask.
 *                  \n [Range: 0..255]
 *
 * @return          Modified value.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetBits(uint8_t u8FlagField, uint8_t u8BitMask) {

    return  u8FlagField & u8BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get and clear bits selected by a bitmask.
 *
 * @remarks         Return value like u8GetBits, Pointer to clear bits of parameter directly
 *
 * @param[in,out]   pu8FlagField: Value to get and clear bits.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8BitMask: Get and clear bit mask.
 *                  \n [Range: 0..255]
 *
 * @return          Modified value.
 *                  \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint8_t LxUtilities_u8GetAndClearBits(uint8_t *pu8FlagField, uint8_t u8BitMask) {
    uint8_t u8Retval = 0u;

    u8Retval =  *pu8FlagField & u8BitMask;
    *pu8FlagField =  *pu8FlagField & ~u8BitMask;

    return u8Retval;
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number.
 *
 * @remarks         -
 *
 * @param[in]       u16FlagField: Value to get bit from.
 *                  \n [Range: 0x0000 .. 0xFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to get.
 *                  \n [Range: 0..15]
 *
 * @return          Value of single bit.
 *                  \n [Range: 0x0000..0x8000]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetBit(uint16_t u16FlagField, uint8_t u8BitNumber) {

    return (u16FlagField & (0x0001u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number and clear it.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: pointer to value.
 *                  \n [Range: 0x0000..0xFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to get
 *                  \n [Range: 0..15]
 *
 * @return          Value of single bit. Other Bits are 0.
 *                  \n [Range: 0x0000..0x8000]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetAndClearBit(uint16_t *pu16FlagField, uint8_t u8BitNumber) {

    uint16_t u16Tmp  = ((*pu16FlagField) & (0x0001u << u8BitNumber));
    *pu16FlagField  &= ~(0x0001u << u8BitNumber);

    return (u16Tmp);
}

/**************************************************************************************************/
/**
 * @brief           Inverts bit selected by a bit number.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: bit values.
 *                  \n [Range: 0x0000 .. 0xFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to inverter
 *                  \n [Range: 0..15]
 *
 * @return          u16FlagField with inverted bit at u8BitNumber - position.
 *                  \n [Range: 0x0000 .. 0xFFFF]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber) {

    *pu16FlagField = (*pu16FlagField ^ (0x0001u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set a specific bit of given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: pointer to variable to set bit.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u8BitNumber: Number of bit to be set.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber) {

    *pu16FlagField =  (*pu16FlagField | (1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Clear a specific bit of a given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Pointer to Value to clear bit.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u8BitNumber: number of bit to be cleared.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitU16(uint16_t *pu16FlagField, uint8_t u8BitNumber) {

    *pu16FlagField =(*pu16FlagField & ~(1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to set bits.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u16BitMask: Set bit mask.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask) {

    *pu16FlagField = *pu16FlagField | u16BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Clear bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to clear bits.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u16BitMask: Clear bit mask.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask) {

    *pu16FlagField = *pu16FlagField & ~u16BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Invert bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to invert bits.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u16BitMask: Invert bit mask.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitsU16(uint16_t *pu16FlagField, uint16_t u16BitMask) {

    *pu16FlagField = *pu16FlagField ^ u16BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in]       u16FlagField: Value to get bits.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u16BitMask: Get bit mask.
 *                  \n [Range: 0..65535]
 *
 * @return          Modified value.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetBits(uint16_t u16FlagField, uint16_t u16BitMask) {

    return  u16FlagField & u16BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get and clear bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to get and clear bits.
 *                  \n [Range: 0..65535]
 *
 * @param[in]       u16BitMask: Get and clear bit mask.
 *                  \n [Range: 0..65535]
 *
 * @return          Modified value.
 *                  \n [Range: 0..65535]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint16_t LxUtilities_u16GetAndClearBits(uint16_t *pu16FlagField, uint16_t u16BitMask) {
    uint16_t u16Retval = 0u;

    u16Retval =  *pu16FlagField & u16BitMask;
    *pu16FlagField =  *pu16FlagField & ~u16BitMask;

    return u16Retval;
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number.
 *
 * @remarks         -
 *
 * @param[in]       u32FlagField: Value to get bit from.
 *                  \n [Range: 0x00000000 .. 0xFFFFFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to get.
 *                  \n [Range: 0..31]
 *
 * @return          Value of single bit.
 *                  \n [Range: 0x00000000..0x80000000]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint32_t LxUtilities_u32GetBit(uint32_t u32FlagField, uint8_t u8BitNumber) {

    return (u32FlagField & (0x00000001u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Get bit selected by a bit number and clear it.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: pointer to value.
 *                  \n [Range: 0x00000000..0xFFFFFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to get.
 *                  \n [Range: 0..31]
 *
 * @return          Value of single bit.
 *                  \n [Range: 0x00000000..0x80000000]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint32_t LxUtilities_u32GetAndClearBit(uint32_t *pu32FlagField, uint8_t u8BitNumber) {

    uint32_t u32Tmp  = ((*pu32FlagField) & (0x00000001u << u8BitNumber));
    *pu32FlagField &= ~(0x00000001u << u8BitNumber);

    return (u32Tmp);
}

/**************************************************************************************************/
/**
 * @brief           Invert bit selected by a bit number
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField:  bit values.
 *                  \n [Range: 0x00000000..0xFFFFFFFF]
 *
 * @param[in]       u8BitNumber: number of bit to invert.
 *                  \n [Range: 0..31]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber) {

    *pu32FlagField = (*pu32FlagField ^ (0x00000001u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Clear a specific bit of a given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to clear bit.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u8BitNumber: Number of bit to be cleared.
 *                  \n [Range: 0..31]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber) {

    *pu32FlagField = (*pu32FlagField & ~(1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set a specific bit of given parameter.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to set bit.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u8BitNumber: Number of bit to be set.
 *                  \n [Range: 0..31]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitU32(uint32_t *pu32FlagField, uint8_t u8BitNumber) {

    *pu32FlagField = (*pu32FlagField | (1u << u8BitNumber));
}

/**************************************************************************************************/
/**
 * @brief           Set bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to set bits.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u32BitMask: Set bit mask.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vSetBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask) {

    *pu32FlagField = *pu32FlagField | u32BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Clear bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in]       pu32FlagField: Value to clear bits.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u32BitMask: Clear bit mask.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vClearBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask) {

    *pu32FlagField = *pu32FlagField & ~u32BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Invert bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to invert bits.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u32BitMask: Invert bit mask.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vInvertBitsU32(uint32_t *pu32FlagField, uint32_t u32BitMask) {

    *pu32FlagField = *pu32FlagField ^ u32BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   u32FlagField: Value to get bits.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u32BitMask: Get bit mask.
 *                  \n [Range: 0..4294967295]
 *
 * @return          Modified value.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint32_t LxUtilities_u32GetBits(uint32_t u32FlagField, uint32_t u32BitMask) {

    return  u32FlagField & u32BitMask;
}

/**************************************************************************************************/
/**
 * @brief           Get and clear bits selected by a bitmask.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to get and clear bits.
 *                  \n [Range: 0..4294967295]
 *
 * @param[in]       u32BitMask: Get and clear bit mask.
 *                  \n [Range: 0..4294967295]
 *
 * @return          Modified value.
 *                  \n [Range: 0..4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline uint32_t LxUtilities_u32GetAndClearBits(uint32_t *pu32FlagField, uint32_t u32BitMask) {
    uint32_t u32Retval;

    u32Retval =  *pu32FlagField & u32BitMask;
    *pu32FlagField =  *pu32FlagField & ~u32BitMask;

    return u32Retval;
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the right
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: Value to shift
 *                  \n [Range: 0x00..0xFF]
 *
 * @param[in]       u8Positions: number of positions to shift.
 *                  \n if u8Position > 7 operation is skipped.
 *                  \n [Range: 0..7]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftRightU8(uint8_t *pu8FlagField, uint8_t u8Positions) {

    *pu8FlagField = (*pu8FlagField >> u8Positions);
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the right
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to shift
 *                  \n [Range: 0x0000..0xFFFF]
 *
 * @param[in]       u8Positions: number of positions to shift
 *                  \n if u8Position > 15 operation is skipped.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftRightU16(uint16_t *pu16FlagField, uint8_t u8Positions) {

    *pu16FlagField = (*pu16FlagField >> u8Positions);
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the right
 *
 * @remarks         -
 *
 * @param[in,out]   *pu32FlagField: Value to shift
 *                  \n [Range: 0x00000000..0xFFFFFFFF]
 *
 * @param[in]       u8Positions: number of positions to shift
 *                  \n if u8Position > 31 operation is skipped.
 *                  \n [Range: 0..31]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftRightU32(uint32_t *pu32FlagField, uint8_t u8Positions) {

    *pu32FlagField = (*pu32FlagField >> u8Positions);
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the left
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField: value to shift
 *                  \n [Range: 0x00..0xFF]
 *
 * @param[in]       u8Positions: number of positions to shift
 *                  \n if u8Position > 7 operation is skipped.
 *                  \n [Range: 0..7]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftLeftU8(uint8_t *pu8FlagField, uint8_t u8Positions) {

    *pu8FlagField = (*pu8FlagField << u8Positions);
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the left
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField: Value to shift
 *                  \n [Range: 0x0000..0xFFFF]
 *
 * @param[in]       u8Positions: number of positions to shift
 *                  \n if u8Position > 15 operation is skipped.
 *                  \n [Range: 0..15]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftLeftU16(uint16_t *pu16FlagField, uint8_t u8Positions) {

    *pu16FlagField = (*pu16FlagField << u8Positions);
}

/**************************************************************************************************/
/**
 * @brief           Shift a value to the left
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField: Value to shift
 *                  \n [Range: 0x00000000..0xFFFFFFFF]
 *
 * @param[in]       u8Positions: number of positions to shift
 *                  \n if u8Position > 31 operation is skipped.
 *                  \n [Range: 0..31]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
__forceinline void LxUtilities_vShiftLeftU32(uint32_t *pu32FlagField, uint8_t u8Positions) {

    *pu32FlagField =(*pu32FlagField << u8Positions);
}

/*lint -restore*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif  /*LXUTILITIES_H*/
