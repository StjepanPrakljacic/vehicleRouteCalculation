#include "driveCalculation.h"

int entryIndex;
int lastEntryIndex;
int accelerationDriveIndex;
int uniformDriveIndex;
int decelerationDriveIndex;

/*
* Function stageStart()
* Description: The function will set the acceleration value in the acceleration array for the initial stage of the route
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void stageStart(STAGE* stageInstance)
{
	stageInstance->stageDrivingType = start;
	stageInstance->stageAccelerations[entryIndex] = acceleration;
	stageResolve(stageInstance);
}

/*
* Function passStageValues()
* Description: The functions will pass the last entered values ​​of the previous stage as the initial values ​​of the new stage
*	@param -  Stage instance that can't be NULL
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void passStageValues(STAGE* newStageInstance, STAGE* lastStageInstance)
{
	newStageInstance->stageDistance[entryIndex] = lastStageInstance->stageDistance[lastEntryIndex];
	newStageInstance->stageSpeeds[entryIndex] = lastStageInstance->stageSpeeds[lastEntryIndex];
	newStageInstance->stageAccelerations[entryIndex] = lastStageInstance->stageAccelerations[lastEntryIndex];
	newStageInstance->stageTimes[entryIndex] = lastStageInstance->stageTimes[lastEntryIndex];
	newStageInstance->stageDrivingType = lastStageInstance->stageDrivingType;
	stageResolve(newStageInstance);
}

/*
* Function addStageSpeed()
* Description: The function used as a menu to set the maximum speed for each stage
*	@param -  Stage instance that can't be NULL
* Returns: Maximum stage speed
*/
static double addStageSpeed()
{
	int stageType, status;
	printf("\nSelection of stage type:\n 1. Driving on the highway at 25[m/s]\n 2. Driving on the main road at 20[m/s]\n 3. Driving on a side road at 15[m/s]\n 4. Driving on the road at 10[m/s]\n");
	printf("Choose type: ");
	status = scanf("%d", &stageType);
	switch (stageType)
	{
	case 1: return highwaySpeed;
		break;
	case 2: return mainRoudSpeed;
		break;
	case 3: return sideRoadSpeed;
		break;
	case 4: return parkingSpeed;
		break;
	default: return mainRoudSpeed;
		break;
	}
}

/*
* Function inputAccelerationSpeed()
* Description: The function used to enter the desired speed of acceleration at a particular stage
*	@param -  Stage instance that can't be NULL
* Returns: Stage speed
*/
static double inputAccelerationSpeed(STAGE* stageInstance)
{
	double speed;
	int status;
	printf("\n");
	printf("Enter the desired acceleration speed [m/s]:");
	do
	{
		status = scanf("%lf", &speed);
		if (speed > stageInstance->maxStageSpeed)
		{
			printf("\nYou entered a speed higher than the maximum allowed speed: %.2lf [m/s]\n", stageInstance->maxStageSpeed);
		}
		else if (speed < 0)
		{
			printf("\nSpeed ​​can't be negative!\n");
		}
	} while (speed > stageInstance->maxStageSpeed || speed < 0);
	return speed;
}

void routeCalculate(ROUTE* routeInstance)
{
	int stageIndex = 0;
	initializationCheck(routeInstance);
	printRoute(routeInstance);
	while (stageIndex < routeInstance->numberOfPoints - 1)
	{
		entryIndex = 0;
		if (stageIndex == 0)
		{
			stageStart(routeInstance->stages[stageIndex]);
		}
		else
		{
			passStageValues(routeInstance->stages[stageIndex], routeInstance->stages[stageIndex - 1]);
		}
		printStage(routeInstance->stages[stageIndex]);
		stageIndex++;
	}
}

void stageResolve(STAGE* stageInstance)
{
	initializationCheck(stageInstance);
	printf("\nStage resolve for stage %d - %d", stageInstance->startingPoint, stageInstance->endPoint);
	printf("\nSTART\n");
	stageInstance->maxStageSpeed = addStageSpeed();
	stageMenu(stageInstance);
}

