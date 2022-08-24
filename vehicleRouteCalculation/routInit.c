#include "routeCalculation.h"

/*
* Function addRoutPoints()
* Description: The function will allocate the memory for the rout points and it will set the values to predefined values
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutPoints(ROUT* routInstance)
{
	int pointsCounter = 0, status;
	printf("Enter the number of points: ");
	status = scanf("%d", &routInstance->numberOfPoints);

	routInstance->points = (int*)malloc(routInstance->numberOfPoints * sizeof(int));
	if (routInstance->points)
	{
		while (pointsCounter < routInstance->numberOfPoints)
		{
			routInstance->points[pointsCounter] = (pointsCounter + 1);
			pointsCounter++;
		}
	}
}

/*
* Function addRoutspaces()
* Description: The function will allocate the memory for the rout space and it will set the values to predefined values
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutspaces(ROUT* routInstance)
{
	int spaceCounter = 0, status;
	routInstance->space = (double*)malloc((routInstance->numberOfPoints - 1) * sizeof(double));
	if (routInstance->space)
	{
		while (spaceCounter < routInstance->numberOfPoints - 1)
		{
			routInstance->space[spaceCounter] = 0;
			printf("Enter %d. rout space: ", spaceCounter + 1);
			status = scanf("%lf", &routInstance->space[spaceCounter]);
			spaceCounter++;
		}
	}
}

/*
* Function addRoutdistance()
* Description: The function will allocate the memory for the rout distance and it will calculate the values with respect to rout space
*	@param -  Rout instance that can't be NULL
* Returns: void
*/
static void addRoutdistance(ROUT* routInstance)
{
	int distanceCounter = 0;
	routInstance->distance = (double*)malloc(routInstance->numberOfPoints * sizeof(double));
	if (routInstance->distance)
	{
		routInstance->distance[distanceCounter] = 0.0;
		while (distanceCounter < routInstance->numberOfPoints)
		{
			distanceCounter++;
			routInstance->distance[distanceCounter] = routInstance->space[distanceCounter - 1] + routInstance->distance[distanceCounter - 1];
		}
	}
}

ROUT* routInitialize()
{
	ROUT* routInstance = (ROUT*)malloc(sizeof(ROUT));
	initializationCheck(routInstance);
	addRoutPoints(routInstance);
	addRoutspaces(routInstance);
	addRoutdistance(routInstance);
	return routInstance;
}




