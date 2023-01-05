/*! @file Button_Confition.h
*   @brief Application button counter
*   @date 04-Jan-2023
*
*   This file contains functions for counting down the presence/absence
*   of a signal from a button
*/
#include <Button_Events.h>
#include <Button_Confition.h>
#include "stdint.h"
#include "gio.h"

/** @brief countdown from the moment the signal was given from the button
 *  @param counter - signal duration storage parameter
 *  @return counter signal duration
 */
void Click_Count(struct Button_State *button) {
    while(gioGetBit(gioPORTA, 7)){
        button->Button_Amount[button->Button_Counter] += 1;
    }
}
/** @brief countdown since no signal from the button
 *  @param counter - parameter for storing the duration of the absence of a signal
 *  @return counter signal duration
 */
void NoClick_Count(struct Button_State *button){
    while(gioGetBit(gioPORTA, 7) == 0){
        button->Button_Amount[button->Button_Counter] += 1;
    }
}
/** @brief looping the excerpt of signal states stored in an array.
  * @param delay - time delay.
  * @param counter - counter of elements of the array that stores the time
  * of the signal (its absence).
 */
void replay(struct Button_State *button){
    uint32_t delay;
    while(1){
        for(uint32_t counter = 0; counter < Num_Of_Button_Events; counter++){
            delay = button->Button_Amount[counter]*4;
            gioToggleBit(gioPORTA, 2);
            while(delay--);
        }
    }
}
