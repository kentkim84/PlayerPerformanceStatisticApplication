#include "app_1.h"

void loadLogin(struct account* account, int max_size, FILE *login_fp)
{
	int i, charHolder;
	i = 0;
	while (!feof(login_fp)) {
		charHolder = fgetc(login_fp);
		if (charHolder == '\n')
			++i;
	}
	int j = 0;
	rewind(login_fp);  // Line I added
					   // read each line and put into accounts
	while (j != i - 1) {
		fscanf(login_fp, "%s %s", (account + j)->userId, (account + j)->password);
		++j;
	}

	// test display account and password
	/*for (i = 0; i < max_size; i++)
	{
		printf("id: %s, pw: %s\n", (account + i)->userId, (account + i)->password);
	}*/

	printf("Welcome to the Player Performance Statistic Application\n");
	loginValidation(account, max_size);

	// close file pointer
	fclose(login_fp);
}

void loginValidation(struct account* account, int max_size)
{
	struct account* login;
	char userId[7];
	char password[7];
	char charHolder;
	int i, length, found;

	login = account;
	found = 0;
	while (found != 1)
	{
		printf("Enter the user id: ");
		i = 0;
		while (i < 6) {

			charHolder = getch();

			if (charHolder == 13) /*ASCII value of RETURN*/
			{
				printf("Login id is too short\n");
				break;
			}
			else if (charHolder == 8) /*ASCII value of BACKSPACE*/
			{
				putch('b');
				putch(NULL);
				putch('b');
				i--;
				continue;
			}
			userId[i] = charHolder;
			printf("%c", userId[i]);
			i++;
		}
		userId[6] = '\0';
		printf("\n");

		printf("Enter the password: ");
		i = 0;
		while (i < 6) {

			charHolder = getch();

			if (charHolder == 13) /*ASCII value of RETURN*/
			{
				printf("Password is too short\n");
				break;
			}
			else if (charHolder == 8) /*ASCII value of BACKSPACE*/
			{
				putch('b');
				putch(NULL);
				putch('b');
				i--;
				continue;
			}
			password[i] = charHolder;
			printf("*");
			i++;
		}
		password[6] = '\0';
		printf("\n");

		// test field
		/*printf("Id is %s\n", userId);
		printf("password is %s\n", password);*/

		for (i = 0; i < max_size; i++)
		{
			if (strcmp((login + i)->userId, userId) == 0 && strcmp((login + i)->password, password) == 0)
			{
				printf("Account %dth Id and Password match\n", i+1);
				found = 1;
				break;
			}
		}
		if (found != 1)
			printf("Id and Password not match\n");		
	}
}

void initArray(player_criteria* position_array, player_criteria* weight_array, int max_size)
{
	int i;

	for (i = 0; i < max_size; i++) {
		// initialise position_array
		(position_array + i)->criteria_cnt = 0;

		(position_array + i)->criteria_data.none_tkl = 0;
		(position_array + i)->criteria_data.less_3_tkl = 0;
		(position_array + i)->criteria_data.less_5_tkl = 0;
		(position_array + i)->criteria_data.more_5_tkl = 0;
		(position_array + i)->criteria_data.none_mtr = 0;
		(position_array + i)->criteria_data.less_10_mtr = 0;
		(position_array + i)->criteria_data.less_20_mtr = 0;
		(position_array + i)->criteria_data.more_20_mtr = 0;

		// initialise weight_array
		(weight_array + i)->criteria_cnt = 0;

		(weight_array + i)->criteria_data.none_tkl = 0;
		(weight_array + i)->criteria_data.less_3_tkl = 0;
		(weight_array + i)->criteria_data.less_5_tkl = 0;
		(weight_array + i)->criteria_data.more_5_tkl = 0;
		(weight_array + i)->criteria_data.none_mtr = 0;
		(weight_array + i)->criteria_data.less_10_mtr = 0;
		(weight_array + i)->criteria_data.less_20_mtr = 0;
		(weight_array + i)->criteria_data.more_20_mtr = 0;
	}
}

