#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct machine
{
	int chassisNum; //Unique
	char machineryMake[50];
	char machineryModel[50];
	int year; //Must be 4 nums, 1950 - 2025
	double cost;
	double currentValue;
	double currentMileage;
	double nextServiceMile;
	char owner[50];
	char email[50];
	long phone;
	int machineType; //1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer
	int breakdownNum; //1 = never, 2 = <3, 3 = <5, 4 = >5

	struct node* NEXT;
	struct node* PREV;
}machineT;

//Initialise psuedo-methods
int userLogin();
int displayOptions();
int checkChassis(machineT* top, int searchNum);
int length(machineT* top);
int addFirstMachine(machineT** top, machineT** end, int pos);
int addLastMachine(machineT** end, int pos);
int addMachine(machineT* top, int pos);
int displayAll(machineT* top);
int displayStats(machineT* top, int machineType);
void listAll(machineT* top);
int displayMachine(machineT* top, int searchTerm);
int updateMachine(machineT* top, int searchTerm);
void deleteMachine(machineT** top, machineT** end, int searchTerm);
void saveMachines(machineT* top);
void loadMachines(machineT** end, machineT** top);


void main()
{
	machineT* headPtr = NULL;
	machineT* tailPtr = NULL;
	machineT* newNode = NULL;
	machineT* prev = NULL;

	bool chassisTaken = false;
	int option = -10, loginMode, machineType, chassisInput;
	char machineOption[1], a[1] = "a", b[1] = "b", c[1] = "c", d[1] = "d", e[1] = "e", A[1] = "A", B[1] = "B", C[1] = "C", D[1] = "D", E[1] = "E";
	char emptyString = "\0";

	loginMode = userLogin(); //-1 = Unsuccessful, 1 = Successful, 2 = Admin

	if (loginMode == 1 || loginMode == 2)
	{
		loadMachines(&tailPtr, &headPtr);

		option = displayOptions();

		while (option != -1)
		{
			//Reset variables
			machineOption;
			machineType = 0;
			chassisTaken = false;
			chassisInput = 0;

			//Option 1: Add machine
			if (option == 1)
			{
				printf("\nPlease enter the chassis number of the new machine: ");
				scanf("%d", &chassisInput);

				chassisTaken = checkChassis(headPtr, chassisInput);
				
				if (chassisTaken == false && chassisInput > 0)
				{
					printf("\nChassis Number is free.\n");

					if (headPtr == NULL || chassisInput < headPtr->chassisNum)
					{
						addFirstMachine(&headPtr, &tailPtr, chassisInput);
					}
					
					else if ((headPtr != NULL && tailPtr == NULL) || chassisInput > tailPtr->chassisNum)
					{
						addLastMachine(&tailPtr, chassisInput);
					}
					
					else if (chassisInput<1)
						printf("Invalid Chassis number\n");

					else
					{
						addMachine(headPtr, chassisInput);
					}
				}

				else if (chassisInput <= 0)
				{
					printf("Chassis Number too low.");
				}

				else 
				{
					printf("Chassis Number already taken.");
				}
				
			}

			//Option 2: Display all machines to screen
			else if (option == 2)
			{
				displayAll(headPtr);
			}

			//Option 3: Display a machine's details (ADMIN)
			else if (option == 3 && loginMode == 2)
			{
				printf("\nPlease enter the chassis number: ");
				scanf("%d", &chassisInput);

				if(headPtr != NULL)
					displayMachine(headPtr, chassisInput);
			}

			//Option 4: Update a machine's details (ADMIN)
			else if (option == 4 && loginMode == 2)
			{
				printf("\nPlease enter the chassis number: ");
				scanf("%d", &chassisInput);

				updateMachine(headPtr, chassisInput);
			}

			//Option 5: Delete machine
			else if (option == 5)
			{
				printf("\nPlease enter the chassis number of the machine you wish to delete: ");
				scanf("%d", &chassisInput);

				deleteMachine(&headPtr, &tailPtr, chassisInput);
			}

			//Option 6: Generate statistics (a - d) based on machinery type
			else if (option == 6)
			{
				printf("\nPlease enter the machine you wish to see the statistics for:");
				printf("\n(a) Tractor");
				printf("\n(b) Excavator");
				printf("\n(c) Roller");
				printf("\n(d) Crane");
				printf("\n(e) Mixer\n");
				scanf("%s", machineOption);

				//Tractor
				if (strstr(machineOption, "a") != NULL || strstr(machineOption, "A") != NULL)
				{
					machineType = 1;
					displayStats(headPtr, machineType);
				}

				//Excavator
				else if (strstr(machineOption, "b") != NULL || strstr(machineOption, "B") != NULL)
				{
					machineType = 2;
					displayStats(headPtr, machineType);
				}

				//Roller
				else if (strstr(machineOption, "c") != NULL || strstr(machineOption, "C") != NULL)
				{
					machineType = 3;
					displayStats(headPtr, machineType);
				}

				//Crane
				else if (strstr(machineOption, "d") != NULL || strstr(machineOption, "D") != NULL)
				{
					machineType = 4;
					displayStats(headPtr, machineType);
				}

				//Mixer
				else if (strstr(machineOption, "e") != NULL || strstr(machineOption, "E") != NULL)
				{
					machineType = 5;
					displayStats(headPtr, machineType);
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
				saveMachines(headPtr);
			}

			//Option 8: List all the machinery in order of current valuation
			else if (option == 8)
			{
				listAll(headPtr);
			}

			//Option -1: End Program
			else if (option == -1)
			{
				printf("\nEnding Program...\n");
			}
			
			//User trying to access admin commands
			else if (loginMode == 1 && (option == 3 || option == 4))
			{
				printf("\nAdmin access required for this option.\n");
			}

			//Invalid input
			else if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != -1)
			{
				printf("\nInvalid input entered, please enter a valid input.\n");
			}

			//Catch-all
			else
			{
				printf("\nInvalid input entered, please enter a valid input.\n");
			}

			option = displayOptions();

		}//End of while Loop

		printf("\nExiting the program...\n");

		//At end of loop run saveAll method
		saveMachines(headPtr);
	}

	else {
		printf("\nUnsuccessful login, exiting program.\n");
	}

}//End of main