void stageMenu(STAGE* stageInstance)
{
	int newAction, status;
	if (stageInstance->stageDrivingType == start)
	{
		printf("\nAction selection:\n 1. Acceleration to max speed\n 2. Acceleration at a certain speed\n");
		do
		{
			printf("Choose action: ");
			status = scanf("%d", &newAction);
		} while (newAction < 1 || newAction > 2);
		stageInstance->stageDrivingType = newAction;
		switch (newAction)
		{
		case 1: acceleratedDrivingCalculation(stageInstance, stageInstance->maxStageSpeed);
			break;
		case 2: acceleratedDrivingCalculation(stageInstance, inputAccelerationSpeed(stageInstance));
			break;
		}
	}
	else if(stageInstance->stageDrivingType == acceleratToMaxSpeed || stageInstance->stageDrivingType == acceleratedAtCertainSpeed)
	{
		printf("\nAction that follows: Uniform drive\n");
		stageInstance->stageDrivingType = uniformDrive;
		uniformDrivingCalculation(stageInstance, uniformDrive);
	}
	else if (stageInstance->stageDrivingType == uniformDrive)
	{
		printf("\nAction selection:\n 3. Passing an intersection with a traffic light\n 4. Slowing down to turn\n 5. Slowing down to half a turn\n 6. Stopp at traffic light\n 7. Stopp at finish\n");
		do
		{
			printf("Choose action: ");
			status = scanf("%d", &newAction);
		} while (newAction < 3 || newAction > 7);
		stageInstance->stageDrivingType = newAction; 
		switch (newAction)
		{
		case 3: stageInstance->stageDrivingType = start; uniformDrivingCalculation(stageInstance, solowingToTraficLight);
			break;
		case 4: decelerationDrivigCalculation(stageInstance, onTurnSpeed);
			break;
		case 5: decelerationDrivigCalculation(stageInstance, onHalfturnSpeed);
			break;
		case 6: decelerationDrivigCalculation(stageInstance, stopSpeed);
			break;
		case 7: decelerationDrivigCalculation(stageInstance, stopSpeed);
			break;
		}
	}
	else if (stageInstance->stageDrivingType == solowingToTurn || stageInstance->stageDrivingType == onHalfturnSpeed)
	{
		printf("\nAction that follows: Uniform drive passing turn/half turn\n");
		stageInstance->stageDrivingType = start;
		uniformDrivingCalculation(stageInstance, solowingToTurn);
	}
	else if (stageInstance->stageDrivingType == solowingToTraficLight)
	{
		stageInstance->stageDrivingType = uniformDrive;
		acceleratedDrivingCalculation(stageInstance, intersectionTrafficLightSpeed);
	}
}

void acceleratedDrivingCalculation(STAGE* stageInstance, double accSpeed)
{
	double deltaT = 0, deltaS = 0;
	entryIndex++;
	deltaT = (accSpeed - stageInstance->stageSpeeds[entryIndex - 1]) / acceleration;
	stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[entryIndex - 1] + deltaT; // acceleration time calculation
	stageInstance->stageSpeeds[entryIndex] = accSpeed; // set acceleration speed value 
	
	if (stageInstance->stageDrivingType == acceleratToMaxSpeed || stageInstance->stageDrivingType == acceleratedAtCertainSpeed)
	{
		stageInstance->stageAccelerations[entryIndex - 1] = acceleration; // set acceleration value
	}

	deltaS = ((0.5 * acceleration * pow(deltaT, 2)) + (stageInstance->stageSpeeds[entryIndex - 1] * deltaT)); 
	stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[entryIndex - 1] + deltaS; // acceleration distance calculation
	
	accelerationDriveIndex = entryIndex; //saving last entry index
	stageMenu(stageInstance); // new stage action 
}

void uniformDrivingCalculation(STAGE* stageInstance, int driveType) 
{
	double deltaT;
	entryIndex++;
	stageInstance->stageSpeeds[entryIndex] = stageInstance->stageSpeeds[entryIndex - 1]; // passing stage speed from previous stage action
	if (driveType == solowingToTurn || driveType == solowingToHalfTurn || driveType == solowingToTraficLight)
	{
		if (driveType == solowingToTurn || driveType == solowingToHalfTurn)
		{
			stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[0] + stopDistance; 
		}
		else
		{
			stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[0] + stopDistance + 10;  
		}
		deltaT = (stageInstance->stageDistance[entryIndex] - stageInstance->stageDistance[entryIndex - 1]) / stageInstance->stageSpeeds[entryIndex];
		stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[entryIndex - 1] + deltaT; //calculating stage time
		stageInstance->stageAccelerations[entryIndex] = acceleration;  
	}
	uniformDriveIndex = entryIndex; //saving last entry index
	stageMenu(stageInstance); // new stage action 
}

