/***************************************************************************************************
  (c) NewTec GmbH 2019   -   www.newtec.de
  $URL: https://svn.newtec.zz/NTCampus/SW-Entwicklung/trunk/system/50_Implementierung/Projekte/Linienfolger/20_Beistellung/Delivery/Beistellung_r300/Coding/src/app/MainTask.c $
***************************************************************************************************/
/**
@addtogroup App
@{
@file       MainTask.c

Main Application task.
For a detailed description see the detailed description in @ref MainTask.h.

@version    %$Id: MainTask.c 300 2024-02-01 12:58:40Z leglaz $
* @}
***************************************************************************************************/

/* INCLUDES ***************************************************************************************/

#include "app/MainTask.h"

#include "os/ErrorHandler.h"
#include "os/Task.h"
#include "os/Scheduler.h"
#include "service/Button.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/** Internal Task cyclic worker function.
 * @param[in] data task data (ignored).
 */
static void mainTaskWork (void * data);

/* VARIABLES **************************************************************************************/

/** MainTask task structure. */
static Task gMainTask;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern MainTask_Ret MainTask_init(void)
{
    MainTask_Ret result = MAINTASK_RET_INTERNAL_ERROR;

    /* TODO: Add your initalization here. */


    if (TASK_RET_SUCCESS == Task_init(&gMainTask, mainTaskWork, TASK_STATE_RUNNING, NULL))
    {
        if ( SCHEDULER_RET_SUCCESS == Scheduler_addTask(&gMainTask))
        {
            /* TODO: Add your application here. */
        }
        else
        {
            result = MAINTASK_RET_ADD_TASK_FAIL;
        }
    }
    else
    {
        result = MAINTASK_RET_INIT_TASK_FAIL;
    }

    return result;
}

/* INTERNAL FUNCTIONS *****************************************************************************/
typedef enum
{
    INIT,
    CALIBRATE,
    POS,
    IDLE,
    START_TIMER,
    
}States;

#include "SoftTimer.h"
#include "GlobalTimers.h"
#include "Display.h"
#include "CalibrationState.h"
#include "LineSensor.h"
#include <stdio.h> 
#include <stdlib.h>

static char text0[] = "SENSOR0: ";
static char text1[] = "SENSOR1: ";
static char text2[] = "SENSOR2: ";
static char text3[] = "SENSOR3: ";
static char text4[] = "SENSOR4: ";

static char value0[5];
static char value1[5];
static char value2[5];
static char value3[5];
static char value4[5];

static UInt16 lastValue0 = 0u; 
static UInt16 lastValue1 = 0u; 
static UInt16 lastValue2 = 0u; 
static UInt16 lastValue3 = 0u; 
static UInt16 lastValue4 = 0u; 

static char text[] = "POSITION: ";
static char position[5];

static LineSensorValues values;
static uint32_t Pos = 0u; 
static char test[] = "ENTERED IDLE";
static States eStates = INIT;
static void mainTaskWork(void * data)
{
    (void)data;

    /* TODO: Add your application here. */
    switch (eStates)
    {
        case INIT:
            //SoftTimer_init(pTimer1);
            SoftTimerHandler_register(pTimer1);
            eStates = CALIBRATE;
            break;
        case CALIBRATE:
            if(CalibrationState_checkTransitionTriggerCalibrationDone() == false)
            {
                CalibrationState_processCalibrate();
            }
            else
            {
                LineSensor_enableEmitter();
                //LineSensor_read(&values);
                //LineSensor_disableEmitter();
                eStates = START_TIMER;

            }
            break;

        case START_TIMER:
            SoftTimer_start(pTimer1, 3000u);
            eStates = POS;

            break; 
        case POS:
            if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                //LineSensor_enableEmitter();
                LineSensor_read(&values);

                Pos = values.value[LINESENSOR_LEFT] * 0u;
                Pos += values.value[LINESENSOR_MIDDLE_LEFT] * 1000u;
                Pos += values.value[LINESENSOR_MIDDLE] * 2000u;
                Pos += values.value[LINESENSOR_MIDDLE_RIGHT]* 3000u;
                Pos += values.value[LINESENSOR_RIGHT]* 4000u;

                snprintf(position, sizeof(position), "%lu", Pos);

                Display_clear();
                Display_gotoxy(0, 6);
                Display_write(text, sizeof(text));
                Display_gotoxy(10, 6);
                Display_write(position, sizeof(position));

                //LineSensor_disableEmitter();

            
            //char text[] = "CALIBRATION \n DONE";
            //Display_clear();
            Display_gotoxy(0, 0);
            Display_write(text0, sizeof(text0));
            Display_gotoxy(0, 1);
            Display_write(text1, sizeof(text1));
            Display_gotoxy(0, 2);
            Display_write(text2, sizeof(text2));
            Display_gotoxy(0, 3);
            Display_write(text3, sizeof(text3));
            Display_gotoxy(0, 4);
            Display_write(text4, sizeof(text4));
            LineSensor_enableEmitter();
            LineSensor_read(&values);
            LineSensor_disableEmitter();
            
            //values.value[LINESENSOR_LEFT]
            snprintf(value0, sizeof(value0), "%d", values.value[LINESENSOR_LEFT]);
            snprintf(value1, sizeof(value1), "%d", values.value[LINESENSOR_MIDDLE_LEFT]);
            snprintf(value2, sizeof(value2), "%d", values.value[LINESENSOR_MIDDLE]);
            snprintf(value3, sizeof(value3), "%d", values.value[LINESENSOR_MIDDLE_RIGHT]);
            snprintf(value4, sizeof(value4), "%d", values.value[LINESENSOR_RIGHT]);

            lastValue0 = values.value[LINESENSOR_LEFT];
            lastValue1 = values.value[LINESENSOR_MIDDLE_LEFT];
            lastValue2 = values.value[LINESENSOR_MIDDLE];
            lastValue3 = values.value[LINESENSOR_MIDDLE_RIGHT];
            lastValue4 = values.value[LINESENSOR_RIGHT];

            Display_gotoxy(10, 0);
            Display_write(value0, sizeof(value0));
            Display_gotoxy(10, 1);
            Display_write(value1, sizeof(value1));
            Display_gotoxy(10, 2);
            Display_write(value2, sizeof(value2));
            Display_gotoxy(10, 3);
            Display_write(value3, sizeof(value3));
            Display_gotoxy(10, 4);
            Display_write(value4, sizeof(value4));
            
            SoftTimer_Stop(pTimer1);
            eStates = START_TIMER;
            }

            break;
        case IDLE:
            
            
            break;
        
    }

}