//userLogin -> prompts user for login
int userLogin()
{
	int loginMode, choice;
	bool attemptingLogin;
	char username1[20], username2[20], adminName[20];
	char password1[7], password2[7], adminPassword[7]; //Each password is 6 characters
	char usernameInput[20], passwordInput[20];

	//Open the logins file and feed them to the variables
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (fp == NULL)
	{
		printf("\nCould not open file...\n");
		loginMode = -1;
	}

	else
	{
		fscanf(fp, "%s %s %s %s %s %s", adminName, adminPassword, username1, password1, username2, password2);

		printf("Do you wish to log in (1 for yes, -1 for no): ");
		scanf("%d", &choice);

		if (choice == 1)
		{
			while (choice == 1)
			{
				printf("\nAttempting login.\n\n");

				printf("Please enter username: ");
				scanf("%s", usernameInput);

				printf("Please enter password: ");
				//Prevent user from seeing the characters inputted
				scanf("%s", passwordInput);

				//Successful login (1)
				if ((strcmp(username1, usernameInput) == 0 && strcmp(password1, passwordInput) == 0) || (strcmp(username2, usernameInput) == 0 && strcmp(password2, passwordInput) == 0))
				{
					loginMode = 1;
					printf("\nSuccessful User Login.\n");
					choice = 0;
				}

				//Admin Login (2)
				else if (strcmp(adminName, usernameInput) == 0 && strcmp(adminPassword, passwordInput) == 0)
				{
					loginMode = 2;
					printf("\nSuccessful Admin Login.\n");
					choice = 0;
				}

				//UnSuccessful login (-1)
				else
				{
					loginMode = -1;
					printf("\nUnsuccessful User Login\n");
					printf("\nDo you wish to try again (1 for yes, -1 for no): ");
					scanf("%d", &choice);
				}
			}

			//Failed login attempt
			if (choice == -1 && loginMode == -1)
			{
				printf("\nLogin failed...\n");
			}
		}//End of log in attempt

		//If user does not want to attempt a log in
		else
		{
			printf("\nNot attempting login.\n");
			loginMode = -1;
		}

		fclose(fp);

	}//End of else

	return loginMode;
}//End of login

//displayOptions -> displays loop options to user
int displayOptions()
{
	int option = 0;

	printf("\n\nEnter 1 to add a machine\n");
	printf("Enter 2 to display all machines to screen\n");
	printf("Enter 3 to display a machine's details (Admin Only)\n");
	printf("Enter 4 to update a machine's details (Admin Only)\n");
	printf("Enter 5 to delete a machine\n");
	printf("Enter 6 to generate statistics based on the machinery type.\n");
	printf("Enter 7 to print all machine details into a report file.\n");
	printf("Enter 8 to list all the machinery in order of current validation.\n");
	printf("Enter -1 to exit\n");
	printf("Please enter option: ");
	scanf("%d", &option);

	return option;
}

