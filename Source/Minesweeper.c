#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct point {
	int x;
	int y;
} point;

typedef struct point_group {
	point* points;
	int length;
} point_group;

void generate();
point_group* neighbors(int x, int y);
int valid(int x, int y);
void print_board();
int cascade(int x, int y);
void free_all();

int** board;
int bheight;
int bwidth;
int mines;

int nlength;

int main() {
	printf("Welcome to Minesweeper!\n\n");
	printf("Dimensions [x, y]: ");
	scanf("%d %d", &bwidth, &bheight);
	printf("Number of Mines: ");
	scanf("%d", &mines);
	
	generate();
	
	while (1) {
		int cx = 0;
		int cy = 0;
		print_board();
		printf("Cascade Point [x, y] (-1 -1 to quit): ");
		scanf("%d %d", &cx, &cy);
		if (cx == -1 && cy == -1) break;
		int c = cascade(cx, cy);
		if (c == -1) {
			print_board();
			printf("you lose! goodbye!\n");
			break;
		}
	}
	
	free_all();
	
	return 0;
}

// generates the minesweeper board.
void generate() {
	board = (int**) malloc(sizeof(int*) * bheight);
	for (int i = 0; i < bheight; i++)
		board[i] = (int*) malloc(sizeof(int) * bwidth);
		
	// generate mines
	srand(time(NULL));
	while (mines != 0) {
		int x = rand() % bwidth;
		int y = rand() % bheight;
		if (board[y][x] != -11) {
			board[y][x] = -11;
			mines--;
		}
	}
	
	for (int i = 0; i < bheight; i++) {
		for (int j = 0; j < bwidth; j++) {
			if (board[i][j] != -11) {
				point_group* group = neighbors(j, i);
				point* points = group->points;
				
				int c = 0;
				for (int i = 0; i < group->length; i++) {
					if (board[points[i].y][points[i].x] == -11)
						c++;
				}
				board[i][j] = c + 10;
				
				free(group->points);
				free(group);
			}
		}
	}
}

// counts the immediate neighbors from the specific position.
int coor[16] = {0, 1, 0, -1, 1, 1, 1, 0, 1, -1, -1, 1, -1, 0, -1, -1};
point_group* neighbors(int x, int y) {
	point_group* group = (point_group*) malloc(sizeof(point_group));
	point* points = (point*) malloc(sizeof(point) * 8);
	group->points = points;
	
	int nlength = 0;
	for (int i = 0; i < 16; i += 2) {
		int nx = x + coor[i + 1];
		int ny = y + coor[i];
		if (valid(nx, ny)) {
			points[nlength].x = nx;
			points[nlength++].y = ny;
		}
	}
	group->length = nlength;
	return group;
}

int valid(int x, int y) {
	return x > -1 && x < bwidth && y > -1 && y < bheight;
}

void print_board() {
	printf("\n");
	for (int i = 0; i < bheight; i++) {
		for (int j = 0; j < bwidth; j++) {
			if (board[i][j] / 10 == 1 || board[i][j] / 10 == -1)
				printf("*  ");
			else
				printf("%-2d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// cascades and reveals the board from a specific position.
int cascade(int x, int y) {
	if (board[y][x] == 10) {
		board[y][x] = 0;
		point_group* n = neighbors(x, y);
		point* points = n->points;
		for (int i = 0; i < n->length; i++) {
			cascade(points[i].x, points[i].y);
		}
		
		free(points);
		free(n);
	} else if (board[y][x] != 0)
		board[y][x] %= 10;
	
	return board[y][x];
}

// frees memory used for the game.
void free_all() {
	for (int i = 0; i < bheight; i++)
		free(board[i]);
	free(board);
}