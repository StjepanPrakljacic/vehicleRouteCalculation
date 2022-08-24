#include "routeCalculation.h"


int main()
{
	ROUT* routInstance = NULL;
	routInstance = routInitialize();
	stageInitialize(routInstance);
	routCalculate(routInstance);
	return 0;
}