//checkChassis -> Checks to see if a machine with the selected chassis number exists
int checkChassis(machineT* top, int searchNum)
{
	bool chassisTaken = false;
	machineT* temp;

	temp = top;

	while (temp != NULL && chassisTaken == false)
	{
		if (temp->chassisNum == searchNum)
		{
			return true;
		}
		//printf("The value of the node is %d\n", temp->chassisNum);

		temp = temp->NEXT;
	}

	return false;
}

//lenth
int length(machineT* top)
{
	machineT* temp;
	int count = 0;

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}

	return count;

}

//addFirstMachine -> add first machine
int addFirstMachine(machineT** top, machineT** end, int pos)
{
	machineT* newMachine;
	int chassisNum = pos;
	bool validInput = false;

	newMachine = (machineT*)malloc(sizeof(machineT));

	newMachine->PREV = NULL;
	newMachine->NEXT = *top;

	printf("\nAdding first machine at position %d\n", pos);

	newMachine->chassisNum = chassisNum;

	printf("\nEnter the machinery make: ");
	scanf("%s", newMachine->machineryMake);

	printf("\nEnter the machinery model: ");
	scanf("%s", newMachine->machineryModel);

	while (validInput == false)
	{
		printf("\nEnter the year of manufacture: ");
		scanf("%d", &newMachine->year);
		if (newMachine->year >= 1950 && newMachine->year <= 2025)
		{
			validInput = true;
		}

		else
		{
			printf("\nInvalid year, please try again.");
		}
	}

	printf("\nEnter the cost: ");
	scanf("%lf", &newMachine->cost);

	printf("\nEnter the current valuation: ");
	scanf("%lf", &newMachine->currentValue);

	printf("\nEnter the current mileage: ");
	scanf("%lf", &newMachine->currentMileage);

	printf("\nEnter the next service mileage: ");
	scanf("%lf", &newMachine->nextServiceMile);

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner name (no spaces): ");
		scanf("%s", newMachine->owner);

		if (strstr(newMachine->owner, " ") != NULL)
			printf("\nInvalid input, please do not include spaces.");

		else
			validInput = true;
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner email address: ");
		scanf("%s", newMachine->email);

		//https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
		if (strstr(newMachine->email, "@") != NULL && strstr(newMachine->email, ".com") != NULL)
			validInput = true;

		else
			printf("\nInvalid input, please use @ and .com in the address");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner phone number: ");
		scanf("%ld", &newMachine->phone);

		if (newMachine->phone >= 0000000000 && newMachine->phone <= 9999999999)
			validInput = true;

		else
			printf("\nPlease enter a valid phone number.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine type (1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer): ");
		scanf("%d", &newMachine->machineType);

		if (newMachine->machineType > 0 && newMachine->machineType < 6)
			validInput = true;

		else
			printf("\nPlease enter a valid machine type.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine breakdowns this year (1 = never, 2 = <3, 3 = <5, 4 = >5): ");
		scanf("%d", &newMachine->breakdownNum);

		if (newMachine->breakdownNum > 0 && newMachine->breakdownNum < 5)
			validInput = true;

		else
			printf("\nPlease enter a valid breakdown number.");
	}

	if (*top != NULL)
		(*top)->PREV = newMachine;

	*top = newMachine;

	if (*end == NULL)
		*end = newMachine;
}

