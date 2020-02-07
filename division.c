////////////////////////////////////////////////////////////////////////////////
// This File:        division.c
// Other Files:      sendsig.c , intdate.c
// Semester:         CS 354 Spring 2019
//
// Author:           Omjaa Rai
// Email:            orai@wisc.edu
// CS Login:         omjaa
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int numerator; // First integer
int denominator; // Second integer
int count; // number of successful operations

//  SIGINT Handler
//  It prints a how many sucessful operations and ends program
void handler_SIGINT() {
        printf("\nTotal number of operations completed successfully: %d\n"
                        "The program will be terminated.\n", count);
        exit(0);
}

// SIGFPE Handler
void handler_SIGFPE() {
	printf("Error: a division by 0 operation was attempted.\n"
			"Total number of operations completed successfully: %d\n"
			"The program will be terminated.\n", count);
	exit(0);
}

// This program requests the user enter a numerator and denominator to find the
// quotient and the remainder.
// The program keeps count of the number of sucessful divisions.
int main() {

	// Setting up signal handler for SIGFPE
        struct sigaction setFPE;
        memset(&setFPE, 0, sizeof(setFPE));
        setFPE.sa_handler = handler_SIGFPE;
        setFPE.sa_flags = 0;

        // Checking the return type for SIGFPE
        if ((sigaction(SIGFPE, &setFPE, NULL)) != 0){
                printf("Error setting handler for SIGFPE");
        }

	// Setting up signal handler for SIGINT
        struct sigaction setINT;
        memset(&setINT, 0, sizeof(setINT));
        setINT.sa_handler = handler_SIGINT;
        setINT.sa_flags = 0;
       	
        // Checking the return type for SIGINT
        if ((sigaction(SIGINT, &setINT, NULL)) != 0){
                printf("Error setting handler for SIGINT");
        }

	while(1) {

		// Prompting user for first integer, numerator
		printf("Enter first integer: ");
		
		const int bufsize = 100;
		char buffer[bufsize];
		if(fgets(buffer, bufsize, stdin) != NULL) {
			numerator = atoi(buffer);
			
			// Prompting user for second integer, denominator
			printf("Enter second integer: ");
			if(fgets(buffer, bufsize, stdin) != NULL) {
				denominator = atoi(buffer);
			}
			else {
				printf("ERROR");
				exit(0);
			}
		}
		else {
			printf("ERROR");
			exit(0);
		}

		//doing the division and printing the result
		int result = numerator/denominator;
		int remainder = numerator%denominator;
		count++;
		printf("%d / %d is %d with a remainder of %d\n", numerator, denominator, result, remainder);
	}

	return(0);

}
