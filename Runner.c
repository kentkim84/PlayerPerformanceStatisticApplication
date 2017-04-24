#include "app_1.h"
#include "app_2.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE_CRITERIA 7
#define MAX_SIZE_ADMIN 3

void main()
{
	FILE *login_fp, *db_fp, *report_fp;
	struct node* head;
	struct node* tail;	

	struct account* account;
	player_criteria* position_array;
	player_criteria* weight_array;

	head = NULL;
	tail = NULL;
	
	account = (struct account*)malloc(sizeof(struct account) * MAX_SIZE_ADMIN);
	position_array = (player_criteria*)malloc(sizeof(player_criteria) * MAX_SIZE_CRITERIA);
	weight_array = (player_criteria*)malloc(sizeof(player_criteria) * MAX_SIZE_CRITERIA);

	// validate the login section
	login_fp = fopen("login.txt", "r");

	if (login_fp == NULL)
	{
		printf("Failed to open file");
		getchar();
		return EXIT_FAILURE;
	}
	else
	{
		loadLogin(account, MAX_SIZE_ADMIN, login_fp);
	}

	db_fp = fopen("rugby.txt", "r");

	if (db_fp == NULL)
	{
		printf("Failed to open file");
		getchar();
		return EXIT_FAILURE;
	}
	else
	{
		loadDb(&head, &tail, db_fp);
	}

	report_fp = fopen("report.txt", "w+");

	if (report_fp == NULL)
	{
		printf("Failed to open file");
		getchar();
		return EXIT_FAILURE;
	}

	// initialise arrays
	initArray(position_array, weight_array, MAX_SIZE_CRITERIA);

	int choice;
	int option = 0;
	char search[30];
	
	printf("Please enter 1 to add a player\n");
	printf("Please enter 2 to display all player's details\n");
	printf("Please enter 3 to display a player's details\n");
	printf("Please enter 4 to update a player's details\n");
	printf("Please enter 5 to delete a player\n");
	printf("Please enter 6 to generate statistics\n");
	printf("Please enter 7 to print all details into a report file\n");
	printf("Please enter 8 to list all the players of a matching category\n");
	printf("Please enter -1 to exit: ");
	scanf("%d", &choice);
	printf("\n");

	while (choice != -1)
	{

		if (choice == 1)
		{
			addPlayer(&head, &tail);
		}

		else if (choice == 2)
		{
			displayAll(head);
		}

		else if (choice == 3)
		{
			printf("Enter the IRFU number or first name to display a player's details: ");
			scanf("%s", search);
			displayDetails(head, search);
		}

		else if (choice == 4)
		{
			printf("Enter the IRFU number or first name to display a player's details: ");
			scanf("%s", search);
			updatePlayer(head, search);
		}
		else if (choice == 5)
		{
			printf("Enter the IRFU number or first name to display a player's details: ");
			scanf("%s", search);
			deletePlayer(&head, &tail, search);
		}
		else if (choice == 6)
		{
			printf("Enter the number from the given list\n");
			printf("[1: Player Position, 2: Weight]: ");
			scanf("%d", &option);
			// initialise arrays 0
			initArray(position_array, weight_array, MAX_SIZE_CRITERIA);
			generateStatistic(head, position_array, weight_array, MAX_SIZE_CRITERIA, option);
		}
		else if (choice == 7)
		{
			// initialise arrays 0
			initArray(position_array, weight_array, MAX_SIZE_CRITERIA);
			printAll(head, position_array, weight_array, MAX_SIZE_CRITERIA, report_fp);
		}
		else if (choice == 8)
		{
			printf("Enter the number from the given list\n");
			printf("[1: Second row, 2: Back row]: ");
			scanf("%d", &option);
			listPlayers(head, option);
		}
		else
		{
			printf("Invalid!\n");
		}

		printf("Please enter 1 to add a player\n");
		printf("Please enter 2 to display all player's details\n");
		printf("Please enter 3 to display a player's details\n");
		printf("Please enter 4 to update a player's details\n");
		printf("Please enter 5 to delete a player\n");
		printf("Please enter 6 to generate statistics\n");
		printf("Please enter 7 to print all details into a report file\n");
		printf("Please enter 8 to list all the players of a matching category\n");
		printf("Please enter -1 to exit: ");
		scanf("%d", &choice);
		printf("\n");
	}

	
}
