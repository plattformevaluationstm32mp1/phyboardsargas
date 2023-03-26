/**************************************************************************************************/
/**
 * @file        LxUtilities.c
 *
 * @brief       Contains the implementation of the module.
 *
 * @remarks     See @ref LxUtilitiesInternal for explanation of implementation detail.
 *
 ***************************************************************************************************
 * @copyright
 *
 * <h2><center>&copy; COPYRIGHT 2021 blum</center></h2>
 **************************************************************************************************/
#include "LxUtilities.h"
#include "LxMath.h"

/** \cond */
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
/** \endcond */


/** @ingroup    LxUtilities
  * @addtogroup LxUtilitiesInternal  LxUtilities - Internal
  * @{
  *
  * @brief      No internal documentation see @ref LxUtilities for module description.
  *
  * @remarks    -
  *
  */

/************************************ private defines *********************************************/
/************************************ private typedef *********************************************/
/************************************ private macros **********************************************/
/************************************ private const ***********************************************/
/************************************ private variables *******************************************/
/************************************ private function declaration ********************************/
/**************************************************************************************************/
/************************************ private function definition *********************************/
/**************************************************************************************************/
/**************************************************************************************************/
/************************************ public function definition **********************************/
/**************************************************************************************************/

/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "true" or "false"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string.
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToString(bool bValue) {

    return ((bValue) ? "true" : "false");
}

/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "ok" or "error"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string. true: "ok" false: "error"
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToOkString(bool bValue) {

    return ((bValue) ? "ok" : "error");
}

/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "high" or "low"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string. true: "high" false: "low"
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToLevelString(bool bValue) {

    return ((bValue) ? "high" : "low");
}

/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "1" or "0"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string. true: "1" false: "0"
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToNumberString(bool bValue) {

    return ((bValue) ? "1" : "0");
}



/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "ON" or "OFF"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string. true: "ON" false: "OFF"
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToStatusString(bool bValue) {

    return ((bValue) ? "on" : "off");
}

/**************************************************************************************************/
/**
 * @brief           Converts a boolean to a printable string. "YES" or "NO"
 *
 * @remarks         -
 *
 * @param[in]       bValue: Booloan value.
 *                  \n [Range: true, false]
 *
 * @return          Boolean value as string. true: "YES" false: "NO"
 *                  \n [Range: Zero terminated string]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
const char *LxUtilities_pcBoolToDecisionString(bool bValue) {

    return ((bValue) ? "yes" : "no");
}

/**************************************************************************************************/
/**
 * @brief           Converts a hex8 value into a uint8_t value.
 *
 * @remarks         -
 *
 * @param[in]       stHex8Input: Hex8 value to convert. Each digit is in ascii format.
 *                  \n [Range: '0'..'9', 'a'..'f', 'A'..'F']
 *
 * @param[out]      pu8Result: Converted data.
 *                  \n [Range: 0..255]
 *
 * @return          bValidConversion: Result of the conversion
 *                  \n - true: ok
 *                  \n - false: conversion error. Invalid hex8 input data.
 *                  \n [Range: false, true]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
bool LxUtilities_bHexToUint8(const LxUtilities_Hex8Struct_t stHex8Input, uint8_t *const pu8Result) {
    L0ASSERT_vERROR(pu8Result != NULL);

    uint8_t u8TempValue = 0u;
    bool bValidConversion = true;
    *pu8Result = 0u;

    for (uint8_t u8Index = 0u; u8Index < 2u; u8Index++) {
        u8TempValue = 0u;
/*lint -e48 -e56 -e409*/
        if ((stHex8Input.u8Digits[u8Index] >= (uint8_t)'0') && (stHex8Input.u8Digits[u8Index] <= (uint8_t)'9')) {
/*lint -e48 -e56 -e409*/
            u8TempValue = stHex8Input.u8Digits[u8Index] - 48u;
/*lint -e48 -e56 -e409*/
        } else if ((stHex8Input.u8Digits[u8Index] >= (uint8_t)'A') && (stHex8Input.u8Digits[u8Index] <= (uint8_t)'F')) {
/*lint -e48 -e56 -e409*/
            u8TempValue = stHex8Input.u8Digits[u8Index] - 55u;
/*lint -e48 -e56 -e409*/
        } else if ((stHex8Input.u8Digits[u8Index] >= (uint8_t)'a') && (stHex8Input.u8Digits[u8Index] <= (uint8_t)'f')) {
/*lint -e48 -e56 -e409*/
            u8TempValue = stHex8Input.u8Digits[u8Index] - 87u;
        } else {
            bValidConversion = false;
        }
        *pu8Result = ((*pu8Result << 4u) & 0xF0u) + u8TempValue;
    }
    return bValidConversion;
}

