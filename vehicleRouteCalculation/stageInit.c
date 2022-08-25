#include "routeCalculation.h"

void stageInitialize(ROUTE* routeInstance)
{
	initializationCheck(routeInstance);
	int stageCounter = 0;
	while (stageCounter < routeInstance->numberOfPoints - 1)
	{
		routeInstance->stages[stageCounter] = (STAGE*)malloc(sizeof(STAGE));
		if (routeInstance->stages[stageCounter])
		{
			int stageValueIndex = 0;
			routeInstance->stages[stageCounter]->startingPoint = routeInstance->points[stageCounter];
			routeInstance->stages[stageCounter]->endPoint = routeInstance->points[stageCounter + 1];
			routeInstance->stages[stageCounter]->totalStageDistance = routeInstance->distance[stageCounter + 1];
			routeInstance->stages[stageCounter]->maxStageSpeed = 0.0;
			while (stageValueIndex < defaultValue)
			{
				routeInstance->stages[stageCounter]->stageDistance[stageValueIndex] = 0.0;
				routeInstance->stages[stageCounter]->stageSpeeds[stageValueIndex] = 0.0;
				routeInstance->stages[stageCounter]->stageAccelerations[stageValueIndex] = 0;
				routeInstance->stages[stageCounter]->stageTimes[stageValueIndex] = 0.0;
				stageValueIndex++;
			}
		}
		else
		{
			fprintf(stderr, "Stage allocation Error");
			exit(EXIT_FAILURE);
		}
		stageCounter++;
	}
}
