#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// char* fgets(char* buf, int to, FILE* fp) - scans input from file
  // includes stdin, stdout, stderr

// char* fscanf(FILE* fp, char* format, char* buf) - scans word from file
  // includes stdin, stdout, stderr

// int fgetc(FILE* fp) - gets character from file

// int fputc(int c, FILE* fp) - writes character to file

// int fputs(char* s, FILE* fp) - writes the contents of a buffer to a file

// fprintf(FILE* fp, char* format, ...) - writes the contents of printf to a file

// fopen(char* filename, char* modes) - opens a file
  // supported modes:
  // r - open file for reading
  // w = open file for writing. creates file if no file exists
  // a = open file for appending - creates file if no file exists
  // r+ = open a file for both reading and writing
  // w+  = open a file for both reading and writing. creates a file if no file exists 
  // a+ = open a file for both reading and appending. creates file if no file exists

// fclose(FILE* fp) - closes a file (frees up memory for file)

// int strcmp(char* str, char* str2) <string.h> - compare two strings for eqaulity
  // return 0 if equal
  // return 1 if first is bigger
  // return -1 if second is bigger

// MULTITHREADING
// pthread

// SYSTEM CALLS 
// open()
// close()
// create()
// read()
// write()
// dup()
// sup2()
// pipe()

//------------- Data Structures -------------//

struct node_int {
  struct node_int* next;
  struct node_int* prev;
  int data;
};

struct node_char {
  struct node_char* next;
  struct node_char* prev;
  char data;
};

struct node_coor {
  struct node_coor* next;
  struct node_coor* prev;
  int data_x;
  int data_y; 
};






//-----------------------------------//

//------------- Utility (Misc) -------------//

struct point {
  int x;
  int y;
};

struct arr_point {
  struct point* arr;
  int arr_l;
};

void dealloc_point_arr(struct arr_point* pair) {
  free(pair->arr);
  free(pair);
}

struct arr_int {
  int* arr;
  int arr_l;
};

struct grid_int {
  int** arr;
  int arr_h;
  int arr_w;
};

struct arr_char {
  char* arr; 
  int arr_l;
};

struct grid_char {
  char** arr;
  int arr_h;
  int arr_w;
};

//-----------------------------------//

//------------- 2D Integer Array -------------//

struct grid_int* int_grid(int height, int width, int all_values_to) {
  struct grid_int* pair = (struct grid_int*) malloc(sizeof(struct grid_int));
  int** arr = (int**) malloc(height * sizeof(int*));
  pair->arr = arr;

  for (int i = 0; i < height; i++) {
    arr[i] = malloc(width * sizeof(int));
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      arr[i][j] = all_values_to;
    }
  }
  pair->arr_h = height;
  pair->arr_w = width;

  return pair;
}

void dealloc_int_grid(struct grid_int* pair) {
  for (int i = 0; i < pair->arr_h; i++) {
    free(pair->arr[i]);
  }
  free(pair->arr);
  free(pair);
}

void write_int_grid (struct grid_int* pair) {
  for (int i = 0; i < pair->arr_h; i++) {
    for (int j = 0; j < pair->arr_w; j++) {
      printf("%3d", pair->arr[i][j]);
    }
    printf("\n");
  }
}

int in_int_grid_range(int x, int y, struct grid_int* pair) {
  if (x > -1 && x < pair->arr_w && y > -1 && y < pair->arr_h) return 1;
  return 0;
}

struct arr_int* int_arr(int length, int all_values_to) {
  struct arr_int* pair = (struct arr_int*) malloc(sizeof(struct arr_int));
  pair->arr = (int*) malloc(length * sizeof(int));
  pair->arr_l = length;

  for (int i = 0; i < length; i++) {
    pair->arr[i] = all_values_to;
  }
  return pair;
}

void dealloc_int_arr(struct arr_int* pair) {
  free(pair->arr);
  free(pair);
}

void write_int_arr(struct arr_int* pair) {
  printf("[");
  for (int i = 0; i < pair->arr_l; i++) {
    if (i != pair->arr_l - 1) {
      printf("%d, ", pair->arr[i]);
    } else {
      printf("%d", pair->arr[i]);
    }
  }
  printf("]");
}

