#include "vehicleRouteFunctions.h"

/*
* Function addRoutPoints()
* Description: The function will allocate the memory for the rout points and it will set the values to predefined values
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutPoints(ROUT* routInstance);

/*
* Function addRoutspaces()
* Description: The function will allocate the memory for the rout space and it will set the values to predefined values
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutspaces(ROUT* routInstance);

/*
* Function addRoutdistance()
* Description: The function will allocate the memory for the rout distance and it will calculate the values with respect to rout space
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutdistance(ROUT* routInstance);

/*
* Function addStage()
* Description: The function will set the values of all stages to predifined values with respect to given parametar
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addStage(ROUT* routInstance);

/*
* Function stageResolve()
* Description: The function will set the maximum speed of each driving stage through the menu. By starting the stage menu, the desired action is selected at the beginning of each stage.
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void stageResolve(STAGE* stageInstance);

/*
* Function stageStart()
* Description: The function will set the acceleration value in the acceleration array for the initial stage of the route
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void stageStart(STAGE* stageInstance);

/*
* Function addStageSpeed()
* Description: The function used as a menu to set the maximum speed for each stage
*	@param -  Stage instance that can't be NULL
* Returns: Maximum stage speed
*/
static double addStageSpeed(STAGE* stageInstance);

/*
* Function addStageSpeed()
* Description: The function used as a menu to select an action at the beginning of each stage
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void stageMenu(STAGE* stageInstance);

/*
* Function stageNextManu()
* Description: The function used as a menu to select an action of each stage
*	@param -  Stage instance that can't be NULL
* Returns: void
*/
static void stageNextManu(STAGE* stageInstance);

/*
* Function inputAccelerationSpeed()
* Description: The function used to enter the desired speed of acceleration at a particular stage
*	@param -  Stage instance that can't be NULL
* Returns: Stage speed
*/
static double inputAccelerationSpeed(STAGE* stageInstance);

/*
* Function acceleratedDrivingCalculation()
* Description: The function used to calculates the vehicle's acceleration
*	@param -  Stage instance that can't be NULL
*   @param -  Acceleration speed
* Returns: void
*/
static void acceleratedDrivingCalculation(STAGE* stageInstance, double accSpeed);

/*
* Function uniformDrivingCalculation()
* Description: The function used to calculates the vehicle's uniform driving 
*	@param -  Stage instance that can't be NULL
*   @param -  Next stage drivig action
* Returns: void
*/
static void uniformDrivingCalculation(STAGE* stageInstance, int driveType);

/*
* Function decelerationDrivigCalculation()
* Description: The function used to calculates the vehicle's deceleration
*	@param -  Stage instance that can't be NULL
*   @param -  The speed that the vehicle must reach at the stopping point
* Returns: void
*/
static void decelerationDrivigCalculation(STAGE* stageInstance, double decSpeed);

/*
* Function initializationCheck()
* Description: The function used to check initialization with respect to the passed instance
*	@param -  Instance to check
* Returns: void
*/
static void initializationCheck(void* instanceToCheck);

static int lastEntryIndex;
static int entryIndex;
static int accelerationDriveIndex;
static int decelerationDriveIndex;
static int uniformDriveIndex;
int actionState;
static int finish = 0;


int routInitialize(ROUT** routInstance)
{
	*routInstance = (ROUT*)malloc(sizeof(ROUT));
	if (*routInstance == NULL) return -1;
	
	(*routInstance)->numberOfPoints = 0;
	(*routInstance)->points = NULL;
	(*routInstance)->space = NULL;
	(*routInstance)->distance = NULL;
	
	addRoutPoints(*routInstance);
	addRoutspaces(*routInstance);
	addRoutdistance(*routInstance);
	return 0;
}

static void addRoutPoints(ROUT* routInstance)
{
	int i;
	printf("Enter the number of points: ");
	scanf("%d", &routInstance->numberOfPoints);

	routInstance->points = (int*)malloc(routInstance->numberOfPoints * sizeof(int));
	initializationCheck(routInstance->points);
	for (i = 0; i < routInstance->numberOfPoints; i++)
	{
		routInstance->points[i] = (i + 1);
	}
}

static void addRoutspaces(ROUT* routInstance)
{
	int i;
	routInstance->space = (double*)malloc((routInstance->numberOfPoints - 1) * sizeof(double));
	initializationCheck(routInstance->space);
	for (i = 0; i < (routInstance->numberOfPoints - 1); i++)
	{
		routInstance->space[i] = 0;
		printf("Enter %d. rout space: ", i + 1);
		scanf("%lf", &routInstance->space[i]);
	}
}

