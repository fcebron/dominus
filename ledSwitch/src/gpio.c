#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <wchar.h>
#include <wctype.h>
#include <limits.h>

/* #################################### */
/* ##            PROTOTYPES          ## */
/* #################################### */
int write_gpio(const char*, int);

int init_gpio(const char*, int);

int destroy_gpio(const char*);



/* #################################### */
/* ##               MAIN             ## */
/* #################################### */
int main() 
{	
	const char *gpioLedNumber = "26";

	// Initialization of the GPIO:
	init_gpio(gpioLedNumber, 1);

	// Writing:
	write_gpio(gpioLedNumber, 1);

	// To let some time pass:
	int i;
	for (i = 0; i < 150; i ++) {
		printf("i = %d\n", i);
	}

	//Destroying the GPIO:
	destroy_gpio(gpioLedNumber);

	return 0;
}


/* #################################### */
/* ##            FUNCTIONS           ## */
/* #################################### */
/**
 * Writing on the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing the expected state of the GPIO: '0' for Off and '1' for On.
 */
int write_gpio(const char *gpioNumber, int state) {
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
 * Initialization of the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 * @param state: int containing '0' if Output or '1' if Input 
 */
int init_gpio(const char *gpioNumber, int state) {
	// Creation:
	// 		Defining the gpio:
	FILE *GPIO_CREATION = fopen("/sys/class/gpio/export", "w");
	fprintf(GPIO_CREATION, gpioNumber);
	fclose(GPIO_CREATION);


	// Setting-up the type state of the gpio (input or output)
	// 		- Storing the path of the gpio for future writing:
	unsigned char *stateFile[31];
	fprintf(stateFile, "/sys/class/gpio/gpio%s/direction", gpioNumber);

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
	if (state == 0) {
		printf("The GPIO_%s is created as an Output !\n", gpioNumber);
 	}
 	else {
 		printf("The GPIO_%s is created as an Input !\n", gpioNumber);	
 	}
 	return 0;
}


/**
 * Closing the GPIO
 * 
 * @param gpio: int containing the number of the GPIO
 */
int destroy_gpio(const char *gpioNumber) {
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
