#include "routeCalculation.h"


int main()
{
	ROUTE* routeInstance = NULL;
	routeInstance = routeInitialize();
	stageInitialize(routeInstance);
	routeCalculate(routeInstance);
	return 0;
}