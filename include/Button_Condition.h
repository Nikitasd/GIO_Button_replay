/*! @file Button_Condition.h
*   @brief Application button counter
*   @date 04-Jan-2023
*
*   This file contains functions for counting down the presence/absence
*   of a signal from a button
*/
#pragma once

#include <Button_Events.h>
#include "stdint.h"
#include "gio.h"

/** @brief countdown from the moment the signal was given from the button
 */
/** @brief looping the excerpt of signal states stored in an array.
 */
void Button_State_Replay(/*struct Button_State *button*/);

void Button_State_Push_Value_Counter();

struct Button_State{
    uint64_t Button_Amount[Num_Of_Button_Events];
    uint16_t Button_Counter;
};

void Button_Struct_Init(struct Button_State *btn);
