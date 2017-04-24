#include "app_1.h"

// Primitive functions
// add: add a node to the end
// remove: remove a node from the list where user wants from
// display: position 0 => display all details, position (num) => display a node
// update: search for a position where the keyword is located, then modify a node of that position
// sort: using the selection sort method
// length: get the length of the list
// search: pass user's keyword to look for where the keyword matches then return the positon

void addEnd(struct node** head, struct node** tail);
void removeStart(struct node** head, struct node** tail);
void removeEnd(struct node** head, struct node** tail);
void removePosition(struct node** head, struct node** tail, int pos);
void display(struct node* head, int pos);
void update(struct node* head, int pos);
void statisticCriterias(struct node* head, player_criteria* position_array, player_criteria* weight_array);
void displayStatistics(player_criteria* position_array, player_criteria* weight_array, int max_size, int cat);
int length(struct node* head);
int search(struct node* head, char key[20]);
float caculateStatistics(int num1, int num2);
void selectionSort(struct node* head);
void swap(struct node* start, struct node* min);
void displaySortedList(struct node* head, int pos);