//addLastMachine -> add last machine
int addLastMachine(machineT** end, int pos)
{
	machineT* newMachine;
	machineT* temp;
	bool validInput = false;
	int chassisNum = pos;

	temp = *end;

	newMachine = (machineT*)malloc(sizeof(machineT));
	
	printf("\nAdding machine at the bottom of the database at position %d\n", pos);

	newMachine->chassisNum = chassisNum;

	printf("\nEnter the machinery make: ");
	scanf("%s", newMachine->machineryMake);

	printf("\nEnter the machinery model: ");
	scanf("%s", newMachine->machineryModel);

	while (validInput == false)
	{
		printf("\nEnter the year of manufacture: ");
		scanf("%d", &newMachine->year);
		if (newMachine->year >= 1950 && newMachine->year <= 2025)
		{
			validInput = true;
		}

		else
		{
			printf("\nInvalid year, please try again.");
		}
	}

	printf("\nEnter the cost: ");
	scanf("%lf", &newMachine->cost);

	printf("\nEnter the current valuation: ");
	scanf("%lf", &newMachine->currentValue);

	printf("\nEnter the current mileage: ");
	scanf("%lf", &newMachine->currentMileage);

	printf("\nEnter the next service mileage: ");
	scanf("%lf", &newMachine->nextServiceMile);

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner name (no spaces): ");
		scanf("%s", newMachine->owner);

		if (strstr(newMachine->owner, " ") != NULL)
			printf("\nInvalid input, please do not include spaces.");

		else
			validInput = true;
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner email address: ");
		scanf("%s", newMachine->email);

		//https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
		if (strstr(newMachine->email, "@") != NULL && strstr(newMachine->email, ".com") != NULL)
			validInput = true;

		else
			printf("\nInvalid input, please use @ and .com in the address");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner phone number: ");
		scanf("%ld", &newMachine->phone);

		if (newMachine->phone >= 0000000000 && newMachine->phone <= 9999999999)
			validInput = true;

		else
			printf("\nPlease enter a valid phone number.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine type (1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer): ");
		scanf("%d", &newMachine->machineType);

		if (newMachine->machineType > 0 && newMachine->machineType < 6)
			validInput = true;

		else
			printf("\nPlease enter a valid machine type.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine breakdowns this year (1 = never, 2 = <3, 3 = <5, 4 = >5): ");
		scanf("%d", &newMachine->breakdownNum);

		if (newMachine->breakdownNum > 0 && newMachine->breakdownNum < 5)
			validInput = true;

		else
			printf("\nPlease enter a valid breakdown number.");
	}


	temp->NEXT = newMachine;
	newMachine->PREV = temp;
	newMachine->NEXT = NULL;
	*end = newMachine;

}

//addMachine -> adds machine to position in LL based on Chassis Number (Unique)
int addMachine(machineT* top, int pos)
{
	machineT* temp, * temp2;
	machineT* newMachine;

	bool validInput = false;
	int chassisNum = pos;

	newMachine = (machineT*)malloc(sizeof(machineT));

	validInput = false;

	printf("\nAdding machine at position %d.\n", pos);
	
	newMachine->chassisNum = chassisNum;

	printf("\nEnter the machinery make: ");
	scanf("%s", newMachine->machineryMake);

	printf("\nEnter the machinery model: ");
	scanf("%s", newMachine->machineryModel);

	while (validInput == false)
	{
		printf("\nEnter the year of manufacture: ");
		scanf("%d", &newMachine->year);
		if (newMachine->year >= 1950 && newMachine->year <= 2025)
		{
			validInput = true;
		}

		else
		{
			printf("\nInvalid year, please try again.");
		}
	}

	printf("\nEnter the cost: ");
	scanf("%lf", &newMachine->cost);

	printf("\nEnter the current valuation: ");
	scanf("%lf", &newMachine->currentValue);

	printf("\nEnter the current mileage: ");
	scanf("%lf", &newMachine->currentMileage);

	printf("\nEnter the next service mileage: ");
	scanf("%lf", &newMachine->nextServiceMile);

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner name (no spaces): ");
		scanf("%s", newMachine->owner);

		if (strstr(newMachine->owner, " ") != NULL)
			printf("\nInvalid input, please do not include spaces.");

		else
			validInput = true;
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner email address: ");
		scanf("%s", newMachine->email);

		//https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
		if (strstr(newMachine->email, "@") != NULL && strstr(newMachine->email, ".com") != NULL)
			validInput = true;

		else
			printf("\nInvalid input, please use @ and .com in the address");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the owner phone number: ");
		scanf("%ld", &newMachine->phone);

		if (newMachine->phone >= 0000000000 && newMachine->phone <= 9999999999)
			validInput = true;

		else
			printf("\nPlease enter a valid phone number.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine type (1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer): ");
		scanf("%d", &newMachine->machineType);

		if (newMachine->machineType > 0 && newMachine->machineType < 6)
			validInput = true;

		else
			printf("\nPlease enter a valid machine type.");
	}

	validInput = false;
	while (validInput == false)
	{
		printf("\nEnter the machine breakdowns this year (1 = never, 2 = <3, 3 = <5, 4 = >5): ");
		scanf("%d", &newMachine->breakdownNum);

		if (newMachine->breakdownNum > 0 && newMachine->breakdownNum < 5)
			validInput = true;

		else
			printf("\nPlease enter a valid breakdown number.");
	}

	temp = top;

	for (int i = 0; i < pos - 2; i++)
	{
		temp = temp->NEXT;
	}

	temp2 = temp->NEXT;

	temp->NEXT = newMachine;
	newMachine->PREV = temp;
	newMachine->NEXT = temp2;
	temp2->PREV = newMachine;
}

