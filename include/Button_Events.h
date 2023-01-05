/*! @file Button_Events.h
*   @brief Button states application
*   @date 04-Jan-2023
*
*   This file contains a structure that stores the duration of
*   signals from the button
*/

#pragma once

#include "stdint.h"

#define Num_Of_Button_Events ((uint32_t)4)

/** @brief Button entry structure
   * @param Button_amount[4] - an array storing signal/absence time
   * button signal.
   * @param Button_Counter - signal connection counter, when using a
   * signal it is in ñonsequences will change.
   * @param button - Button_State object structure
 */

struct Button_State{
    uint64_t Button_Amount[Num_Of_Button_Events];
    uint16_t Button_Counter;
};
