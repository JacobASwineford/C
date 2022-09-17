#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct path {
	int first;
	int second;
} path;

typedef struct point {
	int location;
	int num_paths;
	path* paths;
	int occupied;
} point;

point** points;
int* raw; // used for initializing path in point

void put_point(int lo, int np);
void put_raw(int n, ...);
void init_all();
void free_point(point* p); // also frees raw
void free_all();

int valid_path(path p);

void print(int* arr, int length);
void print_path(path p);
void print_board();

int main() {
	init_all();
	
	printf("Welcome to the game of Pegs!\n");
	
//	for (int i = 0; i < 15; i++) {
//		printf("Point %d:\n", i);
//		path* paths = points[i]->paths;
//		for (int j = 0; j < points[i]->num_paths; j++) {
//			printf("[%d, %d]\n", paths[j].first, paths[j].second);
//		}
//		printf("\n");
//	}

	print_board();
	int selected = 0;
	printf("Select a point to be empty: ");
	scanf("%d", &selected);
	points[selected - 1]->occupied = 0;
	
	while (1) {
		print_board();
		printf("Select a point: ");
		scanf("%d", &selected);
		if (!points[selected - 1]->occupied) {
			printf("This point is not occupied. Please Try Again.\n");
			continue;
		}
		path* paths = points[selected - 1]->paths;
		int np = points[selected - 1]->num_paths;
		int* valid = (int*) malloc(sizeof(int) * 4);
		int c = 0;
		for (int i = 0; i < np; i++) {
			if (valid_path(paths[i])) {
				print_path(paths[i]);
				c++;
			}
		}
		if (c == 0) {
			printf("No Valid Paths Found. Please try Again.\n");
			free(valid);
			continue;
		}
		break;
	}
	
	free_all();
	return 0;
}

void put_point(int lo, int np) {
	point* p = (point*) malloc(sizeof(point));
	p->location = lo;
	p->num_paths = np;
	p->occupied = 1;
	path* paths = (path*) malloc(sizeof(path) * np);
	int c = 0;
	for (int i = 0; i < np; i++) {
		paths[i].first = raw[c++];
		paths[i].second = raw[c++];
	}
	p->paths = paths;
	points[lo] = p;
}

void put_raw(int n, ...) {
	va_list li;
	va_start(li, n);
	for (int i = 0; i < n; i++)
		raw[i] = va_arg(li, int);
}

void init_all() {
	points = (point**) malloc(sizeof(point*) * 15);
	raw = (int*) malloc(sizeof(int) * 8);
	
	put_raw(4, 1, 3, 2, 5);
	put_point(0, 2);
	
	put_raw(4, 3, 6, 7, 12);
	put_point(1, 2);
	
	put_raw(4, 4, 7, 5, 9);
	put_point(2, 2);
	
	put_raw(8, 1, 0, 4, 5, 7, 12, 6, 10);
	put_point(3, 4);
	
	put_raw(4, 7, 11, 8, 13);
	put_point(4, 2);
	
	put_raw(8, 2, 0, 9, 14, 8, 12, 4, 3);
	put_point(5, 4);
	
	put_raw(4, 3, 1, 7, 8);
	put_point(6, 2);
	
	put_raw(4, 8, 9, 4, 2);
	put_point(7, 2);
	
	put_raw(4, 7, 6, 4, 1);
	put_point(8, 2);
	
	put_raw(4, 8, 7, 5, 2);
	put_point(9, 2);
	
	put_raw(4, 6, 3, 11, 12);
	put_point(10, 2);
	
	put_raw(4, 7, 4, 12, 13);
	put_point(11, 2);
	
	put_raw(8, 11, 10, 7, 3, 8, 5, 13, 14);
	put_point(12, 4);
	
	put_raw(4, 12, 11, 8, 4);
	put_point(13, 2);
	
	put_raw(4, 13, 12, 9, 5);
	put_point(14, 2);
}

void free_point(point* p) {
	free(p->paths);
	free(p);
}

void free_all() {
	for (int i = 0; i < 15; i++)
		free_point(points[i]);
	free(points);
	free(raw);
}

int valid_path(path p) {
	return points[p.first]->occupied && !points[p.second]->occupied;
}

void print(int* arr, int length) {
	printf("[");
	int last = length - 1;
	for (int i = 0; i < length; i++) {
		if (i != last) printf("%d, ", arr[i]);
		else printf("%d]", arr[i]);
	}
}

void print_path(path p) {
	printf("[%d, %d]\n", p.first + 1, p.second + 1);
}

void print_board() {
	printf("\n");
	int c = 0;
	int spaces = 10;
	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < spaces; j++) 
			printf(" ");
		for (int e = 0; e < i; e++) {
			int oc = points[c++]->occupied;
			if (oc) printf("%2d  ", c);
			else printf("%2d  ", 0);
		}
		printf("\n");
		spaces -= 2;
	}
	printf("\n");
}