struct arr_point* int_neighbors(int x, int y, struct grid_int* pair) {
  struct point* arr = (struct point*) malloc(8 * sizeof(struct point));

  int size = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) continue;

      if (in_int_grid_range(j + x, i + y, pair) == 1) {
        struct point p; p.x = j + x; p.y = i + y; 
        arr[size++] = p;
      }
    }
  }

  struct arr_point* re_arr = (struct arr_point*) malloc(sizeof(struct arr_point));
  re_arr->arr = arr;
  re_arr->arr_l = size;

  return re_arr;
}



//----------------------------------------------//

//------------- 2D Character Array -------------//

struct grid_char* char_grid(int height, int width, char all_values_to) {
  struct grid_char* pair = (struct grid_char*) malloc(sizeof(struct grid_char));
  char** arr = (char**) malloc(height * sizeof(char*));
  pair->arr = arr;
  for (int i = 0; i < height; i++) {
    arr[i] = malloc(width * sizeof(char));
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      arr[i][j] = all_values_to;
    }
  }

  pair->arr_h = height;
  pair->arr_w = width;

  return pair;
}

void dealloc_char_grid(struct grid_char* pair) {
  for (int i = 0; i < pair->arr_h; i++) {
    free(pair->arr[i]);
  }
  free(pair->arr);
  free(pair);
}

int in_char_grid_range(int x, int y, struct grid_char* pair) {
  if (x > -1 && x < pair->arr_w && y > -1 && y < pair->arr_h) return 1;
  return 0;
}

void write_char_grid (struct grid_char* pair) {
  for (int i = 0; i < pair->arr_h; i++) {
    for (int j = 0; j < pair->arr_w; j++) {
      char c = 
      printf("%3c", pair->arr[i][j]);
    }
    printf("\n");
  }
}

struct arr_char* char_arr(int length, char all_values_to) {
  struct arr_char* pair = (struct arr_char*) malloc(sizeof(struct arr_char));
  pair->arr = (char*) malloc(length * sizeof(char));
  pair->arr_l = length;
  return pair;
}

void dealloc_char_arr(struct arr_char* pair) {
  free(pair->arr);
  free(pair);
}

void write_char_arr(struct arr_char* pair) {
  printf("[");
  for (int i = 0; i < pair->arr_l; i++) {
    if (i != pair->arr_l - 1) {
      printf("%c, ", pair->arr[i]);
    } else {
      printf("%c", pair->arr[i]);
    }
  }
  printf("]");
}

struct arr_point* char_neighbors(int x, int y, struct grid_char* pair) {
  struct point* arr = (struct point*) malloc(8 * sizeof(struct point));

  int size = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) continue;

      if (in_char_grid_range(j + x, i + y, pair) == 1) {
        struct point p; p.x = j + x; p.y = i + y; 
        arr[size++] = p;
      }
    }
  }

  struct arr_point* re_arr = (struct arr_point*) malloc(sizeof(struct arr_point));
  re_arr->arr = arr;
  re_arr->arr_l = size;

  return re_arr;
}

//-------------Utilities 2--------------//

struct grid_args {
  char** argv;
  int* len_arr;
  int words;
};

struct grid_args* args_grid() {
  char buf[100];
  int words = 0;
  int word_length = 0;
  struct grid_args* grid = (struct grid_args*) malloc(sizeof(struct grid_args));

  // go through the array and find the amount of words in the array
  int index = 0;
  while (1) {
    char c = getchar();
    buf[index++] = c;

    if (c == ' ' || c == '\n') {
      
      if (word_length != 0) {
        words++;
        word_length = 0;
      }

      if (c == '\n') break;
      
    } else {
      word_length++;
    }
  }
  
  // allocate
  grid->argv = (char**) malloc((words + 1) * sizeof(char*));
  grid->len_arr = (int*) malloc((words + 1) * sizeof(int));