static void addRoutdistance(ROUT* routInstance)
{
	int i = 0;
	routInstance->distance = (double*)malloc(routInstance->numberOfPoints * sizeof(double));
	initializationCheck(routInstance->distance);
	routInstance->distance[i] = 0.0;
	for (i = 1; i < routInstance->numberOfPoints; i++)
	{
		routInstance->distance[i] = routInstance->space[i - 1] + routInstance->distance[i - 1];
	}

}

int stageInitialize(ROUT* routInstance)
{
	initializationCheck(routInstance);
	int i;
	for (i = 0; i < routInstance->numberOfPoints - 1; i++)
	{
		routInstance->stages[i] = (STAGE*)malloc(sizeof(STAGE));
		if (routInstance->stages[i] == NULL) return -1;
	}
	addStage(routInstance);
	return 0;
}

static void addStage(ROUT* routInstance)
{
	int i, j;
	for (i = 0; i < routInstance->numberOfPoints - 1; i++)
	{
		routInstance->stages[i]->startingPoint = routInstance->points[i];
		routInstance->stages[i]->endPoint = routInstance->points[i + 1];
		routInstance->stages[i]->maxStageSpeed = 0.0;
		routInstance->stages[i]->maxdistance = routInstance->distance[i + 1];
		for (j = 0; j < defaultValue; j++)
		{
			routInstance->stages[i]->stageSpeeds[j] = 0.0;
			routInstance->stages[i]->stageAccelerations[j] = 0;
			routInstance->stages[i]->stageDistance[j] = 0.0;
			routInstance->stages[i]->stageTimes[j] = 0.0;
		}
	}
}

int routCalculate(ROUT* routInstance)
{
	initializationCheck(routInstance);
	int i;
	printRout(routInstance);
	for (i = 0; i < routInstance->numberOfPoints - 1; i++)
	{
		entryIndex = 0;
		if (i == 0) stageStart(routInstance->stages[i]);
		else
		{
			/*Copying the final parameters of the previous stage as the initial value of the next stage*/
			routInstance->stages[i]->stageDistance[entryIndex] = routInstance->stages[i - 1]->stageDistance[lastEntryIndex];
			routInstance->stages[i]->stageSpeeds[entryIndex] = routInstance->stages[i - 1]->stageSpeeds[lastEntryIndex];
			routInstance->stages[i]->stageAccelerations[entryIndex] = routInstance->stages[i - 1]->stageAccelerations[lastEntryIndex];
			routInstance->stages[i]->stageTimes[entryIndex] = routInstance->stages[i - 1]->stageTimes[lastEntryIndex];
			if (i == routInstance->numberOfPoints - 2) finish = 1;
			stageResolve(routInstance->stages[i]);
		}
		printStage(routInstance->stages[i]);
	}
	return 0;
}

static void stageStart(STAGE* stageInstance)
{
	stageInstance->stageAccelerations[entryIndex] = acceleration;
	stageResolve(stageInstance);
}

static void stageResolve(STAGE* stageInstance)
{
	initializationCheck(stageInstance);
	printf("\nStage resolve for stage %d - %d", stageInstance->startingPoint, stageInstance->endPoint);
	printf("\nSTART\n");
	stageInstance->maxStageSpeed = addStageSpeed(stageInstance);
	stageMenu(stageInstance);
}


