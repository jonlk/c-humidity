#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double REVISED_MAGNUS_BETA = 17.625;
const double REVISED_MAGNUS_LAMBDA = 243.04;

double calculate_dewpoint(double *tempC, double *relativeHumidityPercentage)
{
	double a = log(*relativeHumidityPercentage / 100);
	double b = (REVISED_MAGNUS_BETA * *tempC) / (REVISED_MAGNUS_LAMBDA + *tempC);

	double humidity_multiplier = (a + b);

	double numerator = REVISED_MAGNUS_LAMBDA * humidity_multiplier;
	double denominator = REVISED_MAGNUS_BETA - humidity_multiplier;

	double result = numerator / denominator;

	return result;
}

double calculate_relative_humidity(double *tempC, double *dewpointC)
{
	double numerator = exp((REVISED_MAGNUS_BETA * *dewpointC) / (REVISED_MAGNUS_LAMBDA + *dewpointC));
	double denominator = exp((REVISED_MAGNUS_BETA * *tempC) / (REVISED_MAGNUS_LAMBDA + *tempC));

	double result = (numerator / denominator) * 100;

	return result;
}

void dewpoint_input()
{
	fputs("Enter temp in Celsius: ", stdout);

	double temp_celsius;
	scanf("%lf", &temp_celsius);

	fputs("Enter humidity percentage: ", stdout);

	double humidity;
	scanf("%lf", &humidity);

	double result = calculate_dewpoint(&temp_celsius, &humidity);
	printf("Dewpoint is %.2lf C\n", result);
}

void relative_humidity_input()
{
	fputs("Enter temp in Celsius: ", stdout);

	double temp_celsius;
	scanf("%lf", &temp_celsius);

	fputs("Enter dewpoint in Celsius: ", stdout);

	double dewpoint_celsius;
	scanf("%lf", &dewpoint_celsius);

	double result = calculate_relative_humidity(&temp_celsius, &dewpoint_celsius);
	printf("Relative Humidity is %.0lf %% \n", result);
}

int main()
{
	fputs("(D)ewpoint or (R)elative Humidity? ", stdout);

	char selection[2];
	fgets(selection, 2, stdin);

	switch (selection[0])
	{
	case (68):
	case (100):
		dewpoint_input();
		break;
	case (82):
	case (114):
		relative_humidity_input();
		break;
	default:
		puts("\ninvalid entry\n");
		break;
	};

	return EXIT_SUCCESS;
}