/**************************************************************************************************/
/**
 * @brief           Converts a uint8_t value into a hex8 value.
 *
 * @remarks         -
 *
 * @param[in]       u8Input: Value to convert.
 *                  \n [Range: 0..255]
 *
 * @param[out]      pstHex8Result: Array of hex digits in ascii format.
 *                  \n [Range: '0'..'9', 'A'..'F']
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vUint8ToHex(uint8_t u8Input, LxUtilities_Hex8Struct_t *const pstHex8Result) {
    L0ASSERT_vERROR(pstHex8Result != NULL);

    uint8_t u8LowNibble = u8Input & 0x0Fu;
    uint8_t u8HighNibble = (u8Input >> 4u) & 0x0Fu;
/*lint -e70*/
    ((uint8_t *)pstHex8Result->u8Digits)[0u] = (u8HighNibble < 10u) ? (48u + u8HighNibble) : (55u + u8HighNibble);
/*lint -e70*/
    ((uint8_t *)pstHex8Result->u8Digits)[1u] = (u8LowNibble < 10u) ? (48u + u8LowNibble) : (55u + u8LowNibble);
}

/**************************************************************************************************/
/**
 * @brief           Converts a hex8 array into a uint8_t array.
 *
 * @remarks         -
 *
 * @param[in]       astHex8Input: Data to convert. Each hex digits is in ascii format.
 *                  \n [Range: '0'..'9', 'a'..'f', 'A'..'F']
 *
 * @param[out]      au8Result: Converted data.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u32ArrayLength: Length of the input and result array. They must have the same length.
 *                  \n If u32ArrayLength is 0 function does nothing and returns true. 
 *                  \n [Range: 0..255]
 *
 * @return          bValidResult: Result of the conversion
 *                  \n - true: ok
 *                  \n - false: conversion error. Invalid hex input data.
 *                  \n [Range: true, false]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
bool LxUtilities_bHexToUint8Array(const LxUtilities_Hex8Struct_t astHex8Input[], uint8_t au8Result[], uint32_t u32ArrayLength) {
    L0ASSERT_vERROR(astHex8Input != NULL);
    L0ASSERT_vERROR(au8Result != NULL);

    uint32_t u32ValidCount = 0u;

    for (uint32_t u32Index = 0u; u32Index < u32ArrayLength; u32Index++) {
        if (LxUtilities_bHexToUint8((astHex8Input[u32Index]), &(au8Result[u32Index])) == true) {
            u32ValidCount++;
        }
    }

    return (u32ValidCount == u32ArrayLength ? true : false);
}

/**************************************************************************************************/
/**
 * @brief           Converts a uint8_t array into a 2 byte hex value stored in a array.
 *
 * @remarks         -
 *
 * @param[in]       au8Input: Data to convert.
 *                  \n [Range: 0..255]
 *
 * @param[out]      astHex8Result: Array with the hexadecimal representation of the value.
 *                  \n Each digit is in ascii format
 *                  \n [Range: '0'..'9', 'A'..'F']
 *
 * @param[in]      u32ArrayLength: Length of the input and result array. They must have the same length.
 *                 \n If u32ArrayLength is 0 function does nothing
 *                 \n [Range: 0..255]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vUint8ArrayToHex(const uint8_t au8Input[], LxUtilities_Hex8Struct_t astHex8Result[], uint32_t u32ArrayLength) {
    L0ASSERT_vERROR(au8Input != NULL);
    L0ASSERT_vERROR(astHex8Result != NULL);

    for (uint32_t u32Index = 0u; u32Index < u32ArrayLength; u32Index++) {
        LxUtilities_vUint8ToHex(au8Input[u32Index], &(astHex8Result[u32Index]));
    }
}

/**************************************************************************************************/
/**
 * @brief           Converts an uint32_t value to an array with 4 items.
 *
 * @remarks         -
 *
 * @param[in]       u32Value value to convert.
 *                  \n [Range: 0..4294967295]
 *
 * @param[out]      au8Result: output array.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8ArrayLength:  number of elements in array
 *                  \n If u8ArrayLength is 0 function does nothing
 *                  \n [Range: 0..4]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vUint32ToArray(uint32_t u32Value, uint8_t au8Result[], uint8_t u8ArrayLength) {
    L0ASSERT_vERROR(au8Result != NULL);
    L0ASSERT_vERROR(u8ArrayLength <= 4u);

    if (u8ArrayLength > 0u) {
        au8Result[u8ArrayLength - 1u] = LxUtilities_u8GetLowByte(LxUtilities_u16GetLowWord(u32Value));
    }
    if (u8ArrayLength > 1u) {
        au8Result[u8ArrayLength - 2u] = LxUtilities_u8GetHighByte(LxUtilities_u16GetLowWord(u32Value));
    }
    if (u8ArrayLength > 2u) {
        au8Result[u8ArrayLength - 3u] = LxUtilities_u8GetLowByte(LxUtilities_u16GetHighWord(u32Value));
    }
    if (u8ArrayLength > 3u) {
        au8Result[u8ArrayLength - 4u] = LxUtilities_u8GetHighByte(LxUtilities_u16GetHighWord(u32Value));
    }
}

/**************************************************************************************************/
/**
 * @brief           Converts a 4 byte array to a value of uint32_t.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8Data: Pointer pointing to an array with 4 byte value.
 *                  \n [Range: 0..255]
 *
 * @param[in]       u8ArrayLength: number of elements in array. Assert Warning if 0.
 *                  \n [Range: 1..4]
 *
 * @return          u32Value: resulting value
 *                  \n [Range: 0 .. 4294967295]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
uint32_t LxUtilities_u32ArrayToUint32(uint8_t *pu8Data, uint8_t u8ArrayLength) {
    L0ASSERT_vERROR(pu8Data != NULL);
    L0ASSERT_vERROR(u8ArrayLength <= 4u);
    L0ASSERT_vWARNING(u8ArrayLength > 0u);

    uint32_t u32Value = 0x00000000u;
    uint32_t u32Result = 0x00000000u;

    if (u8ArrayLength > 0u) {
        u32Value = pu8Data[u8ArrayLength - 1u];
        /* No Shift for first element */
        u32Result |= u32Value;
    }
    if (u8ArrayLength > 1u) {
        u32Value = pu8Data[u8ArrayLength - 2u];
        LxUtilities_vShiftLeftU32(&u32Value, 8u);
        u32Result |= u32Value;
    }
    if (u8ArrayLength > 2u) {
        u32Value = pu8Data[u8ArrayLength - 3u];
        LxUtilities_vShiftLeftU32(&u32Value, 16u);
        u32Result |= u32Value;
    }
    if (u8ArrayLength > 3u) {
        u32Value = pu8Data[u8ArrayLength - 4u];
        LxUtilities_vShiftLeftU32(&u32Value, 24u);
        u32Result |= u32Value;
    }
    return u32Result;
}