//displayAll -> display all machine's details on screen
int displayAll(machineT* top)
{
	machineT* temp;
	int count = 0;

	temp = top;

	while (temp != NULL)
	{
		count++;

		printf("\n-----------------------------------------------------------------");

		printf("\nMachine #%d", count);

		printf("\nChassis Number: %d", temp->chassisNum);

		printf("\nMachinery Make: %s", temp->machineryMake);

		printf("\nMachinery Model: %s", temp->machineryModel);

		printf("\nYear of Manufacture: %d", temp->year);

		printf("\nCost: %.2f", temp->cost);

		printf("\nCurrent Valuation: %.2f", temp->currentValue);

		printf("\nCurrent Mileage: %.2f", temp->currentMileage);

		printf("\nNext Service Mileage: %.2f", temp->nextServiceMile);

		printf("\nOwner Name: %s", temp->owner);

		printf("\nOwner Email Address: %s", temp->email);

		printf("\nOwner Phone Number: %ld", temp->phone);

		if (temp->machineType == 1)
			printf("\nMachine Type: Tractor");
		else if (temp->machineType == 2)
			printf("\nMachine Type: Excavator");
		else if (temp->machineType == 3)
			printf("\nMachine Type: Roller");
		else if (temp->machineType == 4)
			printf("\nMachine Type: Crane");
		else if (temp->machineType == 5)
			printf("\nMachine Type: Mixer");

		if (temp->breakdownNum == 1)
			printf("\nMachine Breakdowns this Year: None\n");
		else if (temp->breakdownNum == 2)
			printf("\nMachine Breakdowns this Year: Less than 3\n");
		else if (temp->breakdownNum == 3)
			printf("\nMachine Breakdowns this Year: Less than 5\n");
		else if (temp->breakdownNum == 4)
			printf("\nMachine Breakdowns this Year: More than 5\n");

		temp = temp->NEXT;
	}
	printf("\n-----------------------------------------------------------------");
}

//displayStats -> display statistics of chosen machine types based on user input
int displayStats(machineT* top, int machineType)
{
	int machineCount = 0;
	int machineFailures = 0;

	machineT* temp;

	temp = top;

	while (temp != NULL)
	{
		//Loop that tracks machine num and failures of the selected type
		//Tractors
		if (machineType == 1 && temp->machineType == 1)
		{
			machineCount++;

			if (temp->breakdownNum > 0)
				machineFailures++;
		}

		//Excavators
		else if (machineType == 2 && temp->machineType == 2)
		{
			machineCount++;

			if (temp->breakdownNum > 0)
				machineFailures++;
		}

		//Rollers
		else if (machineType == 3 && temp->machineType == 2)
		{
			machineCount++;

			if (temp->breakdownNum > 0)
				machineFailures++;
		}

		//Cranes
		else if (machineType == 4 && temp->machineType == 2)
		{
			machineCount++;

			if (temp->breakdownNum > 0)
				machineFailures++;
		}

		//Mixers
		else if (machineType == 5 && temp->machineType == 2)
		{
			machineCount++;

			if (temp->breakdownNum > 0)
				machineFailures++;
		}

		temp = temp->NEXT;
	}

	int totalSuccesses = ((machineCount*100) - (machineFailures*100));
	float successesPercentage = ((float)totalSuccesses / machineCount);

	//Tractors
	if (machineType == 1 && machineCount > 0)
	{
		printf("Generating statistics for Tractor Machinery...");
		printf("\n%.2f Percent of the %d Tractors in the fleet have had no breakdowns.", successesPercentage, machineCount);
	}

	//Excavators
	else if (machineType == 2 && machineCount > 0)
	{
		printf("Generating statistics for Excavator Machinery...");
		printf("\n%.2f Percent of the %d Excavators in the fleet have had no breakdowns.", successesPercentage, machineCount);
	}

	//Rollers
	else if (machineType == 3 && machineCount > 0)
	{
		printf("Generating statistics for Roller Machinery...");
		printf("\n%.2f Percent of the %d Rollers in the fleet have had no breakdowns.", successesPercentage, machineCount);
	}

	//Cranes
	else if (machineType == 4 && machineCount > 0)
	{
		printf("Generating statistics for Crane Machinery...");
		printf("\n%.2f Percent of the %d Cranes in the fleet have had 0 breakdowns.", successesPercentage, machineCount);
	}

	//Mixers
	else if (machineType == 5 && machineCount > 0)
	{
		printf("Generating statistics for Mixer Machinery...");
		printf("\n%.2f percent  of the %d Mixers in the fleet have had 0 breakdowns.", successesPercentage, machineCount);
	}

	//No machines
	else if (machineCount <= 0 || top==NULL)
	{
		printf("\nThere are no machines of the selected type in the fleet.\n");
	}

	//For saving values to file
	return successesPercentage;
}

