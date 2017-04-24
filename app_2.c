#include "app_2.h"

void addEnd(struct node** head, struct node** tail)
{
	struct node* temp;
	struct node* newNode;
	int position;
	char temp_id[10];

	temp = *tail;
	newNode = (struct node*)malloc(sizeof(struct node));

	printf("Please enter the IRFU number\n");
	scanf("%s", temp_id);
	while (search(*head, temp_id) != 0)
	{
		printf("IRFU numbers are unique\n");
		printf("Please enter the IRFU number\n");
		scanf("%s", temp_id);
	}
	strcpy(newNode->irfu_number, temp_id);
	printf("Please enter the first name\n");
	scanf("%s", newNode->first_name);
	printf("Please enter the last name\n");
	scanf("%s", newNode->last_name);
	printf("Please enter the age\n");
	scanf("%d", &newNode->age);
	printf("Please enter the height\n");
	scanf("%f", &newNode->height);
	printf("Please enter the weight\n");
	scanf("%f", &newNode->weight);
	printf("Please enter the club name\n");
	scanf("%s", newNode->club);
	printf("Please enter the email\n");
	scanf("%s", newNode->email);
	printf("Please enter the number of the given list\n");
	printf("[1: Prop, 2: Hooker, 3: Second row, 4: Back row, 5: Half row, 6: Centre, 7: Winger/Full back]\n");
	scanf("%d", &newNode->position);
	printf("Please enter the number how many tackles the player misses per match\n");
	scanf("%d", &newNode->ntm);
	printf("Please enter the number how many metres the player makes per match\n");
	scanf("%d", &newNode->nmm);

	newNode->NEXT = NULL;

	if (*head == NULL)
	{
		newNode->PREV = NULL;
		*head = newNode;
	}
	else
	{
		newNode->PREV = temp;
		temp->NEXT = newNode;
	}
	*tail = newNode;
}

int length(struct node* head)
{
	struct node* temp;
	int len = 0;

	temp = head;

	while (temp != NULL)
	{
		len++;
		temp = temp->NEXT;
	}
	return len;
}

void display(struct node* head, int pos)
{
	struct node* temp;
	int i;

	temp = head;

	while (temp != NULL)
	{
		if (pos == 0)
		{
			// test field
			printf("IRFU number: %s\n", temp->irfu_number);
			printf("First name: %s\n", temp->first_name);
			printf("Last name: %s\n", temp->last_name);
			printf("Age: %d\n", temp->age);
			printf("Height: %.2f\n", temp->height);
			printf("Weight: %.2f\n", temp->weight);
			printf("Club: %s\n", temp->club);
			printf("Email: %s\n", temp->email);
			printf("Position: %d\n", temp->position);
			printf("Number of tackles misses: %d\n", temp->ntm);
			printf("Number of metres makes: %d\n", temp->nmm);
			printf("\n");

			temp = temp->NEXT;
		}
		else if (pos > 0)
		{
			printf("positon %d: \n", pos);

			for (i = 0; i < pos - 1; i++)
			{
				temp = temp->NEXT;
			}

			printf("IRFU number: %s\n", temp->irfu_number);
			printf("First name: %s\n", temp->first_name);
			printf("Last name: %s\n", temp->last_name);
			printf("Age: %d\n", temp->age);
			printf("Height: %.2f\n", temp->height);
			printf("Weight: %.2f\n", temp->weight);
			printf("Club: %s\n", temp->club);
			printf("Email: %s\n", temp->email);
			printf("Position: %d\n", temp->position);
			printf("Number of tackles misses: %d\n", temp->ntm);
			printf("Number of metres makes: %d\n", temp->nmm);
			printf("\n");
			break;
		}

		/*temp = temp->NEXT;*/
	}

}

void removeStart(struct node** head, struct node** tail)
{
	struct node* temp;

	if (*head == NULL)
	{
		printf("The list is empty\n");
	}
	else if (length(*head) == 1)
	{
		temp = *head;
		*head = NULL;
		*tail = NULL;

		free(temp);
	}
	else
	{
		temp = *head;
		*head = temp->NEXT;
		(temp->NEXT)->PREV = NULL;

		free(temp);
	}
}

