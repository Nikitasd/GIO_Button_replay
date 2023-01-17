/*! @file Button_Condition.c
 *   @brief Application button counter
 *   @date 04-Jan-2023
 *
 *   This file contains functions for counting down the presence/absence
 *   of a signal from a button
 */
#include <Button_Condition.h>
#include <Button_Events.h>
#include "stdint.h"
#include "gio.h"
#include "rti.h"
#include "string.h"

/** @brief countdown from the moment the signal was given from the button
 *  @param counter - signal duration storage parameter
 *  @return counter signal duration
 */
/*void Click_Count(struct Button_State *button) {
 while(gioGetBit(gioPORTA, 7)){
 }*/
/** @brief countdown since no signal from the button
 *  @param counter - parameter for storing the duration of the absence of a signal
 *  @return counter signal duration
 */
static struct Button_State *button = NULL;

void Button_Struct_Init(struct Button_State *btn)
{
    button = btn;
}

static void RestartRti()
{
    rtiStopCounter(rtiCOUNTER_BLOCK0);
    rtiResetCounter(rtiCOUNTER_BLOCK0);
    rtiStartCounter(rtiCOUNTER_BLOCK0);
}

/** @brief looping the excerpt of signal states stored in an array.
 * @param delay - time delay LED on/off.
 * @param counter - counter of elements of the array that stores the time
 * of the signal (its absence).
 */
void Button_State_Replay(/*struct Button_State *button*/)
{
    uint16_t ten_replay = 0;
    while (ten_replay++ < 10)
    {
        for (uint32_t counter = 0; counter < Num_Of_Button_Events; counter++)
        {
            RestartRti();
            if (gioGetBit(gioPORTA, 2))
            {
                gioSetBit(gioPORTA, 2, 0);
            }
            else
            {
                gioSetBit(gioPORTA, 2, 1);
            }
            uint32_t delay = button->Button_Amount[counter];
            while (rtiREG1->CNT[0].FRCx < delay)
                ;
        }
    }
    RestartRti();
    rtiStopCounter(rtiCOUNTER_BLOCK0);
    memset(button->Button_Amount, 0, sizeof(button->Button_Amount));
    button->Button_Counter = 0;
}

void Button_State_Push_Value_Counter()
{
        button->Button_Amount[button->Button_Counter] = rtiREG1->CNT[0].FRCx;
        button->Button_Counter += 1;
        RestartRti();
}