  // use the appended buffer to process the words and add them to the grid
  char word_buf[30];
  index = 0;
  word_length = 0;
  int word_index = 0;
  while (1) {
    char c = buf[index++];
    if ((c == ' ' || c == '\n') && word_length != 0) {
      char* arr = grid->argv[word_index] = (char*) malloc(word_length + 1);
      for (int i = 0; i < word_length; i++) {
        arr[i] = word_buf[i];
      }
      arr[word_length] = NULL;
      grid->len_arr[word_index++] = word_length;
      word_length = 0;
      if (c == '\n') break;
    } else {
      word_buf[word_length++] = c;
    }

  }
  grid->words = words;
  grid->argv[words + 1] = NULL;
  grid->len_arr[words + 1] = 0;

  return grid;
}

int index_of_args(struct grid_args* argv, char* str) {
  int words = argv->words;
  char** grid = argv->argv;
  for (int i = 0; i < words; i++) {
    if (strcmp(grid[i], str) == 0) return i;
  }
  return -1;
}

void write_args_grid(struct grid_args* grid) {
  int words = grid->words;
  int* len = grid->len_arr;
  char** argv = grid->argv;
  printf("[");
  for (int i = 0; i < words + 1; i++) {
    if (i == words) {
      printf("{%s, l-%d}]\n", argv[i], len[i]);
    } else {
      printf("{%s, l-%d}, ", argv[i], len[i]);
    }
  }
}

struct grid_args* sub_args_grid(struct grid_args* argv, int from, int to) {
  char** grid = argv->argv;
  int* len = argv->len_arr;
  int words = argv->words;
  int re_words = to - from;

  struct grid_args* re = (struct grid_args*) malloc(sizeof(struct grid_args));
  re->argv = (char**) malloc((re_words + 1) * sizeof(char*));
  re->len_arr = (int*) malloc((re_words + 1) * sizeof(int));
  char** re_grid = re->argv;
  int* re_len = re->len_arr;

  re->words = re_words;
  int counter = 0;
  for (int i = from; i < to; i++) {
    re_len[counter] = len[i];
    re_grid[counter] = (char*) malloc(len[i] * sizeof(char));
    strcpy(re_grid[counter++], grid[i]);
  }

  return re;
}

void dealloc_args_grid(struct grid_args* grid) {
  for (int i = 0; i < grid->words; i++) {
    free(grid->argv[i]);
  }
  free(grid->argv);
  free(grid->len_arr);
  free(grid);
}

struct arr_int* args_as_int() {
  struct grid_args* args = args_grid();
  struct arr_int* re = int_arr(args->words, 0);
  for (int i = 0; i < args->words; i++) {
    re->arr[i] = atoi(args->argv[i]);
  }
  dealloc_args_grid(args);
  return re;
}



void command_line() {
  printf("Welcome to BackyBackpackv2's command line!\n\n");
  char cwd[30];
  while (1) {
    getcwd(cwd, 30);
    printf("%s> ", cwd);
    struct grid_args* grid = args_grid();
    char** argv = grid->argv;
    write_args_grid(grid);
    if (strcmp(argv[0], "b") == 0) break;
    if (fork() == 0) {
      execvp(argv[0], argv);
    } else {
      wait(NULL);
      dealloc_args_grid(grid);
    }
    printf("\n");
  }
}

//------------- Minesweeper -------------//

void write_minesweeper_grid(struct grid_int* pair) {
  int** grid = pair->arr;
  for (int i = 0; i < pair->arr_h; i++) {
    for (int j = 0; j < pair->arr_w; j++) {
      if (grid[i][j] > 9 || grid[i][j] < -10)
        printf("%3c", '*');
      else printf("%3d", grid[i][j]);
    }
    printf("\n");
  }
}

int reveal(int x, int y, struct grid_int* pair) {
  int** grid = pair->arr;

  if (grid[y][x] == 10) {
    grid[y][x] %= 10;
    struct arr_point* n = int_neighbors(x, y, pair);
    struct point* arr = n->arr;
    for (int i = 0; i < n->arr_l; i++) {
      struct point p = arr[i];
      reveal(p.x, p.y, pair);
    }
    dealloc_point_arr(n);
  } else if (grid[y][x] != 0) {
    grid[y][x] %= 10;
  }

  return grid[y][x];
}