void removeEnd(struct node** head, struct node** tail)
{
	struct node* temp;

	if (*head == NULL)
	{
		printf("The list is empty\n");
	}
	else if (length(*head) == 1)
	{
		temp = *head;
		*head = NULL;
		*tail = NULL;

		free(temp);
	}
	else
	{
		temp = *tail;
		*tail = temp->PREV;
		(temp->PREV)->NEXT = NULL;

		free(temp);
	}
}

void removePosition(struct node** head, struct node** tail, int pos)
{
	struct node* temp;

	if (*head == NULL)
	{
		printf("Size is 0, nothing to remove\n");
	}
	else if (pos == 1)
	{
		printf("Position is %d, delete from the first\n", pos);
		removeStart(head, tail);
	}
	else if (pos < length(*head))
	{
		temp = *head;

		for (int i = 0; i < pos - 1; i++)
		{
			temp = temp->NEXT;
		}

		(temp->PREV)->NEXT = (temp->NEXT);
		(temp->NEXT)->PREV = (temp->PREV);

		free(temp);
	}
	else
	{
		printf("Position is %d, delete from the end\n", pos);
		removeEnd(head, tail);
	}
}

int search(struct node* head, char key[20])
{
	struct node* temp;
	int location, i, cnt;

	i = 0;
	cnt = 0;
	location = 0;
	temp = head;

	while (temp != NULL)
	{
		i++;
		if (strcmp(temp->irfu_number, key) == 0)
		{
			location = i;
		}
		else if (strcmp(temp->first_name, key) == 0)
		{
			location = i;
			cnt++;
			printf("%s is here at index %d\n", key, location);
		}
		temp = temp->NEXT;
	}
	printf("Location of element you looked for is %d\n", location);

	if (cnt > 1)
	{
		printf("Please choose one of %s: ", key);
		scanf("%d", &location);
	}

	return location;
}

void update(struct node* head, int pos)
{
	struct node* temp;
	char new_irfu_number[8], new_first_name[10], new_last_name[10], new_club[20], new_email[30];
	int new_age, new_position, new_ntm, new_nmm;
	float new_height, new_weight;

	temp = head;

	// move temp pointer to the position
	for (int i = 0; i < pos - 1; i++)
	{
		temp = temp->NEXT;
	}

	// get values to be updated
	//printf("Please enter the IRFU number\n"); // #need validation, unique number
	//scanf("%s", new_irfu_number);
	printf("Please enter the first name\n");
	scanf("%s", new_first_name);
	printf("Please enter the last name\n");
	scanf("%s", new_last_name);
	printf("Please enter the age\n");
	scanf("%d", &new_age);
	printf("Please enter the height\n");
	scanf("%f", &new_height);
	printf("Please enter the weight\n");
	scanf("%f", &new_weight);
	printf("Please enter the club name\n");
	scanf("%s", new_club);
	printf("Please enter the email\n");
	scanf("%s", new_email);
	printf("Please enter the number of the given list\n");
	printf("[1: Prop, 2: Hooker, 3: Second row, 4: Back row, 5: Half row, 6: Centres, 7: Winger/Full back]\n");
	scanf("%d", &new_position);
	printf("Please enter the number how many tackles the player misses per match\n");
	scanf("%d", &new_ntm);
	printf("Please enter the number how many metres the player makes per match\n");
	scanf("%d", &new_nmm);

	// update values
	strcpy(temp->irfu_number, new_irfu_number);
	strcpy(temp->first_name, new_first_name);
	strcpy(temp->last_name, new_last_name);
	temp->age = new_age;
	temp->height = new_height;
	temp->weight = new_weight;
	strcpy(temp->club, new_club);
	strcpy(temp->email, new_email);
	temp->position = new_position;
	temp->ntm = new_ntm;
	temp->nmm = new_nmm;
}

