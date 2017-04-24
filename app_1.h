#ifndef app_h
#define app_h

#include<stdio.h>
#include<stdlib.h>

// Account description
// userId: 6 characters and ends with '\0'
// password: will be displayed ****** instead

// Player criteria and player data
// data will be stored and used for calculating statistics

// Databas description
// IRFU number: Unique, contains a prefix - 'IRFU' then [3 digits numbers(000 - 999)]. ie. IRFU123
// First name: string length of 10. ie. John
// Last name: string length of 10. ie. Smith
// Age: whole number. ie. 23
// height: decimal number #unit: cm. ie. 186.5
// weight: decimal number #unit: kg. ie. 84.6
// email: string length of 30 contains a '@' and ends with '.com'. ie. john_smith@irfu.com
// position: user can choose one of options [1: prop, 2: hooker, 3: second row, 4: back row, 5: half row, 6: centre, 7: winger/full back]. ie. 2
// ntm: user can put a whole 'Number of Tackles Missing'(NTM) per match, that number will be directed to the one of criterias [never, less than 3, less than 5, more than 5]. 
// ie. case 1: 4 (less than 5), case 2: 5 (less than 5 #but 6 will be more than 5)
// ntm: user can put a whole 'Number of Metres Making'(NMM) per match, that number will be directed to the one of criterias [none, less than 10, less than 20, more than 20].
// ie. case 1: 15 (less than 20), case 2: 20 (less than 20 #but 21 will be more than 20)

struct account
{
	char userId[7];
	char password[7];
};

typedef struct player_data
{
	int none_tkl;
	int less_3_tkl;
	int less_5_tkl;
	int more_5_tkl;
	int none_mtr;
	int less_10_mtr;
	int less_20_mtr;
	int more_20_mtr;
}player_data;

typedef struct player_criteria
{
	int criteria_cnt;
	player_data criteria_data;
}player_criteria;

struct node
{
	char irfu_number[8];
	char first_name[10];
	char last_name[10];
	int age;
	float height;
	float weight;
	char club[20];
	char email[30];
	int position;
	int ntm;
	int nmm;
	struct node* NEXT;
	struct node* PREV;
};

// Menu functions
// loadLogin: read user id and password from a file 'login.txt'
// loadDb: read players data from a file 'rugby.txt'
// loginValidataion: validate user id and password
// addPlayer: add a node to the end then sort the list, ascending order
// displayAll: display all players details
// displayDetails: prompt user's search keyword then look for the position in the list, and display a node of that position
// updatePlayer: prompt user's search keyword then look for the position in the list, and prompt values then replace them
// deletePlayer: prompt user's search keyword then look for the position in the list, and link the previous and next nodes together then free the node
// geerateStatistics: generate and calculate statistics from the players data then display
// printAll: print all players into a report file, all details and performance statistics
// caculateStatisticsForPrint: calculate the percentage for printing the report file 'report.txt'
// listPlayers: prompt the number that represents that player's positon [1: second row, 2: back row], then display all details in order of heightS
// initArray: initialise teh Player criteria and player data

void loadLogin(struct account* account, int max_size, FILE *login_fp);
void loadDb(struct node** head, struct node** tail, FILE *db_fp);
void loginValidation(struct account* account, int max_size);
void addPlayer(struct node** head, struct node** tail);
void displayAll(struct node* head);
void displayDetails(struct node* head, char key[20]);
void updatePlayer(struct node* head, char key[20]);
void deletePlayer(struct node** head, struct node** tail, char key[20]);
void generateStatistic(struct node* head, player_criteria* position_array, player_criteria* weight_array, int max_size, int cat);
void printAll(struct node* head, player_criteria* position_array, player_criteria* weight_array, int max_size, FILE *report_fp);
float caculateStatisticsForPrint(int num1, int num2);
void listPlayers(struct node* head, int cat);
void initArray(player_criteria* position_array, player_criteria* weight_array, int max_size);

#endif /* linkedlist_h */