/**************************************************************************************************/
/**
 * @brief           Sets the value of a given bit in a given uint8_t value.
 *
 * @remarks         -
 *
 * @param[in,out]   pu8FlagField value to adapt by setting/clearing bit,
 *                  \n  Range [0x00...0xFF]
 *
 * @param[in]       u8BitNumber: number of the bit to set/clear,
 *                  \n  Range [0..7]
 *
 * @param[in]       bState: true to set / false to clear given bit
 *                  \n  Range [false...true]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vSetBitStateU8(uint8_t *pu8FlagField, uint8_t u8BitNumber, bool bState) {
    L0ASSERT_vERROR(pu8FlagField != NULL);
    L0ASSERT_vWARNING(u8BitNumber <= 7u);

    if (u8BitNumber <= 7u) {
        if (bState) {
            LxUtilities_vSetBitU8(pu8FlagField, u8BitNumber);
        } else {
            LxUtilities_vClearBitU8(pu8FlagField, u8BitNumber);
        }
    }
}

/**************************************************************************************************/
/**
 * @brief           Sets the value of a given bit in a given uint16_t value.
 *
 * @remarks         -
 *
 * @param[in,out]   pu16FlagField value to adapt by setting/clearing bit,
 *                  \n  Range [0x0000...0xFFFF]
 *
 * @param[in]       u8BitNumber: number of the bit to set/clear,
 *                  \n  Range [0..15]
 *
 * @param[in]       bState: true to set / false to clear given bit
 *                  \n  Range [false...true]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vSetBitStateU16(uint16_t *pu16FlagField, uint8_t u8BitNumber, bool bState) {
    L0ASSERT_vERROR(pu16FlagField != NULL);
    L0ASSERT_vWARNING(u8BitNumber <= 15u);

    if (u8BitNumber <= 15u) {
        if (bState) {
            LxUtilities_vSetBitU16(pu16FlagField, u8BitNumber);
        } else {
            LxUtilities_vClearBitU16(pu16FlagField, u8BitNumber);
        }
    }
}

/**************************************************************************************************/
/**
 * @brief           Sets the value of a given bit in a given uint32_t value.
 *
 * @remarks         -
 *
 * @param[in,out]   pu32FlagField value to adapt by setting/clearing bit,
 *                  \n  Range [0x00000000...0xFFFFFFFF]
 *
 * @param[in]       u8BitNumber: number of the bit to set/clear,
 *                  \n  Range [0..31]
 *
 * @param[in]       bState: true to set / false to clear given bit
 *                  \n  Range [false...true]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vSetBitStateU32(uint32_t *pu32FlagField, uint8_t u8BitNumber, bool bState) {
    L0ASSERT_vERROR(pu32FlagField != NULL);
    L0ASSERT_vWARNING(u8BitNumber <= 31u);

    if (u8BitNumber <= 31u) {
        if (bState) {
            LxUtilities_vSetBitU32(pu32FlagField, u8BitNumber);
        } else {
            LxUtilities_vClearBitU32(pu32FlagField, u8BitNumber);
        }
    }
}

/**************************************************************************************************/
/**
 * @brief           Flips the order of bits in a uint8_t variable. Swaps Bit 7 and 0, 6 and 1  and so on.
 *
 * @remarks         Example: 0b11000101 -> 0b10100011
 *
 * @param[in,out]   pu8FlagField - value to flip bits
 *                  \n  Range [0x00..0xFF]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vMirrorBitsU8(uint8_t *pu8FlagField) {
    L0ASSERT_vERROR(pu8FlagField != NULL);

    uint8_t u8Result = 0x00u;
    uint8_t u8Mask1 = 0x80u;
    uint8_t u8Mask2 = 0x01u;

    while (u8Mask1 > 0u) {
        u8Result = (u8Mask1 & *pu8FlagField) ? (u8Result | u8Mask2) : u8Result;
        u8Mask1 = u8Mask1 >> 1u;
        u8Mask2 = u8Mask2 << 1u;
    }
    *pu8FlagField = u8Result;
}

/**************************************************************************************************/
/**
 * @brief           Flips the order of bits in a uint16_t variable. Swaps Bit 15 and 0, 14 and 1  and so on.
 *
 * @remarks         Example: 0b1100000000000101 -> 0b1010000000000011
 *
 * @param[in,out]   pu16FlagField - pointer to adress bits should be flipped.
 *                  \n  Range [0x0000 .. 0xFFFF]
 *
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vMirrorBitsU16(uint16_t *pu16FlagField) {
    L0ASSERT_vERROR(pu16FlagField != NULL);

    uint16_t u16Result = 0x0000u;
    uint16_t u16Mask1 = 0x8000u;
    uint16_t u16Mask2 = 0x0001u;

    while (u16Mask1 > 0u) {
        u16Result = (u16Mask1 & *pu16FlagField) ? (u16Result | u16Mask2) : u16Result;
        u16Mask1 = u16Mask1 >> 1u;
        u16Mask2 = u16Mask2 << 1u;
    }
    *pu16FlagField = u16Result;
}

/**************************************************************************************************/
/**
 * @brief           Flips the order of bits in a uint32_t variable. Swaps Bit 31 and 0, 30 and 1  and so on.
 *
 * @remarks         Example: 0xFA800001 -> 0x8000015F
 *
 * @param[in,out]   pu32FlagField - value to flip bits
 *                  \n  [Range: 0x00000000 .. 0xFFFFFFFF]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vMirrorBitsU32(uint32_t *pu32FlagField) {
    L0ASSERT_vERROR(pu32FlagField != NULL);

    uint32_t u32Result = 0x00000000u;
    uint32_t u32Mask1 = 0x80000000u;
    uint32_t u32Mask2 = 0x00000001u;

    while (u32Mask1 > 0u) {
        u32Result = (u32Mask1 & *pu32FlagField) ? (u32Result | u32Mask2) : u32Result;
        u32Mask1 = u32Mask1 >> 1u;
        u32Mask2 = u32Mask2 << 1u;
    }
    *pu32FlagField = u32Result;
}


/**************************************************************************************************/
/**
 * @brief           Flips the order of bits in a uint64_t variable. Swaps Bit 6, and 0, 2 and 1 and so on.
 *
 * @remarks         Example: 0xFA8000000000001F -> 0xF80000000000015F
 *
 * @param[in,out]   pu64FlagField - value to flip bits
 *                  \n  [Range: 0x0000000000000000 .. 0xFFFFFFFFFFFFFFFF]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vMirrorBitsU64(uint64_t *pu64FlagField) {
    L0ASSERT_vERROR(pu64FlagField != NULL);

    uint64_t u64Result = 0x0000000000000000u;
    uint64_t u64Mask1 = 0x8000000000000000u;
    uint64_t u64Mask2 = 0x0000000000000001u;

    while (u64Mask1 > 0u) {
        u64Result = (u64Mask1 & *pu64FlagField) ? (u64Result | u64Mask2) : u64Result;
        u64Mask1 = u64Mask1 >> 1u;
        u64Mask2 = u64Mask2 << 1u;
    }
    *pu64FlagField = u64Result;
}

/**************************************************************************************************/
/**
 * @brief           Checks if shift operations works as expected.
 *
 * @remarks         Prüft ob beim Schieben immer eine 0 nachgeschoben wird.
 *
 * @return          bResult: Result of test. True if test passed
 *                  \n [Range: true, false]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
bool LxUtilities_bSelfTest(void) {
    bool bResult = true;

    /*lint -save -e572 */  /*PC-Lint-warnings are part of selftest */
    bResult = (((uint8_t)(0xFFu << 7u) == 0x80u) && ((uint8_t)(0xFFu >> 7u) == 0x01u)) ? true : false;
    bResult = ((uint8_t)(0xFFu << 8u) == 0x00u && (uint8_t)(0xFFu >> 8u) == 0x00u) ? bResult : false;
    bResult = ((0x00000001u << 31u) == 0x80000000u && (0xFFFFFFFFu >> 31u) == 0x00000001u) ? bResult : false;
    /*lint -restore*/

    return bResult;
}


