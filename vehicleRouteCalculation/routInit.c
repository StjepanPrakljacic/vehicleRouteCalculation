#include "routeCalculation.h"

/*
* Function addRoutePoints()
* Description: The function will allocate the memory for the Route points and it will set the values to predefined values
*	@param -  Route instance that can't be NULL
* Returns: void
*/
static void addRoutePoints(ROUTE* routeInstance)
{
	int pointsCounter = 0, status;
	printf("Enter the number of points: ");
	status = scanf("%d", &routeInstance->numberOfPoints);

	routeInstance->points = (int*)malloc(routeInstance->numberOfPoints * sizeof(int));
	if (routeInstance->points)
	{
		while (pointsCounter < routeInstance->numberOfPoints)
		{
			routeInstance->points[pointsCounter] = (pointsCounter + 1);
			pointsCounter++;
		}
	}
}

/*
* Function addRoutespaces()
* Description: The function will allocate the memory for the Route space and it will set the values to predefined values
*	@param -  Route instance that can't be NULL
* Returns: void
*/
static void addRoutespaces(ROUTE* routeInstance)
{
	int spaceCounter = 0, status;
	routeInstance->space = (double*)malloc((routeInstance->numberOfPoints - 1) * sizeof(double));
	if (routeInstance->space)
	{
		while (spaceCounter < routeInstance->numberOfPoints - 1)
		{
			routeInstance->space[spaceCounter] = 0;
			printf("Enter %d. route space: ", spaceCounter + 1);
			status = scanf("%lf", &routeInstance->space[spaceCounter]);
			spaceCounter++;
		}
	}
}

/*
* Function addRoutedistance()
* Description: The function will allocate the memory for the route distance and it will calculate the values with respect to Route space
*	@param -  Route instance that can't be NULL
* Returns: void
*/
static void addRoutedistance(ROUTE* routeInstance)
{
	int distanceCounter = 0;
	routeInstance->distance = (double*)malloc(routeInstance->numberOfPoints * sizeof(double));
	if (routeInstance->distance)
	{
		routeInstance->distance[distanceCounter] = 0.0;
		while (distanceCounter < routeInstance->numberOfPoints)
		{
			distanceCounter++;
			routeInstance->distance[distanceCounter] = routeInstance->space[distanceCounter - 1] + routeInstance->distance[distanceCounter - 1];
		}
	}
}

ROUTE* routeInitialize()
{
	ROUTE* routeInstance = (ROUTE*)malloc(sizeof(ROUTE));
	initializationCheck(routeInstance);
	addRoutePoints(routeInstance);
	addRoutespaces(routeInstance);
	addRoutedistance(routeInstance);
	return routeInstance;
}




