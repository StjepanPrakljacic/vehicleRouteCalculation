#ifndef VEHICLE_DRIVE_CALCULATION_H
#define VEHICLE_DRIVE_CALCULATION_H

#include "routeCalculation.h"

/*
* Driving parameters
* speed is expressed as [m/s]
* distance is expressed in [m]
* time is expressed in [s]
*/

#define highwaySpeed 25.0
#define mainRoudSpeed 20.0
#define sideRoadSpeed 15.0
#define parkingSpeed 10.0
#define onTurnSpeed 5.0
#define onHalfturnSpeed 10.0
#define intersectionTrafficLightSpeed 5.0
#define stopSpeed 0.0
#define stopDistance 10.0
#define waitingTime 120 //on STOP or trafic light
#define acceleration 2
#define deceleration -2

/*Ways of driving on a particular stage*/

#define start 0
#define acceleratToMaxSpeed 1
#define acceleratedAtCertainSpeed 2
#define uniformDrive 3
#define solowingToTurn 4
#define solowingToHalfTurn 5
#define solowingToTraficLight 6
#define slowingToFinish 7


/*
* Function stageResolve()
* Description: The function will set the maximum speed of each driving stage through the menu. By starting the stage menu, the desired action is selected at the beginning of each stage.
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
void stageResolve(STAGE* stageInstance);

/*
* Function addStageSpeed()
* Description: The function used as a menu to select an action at the beginning of each stage
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
void stageMenu(STAGE* stageInstance);

/*
* Function acceleratedDrivingCalculation()
* Description: The function used to calculates the vehicle's acceleration
*	@param -  Stage instance that can't be NULL
*   @param -  Acceleration speed
* Returns: void
*/
void acceleratedDrivingCalculation(STAGE* stageInstance, double accSpeed);

/*
* Function acceleratedDrivingCalculation()
* Description: The function used to calculates the vehicle's uniform drive
*	@param -  Stage instance that can't be NULL
*   @param -  uniform drivig type
*		eg. passing intersection with traffic light with appropriate speed
*		eg. uniform driving after acceleration etc.
* Returns: void
*/
void uniformDrivingCalculation(STAGE* stageInstance, int driveType);

void decelerationDrivigCalculation(STAGE* stageInstance, double decSpeed);

#endif // !VEHICLE_DRIVE_CALCULATION_H