// starts to play the game of minesweeper
void minesweeper(int height, int width, int mines) {
  struct grid_int* pair = int_grid(height, width, 10);
  int** grid = pair->arr;
  srand(time(NULL));

  // randomly generate mine spaces
  while (mines != 0) {
    int ry = rand() % height;
    int rx = rand() % width;
    if (grid[ry][rx] != -11) {
      grid[ry][rx] = -11;
      mines--;
    }
  }

  //generate field numbers based on the mines around them
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (grid[i][j] == -11) continue;
      struct arr_point* ne = int_neighbors(j, i, pair);
      struct point* arr = ne->arr;

      for (int k = 0; k < ne->arr_l; k++) {
        struct point p = arr[k];
        if (grid[p.y][p.x] == -11) grid[i][j]++;
      }

      dealloc_point_arr(ne);
    }
  }

  int x;
  int y;
  printf("Welcome to the game of minesweeper!\n\n");

  while (1) {
    write_minesweeper_grid(pair);
    printf("\nEnter a move [x, y]: ");
    scanf("%d %d", &x, &y);
    printf("\n");
    int r = reveal(x, y, pair);
    if (r == -1) {
      write_minesweeper_grid(pair);
      printf("\nRevealed a mine at [%d, %d]! See you next time!\n\n", x, y);
      break;
    }
  }

  dealloc_int_grid(pair);
}

// starts to play eric's game, where one player has the power to add to all adjacent spaces,
// and the other has the power to subtract from all adjacent spaces. The player that marks the most
// spots on the grid to be positive or negative is the winner
void eric_game(int height, int width) {
  struct grid_int* pair = int_grid(height, width, 0);
  int** grid = pair->arr;

  printf("Welcome to the Eric's game!\n\n");

  int player = 1;
  while (1) {
    write_int_grid(pair);
    printf("\nMake a move, player %d! [x, y]: ", player);
    int x;
    int y;
    scanf("%d %d", &x, &y);

    struct arr_point* n = int_neighbors(x, y, pair);
    struct point* points = n->arr;
    for (int i = 0; i < n->arr_l; i++) {
      struct point p = points[i];
      grid[p.y][p.x] += player;
    }
    player *= -1;
    dealloc_point_arr(n);

    printf("\n");
  }

  dealloc_int_grid(pair);
}

void tic_tac_toe() {
  struct grid_char* pair = char_grid(3, 3, '-');
  char** grid = pair->arr;

  printf("Welcome to the game of Tic-Tac-Toe!\n\n");
  int player = 1;

  while (1) {
    write_char_grid(pair);
    printf("\nEnter a move player %d [x, y]: ", player);
    int x;
    int y;
    char c = (player == 1) ? 'o' : 'x';
    scanf("%d %d", &x, &y);
    grid[y][x] = c;
    printf("\n");
    // check for win

    player = (player == 1) ? 2 : 1;
  }

  dealloc_char_grid(pair);
}

void mastermind(int code_length, int num_choices) {
  srand(time(0));
  struct arr_int* code = int_arr(code_length, 0);
  for (int i = 0; i < code_length; i++) {
    code->arr[i] = rand() % num_choices;
  }

  printf("The code is as follows: ");
  write_int_arr(code);
  printf("\nWelcome to mastermind!\n\n");

  while (1) {
    printf("Enter guess [l = %d, r = %d - %d]: ", code_length, 0, num_choices);
    struct arr_int* guess = args_as_int();
    struct arr_int* occupied = int_arr(code_length, 0);
    struct arr_char* color_code = char_arr(code_length, 'r');

    // check for green
    for (int i = 0; i < code_length; i++) {
      int guess_num = guess->arr[i];
      int correct_num = code->arr[i];
      if (guess_num == correct_num) {
        color_code->arr[i] = 'g';
        occupied->arr[i] = 1;
      }
    }

    // check for yellow
    for (int i = 0; i < code_length; i++) {
      if (color_code->arr[i] != 'g') {
        int gn = guess->arr[i];
        for (int j = 0; j < code_length; j++) {
          int an = code->arr[j];

          if (occupied->arr[j] == 0 && an == gn) {
            occupied->arr[j] = 1;
            color_code->arr[i] = 'y';
            break;
          }
        }
      }
    }
    
    write_char_arr(color_code);
    printf("\n\n");

    // check for win
    int win = 1;
    for (int i = 0; i < code_length; i++) {
      if (color_code->arr[i] != 'g') {
        win = 0;
      }
    }

    if (win == 1) {
      printf("You cracked the code! Thanks for playing!\n");
    }
    

    dealloc_int_arr(occupied);
    dealloc_char_arr(color_code);
    dealloc_int_arr(guess);

    if (win == 1) {
      break;
    }
  }
  dealloc_int_arr(code);
}

