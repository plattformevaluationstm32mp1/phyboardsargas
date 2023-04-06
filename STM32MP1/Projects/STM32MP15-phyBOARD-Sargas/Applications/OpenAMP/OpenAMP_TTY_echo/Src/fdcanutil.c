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
//#include "LxUtilities.h"
#include "fdcanutil.h"
//#include "LxMath.h"

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
  //  L0ASSERT_vERROR(pu8Result != NULL);

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
   // L0ASSERT_vERROR(pstHex8Result != NULL);

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
   // L0ASSERT_vERROR(astHex8Input != NULL);
   // L0ASSERT_vERROR(au8Result != NULL);

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
   // L0ASSERT_vERROR(au8Input != NULL);
   // L0ASSERT_vERROR(astHex8Result != NULL);

    for (uint32_t u32Index = 0u; u32Index < u32ArrayLength; u32Index++) {
        LxUtilities_vUint8ToHex(au8Input[u32Index], &(astHex8Result[u32Index]));
    }
}

/**
  * @}
  */