static double addStageSpeed(STAGE * stageInstance)
{
	printf("\nSelection of stage type:\n" "1. Driving on the highway at 25[m/s]\n" "2. Driving on the main road at 20[m/s]\n" "3. Driving on a side road at 15[m/s]\n" "4. Driving on the road at 10[m/s]\n");
	printf("Choose type: ");
	scanf("%d", &stageInstance->stageType);
	switch (stageInstance->stageType)
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

static void stageMenu(STAGE* stageInstance)
{
	int stageAction;
	printf("\nAction selection:\n" "1. Acceleration to max speed\n" "2. Acceleration at a certain speed\n" "3. Uniform driving\n" "4. Crossover / Half turn Passing\n" "5. Start at the traffic lights\n");
	printf("Choose action: ");
	scanf("%d", &stageAction);
	switch (stageAction)
	{
	case 1: acceleratedDrivingCalculation(stageInstance, stageInstance->maxStageSpeed);
		break;
	case 2: acceleratedDrivingCalculation(stageInstance, inputAccelerationSpeed(stageInstance));
		break;
	case 3: uniformDrivingCalculation(stageInstance, uniformDrive);
		break;
	case 4: uniformDrivingCalculation(stageInstance, crossoverPassing);
		break;
	case 5: acceleratedDrivingCalculation(stageInstance, trafficLightIntersection);
		break;
	default: printf("\nIncorrect entry!\nPlease enter again\n"); stageMenu(stageInstance);
		break;
	}
}

static void stageNextManu(STAGE* stageInstance)
{
	int stageAction;
	printf("\nSelecting the next action:\n" "1. Acceleration to max speed\n" "2. Acceleration at a certain speed\n" "3. Uniform drive\n" "4. Passing an intersection with a traffic light\n" "5. Slowing down to turn\n" "6. Slowing down to half a turn\n" "7. Stopping at traffic lights\n" "8. Stopping at the Finish\n");
	printf("Choose action: ");
	scanf("%d", &stageAction);
	switch (stageAction)
	{
	case 1: acceleratedDrivingCalculation(stageInstance, stageInstance->maxStageSpeed);
		break;
	case 2: acceleratedDrivingCalculation(stageInstance, inputAccelerationSpeed(stageInstance)); ;
		break;
	case 3: uniformDrivingCalculation(stageInstance, uniformDrive);
		break;
	case 4: uniformDrivingCalculation(stageInstance, trafficLightIntersection);
		break;
	case 5: decelerationDrivigCalculation(stageInstance, bendSpeed);
		break;
	case 6: decelerationDrivigCalculation(stageInstance, halfturnSpeed);
		break;
	case 7: decelerationDrivigCalculation(stageInstance, stopSpeed);
		break;
	case 8: decelerationDrivigCalculation(stageInstance, stopSpeed);
		break;
	default: printf("\nIncorrect entry!\nPlease enter again\n"); stageNextManu(stageInstance);
		break;
	}
}

static double inputAccelerationSpeed(STAGE* stageInstance)
{
	double speed;
	printf("\n");
	printf("Enter the desired acceleration speed [m/s]:");
	do
	{
		scanf("%lf", &speed);
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

static void acceleratedDrivingCalculation(STAGE* stageInstance, double accSpeed)
{
	double deltaT = 0, deltaS = 0;
	entryIndex++;
	deltaT = (accSpeed - stageInstance->stageSpeeds[entryIndex - 1]) / acceleration;
	stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[entryIndex - 1] + deltaT;
	stageInstance->stageSpeeds[entryIndex] = accSpeed;
	if (actionState == 1 || actionState == 2)stageInstance->stageAccelerations[entryIndex - 1] = acceleration; 
	deltaS = ((0.5 * acceleration * pow(deltaT, 2)) + (stageInstance->stageSpeeds[entryIndex - 1] * deltaT));
	stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[entryIndex - 1] + deltaS;
	accelerationDriveIndex = entryIndex;
	stageNextManu(stageInstance);
}

static void uniformDrivingCalculation(STAGE* stageInstance, int driveType)
{
	double deltaT;
	entryIndex++;
	stageInstance->stageSpeeds[entryIndex] = stageInstance->stageSpeeds[entryIndex - 1];
	if (driveType == crossoverPassing || driveType == trafficLightIntersection)
	{
		if (driveType == crossoverPassing)
		{
			stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[0] + stopDistance;
		}
		else stageInstance->stageDistance[entryIndex] = stageInstance->stageDistance[0] + stopDistance + 10;
		deltaT = (stageInstance->stageDistance[entryIndex] - stageInstance->stageDistance[entryIndex - 1]) / stageInstance->stageSpeeds[entryIndex];
		stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[entryIndex - 1] + deltaT;
		stageInstance->stageAccelerations[entryIndex] = acceleration;
	}
	uniformDriveIndex = entryIndex;
	stageNextManu(stageInstance);
}

static void decelerationDrivigCalculation(STAGE* stageInstance, double decSpeed)
{
	double brakingDistance, brakingTime, delatS;
	entryIndex++;
	brakingTime = (decSpeed - stageInstance->stageSpeeds[uniformDriveIndex]) / deceleration; //brzina na koju kocimo - prijasnja brzina 
	brakingDistance = (0.5 * deceleration * pow(brakingTime, 2) + (stageInstance->stageSpeeds[uniformDriveIndex] * brakingTime));
	delatS = stageInstance->maxdistance - stageInstance->stageDistance[accelerationDriveIndex] - brakingDistance - stopDistance; // stajemo 10 m prije krizanja

	/*Uniform drive section*/
	stageInstance->stageAccelerations[uniformDriveIndex] = deceleration;
	stageInstance->stageDistance[uniformDriveIndex] = stageInstance->stageDistance[accelerationDriveIndex] + delatS;
	stageInstance->stageTimes[uniformDriveIndex] = stageInstance->stageTimes[accelerationDriveIndex] + (delatS / stageInstance->stageSpeeds[uniformDriveIndex]);

	/*Deceleration section*/
	stageInstance->stageSpeeds[entryIndex] = decSpeed;
	stageInstance->stageTimes[entryIndex] = stageInstance->stageTimes[uniformDriveIndex] + brakingTime;
	if (finish == 1)stageInstance->stageDistance[entryIndex] = stageInstance->maxdistance;
	else stageInstance->stageDistance[entryIndex] = stageInstance->maxdistance - stopDistance;

	/* Traffic Light|| Intersection/half-turn section*/
	if (decSpeed == stopSpeed) //Rout End point 
	{
		stageInstance->stageDistance[entryIndex + 1] = stageInstance->stageDistance[entryIndex];
		if (finish == 1) stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex];
		else stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex] + waitingTime;
		if (finish == 0) stageInstance->stageAccelerations[entryIndex + 1] = acceleration;
	}
	else
	{
		stageInstance->stageSpeeds[entryIndex + 1] = decSpeed;
		stageInstance->stageDistance[entryIndex + 1] = stageInstance->maxStageSpeed;
		stageInstance->stageTimes[entryIndex + 1] = stageInstance->stageTimes[entryIndex] + (stopDistance / stageInstance->stageSpeeds[entryIndex + 1]);
	}
	/*The problem of lack of braking distance*/
	if (stageInstance->stageDistance[accelerationDriveIndex] > stageInstance->stageDistance[uniformDriveIndex])
	{
		printf("\nWarning! The braking distance is less than the acceleration distance!");
		printf("\nIf you are accelerating at the max speed of the stage, enter a speed lower than the max possible or enter a speed lower than the speed at which you are accelerating!\n");
		printf("\nThe maximum speed is: %.2lf ", stageInstance->maxStageSpeed);
		printf("\nAfter entering the new speed, continue with uniform movement and deceleration!");
		entryIndex = accelerationDriveIndex - 1;
		acceleratedDrivingCalculation(stageInstance, inputAccelerationSpeed(stageInstance));
	}
	decelerationDriveIndex = entryIndex;
	lastEntryIndex = decelerationDriveIndex + 1;
}

static void initializationCheck(void* instanceToCheck)
{
	if (instanceToCheck == NULL)
	{
		fprintf(stderr, "Instance is not initialized");
		exit(EXIT_FAILURE);
	}
}

void printStage(STAGE* stageInstance)
{
	int i;
	initializationCheck(stageInstance);
	printf("\nStage:  %d - %d\n", stageInstance->startingPoint, stageInstance->endPoint);
	printf("Max stage speed: %.3lf [m/s]\n", stageInstance->maxStageSpeed);
	printf("Stage path [m]:\n\t");
	for (i = 0; i < defaultValue; i++)
	{
		printf("%.3lf, ", stageInstance->stageDistance[i]);
	}
	printf("\nStage speed[m/s]:\n\t");
	for (i = 0; i < defaultValue; i++)
	{
		printf("%.3lf, ", stageInstance->stageSpeeds[i]);
	}
	printf("\nAcceleration[m/s]:\n\t");
	for (i = 0; i < defaultValue; i++)
	{
		printf("%.2lf, ", stageInstance->stageAccelerations[i]);
	}
	printf("\nTimes[s]:\n\t");
	for (i = 0; i < defaultValue; i++)
	{
		printf("%.3lf, ", stageInstance->stageTimes[i]);
	}
	printf("\n");
}

void printRout(ROUT* routInstance)
{
	int i;
	initializationCheck(routInstance);
	printf("\nRout... ");
	printf("\nRout points: ");
	for (i = 0; i < routInstance->numberOfPoints; i++)
	{
		printf("%d, ", routInstance->points[i]);
	}
	printf("\nSpace between stages: ");
	for (i = 0; i < (routInstance->numberOfPoints - 1); i++)
	{
		printf("%.3lf, ", routInstance->space[i]);
	}
	printf("\nPath: ");
	for (i = 0; i < routInstance->numberOfPoints; i++)
	{
		printf("%.3lf, ", routInstance->distance[i]);
	}
	printf("\n");
}

