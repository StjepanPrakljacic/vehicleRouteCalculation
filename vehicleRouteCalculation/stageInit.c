#include "routeCalculation.h"

void stageInitialize(ROUT* routInstance)
{
	initializationCheck(routInstance);
	int stageCounter = 0;
	while (stageCounter < routInstance->numberOfPoints - 1)
	{
		routInstance->stages[stageCounter] = (STAGE*)malloc(sizeof(STAGE));
		if (routInstance->stages[stageCounter])
		{
			int stageValueIndex = 0;
			routInstance->stages[stageCounter]->startingPoint = routInstance->points[stageCounter];
			routInstance->stages[stageCounter]->endPoint = routInstance->points[stageCounter + 1];
			routInstance->stages[stageCounter]->totalStageDistance = routInstance->distance[stageCounter + 1];
			routInstance->stages[stageCounter]->maxStageSpeed = 0.0;
			while (stageValueIndex < defaultValue)
			{
				routInstance->stages[stageCounter]->stageDistance[stageValueIndex] = 0.0;
				routInstance->stages[stageCounter]->stageSpeeds[stageValueIndex] = 0.0;
				routInstance->stages[stageCounter]->stageAccelerations[stageValueIndex] = 0;
				routInstance->stages[stageCounter]->stageTimes[stageValueIndex] = 0.0;
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