void decelerationDrivigCalculation(STAGE* stageInstance, double decSpeed)
{
	double brakingDistance, brakingTime, delatS;
	entryIndex++;
	brakingTime = (decSpeed - stageInstance->stageSpeeds[uniformDriveIndex]) / deceleration; 
	brakingDistance = (0.5 * deceleration * pow(brakingTime, 2) + (stageInstance->stageSpeeds[uniformDriveIndex] * brakingTime));
	delatS = stageInstance->totalStageDistance - stageInstance->stageDistance[accelerationDriveIndex] - brakingDistance - stopDistance; 

	/*Uniform drive section*/
	stageInstance->stageAccelerations[uniformDriveIndex] = deceleration;
	stageInstance->stageDistance[uniformDriveIndex] = stageInstance->stageDistance[accelerationDriveIndex] + delatS;
	stageInstance->stageTimes[uniformDriveIndex] = stageInstance->stageTimes[accelerationDriveIndex] + (delatS / stageInstance->stageSpeeds[uniformDriveIndex]);

	/*Deceleration section*/
	stageInstance->stageSpeeds[entryIndex] = decSpeed;
	stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[uniformDriveIndex] + brakingTime;
	if (stageInstance->stageDrivingType == slowingToFinish)
	{
		stageInstance->stageDistance[entryIndex] = stageInstance->totalStageDistance;
	}
	else
	{
		stageInstance->stageDistance[entryIndex] = stageInstance->totalStageDistance - stopDistance;
	}
	/* Parameters of the end point of the route (destination, traffic light, turn etc.) */
	if (decSpeed == stopSpeed)  
	{
		stageInstance->stageDistance[entryIndex + 1] = stageInstance->stageDistance[entryIndex];
		if (stageInstance->stageDrivingType == slowingToFinish)
		{
			stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex];
		}
		else //trafic light
		{
			stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex] + waitingTime;
			stageInstance->stageAccelerations[entryIndex + 1] = acceleration;
		}
	}
	else
	{
		stageInstance->stageSpeeds[entryIndex + 1] = decSpeed;
		stageInstance->stageDistance[entryIndex + 1] = stageInstance->totalStageDistance;
		stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex] + (stopDistance / stageInstance->stageSpeeds[entryIndex + 1]);
	}

	/*Lack of braking distance*/
	if (stageInstance->stageDistance[accelerationDriveIndex] > stageInstance->stageDistance[uniformDriveIndex])
	{
		printf("\nWarning! The braking distance is less than the acceleration distance!");
		printf("\nIf you are accelerating at the max speed of the stage \nEnter a speed lower than the max possible or enter a speed lower than the speed at which you are accelerating!\n");
		printf("\nThe maximum speed is: %.2lf ", stageInstance->maxStageSpeed);
		printf("\nAfter entering the new speed, continue with uniform movement and deceleration!");
		entryIndex = accelerationDriveIndex - 1;
		stageInstance->stageDrivingType = acceleratedAtCertainSpeed;
		acceleratedDrivingCalculation(stageInstance, inputAccelerationSpeed(stageInstance));
	}
	decelerationDriveIndex = entryIndex;
	lastEntryIndex = decelerationDriveIndex + 1;
}

void initializationCheck(void* instanceToCheck)
{
	if (instanceToCheck == NULL)
	{
		fprintf(stderr, "Instance is not initialized");
		exit(EXIT_FAILURE);
	}
}

void printStage(STAGE* stageInstance)
{
	int stageValueIndex;
	initializationCheck(stageInstance);
	printf("\nStage:  %d - %d\n", stageInstance->startingPoint, stageInstance->endPoint);
	printf("Max stage speed: %.3lf [m/s]\n", stageInstance->maxStageSpeed);
	printf("Stage path [m]:\n\t");
	for (stageValueIndex = 0; stageValueIndex < defaultValue; stageValueIndex++)
	{
		printf("%.3lf, ", stageInstance->stageDistance[stageValueIndex]);
	}
	printf("\nStage speed[m/s]:\n\t");
	for (stageValueIndex = 0; stageValueIndex < defaultValue; stageValueIndex++)
	{
		printf("%.3lf, ", stageInstance->stageSpeeds[stageValueIndex]);
	}
	printf("\nAcceleration[m/s]:\n\t");
	for (stageValueIndex = 0; stageValueIndex < defaultValue; stageValueIndex++)
	{
		printf("%.2lf, ", stageInstance->stageAccelerations[stageValueIndex]);
	}
	printf("\nTimes[s]:\n\t");
	for (stageValueIndex = 0; stageValueIndex < defaultValue; stageValueIndex++)
	{
		printf("%.3lf, ", stageInstance->stageTimes[stageValueIndex]);
	}
	printf("\n");
}

void printRoute(ROUTE* routeInstance)
{
	int routeValueIndex;
	initializationCheck(routeInstance);
	printf("\nRoute... ");
	printf("\nRoute points: ");
	for (routeValueIndex = 0; routeValueIndex < routeInstance->numberOfPoints; routeValueIndex++)
	{
		printf("%d, ", routeInstance->points[routeValueIndex]);
	}
	printf("\nStage distance: ");
	for (routeValueIndex = 0; routeValueIndex < (routeInstance->numberOfPoints - 1); routeValueIndex++)
	{
		printf("%.3lf, ", routeInstance->space[routeValueIndex]);
	}
	printf("\nTotal distance: ");
	for (routeValueIndex = 0; routeValueIndex < routeInstance->numberOfPoints; routeValueIndex++)
	{
		printf("%.3lf, ", routeInstance->distance[routeValueIndex]);
	}
	printf("\n");
}