//listAll -> list all machines in order of current valuation
void listAll(machineT* top)
{
	machineT* temp;
	int count = 0;
	int i = 0;
	double curHighestVal = -1;
	int curHighestChassis = -1;
	double previousHighestVal = 0; //Used a boundry for the check
	int previousChassis = 0; //Saves the chassisNum in case there's ones with an equal valuation -> 0 indicates first in loop

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}

	temp = top;

	//For loop that goes through the linked list as many times as needed
	if (count > 0)
	{
		for (i = 0; i < count; i++)
		{
			curHighestVal = -1;
			curHighestChassis = -1;

			temp = top;
			while (temp != NULL)
			{
				//First Loop, no extra restrictions
				if (temp->currentValue >= curHighestVal && previousChassis == 0)
				{
					//Check that it's not the same machine
					if (temp->chassisNum != previousChassis)
					{
						curHighestChassis = temp->chassisNum;
						curHighestVal = temp->currentValue;
					}
				}

				//Other loops include previousValutation and previousChassis checks to do a top down approach
				else if (temp->currentValue >= curHighestVal && temp->currentValue < previousHighestVal && previousChassis != 0)
				{
					if (temp->chassisNum != previousChassis)
					{
						curHighestChassis = temp->chassisNum;
						curHighestVal = temp->currentValue;
					}
				}

				temp = temp->NEXT;
			}

			//Additional check then print results
			if (curHighestVal != -1)
			{
				printf("\nChassis Num: %d", curHighestChassis);
				printf("  Valuation: %.2f", curHighestVal);

				//Set new variables
				previousChassis = curHighestChassis;
				previousHighestVal = curHighestVal;
			}

			//If it does not pass that check, end the loop since there's no unique machines left
			else
			{
				break;
			}

		}
	}

	else
	{
		printf("\nNo machines in database");
	}
}

//(ADMIN) displayMachine -> displays details of specific machine using inputted Chassis Number
int displayMachine(machineT* top, int searchTerm)
{
	machineT* temp;
	int count = 0;
	int found = 0;
	char machineType[30];

	temp = top;

	printf("\nDisplaying Details of Machine %d\n", searchTerm);

	while (temp != NULL)
	{
		count++;

		if (temp->chassisNum == searchTerm)
		{
			printf("\nChassis Number: %d", temp->chassisNum);

			printf("\nMachinery Make: %s", temp->machineryMake);

			printf("\nMachinery Model: %s", temp->machineryModel);

			printf("\nYear of Manufacture: %d", temp->year);

			printf("\nCost: %.2f", temp->cost);

			printf("\nCurrent Valuation: %.2f", temp->currentValue);

			printf("\nCurrent Mileage: %.2f", temp->currentMileage);

			printf("\nNext Service Mileage: %.2f", temp->nextServiceMile);

			printf("\nOwner Name: %s", temp->owner);

			printf("\nOwner Email Address: %s", temp->email);

			printf("\nOwner Phone Number: %ld", temp->phone);

			if (temp->machineType == 1)
				printf("\nMachine Type: Tractor");
			else if (temp->machineType == 2)
				printf("\nMachine Type: Excavator");
			else if (temp->machineType == 3)
				printf("\nMachine Type: Roller");
			else if (temp->machineType == 4)
				printf("\nMachine Type: Crane");
			else if (temp->machineType == 5)
				printf("\nMachine Type: Mixer");

			if (temp->breakdownNum == 1)
				printf("\nMachine Breakdowns this Year: None");
			else if (temp->breakdownNum == 2)
				printf("\nMachine Breakdowns this Year: Less than 3");
			else if (temp->breakdownNum == 3)
				printf("\nMachine Breakdowns this Year: Less than 5");
			else if (temp->breakdownNum == 4)
				printf("\nMachine Breakdowns this Year: More than 5");


			found = 1;
			break;
		}

		temp = temp->NEXT;
	}

	if (found != 1)
	{
		printf("\nMachine could not be found...\n");
	}

	return found;
}

