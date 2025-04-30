#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

//Define Machine Struct

//Initialise psuedo-methods

//Main
void main()
{
	//Initialise Machine Structs

	//Variables
	int option, loginMode;

	//Load Files

	//Prompt user login
	loginMode = userLogin();

	//Prompt initial user options
	option = displayOptions();

	//Sentinal While Loop
	while(option != -1)
	{
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

		}

		//Option 7: Print all machine details into a report
		else if (option == 7)
		{

		}

		//Option 8: List all the machinery in order of current valuation
		else if (option == 8)
		{

		}

		//Option 9: End Program
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

//userLogin Method -> prompts user for login
int userLogin()
{
	int loginMode, choice;
	bool attemptingLogin;
	char username1[20], username2[20], adminName[20];
	char password1[20], password2[20], adminPassword[20];
	char usernameInput[20], passwordInput[20];

	int loginTesting;//Testing for login info 

	//Open the logins file and feed them to the variables

	//Prompt user to log in or quit
	printf("\nDo you wish to log in (1 for yes, -1 for no): ");
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
		printf("\nNot attempting login, ending program...\n");
		loginMode = -1;
	}

	return loginMode;
}

//displayOptions Method -> displays loop options to user
int displayOptions()
{
	int option;

	return option;
}

//addMachine Method -> adds machine to position in LL based on Chassis Number (Unique)

//displayAll Method -> display all machine's details on screen

//displayStats Method -> display statistics of chosen machine types based on user input

//listAll Method -> list all machines in order of current valuation

//(ADMIN) displayMachine Method ) -> displays details of specific machine using inputted Chassis Number

//(ADMIN) updateMachine Method  -> update details of specific machine using inputted Chassis Number

//deleteMachine Method -> delete machine based on chassis num

//printAll Method -> calls on displayAll and then saveAll

//loadAll Method -> loads machines from file

//saveAll Method -> prints all machines + stats to file