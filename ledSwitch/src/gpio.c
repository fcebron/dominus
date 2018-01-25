#include <stdio.h>
#include <stdlib.h>

const int GPIO_LED_NUMBER = 26;


/**
 * Initialization of the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing '0' if Output or '1' if Input 
 */
int intit_gpio(int gpio, int state) {
	// Creation:
	// 		Storing the gpio number as a string for future writing:
	char gpioNumber[2];
	itoa(gpio, gpioNumber, 10);  // 10 is for the decimal-base

	// 		Defining the gpio:
	FILE *GPIO_CREATION = fopen("/sys/class/gpio/export", "w");
	fprintf(GPIO_CREATION, gpioNumber);
	fclose(GPIO_CREATION);


	// Setting-up the type state of the gpio (input or output)
	// 		- Storing the gpio state as a string for future writing:
	char gpioState[1];
	itoa(gpioState, state, 10);

	// 		- Storing the path of the gpio for future writing:
	char stateFile[31];
	fprintf(stateFile, "/sys/class/gpio/gpio%d/direction", gpio);

	// 		- Setting-up the gpio:
	char state_gpio[4];
	if (state == 1) {
		state_gpio[0] = 'i';
		state_gpio[1] = 'n';
		state_gpio[2] = '\0';
	}
	else {
		state_gpio[0] = 'o';
		state_gpio[1] = 'u';
		state_gpio[2] = 't';
		state_gpio[3] = '\0';
	}
	FILE *GPIO_STATE = fopen(stateFile, "w");
	fprintf(GPIO_STATE, state_gpio);
	fclose(GPIO_CREATION);

	// Shutting down the GPIO:
	write_gpio(gpio, 0);

	// 		Pretty message:
	char state_char[7];
	if (state == 0) {
		state_char[0] = 'O';
		state_char[1] = 'u';
		state_char[2] = 't';
		state_char[3] = 'p';
		state_char[4] = 'u';
		state_char[5] = 't';
		state_char[6] = '\0';
	}
	else {
		state_char[0] = 'I';
		state_char[1] = 'n';
		state_char[2] = 'p';
		state_char[3] = 'u';
		state_char[4] = 't';
		state_char[5] = '\0';
	}

	printf("The GPIO_%d is created as an %s !\n", gpio, state_char);
	return 0;
}


/**
 * Writing on the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing the expected state of the GPIO: '0' for Off and '1' for On.
 */
write_gpio(int gpio, int state) {
	// Changing the state:
	// 		Storing the gpio number as a string for future writing:
	char gpioNumber[2];
	itoa(gpio, gpioNumber, 10);  // 10 is for the decimal-base

	// 		Changing the state of the gpio:
	char path[31];
	sprintf(path, "/sys/class/gpio/export/%s/value", gpioNumber);
	FILE *GPIO_VALUE = fopen(path, "w");
	fprintf(GPIO_VALUE, state);
	fclose(GPIO_VALUE);

	printf("The GPIO_%d's value is %d \n", gpio, state);
	return 0;
}


/**
 * Closing the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 */
int destroy_gpio(int gpio) {
	// Shutting down the GPIO:
	write_gpio(gpio, 0);

	// Closing:
	// 		Storing the gpio number as a string for future writing:
	char gpioNumber[2];
	itoa(gpio, gpioNumber, 10);  // 10 is for the decimal-base

	// 		Closing the gpio:
	FILE *GPIO_DESTRUCTION = fopen("/sys/class/gpio/unexport", "w");
	fprintf(GPIO_DESTRUCTION, gpioNumber);
	fclose(GPIO_DESTRUCTION);


	printf("The GPIO_%d was closed !\n", gpio);
	return 0;
}


int main() {
	// Initialization of the GPIO:
	intit_gpio(GPIO_LED_NUMBER, 1);

	// Writing:
	write_gpio(GPIO_LED_NUMBER, 1);

	//Destroying the GPIO:
	destroy_gpio(GPIO_LED_NUMBER);
}