/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/** @brief Configuring the GIO I/O Module
 */
#include "gio.h"
#include "sys_common.h"
/* USER CODE END */

/* Include Files */


/* USER CODE BEGIN (1) */
/** @brief Button entry structure
   * @param Button_amount[4] - an array storing signal/absence time
   * button signal.
   * @param Button_Counter - signal connection counter, when using a
   * signal it is in ñonsequences will change.
   * @param button - Button_State object structure
 */
struct Button_State{
    long int Button_amount[4];
    unsigned int Button_Counter;
};
struct Button_State button;
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/** @brief Countdown from the moment the signal was given from the button
  * @param counter - parameter storing signal duration
  * @return counter signal duration
 */
int Click_Count(void) {
    long int counter = 0;
    while(gioGetBit(gioPORTA, 7)){
        counter += 1;
    }
    return counter;
}

/** @brief Countdown since no signal from the button
  * @param counter - parameter storing the duration of the absence of a signal
  * @return counter no signal duration
 */
int NoClick_Count(void){
    long int counter = 0;
    while(gioGetBit(gioPORTA, 7) == 0){
        counter += 1;
    }
    return counter;
}

/** @brief looping the excerpt of signal states stored in an array.
  * @param delay - time delay.
  * @param counter counter of elements of the array that stores the time
  * of the signal (its absence).
 */
void replay(void){
    long int delay, counter;
    while(1){
        for(counter = 0; counter < 4; counter++){
            delay = button.Button_amount[counter]*4;
            gioToggleBit(gioPORTA, 2);
            while(delay--);
        }
    }
}
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
/** @brief configuring and initializing the GIO module
  * @detailed when a signal is given from the button, the function is started
  * Click_Count(), which counts the time of the signal. As soon as we
  * release the button, the NoClick_Count() function is launched, which
  * counts down the time of no signal. As soon as we have filled
  * array, the replay() function is run, which performs an excerpt
  * time stored in an array.
 */
    gioInit();
    gioSetDirection(gioPORTA, 1 << 2);
    button.Button_Counter = 0;
    while(1){
        if(button.Button_amount[3] != 0){
            replay();
        }
        if(gioGetBit(gioPORTA,7)){
            button.Button_amount[button.Button_Counter] = Click_Count();
            button.Button_Counter += 1;
        }
        if(button.Button_amount[0] != 0 && gioGetBit(gioPORTA, 7) == 0){
            button.Button_amount[button.Button_Counter] = NoClick_Count();
            button.Button_Counter += 1;
        }
    }
    /* USER CODE END */
}
/* USER CODE BEGIN (4) */
/* USER CODE END */
