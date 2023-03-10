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

#include <Button_Confition.h>
#include <Button_Events.h>
#include "gio.h"
#include "sys_common.h"

/* USER CODE END */
#include "stdint.h"
/* Include Files */

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*! @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */
/* USER CODE BEGIN (3) */
/*!
 * @param gioSetDirection setting up GIO pins
 * @code
 *      gioSetDirection(gioPORTA, 1 << 2);
 * @endcode
 * @param button a structure object that stores button states
 * @code
 *      struct Button_State button;
 * @endcode
 *
 */
int main(void)
{
    struct Button_State button;
    gioInit();
    gioSetDirection(gioPORTA, 1 << 2);
    button.Button_Counter = 0;

    while(1){
/*!
 * Once we have filled the array of the Button State structure, we call the
 * replay() function
 * @code
 * if(button.Button_Amount[Num_Of_Button_Events - 1] != 0){
 *      replay(&button);
 *  }
 *  @endcode
 */
        if(button.Button_Amount[Num_Of_Button_Events - 1] != 0){
            replay(&button);
        }
/*!
 * If there is a signal from channel 7, run the Click_Count function
 * @code
 *  if(gioGetBit(gioPORTA,7)){
            Click_Count(&button);
            button.Button_Counter += 1;
        }
 * @endcode
 */
        if(gioGetBit(gioPORTA,7)){
            Click_Count(&button);
            button.Button_Counter += 1;
        }
/*!
* If there is no signal from channel 7, run the NoClick_Count function
* @code
*  if(gioGetBit(gioPORTA,7)){
        NoClick_Count(&button);
        button.Button_Counter += 1;
}
* @endcode
*
*/
        if(button.Button_Amount[0] != 0 && gioGetBit(gioPORTA, 7) == 0){
            NoClick_Count(&button);
            button.Button_Counter += 1;
        }
    }
}
/* USER CODE END */
/* USER CODE BEGIN (4) */
/* USER CODE END */
