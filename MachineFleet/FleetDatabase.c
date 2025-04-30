/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	int data;
	struct node* NEXT;
	struct node* PREV;
}nodeT;


void addAtTheEnd(nodeT** end);
void addAtTheStart(nodeT** top, nodeT** end);
void addAtPosition(nodeT* top, int pos);
//void addAtTheEndV2(nodeT* top, int newData);
//void addAtTheStartV2(nodeT** top, int newData);

void display(nodeT* top);
void displayReverse(nodeT* end);
int length(nodeT* top);
int search(nodeT* top, int searchTerm);
void deleteAtTheStart(nodeT** top, nodeT** end);
void deleteAtTheEnd(nodeT** top, nodeT** end);

int menu();
void main()
{
	nodeT* headPtr = NULL;
	nodeT* tailPtr = NULL;
	nodeT* newNode;
	nodeT* prev = NULL;
	int option;
	int count;
	int found;
	int searchTerm;
	FILE* ip;
	int dataFromFile;
	int position;
	int numInputs;



	option = menu();

	while (option != -1)
	{
		if (option == 1)
		{
			addAtTheStart(&headPtr, &tailPtr);
		}

		else if (option == 2)
		{
			if (headPtr == NULL)
				addAtTheStart(&headPtr, &tailPtr);
			else
				addAtTheEnd(&tailPtr);
		}

		else if (option == 3)
		{
			display(headPtr);
		}

		else if (option == 4)
		{
			displayReverse(tailPtr);
		}

		else if (option == 5)
		{
			printf("The length of the list is %d\n", length(headPtr));
		}

		else if (option == 6)
		{
			printf("Please enter the search integer\n");
			scanf("%d", &searchTerm);

			found = search(headPtr, searchTerm);

			if (found == 1)
				printf("The number %d was found in the list\n", searchTerm);
			else
				printf("The number was not found\n");
		}

		else if (option == 7)
		{
			deleteAtTheStart(&headPtr, &tailPtr);
		}

		else if (option == 8)
		{
			deleteAtTheEnd(&headPtr, &tailPtr);
		}
		else if (option == 9)
		{
			printf("Please enter the position you wish to add the number in\n");
			scanf("%d", &position);

			if (position == 1)
				addAtTheStart(&headPtr, &tailPtr);
			else if (position == length(headPtr) + 1)
				addAtTheEnd(&tailPtr);
			else if (position<1 || position> length(headPtr) + 1)
				printf("This is not permitted\n");
			else
				addAtPosition(headPtr, position);

		}

		option = menu();
	}


}


int menu()
{
	int option;

	printf("Enter 1 to add a node at the beginning\n");
	printf("Enter 2 to add a node at the end\n");
	printf("Enter 3 to display all the nodes\n");
	printf("Enter 4 to display all the nodes in reverse\n");
	printf("Enter 5 to get the length of the list\n");
	printf("Enter 6 to search the list\n");
	printf("Enter 7 to delete at the start\n");
	printf("Enter 8 to delete at the end\n");
	printf("Enter 9 to add at a position\n");
	printf("Enter -1 to exit\n");
	scanf("%d", &option);

	return option;

}

void addAtTheEnd(nodeT** end)
{
	nodeT* newNode;
	nodeT* temp;

	temp = *end;

	newNode = (nodeT*)malloc(sizeof(nodeT));
	printf("Please enter the data for the new node\n");
	scanf("%d", &newNode->data);

	temp->NEXT = newNode;
	newNode->PREV = temp;
	newNode->NEXT = NULL;
	*end = newNode;

}

void addAtTheStart(nodeT** top, nodeT** end)
{
	nodeT* newNode;

	newNode = (nodeT*)malloc(sizeof(nodeT));
	printf("Please enter the data for the new node\n");
	scanf("%d", &newNode->data);

	newNode->PREV = NULL;
	newNode->NEXT = *top;

	if (*top != NULL)
		(*top)->PREV = newNode;

	*top = newNode;

	if (*end == NULL)
		*end = newNode;
}

void addAtPosition(nodeT* top, int pos)
{
	nodeT* temp, * temp2;
	nodeT* newNode;

	newNode = (nodeT*)malloc(sizeof(nodeT));
	printf("Please enter the data for the new node\n");
	scanf("%d", &newNode->data);

	temp = top;

	for (int i = 0; i < pos - 2; i++)
	{
		temp = temp->NEXT;
	}

	temp2 = temp->NEXT;

	temp->NEXT = newNode;
	newNode->PREV = temp;
	newNode->NEXT = temp2;
	temp2->PREV = newNode;

}

void display(nodeT* top)
{
	nodeT* temp;

	temp = top;

	while (temp != NULL)
	{
		printf("The value of the node is %d\n", temp->data);

		temp = temp->NEXT;
	}

}

void displayReverse(nodeT* end)
{
	nodeT* temp;

	temp = end;

	while (temp != NULL)
	{
		printf("The value of the node is %d\n", temp->data);

		temp = temp->PREV;
	}
}

int length(nodeT* top)
{
	nodeT* temp;
	int count = 0;

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}

	return count;

}
int search(nodeT* top, int searchTerm)
{
	nodeT* temp;
	int count = 0;
	int found = 0;

	temp = top;


	while (temp != NULL)
	{
		count++;

		if (temp->data == searchTerm)
		{
			found = 1;
			break;
		}

		temp = temp->NEXT;

	}

	return found;

}


void deleteAtTheStart(nodeT** top, nodeT** end)
{
	nodeT* temp;


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
void deleteAtTheEnd(nodeT** top, nodeT** end)
{
	nodeT* temp;


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
		temp = *end;
		*end = temp->PREV;
		(*end)->NEXT = NULL;
		free(temp);


	}

}
*/