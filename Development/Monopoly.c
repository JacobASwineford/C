#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct property {
	char* name;
	int price;
	
	// rent is priceline[houses]
	int hcost;
	int houses;
	int* priceline;
} property;

typedef struct railroad {
	char* name;
} railroad;

typedef struct utility {
	char* name;
} utility;

typedef struct player {
	char* name;
	property* properties;
	railroad* railroads;
	utility* utilities;
	int money;
	int bankrupt;
} player;

typedef void (*activation)(void);

typedef struct event {
	char* name;
	char* description;
	activation effect;
} event;

// when players land on the spaces on the board, these functions will run
void pact(void); // property
void ccact(void); // community chest
void chact(void); // chance
void fpact(void); // free parking
void rract(void); // railroad
void ptact(void); // property tax
void itact(void); // income tax

// community chest cards

// chance cards

player** players;
player* pcurrent;

activation landing;
activation chest;
activation  chance;

int pot;

int main () {
	activation act = &pact;
	
	(*act)();
	
	int arr[3] = {1, 2, 3};
	int* p = arr;
	
	for (int i = 0; i < 3; i++) 
		printf("%d\n", *(p + i));
	return 0;
}

void pact(void) {
	printf("Hello, there, world!");
}

void ccact(void) {
	
}

void chact(void) {
	
}

void fpact(void) {
	
} 

void rract(void) {
	
}

void ptact(void) {
	
}

void itact(void) {
	
}
