#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct point {
	int location;
	int num_paths;
	int** paths;
	int empty;
} point;

point** points;
int* raw;

// used while in-game
int*** valid_paths;
int* valid_count;


void put(int n, ...) {
	va_list li;
	va_start(li, n);
	for (int i = 0; i < n; i++) {
		raw[i] = va_arg(li, int);
	}
}

void print(int* arr, int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		if (i != n - 1) printf("%d, ", arr[i]);
		else printf("%d]\n", arr[i]);
	}
}

void print_point(point* p) {
	printf(
	"Location: %d\nEmpty: %d\nNumber of Paths: %d\n", p->location, p->empty, p->num_paths);
	for (int i = 0; i < p->num_paths; i++) {
		printf("Path #%d: ", i);
		print(p->paths[i], 2);
	}
}	

point* init_point(int lo, int np) {
	point* p = (point*) malloc(sizeof(point));
	p->location = lo;
	p->num_paths = np;
	p->empty = 1;
	p->paths = (int**) malloc(sizeof(int*) * np);
	valid_paths[lo - 1] = (int**) malloc(sizeof(int*) * np);
	int c = 0;
	for (int i = 0; i < np; i++) {
		p->paths[i] = (int*) malloc(sizeof(int) * 2);
		p->paths[i][0] = raw[c++];
		p->paths[i][1] = raw[c++];
	}
	//print_point(p);
	return p;
}

void free_point(point* p) {
	for (int i = 0; i < p->num_paths; i++)
		free(p->paths[i]);
	free(p->paths);
}

void init_all() {
	points = (point**) malloc(sizeof(point*) * 15);
	raw = (int*) malloc(sizeof(int) * 8);
	
	valid_paths = (int***) malloc(sizeof(int**) * 15);
	valid_count = (int*) malloc(sizeof(int) * 15);
	for (int i = 0; i < 15; i++) 
		valid_count[i] = 0;
	
	put(4, 2, 4, 3, 6);
	point* one = init_point(1, 2);
	
	put(4, 4, 7, 8, 13);
	point* two = init_point(2, 2);
	
	put(4, 5, 8, 6, 10);
	point* three = init_point(3, 2);
	
	put(8, 2, 1, 5, 6, 8, 13, 7, 11);
	point* four = init_point(4, 4);
	
	put(4, 8, 12, 9, 14);
	point* five = init_point(5, 2);
	
	put(8, 3, 1, 10, 15, 9, 13, 5, 4);
	point* six = init_point(6, 4);
	
	put(4, 4, 2, 8, 9);
	point* seven = init_point(7, 2);
	
	put(4, 9, 10, 5, 3);
	point* eight = init_point(8, 2);
	
	put(4, 8, 7, 5, 2);
	point* nine = init_point(9, 2);
	
	put(4, 9, 8, 6, 3);
	point* ten = init_point(10, 2);
	
	put(4, 7, 4, 12, 13);
	point* eleven = init_point(11, 2);
	
	put(4, 8, 5, 13, 14);
	point* twelve = init_point(12, 2);
	
	put(8, 12, 11, 8, 4, 9, 6, 14, 15);
	point* thirteen = init_point(13, 4);
	
	put(4, 13, 12, 9, 5);
	point* fourteen = init_point(14, 2);
	
	put(4, 14, 13, 10, 6);
	point* fifteen = init_point(15, 2);
	
	points[0] = one;
	points[1] = two;
	points[2] = three;
	points[3] = four;
	points[4] = five;
	points[5] = six;
	points[6] = seven;
	points[7] = eight;
	points[8] = nine;
	points[9] = ten;
	points[10] = eleven;
	points[11] = twelve;
	points[12] = thirteen;
	points[13] = fourteen;
	points[14] = fifteen;
}

void free_all() {
	for (int i = 0; i < 15; i++) {
		free(points[i]);
		free(valid_paths[i]);
	}
	free(points);
	free(raw);
	free(valid_count);
	free(valid_paths);
}

void print_board() {
	printf("\n");
	char sp[6];
	for (int i = 0; i < 5; i++) sp[i] = ' ';
	sp[5] = '\0';
	int c = 0;
	for (int row = 1; row < 6; row++) {
		int spaces = 6 - row;
		printf("%.*s", spaces, sp);
		for (int e = 0; e < row; e++) {
			printf("%d ", points[c++]->empty);
		}
		printf("\n");
	}
	printf("\n");
}

int valid_path(int* path) {
	return !points[path[1]]->empty && points[path[0]]->empty;
}

void update_validity() {
	// clear valid arrays
	
	// update valid arrays
	for (int i = 0; i < 15; i++) {
		point* p = points[i];
		int** paths = p->paths;
		int c = 0;
		for (int j = 0; j < p->num_paths; j++) {
			int* path = paths[j];
			if (valid_path(path)) {
				valid_paths[i][c++] = path;
				valid_count[i] = c;
			}
		}
	}
}

int main() {
	printf("Welcome to the game of Pegs!\n");
	init_all();
	
	int start;
	printf("Enter Point to be empty [1-15]: ");
	scanf("%d", &start);
	points[start - 1]->empty = 0;
	
	while (1) {
		int peg;
		int path;
		print_board();
		
		while (1) {
			printf("Peg (42 to quit): ");
			scanf("%d", &peg);
			if (peg == 42) {
				printf("goodbye!");
				free_all();
				return 0;
			}
			printf("\nPATHS FOR PEG!\n");
			printf("Path (24 to peg selection): ");
			scanf("%d", &path);
			if (path == 24) continue;
			break;
		}
		
	}
	
	free_all();
	return 0;
}