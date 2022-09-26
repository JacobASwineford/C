#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generate_code(int length, int num_choices);
void print(int* arr, int length);
void printc(char* arr, int length);

int* code;
int* guess;
char* clue;
int* blist;

int code_length;

int main() {
	int length = 0;
	int num_choices = 0;
	printf("Enter length and number of choices: ");
	scanf("%d %d", &length, &num_choices);
	generate_code(length, num_choices);
	
	while (1) {
		printf("\nEnter guess: ");
		int g = 0;
		for (int i = 0; i < length; i++) {
			scanf("%d", &g);
			guess[i] = g;
			clue[i] = 'r';
		}
		
		// test for exact match
		for (int i = 0; i < length; i++) {
			if (guess[i] == code[i]) {
				clue[i] = 'g';
				blist[i] = 1;
			}
		}
		
		// test for yellow
		
		
		
		break;
		
	}
	
	printf("code: ");
	print(code, length);
	printf("guess: ");
	print(guess, length);
	printf("clue: ");
	printc(clue, length);
	printf("blist: ");
	print(blist, length);
	// 1 1 2 2
	// 2 2 2 4
	// y r g r  
	
	
	free(code);
	free(guess);
	free(clue);
	free(blist);
}

void generate_code(int length, int num_choices) {
	srand(time(NULL));
	code = (int*) malloc(sizeof(int) * length);
	clue = (char*) malloc(length);
	guess = (int*) malloc(sizeof(int) * length);
	blist = (int*) malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++) {
		blist[i] = 0;
		code[i] = rand() % num_choices;
	}
}

void print(int* arr, int length) {
	printf("[");
	for (int i = 0; i < length; i++) {
		if (i == length - 1) printf("%d]\n", arr[i]);
		else printf("%d, ", arr[i]);
	}
}

void printc(char* arr, int length) {
	printf("[");
	for (int i = 0; i < length; i++) {
		if (i == length - 1) printf("%c]\n", arr[i]);
		else printf("%c, ", arr[i]);
	}
}
