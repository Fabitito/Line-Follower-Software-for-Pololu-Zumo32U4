/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchingStartLineState.h
 *
 * Header of SearchingStartLineState.c.
 */
/**************************************************************************************************/
#ifndef SEARCHING_START_LINE_STATE_H
#define SEARCHING_START_LINE_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 * @brief Restarts timer1 to measure the time until the startLine is found and starts the DualMotorDriveSystem to drive to the StartLine
*/
extern void SearchingStartLineState_enterRestartTimer1AndWait3sAndStartDriving(void)

/** 
 * @brief stops and resets timer1
*/
extern void SearchingStartLineState_exitStopTimer1(void);

/**
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States SearchningStartLineState_getTransitions(void);

/**
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* SearchingStartLineState_getStateFunctions(void);

#endif /* SEARCHING_START_LINE_STATE_H */