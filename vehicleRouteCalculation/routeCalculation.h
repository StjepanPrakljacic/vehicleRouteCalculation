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

#define defaultValue 7

typedef struct stage {
	int startingPoint;
	int endPoint;
	int stageDrivingType;
	double totalStageDistance;
	double maxStageSpeed;
	double stageDistance[defaultValue];
	double stageSpeeds[defaultValue];
	double stageAccelerations[defaultValue];
	double stageTimes[defaultValue];
}STAGE;

typedef struct route {
	int numberOfPoints;
	int* points;
	double* space;
	double* distance;
	STAGE* stages[20];
}ROUTE;

/*
* Function routeInitialize()
* Description: The function will allocate memory for Route instance and it will set all values ​​of allocated instance to defined values
*	@param -  none
* Returns: Allocated Route instance
*/
ROUTE* routeInitialize();

/*
* Function printRoute()
* Description: The function will print to the standard output all route elements
*	@param -  Route instance that can't be NULL
* Returns: void
*/
void printRoute(ROUTE* routInstance);

/*
* Function stageInitialize()
* Description: The function will allocate memory for stages of the passed route instance and it will set all values ​​of stages to defined values
*	@param -  Route instance that can't be NULL
* Returns: void
*/
void stageInitialize(ROUTE* routeInstance);

/*
* Function printStage()
* Description: The function will print to the standard output all stage elements
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
void printStage(STAGE* stageInstance);

/*
* Function routeCalculate()
* Description: Using the stageResolve() function, the function will calculate all the necessary data related to each stage of the route for the given instance of the route and print them to the standard output
*	@param -  Route instance that can't be NULL
* Returns: void
*/
void routeCalculate(ROUTE* routeInstance);

/*
* Function initializationCheck()
* Description: The function used to check initialization with respect to the passed instance
*	@param -  Instance to check
* Returns: void
*/
void initializationCheck(void* instanceToCheck);

#endif // !VEHICLE_ROUTE_FUNCTIONS_H