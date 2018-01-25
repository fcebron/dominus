#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * Initialization of the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing '0' if Output or '1' if Input 
 */
int intit_gpio(char[2] gpioNumber, int state) {
	// Creation:
	// 		Defining the gpio:
	FILE *GPIO_CREATION = fopen("/sys/class/gpio/export", "w");
	fprintf(GPIO_CREATION, gpioNumber);
	fclose(GPIO_CREATION);


	// Setting-up the type state of the gpio (input or output)
	// 		- Storing the path of the gpio for future writing:
	char stateFile[31];
	fprintf(stateFile, "/sys/class/gpio/gpio%d/direction", gpioNumber);

	// 		- Setting-up the gpio:
	FILE *GPIO_STATE = fopen(stateFile, "w");
	if (state == 1) {
		fprintf(GPIO_STATE, "In");
	}
	else {
		fprintf(GPIO_STATE, "out");
	}
	fclose(GPIO_STATE);

	// Turning off the GPIO:
	write_gpio(gpioNumber, 0);

	// 		Pretty message:
	char state_char[7];
	if (state == 0) {
		printf("The GPIO_%s is created as an Output !\n", gpioNumber);
	}
	else {
		printf("The GPIO_%s is created as an Input !\n", gpioNumber);	
	}
	return 0;
}


/**
 * Writing on the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing the expected state of the GPIO: '0' for Off and '1' for On.
 */
int write_gpio(char[2] gpioNumber, int state) {
	// Changing the state:

	// 		Changing the state of the gpio:
	char path[31];
	sprintf(path, "/sys/class/gpio/export/%s/value", gpioNumber);

	FILE *GPIO_VALUE = fopen(path, "w");
	if (state == 1) {
		fprintf(GPIO_VALUE, "1");
	}
	else {
		fprintf(GPIO_VALUE, "0");
	}
	fclose(GPIO_VALUE);

	printf("The GPIO_%s's value is %d \n", gpioNumber, state);
	return 0;
}


/**
 * Closing the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 */
int destroy_gpio(char[2] gpioNumber) {
	// Turning off the GPIO:
	write_gpio(gpioNumber, 0);

	// Closing:
	// 		Closing the gpio:
	FILE *GPIO_DESTRUCTION = fopen("/sys/class/gpio/unexport", "w");
	fprintf(GPIO_DESTRUCTION, gpioNumber);
	fclose(GPIO_DESTRUCTION);

	printf("The GPIO_%s was closed !\n", gpioNumber);
	return 0;
}


int main() {
	const char[] GPIO_LED_NUMBER = "26";
	// GPIO_LED_NUMBER[0] = '2';
	// GPIO_LED_NUMBER[1] = '6';
	// GPIO_LED_NUMBER[2] = '\0';

	// Initialization of the GPIO:
	intit_gpio(GPIO_LED_NUMBER, 1);

	// Writing:
	write_gpio(GPIO_LED_NUMBER, 1);

	// To let some time pass:
	int i;
	for (i = 0; i < 150; i ++) {
		printf("i = %d\n", i);
	}

	//Destroying the GPIO:
	destroy_gpio(GPIO_LED_NUMBER);

	return 0;
}