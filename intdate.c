////////////////////////////////////////////////////////////////////////////////
// This File:        intdate.c
// Other Files:      sendsig.c , division.c
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

// Set up number of seconds for alarm
int sec = 3;
// Counter to track SIGUSR1
int count = 0;

// SIGINT Handler
void handler_SIGINT(){
	// Print the number of times SIGSUR1 was received
	printf("SIGINT recieved.\nSIGUSR1 was recieved %d times. Exiting now\n", count);
	exit(0);
}

// SIGSUR1 Handler 
void handler_SIGUSR1(){
	printf("SIGUSR1 caught!\n");
	// SIGSUR1 Counter
	count++;
}

// SIGALRM Handler
void handler_SIGALRM(){
	// Getting current time and date
	time_t curr_time = time(NULL);
	struct tm *tm = localtime(&curr_time);
	
	// Printing pid and time 
        printf("PID: %d | Current Time: %s", getpid(), asctime(tm));
        
	// Re arm alarm
	alarm(sec);
	
	return;
}

// This program prints out pid, date and time every 3 seconds 
int main(){
	// Description of program
	printf("Pid and time will be printed every 3 seconds.\n"
			"Enter ^C to end the program.\n");

	// Setting up signal handler for SIGALRM
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = handler_SIGALRM;
	act.sa_flags = 0;
	// Checking the return type for SIGALRM
	if ((sigaction(SIGALRM, &act, NULL)) != 0){
		printf("Error setting handler for SIGALRM");
	}
	
	// Setting up signal handler for SIGUSR1
        struct sigaction useract;
        memset(&useract, 0, sizeof(useract));
        useract.sa_handler = handler_SIGUSR1;
        useract.sa_flags = 0;
        // Checking the return type for SIGUSR1
        if ((sigaction(SIGUSR1, &useract, NULL)) != 0){
                printf("Error setting handler for SIGUSR1");
        }

	// Setting up the signal handler
        struct sigaction intact;
        memset(&intact, 0, sizeof(intact));
        intact.sa_handler = handler_SIGINT;
        intact.sa_flags = 0;
        // Checking the return type for SIGINT
        if ((sigaction(SIGINT, &intact, NULL)) != 0){
                printf("Error setting handler for SIGUSR1");
        }

	// Setting up alarm
	// causing SIGALRM to be sent
	alarm(sec);

	while(1){
	}
	return(0);
}
