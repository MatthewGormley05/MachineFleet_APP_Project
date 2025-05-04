#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct machine
{
	char chassisNum[20]; //Unique
	char machineryMake[20];
	char machineryModel[20];
	int year; //Must be 4 nums, 1950 - 2025
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
}machineT;

//Initialise psuedo-methods
int userLogin();
int displayOptions();
int checkChassis(machineT* top, int searchNum);
int length(machineT* top);
int addFirstMachine(machineT** top, machineT** end);
int addLastMachine(machineT** end);
int addMachine(machineT* top, int pos);
int displayAll(machineT* top);
int displayStats(machineT* top, int machineType);
int displayStats(machineT* top, int machineType);
void listAll(machineT* top);
int displayMachine(machineT* top, int searchTerm);
int updateMachine(machineT* top, int searchTerm);
void deleteMachine(machineT** top, machineT** end, int searchTerm);


void main()
{
	machineT* headPtr = NULL;
	machineT* tailPtr = NULL;
	machineT* newNode = NULL;
	machineT* prev = NULL;

	bool chassisTaken = false;
	int option = -10, loginMode, machineType, newChassisNum;
	char machineOption[1], a[1] = "a", b[1] = "b", c[1] = "c", d[1] = "d", e[1] = "e", A[1] = "A", B[1] = "B", C[1] = "C", D[1] = "D", E[1] = "E";
	char chassisInput[20] = "\0";
	char emptyString = "\0";

	//loadAll();//Load Files

	loginMode = userLogin(); //-1 = Unsuccessful, 1 = Successful, 2 = Admin

	if (loginMode == 1 || loginMode == 2)
	{
		option = displayOptions();

		while (option != -1)
		{
			//Reset variables
			machineOption;
			machineType = 0;
			chassisTaken = false;
			newChassisNum = NULL;
			strcpy(chassisInput, emptyString);

			//Option 1: Add machine
			if (option == 1)
			{
				printf("\nPlease enter the chassis number of the new machine: ");
				scanf("%d", newChassisNum);

				chassisTaken = checkChassis(headPtr, newChassisNum);

				if (chassisTaken == false)
				{
					if (newChassisNum == 1)
						addFirstMachine(&headPtr, &tailPtr);
					
					else if (newChassisNum == length(headPtr) + 1)
						addLastMachine(&tailPtr);
					
					else if (newChassisNum<1 || newChassisNum> length(headPtr) + 1)
						printf("Invalid Chassis number\n");

					else
						addMachine(headPtr, newChassisNum);
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
				scanf("%s", chassisInput);
			}

			//Option 4: Update a machine's details (ADMIN)
			else if (option == 4 && loginMode == 2)
			{
				printf("\nPlease enter the chassis number: ");
				scanf("%s", chassisInput);
			}

			//Option 5: Delete machine
			else if (option == 5)
			{
				printf("\nPlease enter the chassis number: ");
				scanf("%s", chassisInput);
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
					displayStats(headPtr, machineType);
				}

				//Excavator
				else if (strcmp(machineOption, b) == 0 || strcmp(machineOption, B) == 0)
				{
					machineType = 2;
					displayStats(headPtr, machineType);
				}

				//Roller
				else if (strcmp(machineOption, c) == 0 || strcmp(machineOption, C) == 0)
				{
					machineType = 3;
					displayStats(headPtr, machineType);
				}

				//Crane
				else if (strcmp(machineOption, d) == 0 || strcmp(machineOption, D) == 0)
				{
					machineType = 4;
					displayStats(headPtr, machineType);
				}

				//Mixer
				else if (strcmp(machineOption, e) == 0 || strcmp(machineOption, E) == 0)
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
				//saveAll();
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
		//saveAll();
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

	//int loginTesting = 1;//Testing
	//strcpy(username1, "Bethany"); //Testing
	//strcpy(username2, "Alexander"); //Testing
	//strcpy(adminName, "admin"); //Testing
	//strcpy(password1, "Beth12"); //Testing
	//strcpy(password2, "alex54"); //Testing
	//strcpy(adminPassword, "admin1"); //Testing

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

	printf("\nEnter 1 to add a machine\n");
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
			chassisTaken = true;
		}
		//printf("The value of the node is %d\n", temp->chassisNum);

		temp = temp->NEXT;
	}

	return chassisTaken;
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
int addFirstMachine(machineT** top, machineT** end)
{
	machineT* newMachine;

	newMachine = (machineT*)malloc(sizeof(machineT));
	printf("Please enter the data for the new node\n");
	//scanf("%d", &newMachine->data);

	newMachine->PREV = NULL;
	newMachine->NEXT = *top;

	if (*top != NULL)
		(*top)->PREV = newMachine;

	*top = newMachine;

	if (*end == NULL)
		*end = newMachine;
}

//addLastMachine -> add last machine
int addLastMachine(machineT** end)
{
	machineT* newNode;
	machineT* temp;

	temp = *end;

	newNode = (machineT*)malloc(sizeof(machineT));
	printf("Please enter the data for the new node\n");
	//scanf("%d", &newNode->data);

	temp->NEXT = newNode;
	newNode->PREV = temp;
	newNode->NEXT = NULL;
	*end = newNode;

}

//addMachine -> adds machine to position in LL based on Chassis Number (Unique)
int addMachine(machineT* top, int pos)
{
	machineT* temp, * temp2;
	machineT* newMachine;

	newMachine = (machineT*)malloc(sizeof(machineT));
	printf("Please enter the data for the new node\n");
	//scanf("%d", &newNode->data);

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

		printf("\nMachine #%d", &count);

		printf("\nChassis Number: %s", (temp)->chassisNum);

		printf("\nMachinery Make: %s", (temp)->machineryMake);

		printf("\nMachinery Model: %s", (temp)->machineryModel);

		printf("\nYear of Manufacture: %d", &(temp)->year);

		printf("\nCost: %f", &(temp)->cost);

		printf("\nCurrent Valuation: %f", &(temp)->currentValue);

		printf("\nCurrent Mileage: %f", &(temp)->currentMileage);

		printf("\nNext Service Mileage: %f", &(temp)->nextServiceMile);

		printf("\nOwner Name: %s", (temp)->owner);

		printf("\nOwner Email Address: %s", (temp)->email);

		printf("\nOwner Phone Number: %d", &(temp)->phone);

		if ((temp)->machineType == 1)
			printf("\nMachine Type: Tractor");
		else if ((temp)->machineType == 2)
			printf("\nMachine Type: Excavator");
		else if ((temp)->machineType == 3)
			printf("\nMachine Type: Roller");
		else if ((temp)->machineType == 4)
			printf("\nMachine Type: Crane");
		else if ((temp)->machineType == 5)
			printf("\nMachine Type: Mixer");

		if ((temp)->breakdownNum == 1)
			printf("\nMachine Breakdowns this Year: None");
		else if ((temp)->breakdownNum == 2)
			printf("\nMachine Breakdowns this Year: Less than 3");
		else if ((temp)->breakdownNum == 3)
			printf("\nMachine Breakdowns this Year: Less than 5");
		else if ((temp)->breakdownNum == 4)
			printf("\nMachine Breakdowns this Year: More than 5");

		temp = temp->NEXT;
	}
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

		temp = temp->NEXT;
	}

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
void listAll(machineT* top)
{
	machineT* temp;

	temp = top;

	//Create array of chassis num + valuation
	while (temp != NULL)
	{
		//printf("The value of the node is %d\n", temp->data);

		temp = temp->NEXT;
	}

	//Sort array

	//Print Array

}

//(ADMIN) displayMachine -> displays details of specific machine using inputted Chassis Number
int displayMachine(machineT* top, int searchTerm)
{
	machineT* temp;
	int count = 0;
	int found = 0;
	char machineType[30];

	temp = top;

	while (temp != NULL)
	{
		count++;

		if (temp->chassisNum == searchTerm)
		{
			printf("\nChassis Number: %s", (temp)->chassisNum);

			printf("\nMachinery Make: %s", (temp)->machineryMake);

			printf("\nMachinery Model: %s", (temp)->machineryModel);

			printf("\nYear of Manufacture: %d", &(temp)->year);

			printf("\nCost: %f", &(temp)->cost);

			printf("\nCurrent Valuation: %f", &(temp)->currentValue);

			printf("\nCurrent Mileage: %f", &(temp)->currentMileage);

			printf("\nNext Service Mileage: %f", &(temp)->nextServiceMile);

			printf("\nOwner Name: %s", (temp)->owner);

			printf("\nOwner Email Address: %s", (temp)->email);

			printf("\nOwner Phone Number: %d", &(temp)->phone);

			if ((temp)->machineType == 1)
				printf("\nMachine Type: Tractor");
			else if ((temp)->machineType == 2)
				printf("\nMachine Type: Excavator");
			else if ((temp)->machineType == 3)
				printf("\nMachine Type: Roller");
			else if ((temp)->machineType == 4)
				printf("\nMachine Type: Crane");
			else if ((temp)->machineType == 5)
				printf("\nMachine Type: Mixer");

			if ((temp)->breakdownNum == 1)
				printf("\nMachine Breakdowns this Year: None");
			else if ((temp)->breakdownNum == 2)
				printf("\nMachine Breakdowns this Year: Less than 3");
			else if ((temp)->breakdownNum == 3)
				printf("\nMachine Breakdowns this Year: Less than 5");
			else if ((temp)->breakdownNum == 4)
				printf("\nMachine Breakdowns this Year: More than 5");


			found = 1;
			break;
		}

		temp = temp->NEXT;
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


	while (temp != NULL)
	{
		count++;

		if (temp->chassisNum == searchTerm)
		{
			//Allow updates for everything except chassis num (with checks)
			printf("\nEnter the new machinery make: ");
			scanf("%s", (temp)->machineryMake);

			printf("\nEnter the new machinery model: ");
			scanf("%s", (temp)->machineryModel);

			printf("\nEnter the new year of manufacture: ");
			scanf("%d", &(temp)->year);

			printf("\nEnter the new cost: ");
			scanf("%f", &(temp)->cost);

			printf("\nEnter the new current valuation: ");
			scanf("%f", &(temp)->currentValue);

			printf("\nEnter the new current mileage: ");
			scanf("%f", &(temp)->currentMileage);

			printf("\nEnter the new next service mileage: ");
			scanf("%f", &(temp)->nextServiceMile);

			printf("\nEnter the new owner name: ");
			scanf("%s", (temp)->owner);

			printf("\nEnter the new owner email address: ");
			scanf("%s", (temp)->email);

			printf("\nEnter the new owner phone number: ");
			scanf("%d", &(temp)->phone);

			printf("\nEnter the new machine type: ");
			scanf("%d", &(temp)->machineType);

			printf("\nEnter the new machine breakdowns this year (1 = never, 2 = <3, 3 = <5, 4 = >5): ");
			scanf("%d", &(temp)->breakdownNum);

			found = 1;
			break;
		}

		temp = temp->NEXT;

	}
	//return found;
}

//deleteMachine -> delete machine based on chassis num
void deleteMachine(machineT** top, machineT** end, int searchTerm)
{
	machineT* temp;
	int count = 0;
	int found = 0;


	if (*top == NULL)
	{
		printf("Sorry the list is empty you can not delete from the list\n");
	}
	else if (*top == *end)
	{
		temp = *top;
		*top = NULL;
		*end = NULL;
		free(temp);
	}
	else
	{
		temp = *top;
		*top = temp->NEXT;
		(*top)->PREV = NULL;
		free(temp);
	}
}

/*
//loadAll -> loads machine fleet from file using addMachine
void loadAll()
{
	//Do the same things as option 1

	//File is ordered by chassis num so no working needed
}

//saveAll -> prints all machines + all 5 performance stats to file
void saveAll()
{
	//Save in order of chassis num using modified listAll

}
*/