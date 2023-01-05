/*! @file Button_Confition.h
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
void Click_Count(struct Button_State *button);
/** @brief countdown since no signal from the button
 */
void NoClick_Count(struct Button_State *button);
/** @brief looping the excerpt of signal states stored in an array.
 */
void replay(struct Button_State *button);
