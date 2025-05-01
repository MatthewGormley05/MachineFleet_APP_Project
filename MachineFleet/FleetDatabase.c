#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct node
{
	char chassisNum[20];
	char machineryMake[20];
	char machineryModel[20];
	int year;
	double cost;
	double currentValue;
	double currentMileage;
	double nextServiceMile;
	char owner[30];
	char email[30];
	int phone[10];
	int machineType; //1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer
	int breakdownNum; //1 = never, 2 = <3, 3 = <5, 4 = >5
	struct node* NEXT;
	struct node* PREV;
}machine;

//Initialise psuedo-methods


//Main
void main()
{
	//Initialise Machine Structs
	machine* headPtr = NULL;
	machine* tailPtr = NULL;
	machine* newNode = NULL;
	machine* prev = NULL;

	//Variables
	int option = -10, loginMode, machineType;
	char machineOption[1], a[1] = "a", b[1] = "b", c[1] = "c", d[1] = "d", e[1] = "e", A[1] = "A", B[1] = "B", C[1] = "C", D[1] = "D", E[1] = "E";

	//Load Files

	//Prompt user login
	loginMode = userLogin();

	//Prompt initial user options
	option = displayOptions();

	//Sentinal While Loop
	while (option != -1)
	{
		//Reset variables
		machineOption;
		machineType = 0;

		//Option 1: Add machine
		if (option == 1)
		{

		}

		//Option 2: Display all machines to screen
		else if (option == 2)
		{

		}

		//Option 3: Display machines details
		else if (option == 3)
		{

		}

		//Option 4: Update a machine's details
		else if (option == 4)
		{

		}

		//Option 5: Delete machine
		else if (option == 5)
		{

		}

		//Option 6: Generate statistics (a - d) based on machinery type
		else if (option == 6)
		{
			printf("\nPlease enter the machine you wish to see the statistics for:");
			printf("(a) Tractor");
			printf("(b) Excavator");
			printf("(c) Roller");
			printf("(d) Crane");
			printf("(e) Mixer\n");
			scanf("%s", machineOption);

			//Tractor
			if (strcmp(machineOption, a) == 0 || strcmp(machineOption, A) == 0)
			{
				machineType = 1;
				displayStats(machineType); //Feed Fleet
			}

			//Excavator
			else if (strcmp(machineOption, b) == 0 || strcmp(machineOption, B) == 0)
			{
				machineType = 2;
				displayStats(machineType); //Feed Fleet
			}

			//Roller
			else if (strcmp(machineOption, c) == 0 || strcmp(machineOption, C) == 0)
			{
				machineType = 3;
				displayStats(machineType); //Feed Fleet
			}

			//Crane
			else if (strcmp(machineOption, d) == 0 || strcmp(machineOption, D) == 0)
			{
				machineType = 4;
				displayStats(machineType); //Feed Fleet
			}

			//Mixer
			else if (strcmp(machineOption, e) == 0 || strcmp(machineOption, E) == 0)
			{
				machineType = 5;
				displayStats(machineType); //Feed Fleet
			}

			//Invalid input
			else
			{
				printf("\nInvalid input...\n");
			}
		}

		//Option 7: Print all machine details into a report
		else if (option == 7)
		{

		}

		//Option 8: List all the machinery in order of current valuation
		else if (option == 8)
		{

		}

		//Option -1: End Program
		else if (option == -1)
		{
			printf("\nEnding Program...\n");
		}

		//Invalid Input
		else if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != -1)
		{
			printf("\nInvalid input entered, please enter a valid input.\n");
		}

		//Ask for user option again at end of loop
		option = displayOptions();

	}//End of while Loop

	//At end of loop run saveAll method

}//End of main