/**************************************************************************************************/
/**
 * @brief           Calculates percentual part form absolute value.
 *
 * @remarks         -
 *
 * @param[in]       fMax - maximal value corresponding to 100%
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f]
 *
 * @param[in] 		  fMin - minimal value corresponding to 0%
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f]
 *
 * @param[in] 			fValue - searched value.
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f, fMin .. fMax]
 *
 * @return          Value in Percent calculated from absolute value. 
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
float LxUtilities_fGetPercentFlt1Pct( float fMax, float fMin, float fValue ){
  L0ASSERT_vERROR(LxMath_bIsFloatNumber(fMax));
  L0ASSERT_vERROR(LxMath_bIsFloatNumber(fMin));
	L0ASSERT_vERROR(LxMath_bIsFloatNumber(fValue));
  L0ASSERT_vERROR((fMin <= fValue) && (fValue <= fMax));

	float fDiff = fMax-fMin; 
	float fValueWithoutOffset = fValue - fMin; 
	float fPercent1Pct = (fValueWithoutOffset * 100.0f) / fDiff;
	return fPercent1Pct; 
}

/**************************************************************************************************/
/**
 * @brief           Calculates percentual part form absolute value.
 *
 * @remarks         -
 *
 * @param[in]       u32Max - maximal value corresponding to 100%
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[in] 		  u32Min - minimal value corresponding to 0%
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[in] 			u32Value - searched value.
 *                  \n \n [Range: 0 .. 4294967295, u32Min .. u32Max]
 *
 * @return          Value in Percent calculated from absolute value. 
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
float LxUtilities_fGetPercentU321Pct( uint32_t u32Max, uint32_t u32Min, uint32_t u32Value ){
  L0ASSERT_vERROR((u32Min <= u32Value) && (u32Value <= u32Max));
	
	float fDiff = (float)(u32Max-u32Min); 
	float fValueWithoutOffset = (float) (u32Value - u32Min); 
	float fPercent1Pct = (fValueWithoutOffset * 100.0f) / fDiff;
	return fPercent1Pct; 
}

/**************************************************************************************************/
/**
 * @brief           Calculates percentual part form absolute value.
 *
 * @remarks         -
 *
 * @param[in]       i32Max - maximal value corresponding to 100%
 *                  \n [Range: -2147483648 ..2147483647]
 *
 * @param[in] 		  i32Min - minimal value corresponding to 0%
 *                  \n [Range: -2147483648 ..2147483647]
 *
 * @param[in] 			i32Value - searched value.
 *                  \n [Range: -2147483648 ..2147483647, i32Min .. i32Max]
 *
 * @return          Value in Percent calculated from absolute value. 
 *                  \n [Range: -3.40282347e+38f .. 3.40282347e+38f]
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
float LxUtilities_fGetPercentI321Pct( int32_t i32Max, int32_t i32Min, int32_t i32Value ){
	L0ASSERT_vERROR((i32Min <= i32Value) && (i32Value <= i32Max));
	
	float fDiff = (float)(i32Max-i32Min); 
	float fValueWithoutOffset = (float) (i32Value - i32Min); 
	float fPercent1Pct = (fValueWithoutOffset * 100.0f) / fDiff;
	return fPercent1Pct; 
}


/**************************************************************************************************/
/**
 * @brief           Converts a Timestamp to days, hours, minutes, seconds, and miliseconds. 
 *
 * @remarks         -
 *
 * @param[in] 			u64Timestamp - time in miliseconds.
 *                  \n [Range: 0 .. 18446744073709551615]
 *
 * @param[out] 			pu32Day - pointer to outputvariable for Days.
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[out] 			pu32Hour - pointer to outputvariable for hours.
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[out] 			pu32Minute - pointer to outputvariable for minutes-
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[out] 			pu32Second  - pointer to outputvariable for seconds.
 *                  \n [Range: 0 .. 4294967295]
 *
 * @param[out] 			pu32MilliSecond - pointer to outputvariable for miliseconds.
 *                  \n [Range: 0 .. 4294967295]
 *
 * @return          -
 *
 * @pre             -
 *
 * @post            -
 *
 **************************************************************************************************/
void LxUtilities_vTimestampToInt(uint64_t u64Timestamp, uint32_t *pu32Day, uint32_t *pu32Hour, uint32_t *pu32Minute, uint32_t *pu32Second, uint32_t *pu32MilliSecond){
		L0ASSERT_vERROR( pu32Day != NULL && 
										 pu32Hour != NULL &&
										 pu32Minute != NULL &&
										 pu32Second != NULL &&
									   pu32MilliSecond != NULL ); 
	
	  uint32_t u32OperatingTime1s = u64Timestamp / 1000u; 	  
    *pu32Day = u32OperatingTime1s / (24u * 60u * 60u);                    /*calc [day] from OperatingTime [s]*/
    *pu32Hour = (u32OperatingTime1s % (24u * 60u * 60u)) / (60u * 60u);   /*calc [hour] from remaining day [s]*/
    *pu32Minute = (u32OperatingTime1s % (60u * 60u)) / (60u);             /*calc [minute] from remaining hour [s]*/
    *pu32Second = u32OperatingTime1s % 60;                                /*calc [s] from remaining minute [s]*/
		*pu32MilliSecond = u64Timestamp % 1000; 
}









/**
  * @}
  */
