/*
 * functions.h
 *  Created on: Aug 23, 2022
 *      Author: Stjepan Prakljacic
 */

#ifndef VEHICLE_ROUTE_FUNCTIONS_H
#define VEHICLE_ROUTE_FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Driving parameters */
#define bendSpeed 5.0
#define intersectionTrafficLightSpeed 5.0
#define halfturnSpeed 10.0
#define stopSpeed 0.0

#define highwaySpeed 20.0
#define mainRoudSpeed 15.0
#define sideRoadSpeed 14.0
#define parkingSpeed 10.0

#define stopDistance 10.0
#define waitingTime 120 //on STOP or trafic light
#define acceleration 2
#define deceleration -2

/*Ways of driving on a particular stage*/

#define uniformDrive 1
#define crossoverPassing 2
#define trafficLightIntersection 3

#define defaultValue 7

typedef struct stage {
	int startingPoint;
	int endPoint;
	int stageType;
	double maxdistance;
	double maxStageSpeed;
	double stageAccelerations[defaultValue];
	double stageSpeeds[defaultValue];
	double stageDistance[defaultValue];
	double stageTimes[defaultValue];
}STAGE;

typedef struct rout {
	int numberOfPoints;
	int* points;
	double* space;
	double* distance;
	STAGE* stages[20];
}ROUT;

/*
* Function routInitialize()
* Description: The function will allocate memory for the passed instance of the rout and will set all values ​​of the passed instance to defined values
*	@param -  Rout instance that can be NULL
* Returns: Succes status
*/
int routInitialize(ROUT** routInstance);

/*
* Function printRout()
* Description: The function will print to the standard output all rout elements
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
void printRout(ROUT* routInstance);

/*
* Function printStage()
* Description: The function will allocate memory for stages of the passed rout instance and it will set all values ​​of stages to defined values by using addStage() function.
*	@param -  Stage instance that can be NULL
* Returns: Succes status
*/
int stageInitialize(ROUT* routInstance);

/*
* Function printStage()
* Description: The function will print to the standard output all stage elements
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
void printStage(STAGE* stageInstance);

/*
* Function routCalculate()
* Description: Using the stageResolve() function, the function will calculate all the necessary data related to each stage of the route for the given instance of the route and print them to the standard output
*	@param -  Rout instance that can't be NULL
* Returns: Succes status
*/
int routCalculate(ROUT* routInstance);

#endif // !VEHICLE_ROUTE_FUNCTIONS_H