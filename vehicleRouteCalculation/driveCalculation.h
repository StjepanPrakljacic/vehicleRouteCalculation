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
#define acceleration 1
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
* Function stageMenu()
* Description: 
	* The function is used as a menu to select the next action on the stage
	* At start we select the type of acceleration followed by the operation of uniform driving
	* After which we select whether the vehicle stops or just slows down until the next action
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
void stageMenu(STAGE* stageInstance);

/*
* Function acceleratedDrivingCalculation()
* Description: The function will calculate the necessary values ​​for acceleration drive
*	@param -  Stage instance that can't be NULL
*   @param -  Acceleration speed
* Returns: void
*/
void acceleratedDrivingCalculation(STAGE* stageInstance, double accSpeed);

/*
* Function uniformDrivingCalculation()
* Description: 
		*The function will calculate the necessary values ​​for uniform drive, using physical parameters: distance, speed and time 
		*Function will calculate a values for actions: passing a turn/half turn, pass an intersection with a traffic light.
			* By setting the driveType, (using the function for passing a turn/half turn, passing an intersection with a traffic light) the function calculates the stopping distance 
*	@param -  Stage instance that can't be NULL
*   @param -  uniform drivig type
*		eg. passing intersection with traffic light with appropriate speed
*		eg. uniform driving after acceleration
* Returns: void
*/
void uniformDrivingCalculation(STAGE* stageInstance, int driveType);

/*
* Function decelerationDrivigCalculation()
* Description: 
		*The function calculates the braking parameters. It sets the parameters of uniform driving on the stage as well as the parameters of the braking part.
		*The function determines the parameters of the stopping point and deals with the problem of the lack of a braking distance.
*	@param -  Stage instance that can't be NULL
*   @param -  deceleration speed
* Returns: void
*/
void decelerationDrivigCalculation(STAGE* stageInstance, double decSpeed);

#endif // !VEHICLE_DRIVE_CALCULATION_H