//(ADMIN) updateMachine -> update details of specific machine using inputted Chassis Number
int updateMachine(machineT* top, int searchTerm)
{
	machineT* temp;
	int count = 0;
	int found = 0;

	temp = top;

	bool validInput = false;


	while (temp != NULL)
	{
		count++;

		if (temp->chassisNum == searchTerm)
		{

			//Allow updates for everything except chassis num (with checks)
			validInput = false;

			printf("\nEnter the new machinery make: ");
			scanf("%s", temp->machineryMake);

			printf("\nEnter the new machinery model: ");
			scanf("%s", temp->machineryModel);

			while (validInput == false)
			{
				printf("\nEnter the new year of manufacture: ");
				scanf("%d", &temp->year);
				if (temp->year >= 1950 && temp->year <= 2025)
				{
					validInput = true;
				}

				else
				{
					printf("\nInvalid year, please try again.");
				}
			}

			printf("\nEnter the new cost: ");
			scanf("%lf", &temp->cost);

			printf("\nEnter the new current valuation: ");
			scanf("%lf", &temp->currentValue);

			printf("\nEnter the new current mileage: ");
			scanf("%lf", &temp->currentMileage);

			printf("\nEnter the new next service mileage: ");
			scanf("%lf", &temp->nextServiceMile);

			validInput = false;
			while (validInput == false)
			{
				printf("\nEnter the new owner name (no spaces): ");
				scanf("%s", temp->owner);

				if (strstr(temp->owner, " ") != NULL)
					printf("\nInvalid input, please do not include spaces.");

				else
					validInput = true;
			}

			validInput = false;
			while (validInput == false)
			{
				printf("\nEnter the new owner email address: ");
				scanf("%s", temp->email);

				//https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
				if (strstr(temp->email, "@") != NULL && strstr(temp->email, ".com") != NULL)
					validInput = true;

				else
					printf("\nInvalid input, please use @ and .com in the address");
			}

			validInput = false;
			while (validInput == false)
			{
				printf("\nEnter the new owner phone number: ");
				scanf("%ld", &temp->phone);

				if (temp->phone >= 0000000000 && temp->phone <= 9999999999)
					validInput = true;

				else
					printf("\nPlease enter a valid phone number.");
			}

			validInput = false;
			while (validInput == false)
			{
				printf("\nEnter the new machine type (1 = Tractor, 2 = Excavator, 3 = Roller, 4 = Crane, 5 = Mixer): ");
				scanf("%d", &temp->machineType);

				if (temp->machineType > 0 && temp->machineType < 6)
					validInput = true;

				else
					printf("\nPlease enter a valid machine type.");
			}

			validInput = false;
			while (validInput == false)
			{
				printf("\nEnter the new machine breakdowns this year (1 = never, 2 = <3, 3 = <5, 4 = >5): ");
				scanf("%d", &temp->breakdownNum);

				if (temp->breakdownNum > 0 && temp->breakdownNum < 5)
					validInput = true;

				else
					printf("\nPlease enter a valid breakdown number.");
			}

			found = 1;
			break;
		}

		temp = temp->NEXT;
	}

	if (found != 1)
		printf("\nMachine could not be found.\n");

	else
		printf("\nMachine has been updated.\n");
}

//deleteMachine -> delete machine based on chassis num
void deleteMachine(machineT** top, machineT** end, int searchTerm)
{
	machineT* temp;
	machineT* closer;
	int found = 0;

	//Check if there's no machines
	if (*top == NULL)
	{
		printf("Sorry the list is empty you can not delete from the list\n");
	}
	//Check if there's only one item in the list
	else if (*top == *end)
	{
		temp = *top;
		*top = NULL;
		*end = NULL;
		free(temp);
		printf("\nMachine has been deleted, fleet is now empty.\n");
	}
	//If head pointer is a match
	else if ((*top)->chassisNum == searchTerm)
	{
		temp = *top;
		*top = temp->NEXT;
		(*top)->PREV = NULL;
		free(temp);
		printf("\nMachine has been deleted, first item in list has been replaced.\n");
	}

	//If the tail pointer is a match
	else if ((*end)->chassisNum == searchTerm)
	{
		temp = *end;
		*end = temp->PREV;
		(*end)->NEXT = NULL;
		free(temp);
		printf("\nMachine has been deleted, last item in list has been replaced.\n");
	}
	
	//Search for the specific term
	else
	{
		//Loop through until found
		temp = *top;

		while (temp != NULL)
		{

			if (temp->chassisNum == searchTerm)
			{
				printf("\nMachine was found.");
				closer = temp;
				temp = closer->PREV;
				temp->NEXT = closer->NEXT;
				free(closer);

				printf("\nMachine has been deleted...\n");

				found = 1;
				break;
			}

			temp = temp->NEXT;
		}

		if (found != 1)
		{
			printf("\nMachine could not be found\n");
		}
	}
}

