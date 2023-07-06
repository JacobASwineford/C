#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generate_code(int length, int num_choices);
void print(int* arr, int length);
void printc(char* arr, int length);

int* code;
int* guess;
char* clue;

int code_length;

int main() {
	int length = 0;
	int num_choices = 0;
	printf("\nEnter length and number of choices: ");
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
		
		// test for green
		for (int i = 0; i < length; i++) {
			if (guess[i] == code[i]) {
				clue[i] = 'g';
			}
		}
		
		// test for yellow
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				if (guess[i] == code[j] && clue[j] != 'g') {
					clue[i] = 'y';
					break;
				}
			}
		}
		
		printf("\nguess: ");
		print(guess, length);
		printf("clue: ");
		printc(clue, length);
		
		// check for end of the game
		int end = 1;
		for (int i = 0; i < length; i++) {
			if (clue[i] != 'g') end = 0;
		}
		
		if (end) {
			printf("\nCongratulations, you win! the code is: ");
			print(code, length);
			break;
		}
		
		// after printing clue, revert clue back to red
		for (int i = 0; i < length; i++)
			clue[i] = 'r';
	}
	
	free(code);
	free(guess);
	free(clue);
}

void generate_code(int length, int num_choices) {
	srand(time(NULL));
	code = (int*) malloc(sizeof(int) * length);
	clue = (char*) malloc(length);
	guess = (int*) malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++) {
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
