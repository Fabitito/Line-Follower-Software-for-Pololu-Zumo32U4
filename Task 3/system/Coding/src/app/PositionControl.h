/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       PositionControl.h
 *
 * Header of PositionControl.c.
 */
/**************************************************************************************************/
#ifndef POSITION_COTROL_H
#define POSITION_COTROL_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"

#include "LineSensor.h"
#include "DriveControl.h"
#include "Parameters.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

extern void PositionControl_DriveOnTrack(ParameterSet parameters);

#endif /* POSITION_COTROL_H */