void statisticCriterias(struct node* head, player_criteria* position_array, player_criteria* weight_array)
{
	int i;
	struct node* temp;
	player_criteria* position;
	player_criteria* weight;
	
	temp = head;
	position = position_array;
	weight = weight_array;

	while (temp != NULL)
	{
		// update data of position array
		for (i = 0; i < 7; i++)
		{
			if (temp->position == i + 1)
			{
				(position + i)->criteria_cnt++;

				// update the number of tackles misses
				if (temp->ntm == 0)
				{
					(position + i)->criteria_data.none_tkl++;
				}
				else if (temp->ntm <= 3)
				{
					(position + i)->criteria_data.less_3_tkl++;
				}
				else if (temp->ntm <= 5)
				{
					(position + i)->criteria_data.less_5_tkl++;
				}
				else if (temp->ntm > 5)
				{
					(position + i)->criteria_data.more_5_tkl++;
				}

				// update the number of metres makes
				if (temp->nmm == 0)
				{
					(position + i)->criteria_data.none_mtr++;
				}
				else if (temp->nmm <= 10)
				{
					(position + i)->criteria_data.less_10_mtr++;
				}
				else if (temp->nmm <= 20)
				{
					(position + i)->criteria_data.less_20_mtr++;
				}
				else if (temp->nmm > 20)
				{
					(position + i)->criteria_data.more_20_mtr++;
				}
			}
		}

		// update data of weight array
		for (i = 0; i < 7; i++)
		{
			if (i == 0 && temp->weight <= 75 + (i * 5))
			{
				(weight + i)->criteria_cnt++;

				// update the number of tackles misses
				if (temp->ntm == 0)
				{
					(weight + i)->criteria_data.none_tkl++;
				}
				else if (temp->ntm <= 3)
				{
					(weight + i)->criteria_data.less_3_tkl++;
				}
				else if (temp->ntm <= 5)
				{
					(weight + i)->criteria_data.less_5_tkl++;
				}
				else if (temp->ntm > 5)
				{
					(weight + i)->criteria_data.more_5_tkl++;
				}

				// update the number of metres makes
				if (temp->nmm == 0)
				{
					(weight + i)->criteria_data.none_mtr++;
				}
				else if (temp->nmm <= 10)
				{
					(weight + i)->criteria_data.less_10_mtr++;
				}
				else if (temp->nmm <= 20)
				{
					(weight + i)->criteria_data.less_20_mtr++;
				}
				else if (temp->nmm > 20)
				{
					(weight + i)->criteria_data.more_20_mtr++;
				}
			}
			else if (temp->weight > 70 + (i * 5) && temp->weight <= 75 + (i * 5))
			{
				(weight + i)->criteria_cnt++;

				// update the number of tackles misses
				if (temp->ntm == 0)
				{
					(weight + i)->criteria_data.none_tkl++;
				}
				else if (temp->ntm <= 3)
				{
					(weight + i)->criteria_data.less_3_tkl++;
				}
				else if (temp->ntm <= 5)
				{
					(weight + i)->criteria_data.less_5_tkl++;
				}
				else if (temp->ntm > 5)
				{
					(weight + i)->criteria_data.more_5_tkl++;
				}

				// update the number of metres makes
				if (temp->nmm == 0)
				{
					(weight + i)->criteria_data.none_mtr++;
				}
				else if (temp->nmm <= 10)
				{
					(weight + i)->criteria_data.less_10_mtr++;
				}
				else if (temp->nmm <= 20)
				{
					(weight + i)->criteria_data.less_20_mtr++;
				}
				else if (temp->nmm > 20)
				{
					(weight + i)->criteria_data.more_20_mtr++;
				}
			}
			if (i == 6 && temp->weight > 100)
			{
				(weight + 6)->criteria_cnt++;

				// update the number of tackles misses
				if (temp->ntm == 0)
				{
					(weight + 6)->criteria_data.none_tkl++;
				}
				else if (temp->ntm <= 3)
				{
					(weight + 6)->criteria_data.less_3_tkl++;
				}
				else if (temp->ntm <= 5)
				{
					(weight + 6)->criteria_data.less_5_tkl++;
				}
				else if (temp->ntm > 5)
				{
					(weight + 6)->criteria_data.more_5_tkl++;
				}

				// update the number of metres makes
				if (temp->nmm == 0)
				{
					(weight + 6)->criteria_data.none_mtr++;
				}
				else if (temp->nmm <= 10)
				{
					(weight + 6)->criteria_data.less_10_mtr++;
				}
				else if (temp->nmm <= 20)
				{
					(weight + 6)->criteria_data.less_20_mtr++;
				}
				else if (temp->nmm > 20)
				{
					(weight + 6)->criteria_data.more_20_mtr++;
				}
			}
			
		}

		// move to the next node
		temp = temp->NEXT;
	}
}