void addPlayer(struct node** head, struct node** tail)
{
	// call the addEnd function to add a node to the end, then sort the list out
	addEnd(head, tail);
}

void displayAll(struct node* head)
{
	// call the display function with 0 position, display all details
	display(head, 0);
}

void displayDetails(struct node* head, char key[20])
{
	// call the search function then pass the position where keyword is located to the display function
	int pos;
	pos = search(head, key);
	if (pos == 0)
	{
		printf("Search Failed\n");
	}
	else {
		display(head, pos);
	}
}

void updatePlayer(struct node* head, char key[20])
{
	// call the search function then pass the position where keyword is located to the update function
	int pos;
	pos = search(head, key);
	update(head, pos);
}

void deletePlayer(struct node** head, struct node** tail, char key[20])
{
	// call the search function then pass the position where keyword is located to the remove function
	int pos;
	pos = search(*head, key);
	removePosition(head, tail, pos);
}

void generateStatistic(struct node* head, player_criteria* position_array, player_criteria* weight_array, int max_size, int cat)
{
	// call the statisticCriterias function to generate statistics
	statisticCriterias(head, position_array, weight_array);
	displayStatistics(position_array, weight_array, max_size, cat);
}

void printAll(struct node* head, player_criteria* position_array, player_criteria* weight_array, int max_size, FILE *report_fp)
{
	// generate statistics before create the report file
	statisticCriterias(head, position_array, weight_array);

	player_criteria* placeHolder;
	struct node* temp;
	int i, j, cat;
	char positoin_title[20];
	char strPlaceHolder[20];
	float none_tkl[7], less_3_tkl[7], less_5_tkl[7], more_5_tkl[7];
	float none_mtr[7], less_10_mtr[7], less_20_mtr[7], more_20_mtr[7];

	temp = head;

	while (temp != NULL)
	{
		// test field
		fprintf(report_fp, "IRFU number: %s\n", temp->irfu_number);
		fprintf(report_fp, "First name: %s\n", temp->first_name);
		fprintf(report_fp, "Last name: %s\n", temp->last_name);
		fprintf(report_fp, "Age: %d\n", temp->age);
		fprintf(report_fp, "Height: %.2f\n", temp->height);
		fprintf(report_fp, "Weight: %.2f\n", temp->weight);
		fprintf(report_fp, "Club: %s\n", temp->club);
		fprintf(report_fp, "Email: %s\n", temp->email);
		fprintf(report_fp, "Position: %d\n", temp->position);
		fprintf(report_fp, "Number of tackles misses: %d\n", temp->ntm);
		fprintf(report_fp, "Number of metres makes: %d\n", temp->nmm);
		fprintf(report_fp, "\n");

		temp = temp->NEXT;
	}

	for (i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			cat = 1;
			placeHolder = position_array;
			strcpy(strPlaceHolder, "Position");
		}
		else if (i == 1)
		{
			cat = 2;
			placeHolder = weight_array;
			strcpy(strPlaceHolder, "Weight");
		}
		
		fprintf(report_fp, "-----------------< %s >-----------------\n", strPlaceHolder);

		for (j = 0; j < max_size; j++)
		{
			if (cat == 1)
			{
				if (j == 0)
					strcpy(strPlaceHolder, "Prop");
				else if (j == 1)
					strcpy(strPlaceHolder, "Hooker");
				else if (j == 2)
					strcpy(strPlaceHolder, "Second row");
				else if (j == 3)
					strcpy(strPlaceHolder, "Back row");
				else if (j == 4)
					strcpy(strPlaceHolder, "Half back");
				else if (j == 5)
					strcpy(strPlaceHolder, "Centre");
				else if (j == 6)
					strcpy(strPlaceHolder, "Winger/Full Back");
			}
			else if (cat == 2)
			{
				if (j == 0)
					strcpy(strPlaceHolder, "Weight <= 75");
				else if (j == 1)
					strcpy(strPlaceHolder, "Weight <= 80");
				else if (j == 2)
					strcpy(strPlaceHolder, "Weight <= 85");
				else if (j == 3)
					strcpy(strPlaceHolder, "Weight <= 90");
				else if (j == 4)
					strcpy(strPlaceHolder, "Weight <= 95");
				else if (j == 5)
					strcpy(strPlaceHolder, "Weight <= 100");
				else if (j == 6)
					strcpy(strPlaceHolder, "Weight > 100");
			}

			none_tkl[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.none_tkl, (placeHolder + i)->criteria_cnt);
			less_3_tkl[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.less_3_tkl, (placeHolder + i)->criteria_cnt);
			less_5_tkl[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.less_5_tkl, (placeHolder + i)->criteria_cnt);
			more_5_tkl[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.more_5_tkl, (placeHolder + i)->criteria_cnt);

			none_mtr[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.none_mtr, (placeHolder + i)->criteria_cnt);
			less_10_mtr[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.less_10_mtr, (placeHolder + i)->criteria_cnt);
			less_20_mtr[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.less_20_mtr, (placeHolder + i)->criteria_cnt);
			more_20_mtr[i] = caculateStatisticsForPrint((placeHolder + i)->criteria_data.more_20_mtr, (placeHolder + i)->criteria_cnt);

			fprintf(report_fp, "%s, total count: %d\n", strPlaceHolder, (placeHolder + j)->criteria_cnt);
			
			fprintf(report_fp, "a: none tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.none_tkl, none_tkl[i]);
			fprintf(report_fp, "b: less than 3 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_3_tkl, less_3_tkl[i]);
			fprintf(report_fp, "c: less than 5 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_5_tkl, less_5_tkl[i]);
			fprintf(report_fp, "d: more than 5 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.more_5_tkl, more_5_tkl[i]);

			fprintf(report_fp, "e: none metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.none_mtr, none_mtr[i]);
			fprintf(report_fp, "f: less than 10 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_10_mtr, less_10_mtr[i]);
			fprintf(report_fp, "g: less than 20 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_20_mtr, less_20_mtr[i]);
			fprintf(report_fp, "h: more than 20 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.more_20_mtr, more_20_mtr[i]);
			fprintf(report_fp, "\n");
		}
		printf("\n");
	}
	
	fclose(report_fp);
}

float caculateStatisticsForPrint(int num1, int num2)
{
	float result;
	if (num2 == 0)
	{
		result = 0;
	}
	else
	{
		result = ((float)num1 / num2) * 100;
	}

	return result;
}

void listPlayers(struct node* head, int cat)
{
	int pos;
	if (cat == 1)
	{
		pos = 3;
	}
	else if (cat == 2)
	{
		pos = 4;
	}
	
	/*bubbleSort(head, pos);*/
	selectionSort(head);
	displaySortedList(head, pos);
}

void loadDb(struct node** head, struct node** tail, FILE *db_fp)
{
	while (!feof(db_fp)) {
		struct node* temp;
		struct node* newNode;

		newNode = (struct node*)malloc(sizeof(struct node));

		fscanf(db_fp, "%s %s %s %d %f %f %s %s %d %d %d",
			newNode->irfu_number,
			newNode->first_name,
			newNode->last_name,
			&newNode->age,
			&newNode->height,
			&newNode->weight,
			newNode->club,
			newNode->email,
			&newNode->position,
			&newNode->ntm,
			&newNode->nmm
		);

		temp = *tail;
		newNode->NEXT = NULL;

		if (*head == NULL) {
			newNode->PREV = NULL;
			*head = newNode;
		}
		else {
			newNode->PREV = temp;
			temp->NEXT = newNode;
		}
		*tail = newNode;

	}

	// close file pointer
	fclose(db_fp);
}