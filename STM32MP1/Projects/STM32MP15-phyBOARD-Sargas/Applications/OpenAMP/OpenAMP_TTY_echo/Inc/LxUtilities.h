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


/************************************ public const ************************************************/
/************************************ public variables ********************************************/
/************************************ public function declaration *********************************/


/*Konvertierung hex to uint8_t, uint8_t to hex*/
bool LxUtilities_bHexToUint8(const LxUtilities_Hex8Struct_t stHex8Input, uint8_t *const pu8Result);
void LxUtilities_vUint8ToHex(uint8_t u8Input, LxUtilities_Hex8Struct_t *const pstHex8Result);

bool LxUtilities_bHexToUint8Array(const LxUtilities_Hex8Struct_t astHex8Input[], uint8_t au8Result[], uint32_t u32ArrayLength);
void LxUtilities_vUint8ArrayToHex(const uint8_t au8Input[], LxUtilities_Hex8Struct_t astHex8Result[], uint32_t u32ArrayLength);

void LxUtilities_vUint32ToArray(uint32_t u32Value, uint8_t au8Result[], uint8_t u8ArrayLength);
uint32_t LxUtilities_u32ArrayToUint32(uint8_t *pu8Data, uint8_t u8ArrayLength);




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