//userLogin -> prompts user for login
int userLogin()
{
	int loginMode, choice;
	bool attemptingLogin;
	char username1[20], username2[20], adminName[20];
	char password1[20], password2[20], adminPassword[20];
	char usernameInput[20], passwordInput[20];

	int loginTesting = 1;//Testing for login info 

	//Open the logins file and feed them to the variables

	//Prompt user to log in or quit
	printf("Do you wish to log in (1 for yes, -1 for no): ");
	scanf("%d", &choice);

	//If the user is trying to log in
	if (choice == 1)
	{
		while (choice == 1)
		{
			printf("\nAttempting login.\n");
			//Prompt user for login details

			//UnSuccessful login (-1)
			if (loginTesting == 0)
			{
				loginMode = -1;
				printf("\nUnsuccessful User Login\n");
			}

			//Successful login (1)
			if (loginTesting == 1)
			{
				loginMode = 1;
				printf("\nSuccessful User Login.\n");
			}

			//Admin Login (2)
			if (loginTesting == 2)
			{
				loginMode = 2;
				printf("\nSuccessful Admin Login.\n");
			}

			//Prompt user to log in or quit
			printf("\nDo you wish to try again (1 for yes, -1 for no): ");
			scanf("%d", &choice);
		}

		//Failed login attempt
		if (choice == -1 && loginMode == -1)
		{
			printf("\nLogin failed, ending program...\n");
		}
	}//End of log in attempt

	//If user does not want to attempt a log in
	else
	{
		printf("\nNot attempting login, ending program...\n\n");
		loginMode = -1;
	}

	return loginMode;
}

//displayOptions -> displays loop options to user
int displayOptions()
{
	int option;
	printf("Please enter option: ");
	scanf("%d", &option);

	return option;
}

//addMachine -> adds machine to position in LL based on Chassis Number (Unique)

//displayAll -> display all machine's details on screen
int displayAll()
{

}

//displayStats -> display statistics of chosen machine types based on user input
int displayStats(int machineType) //Feed fleet
{
	//Loop that tracks machine num and failures of the selected type

	int machineCount = 0; //Update
	int machineFailures = 0; //Update

	int totalSuccesses = (machineCount - machineFailures);
	float successesPercentage = (totalSuccesses / machineCount) * 100;

	//Tractors
	if (machineType == 1 && machineCount > 0)
	{
		printf("Generating statistics for Tractor Machinery...");
		printf("There are %f of the %d Tractors in the fleet have had 0 breakdowns.", &successesPercentage, machineCount);
	}

	//Excavators
	else if (machineType == 2 && machineCount > 0)
	{
		printf("Generating statistics for Excavator Machinery...");
		printf("There are %f of the %d Excavators in the fleet have had 0 breakdowns.", &successesPercentage, machineCount);
	}

	//Rollers
	else if (machineType == 3 && machineCount > 0)
	{
		printf("Generating statistics for Roller Machinery...");
		printf("There are %f of the %d Rollers in the fleet have had 0 breakdowns.", &successesPercentage, machineCount);
	}

	//Cranes
	else if (machineType == 4 && machineCount > 0)
	{
		printf("Generating statistics for Crane Machinery...");
		printf("There are %f of the %d Cranes in the fleet have had 0 breakdowns.", &successesPercentage, machineCount);
	}

	//Mixers
	else if (machineType == 5 && machineCount > 0)
	{
		printf("Generating statistics for Mixer Machinery...");
		printf("There are %f of the %d Mixers in the fleet have had 0 breakdowns.", &successesPercentage, machineCount);
	}

	//No machines
	else if (machineCount <= 0)
	{
		printf("There are no machines of the selected type in the fleet.");
	}
}

//listAll -> list all machines in order of current valuation

//(ADMIN) displayMachine -> displays details of specific machine using inputted Chassis Number

//(ADMIN) updateMachine -> update details of specific machine using inputted Chassis Number

//deleteMachine -> delete machine based on chassis num

//printAll -> calls on displayAll and then saveAll

//loadAll -> loads machine fleet from file

//saveAll -> prints all machines + stats to file