//loadAll -> loads machine fleet from file using addMachine, file is ordered by chassis num so no working needed
void loadMachines(machineT **end, machineT **top)
{
	//Use addMachine as guide
	printf("\nLoading Machine Fleet.....\n");

	FILE* fp;
	machineT* temp = NULL;
	machineT* newMachine;
	int inputs;
	
	fp = fopen("fleet.txt", "r");

	if (fp != NULL)
	{
		printf("\nLoading files from fleet.txt...\n");

		//Until file has ended
		while (!feof(fp))
		{
			//Set new node
			newMachine = (machineT*)malloc(sizeof(machineT));

			inputs = fscanf(fp, "%d %s %s %d %lf %lf %lf %lf %s %s %ld %d %d",
				&newMachine->chassisNum, newMachine->machineryMake, newMachine->machineryModel, &newMachine->year, &newMachine->cost, &newMachine->currentValue,
				&newMachine->currentMileage, &newMachine->nextServiceMile, newMachine->owner, newMachine->email, &newMachine->phone, &newMachine->machineType, &newMachine->breakdownNum);

			/*
			printf("\n%d\n", inputs);
			printf("%d %s %s %d %.2f %.2f %.2f %.2f %s %s %ld %d %d\n",
				newMachine->chassisNum, newMachine->machineryMake, newMachine->machineryModel, newMachine->year, newMachine->cost, newMachine->currentValue,
				newMachine->currentMileage, newMachine->nextServiceMile, newMachine->owner, newMachine->email, newMachine->phone, newMachine->machineType, newMachine->breakdownNum);
				*/


			if (inputs == 13)
			{
				//If it's the head pointer
				if (*top == NULL)
				{
					printf("\nAdding first machine....\n");

					//Set head pointer stuff
					newMachine->PREV = NULL;
					newMachine->NEXT = NULL;
					*top = newMachine;
					*end = newMachine;

					//Set temp as new machine to solidify it
					temp = newMachine;
					printf("First machine added.\n");
				}
				//Add node at end of linked list
				else
				{
					printf("\nAdding machine......");

					//Set up points
					temp->NEXT = newMachine;
					newMachine->PREV = temp;
					newMachine->NEXT = NULL;

					//Set it as last machine
					*end = newMachine;
					temp = *end;

					printf("\nMachine has been added.\n");
				}
			}

			else {
				printf("\nMachines have all been added\n");
				free(newMachine);
				break;
			}



		}//End of While

		fclose(fp);
	}

	else
		printf("\nFile could not be loaded...\n");
}

//saveAll -> prints all machines + all 5 performance stats to file
void saveMachines(machineT *top)
{
	FILE* fp;
	float tractorPercentage, excavatorPercentage, rollerPercentage, cranePercentage, mixerPercentage;
	machineT* temp;
	temp = top;

	if (temp != NULL)
	{
		printf("\nSaving Machine Fleet.....\n");

		fp = fopen("fleet.txt", "w");

		if (fp == NULL)
		{
			printf("\nError, could not open file.");
		}

		else
		{
			while (temp != NULL)
			{
				fprintf(fp, "%d %s %s %d %.2f %.2f %.2f %.2f %s %s %ld %d %d\n",
					temp->chassisNum, temp->machineryMake, temp->machineryModel, temp->year, temp->cost, temp->currentValue,
					temp->currentMileage, temp->nextServiceMile, temp->owner, temp->email, temp->phone, temp->machineType, temp->breakdownNum);

				temp = temp->NEXT;
			}


			//Save 5 stats
			printf("\nSaving machine stats...\n");
			tractorPercentage = displayStats(top, 1);
			excavatorPercentage = displayStats(top, 2);
			rollerPercentage = displayStats(top, 3);
			cranePercentage = displayStats(top, 4);
			mixerPercentage = displayStats(top, 5);

			fprintf(fp, "%.2f %.2f %.2f %.2f %.2f", tractorPercentage, excavatorPercentage, rollerPercentage, cranePercentage, mixerPercentage);
			fclose(fp);

			printf("\nMachine Fleet has been saved to file!\n");
		}
	}

	else
	{
		printf("\nDatabase is empty, not saving to file...\n");
	}
}