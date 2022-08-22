#include "vehicleRouteFunctions.h"

int main()
{
	ROUT* routInstance = NULL;
	int status; 
	status = routInitialize(&routInstance);
	if (status < 0)
	{
		fprintf(stderr, "Rout initialize Error");
		exit(EXIT_FAILURE);
	}
	status = stageInitialize(routInstance);
	if (status < 0)
	{
		fprintf(stderr, "Stage initialize Error");
		exit(EXIT_FAILURE);
	}

	status = routCalculate(routInstance);
	if (status < 0)
	{
		fprintf(stderr, "Rout calculation Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nThe route has been resolved! End of program!");
		free(routInstance);
		routInstance = NULL;
		exit(EXIT_SUCCESS);
	}
}