void displayStatistics(player_criteria* position_array, player_criteria* weight_array, int max_size, int cat)
{
	player_criteria* placeHolder;
	int i;
	char positoin_title[20];
	char strPlaceHolder[20];
	float none_tkl[7], less_3_tkl[7], less_5_tkl[7], more_5_tkl[7];
	float none_mtr[7], less_10_mtr[7], less_20_mtr[7], more_20_mtr[7];


	if (cat == 1)
	{
		placeHolder = position_array;
		strcpy(strPlaceHolder, "Position");
	}
	else if (cat == 2)
	{
		placeHolder = weight_array;
		strcpy(strPlaceHolder, "Weight");
	}

	printf("-----------------< %s >-----------------\n", strPlaceHolder);
		
	for (i = 0; i < max_size; i++)
	{
		if (cat == 1)
		{
			if (i == 0)
				strcpy(strPlaceHolder, "Prop");
			else if (i == 1)
				strcpy(strPlaceHolder, "Hooker");
			else if (i == 2)
				strcpy(strPlaceHolder, "Second row");
			else if (i == 3)
				strcpy(strPlaceHolder, "Back row");
			else if (i == 4)
				strcpy(strPlaceHolder, "Half back");
			else if (i == 5)
				strcpy(strPlaceHolder, "Centre");
			else if (i == 6)
				strcpy(strPlaceHolder, "Winger/Full Back");
		}
		else if (cat == 2)
		{
			if (i == 0)
				strcpy(strPlaceHolder, "Weight <= 75");
			else if (i == 1)
				strcpy(strPlaceHolder, "Weight <= 80");
			else if (i == 2)
				strcpy(strPlaceHolder, "Weight <= 85");
			else if (i == 3)
				strcpy(strPlaceHolder, "Weight <= 90");
			else if (i == 4)
				strcpy(strPlaceHolder, "Weight <= 95");
			else if (i == 5)
				strcpy(strPlaceHolder, "Weight <= 100");
			else if (i == 6)
				strcpy(strPlaceHolder, "Weight > 100");
		}

		none_tkl[i] = caculateStatistics((placeHolder + i)->criteria_data.none_tkl, (placeHolder + i)->criteria_cnt);
		less_3_tkl[i] = caculateStatistics((placeHolder + i)->criteria_data.less_3_tkl, (placeHolder + i)->criteria_cnt);
		less_5_tkl[i] = caculateStatistics((placeHolder + i)->criteria_data.less_5_tkl, (placeHolder + i)->criteria_cnt);
		more_5_tkl[i] = caculateStatistics((placeHolder + i)->criteria_data.more_5_tkl, (placeHolder + i)->criteria_cnt);

		none_mtr[i] = caculateStatistics((placeHolder + i)->criteria_data.none_mtr, (placeHolder + i)->criteria_cnt);
		less_10_mtr[i] = caculateStatistics((placeHolder + i)->criteria_data.less_10_mtr, (placeHolder + i)->criteria_cnt);
		less_20_mtr[i] = caculateStatistics((placeHolder + i)->criteria_data.less_20_mtr, (placeHolder + i)->criteria_cnt);
		more_20_mtr[i] = caculateStatistics((placeHolder + i)->criteria_data.more_20_mtr, (placeHolder + i)->criteria_cnt);
			
		printf("%s, total count: %d\n", strPlaceHolder, (placeHolder + i)->criteria_cnt);

		printf("a: none tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.none_tkl, none_tkl[i]);
		printf("b: less than 3 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_3_tkl, less_3_tkl[i]);
		printf("c: less than 5 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_5_tkl, less_5_tkl[i]);
		printf("d: more than 5 tackles: %d, %.2f%%\n", (placeHolder + i)->criteria_data.more_5_tkl, more_5_tkl[i]);

		printf("e: none metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.none_mtr, none_mtr[i]);
		printf("f: less than 10 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_10_mtr, less_10_mtr[i]);
		printf("g: less than 20 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.less_20_mtr, less_20_mtr[i]);
		printf("h: more than 20 metres: %d, %.2f%%\n", (placeHolder + i)->criteria_data.more_20_mtr, more_20_mtr[i]);
		printf("\n");
	}
	printf("\n");

}

float caculateStatistics(int num1, int num2)
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

void selectionSort(struct node* head)
{
	struct node* start = head;
	struct node* traverse;
	struct node* min;
	int i = 0, j = 0;

	while (start->NEXT)
	{
		min = start;
		traverse = start->NEXT;

		while (traverse)
		{
			// Find minimum element from array 
			if (min->height > traverse->height)
			{
				min = traverse;
			}

			traverse = traverse->NEXT;
		}

		// Put minimum element on starting location
		swap(start, min);			
		start = start->NEXT;
	}
}

// Swap data field of linked list 
void swap(struct node* start, struct node* min)
{
	// initialise
	struct node* temp;
	char temp_irfu_number[8] = "";
	char temp_first_name[10] = "";
	char temp_last_name[10] = "";
	int temp_age = 0;
	float temp_height = 0;
	float temp_weight = 0;
	char temp_club[20] = "";
	char temp_email[30] = "";
	int temp_position = 0;
	int temp_ntm = 0;
	int temp_nmm = 0;
	
	strcpy(temp_irfu_number, start->irfu_number);
	strcpy(temp_first_name, start->first_name);
	strcpy(temp_last_name, start->last_name);
	temp_age = start->age;
	temp_height = start->height;
	temp_weight = start->weight;
	strcpy(temp_club, start->club);
	strcpy(temp_email, start->email);
	temp_position = start->position;
	temp_ntm = start->ntm;
	temp_nmm = start->nmm;
	
	strcpy(start->irfu_number, min->irfu_number);
	strcpy(start->first_name, min->first_name);
	strcpy(start->last_name, min->last_name);
	start->age = min->age;
	start->height = min->height;
	start->weight = min->weight;
	strcpy(start->club, min->club);
	strcpy(start->email, min->email);
	start->position = min->position;
	start->ntm = min->ntm;
	start->nmm = min->nmm;
	
	strcpy(min->irfu_number, temp_irfu_number);
	strcpy(min->first_name, temp_first_name);
	strcpy(min->last_name, temp_last_name);
	min->age = temp_age;
	min->height = temp_height;
	min->weight = temp_weight;
	strcpy(min->club, temp_club);
	strcpy(min->email, temp_email);
	min->position = temp_position;
	min->ntm = temp_ntm;
	min->nmm = temp_nmm;
}

void displaySortedList(struct node* head, int pos)
{
	struct node* temp;
	int i = 0;
	temp = head;

	while (temp != NULL)
	{
		if (temp->position == pos)
		{
			i++;
			printf("found at %d\n", i);
			printf("IRFU number: %s\n", temp->irfu_number);
			printf("First name: %s\n", temp->first_name);
			printf("Last name: %s\n", temp->last_name);
			printf("Age: %d\n", temp->age);
			printf("Height: %.2f\n", temp->height);
			printf("Weight: %.2f\n", temp->weight);
			printf("Club: %s\n", temp->club);
			printf("Email: %s\n", temp->email);
			printf("Position: %d\n", temp->position);
			printf("Number of tackles misses: %d\n", temp->ntm);
			printf("Number of metres makes: %d\n", temp->nmm);
			printf("\n");
		}
		temp = temp->NEXT;
	}

}