//-----------------------------------//

// no invisible characters
int is_token_character(char c) {
  return c > 32;
}

int sum(int a, int b) {
  return a + b;
}

void do_thing(int (*method)(int, int), int a, int b) {
  int i = method(a, b);
  printf("the sum is %d\n", i);
}

int num_tokens(char* str, char* delim) {
  char c = ' '; // not null
  int index = 0;
  int tokens = 0;
  int token_length = 0;
  while (c != 0) {
    c = str[index++];
    if (c != *delim && c > '\n') {
      // printf("%c", c);
      token_length++;
    } else if (token_length != 0) {
      // printf("\n");
      token_length = 0;
      tokens++;
    }
  }
  return tokens;
}

char** tokenize(char* str, char* delim) {
  int tokens = num_tokens(str, delim);
  char* tok;
  char** tokenized = (char**) malloc((tokens + 1) * sizeof(char*));

  tok = strtok(str, delim);
  for (int i = 0; i < tokens; i++) {
    tokenized[i] = tok;
    tok = strtok(NULL, delim);
  }

  return tokenized;
}

int main(int argc, char** argv) {
  // mastermind(4, 4);

  char str[100] = "grep there append.txt";
  char delim[2] = " "; 
  int tokens = num_tokens(str, delim);
  printf("number of tokens: %d\n", tokens);
  char** tokenized = tokenize(str, delim);
  for (int i = 0; i < tokens + 1; i++) {
    printf("token %d: %s\n", i, tokenized[i]);
  }
  execvp(tokenized[0], tokenized);
  

  // char str[100] = "ls -l";
  // char delim[2] = " ";
  // char* tok;

  // char* stuff[20];

  // tok = strtok(str, delim);
  // int tokens = 0;
  // while (tok != NULL) {
  //   stuff[tokens] = tok;
  //   tok = strtok(NULL, delim);
  //   tokens++;
  // }
  // stuff[tokens] = NULL;

  // for (int i = 0; i < tokens; i++) {
  //   printf("%s ", stuff[i]);
  // }

  // execvp(stuff[0], stuff);
  
  
  // printf("Enter a sentence: ");
  // struct grid_args* grid = args_grid();
  // struct grid_args* half = sub_args_grid(grid, 0, grid->words / 2);
  // write_args_grid(grid);
  // printf("\n");
  // write_args_grid(half);
  // dealloc_args_grid(grid);
  // dealloc_args_grid(half);




  // char mes[] = {"This is from the child.\n"};
  // char buf[50];
  // int pd[2];
  // pipe(pd);

  // if (fork() == 0) {
  //   for (int i = 0; i < 10; i++) {
  //     sleep(1);
  //     if (i == 9) {
  //       write(pd[1], "hi2", 3);
  //     } else {
  //       write(pd[1], "hi", 2);
  //     }
  //   }
  //   exit(0);
  // } 

  // while (1) {
  //   read(pd[0], buf, 50);
  //   printf("%s\n", buf);
  //   if (strcmp(buf, "hi2") == 0) break;
  // }

  // printf("Enter a sentence: ");
  // struct grid_args* grid = args_grid();
  // printf("Full array: "); write_args_grid(grid);

  // struct grid_args* sub_grid = sub_args_grid(grid, 1, 3);
  // printf ("Partial array: "); write_args_grid(sub_grid);

  // dealloc_args_grid(grid);
  // dealloc_args_grid(sub_grid);
  // int file_desc = open("cool.txt", O_WRONLY);

  // if (fork() == 0) {
  //   dup2(file_desc, 1);
  //   printf("this will be printed in cool.txt.\n");
  //   exit(0);
  // } else {
  //   wait(NULL);
  //   printf("this will be printed to stdout.\n");
  // }
  // printf("this line will only be printed once.\n");

  return 0;
}