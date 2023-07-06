#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CLEAR "cls"

typedef void (*activation)(void);

typedef struct property {
  int price;

  // rent is priceline[houses]
  int hcost;
  int houses;
  int *priceline;
  int mortgage;

  int location;

  int group;

  int is_owned;
  int owner;
} property;

typedef struct railroad {
  int price;
  int mortgage;
  int location;
} railroad;

typedef struct utility {
  int price;
  int mortgage;
  int location;
} utility;

typedef struct player {
  char *name;
  int money;
  int bankrupt;
  int pnum;
  int rnum;
  int unum;
  int location;

  property **properties;
  railroad **railroads;
  utility **utilities;
} player;

typedef struct event {
  char *name;
  char *description;
  activation effect;
} event;

typedef struct space {
  char *name;
  char *des;
  void *obj;
  activation act;
  int owner;
} space;

typedef struct pgroup {
  char* name;
  property **properties;
  int length;
} pgroup;

// initialize and deallocate memory used for storing data for spaces.
// global variables are initialized in the main method, such that it uses
// static allocation instead of dynamic allocation (though either would work)
void init();
void run();
void dealloc();

// when players land on the spaces on the board, these functions will run
void pact(void);  // property
void ccact(void); // community chest
void chact(void); // chance
void fpact(void); // free parking
void rract(void); // railroad
void ltact(void); // luxury tax
void itact(void); // income tax
void goact(void); // go
void jvact(void); // just visiting
void uact(void);  // utility
void gjact(void); // go to jail

void printb(void);

// panels for play
void welcome(void);
void sfs(void);
void ng(void);
void play(void);
void move(void);
void view_spaces(void);
void stats(void);
void mortgage(void);
void trade(void);

void put(int *arrs, int args, ...);

void wwrite(char *fname);
void load(char *fname);
int loads;
void load_player(FILE *fp, int index);

// array of current players and the current player
player *players;
player pcurrent;
int turn;
int nump;

// community chest cards and chance cards
event *ccevents;
event *chevents;

space *spaces;
property* properties;
railroad* railroads;
utility* utilities;

pgroup *pgroups;

int pot;

int main() {

  int snum = 40;
  int unum = 2;
  int rnum = 4;
  int prnum = 22;
  int pnum = 4;

  space s[snum];
  utility u[unum];
  railroad r[rnum];
  property pr[prnum];
  player p[pnum];
  spaces = s;
  utilities = u;
  railroads = r;
  properties = pr;
  players = p;

  property *pp1[prnum];
  property *pp2[prnum];
  property *pp3[prnum];
  property *pp4[prnum];
  p[0].properties = pp1;
  p[1].properties = pp2;
  p[2].properties = pp3;
  p[3].properties = pp4;
  p[0].pnum = 0;
  p[1].pnum = 0;
  p[2].pnum = 0;
  p[3].pnum = 0;

  utility *up1[unum];
  utility *up2[unum];
  utility *up3[unum];
  utility *up4[unum];
  p[0].utilities = up1;
  p[1].utilities = up2;
  p[2].utilities = up3;
  p[3].utilities = up4;
  p[0].unum = 0;
  p[1].unum = 0;
  p[2].unum = 0;
  p[3].unum = 0;

  railroad *rp1[rnum];
  railroad *rp2[rnum];
  railroad *rp3[rnum];
  railroad *rp4[rnum];
  p[0].railroads = rp1;
  p[1].railroads = rp2;
  p[2].railroads = rp3;
  p[3].railroads = rp4;
  p[0].rnum = 0;
  p[1].rnum = 0;
  p[2].rnum = 0;
  p[3].rnum = 0;

  pgroup pg[8];
  pgroups = pg;
  property* g1[2];
  property* g2[3];
  property* g3[3];
  property* g4[3];
  property* g5[3];
  property* g6[3];
  property* g7[3];
  property* g8[2];
  pg[0].properties = g1;
  pg[0].length = 2;
  pg[0].name = "Brown";
  pg[1].properties = g2;
  pg[1].length = 3;
  pg[1].name = "Light Blue";
  pg[2].properties = g3;
  pg[2].length = 3;
  pg[2].name = "Pink";
  pg[3].properties = g4;
  pg[3].length = 3;\
  pg[3].name = "Orange";
  pg[4].properties = g5;
  pg[4].length = 3;
  pg[4].name = "Red";
  pg[5].properties = g6;
  pg[5].length = 3;
  pg[5].name = "Yellow";
  pg[6].properties = g7;
  pg[6].length = 3;
  pg[6].name = "Green";
  pg[7].properties = g8;
  pg[7].length = 2;
  pg[7].name = "Dark Blue";

  pcurrent = players[0];
  turn = 0;
  loads = 0;

  int i;
  for (i = 0; i < prnum; i++) {
    properties[i].is_owned = 0;
    properties[i].owner = -1;
  }

  init();
  run();
  dealloc();
  return 0;
}

void init() {

  property *p;
  railroad *r;
  utility *u;
  event *e;
  int *pline;

  int ll = sizeof(int) * 6;

  int i;
  for (i = 0; i < 40; i++)
    spaces[i].owner = -1;

  spaces[0].name = "Go";
  spaces[0].des = "Pass Go and Collect 200!";
  spaces[0].act = &goact;

  spaces[1].name = "Mediterranean Avenue";
  spaces[1].des = "Brown property #1";
  spaces[1].act = &pact;
  spaces[1].obj = &properties[0];
  p = (property *)spaces[1].obj;
  p->price = 60;
  p->hcost = 50;
  p->houses = 0;
  p->mortgage = 30;
  p->location = 1;
  pline = (int *)malloc(ll);
  put(pline, 6, 2, 10, 30, 90, 160, 250);
  p->priceline = pline;
  pgroups[0].properties[0] = p;
  p->group = 0;

  spaces[2].name = "Community Chest";
  spaces[2].des = "Draw a Community Chest Card!";
  spaces[2].act = &ccact;

  spaces[3].name = "Baltic Avenue";
  spaces[3].des = "Brown Property #2";
  spaces[3].act = &pact;
  spaces[3].obj = &properties[1];
  p = (property *)spaces[3].obj;
  p->price = 60;
  p->hcost = 50;
  p->houses = 0;
  p->mortgage = 30;
  p->location = 3;
  pline = (int *)malloc(ll);
  put(pline, 6, 4, 20, 60, 180, 320, 450);
  p->priceline = pline;
  pgroups[0].properties[1] = p;
  p->group = 0;

  spaces[4].name = "Income Tax";
  spaces[4].des = "Pay 10% or 200!";
  spaces[4].act = &itact;

  spaces[5].name = "Reading Railroad";
  spaces[5].des = "Railroad #1";
  spaces[5].act = &rract;
  spaces[5].obj =  &railroads[0];
  r = (railroad *)spaces[5].obj;
  r->price = 200;
  r->mortgage = 100;
  r->location = 5;

  spaces[6].name = "Oriental Avenue";
  spaces[6].des = "Light Blue Property #1";
  spaces[6].act = &pact;
  spaces[6].obj = &properties[2];
  p = (property *)spaces[6].obj;
  p->price = 100;
  p->hcost = 50;
  p->houses = 0;
  p->mortgage = 50;
  p->location = 6;
  pline = (int *)malloc(ll);
  put(pline, 6, 6, 30, 90, 270, 400, 550);
  p->priceline = pline;
  pgroups[1].properties[0] = p;
  p->group = 1;

  spaces[7].name = "Chance";
  spaces[7].des = "Draw a Chance Card!";
  spaces[7].act = &chact;

  spaces[8].name = "Vermont Avenue";
  spaces[8].des = "Light Blue Property #2";
  spaces[8].act = &pact;
  spaces[8].obj = &properties[3];
  p = (property *)spaces[8].obj;
  p->price = 100;
  p->hcost = 50;
  p->houses = 0;
  p->mortgage = 50;
  p->location = 8;
  pline = (int *)malloc(ll);
  put(pline, 6, 6, 30, 90, 270, 400, 550);
  p->priceline = pline;
  pgroups[1].properties[1] = p;
  p->group = 1;

  spaces[9].name = "Connecticut Avenue";
  spaces[9].des = "Light Blue Property #3";
  spaces[9].act = &pact;
  spaces[9].obj = &properties[4];
  p = (property *)spaces[9].obj;
  p->price = 120;
  p->hcost = 50;
  p->houses = 0;
  p->mortgage = 60;
  p->location = 9;
  pline = (int *)malloc(ll);
  put(pline, 6, 8, 40, 100, 300, 450, 600);
  p->priceline = pline;
  pgroups[1].properties[2] = p;
  p->group = 1;

  spaces[10].name = "Jail / Just Visiting";
  spaces[10].des = "Just Visiting!";
  spaces[10].act = &jvact;

  spaces[11].name = "St. Charles Place";
  spaces[11].des = "Pink Property #1";
  spaces[11].act = &pact;
  spaces[11].obj = &properties[5];
  p = (property *)spaces[11].obj;
  p->price = 140;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 70;
  p->location = 11;
  pline = (int *)malloc(ll);
  put(pline, 6, 10, 50, 150, 450, 625, 750);
  p->priceline = pline;
  pgroups[2].properties[0] = p;
  p->group = 2;

  spaces[12].name = "Electric Company";
  spaces[12].des = "Utility #1";
  spaces[12].act = &uact;
  spaces[12].obj = &utilities[0];
  u = (utility *)spaces[12].obj;
  u->price = 150;
  u->mortgage = 75;
  u->location = 12;

  spaces[13].name = "States Avenue";
  spaces[13].des = "Pink Property #2";
  spaces[13].act = &pact;
  spaces[13].obj = &properties[6];
  p = (property *)spaces[13].obj;
  p->price = 140;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 70;
  p->location = 13;
  pline = (int *)malloc(ll);
  put(pline, 6, 10, 50, 150, 450, 625, 750);
  p->priceline = pline;
  pgroups[2].properties[1] = p;
  p->group = 2;

  spaces[14].name = "Virginia Avenue";
  spaces[14].des = "Pink Property #3";
  spaces[14].act = &pact;
  spaces[14].obj = &properties[7];
  p = (property *)spaces[14].obj;
  p->price = 160;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 80;
  p->location = 14;
  pline = (int *)malloc(ll);
  put(pline, 6, 12, 60, 180, 500, 700, 900);
  p->priceline = pline;
  pgroups[2].properties[2] = p;
  p->group = 2;

  spaces[15].name = "Pennsylvania Railroad";
  spaces[15].des = "Railroad #2";
  spaces[15].act = &rract;
  spaces[15].obj = &railroads[1];
  r = (railroad *)spaces[15].obj;
  r->price = 200;
  r->mortgage = 100;
  r->location = 15;

  spaces[16].name = "St. James Place";
  spaces[16].des = "Orange Property #1";
  spaces[16].act = &pact;
  spaces[16].obj = &properties[8];
  p = (property *)spaces[16].obj;
  p->price = 180;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 90;
  p->location = 16;
  pline = (int *)malloc(ll);
  put(pline, 6, 14, 70, 200, 550, 750, 950);
  p->priceline = pline;
  pgroups[3].properties[0] = p;
  p->group = 3;

  spaces[17].name = "Community Chest";
  spaces[17].des = "Draw a Community Chest Card!";
  spaces[17].act = &ccact;

  spaces[18].name = "Tennessee Avenue";
  spaces[18].des = "Orange Property #2";
  spaces[18].act = &pact;
  spaces[18].obj = &properties[9];
  p = (property *)spaces[18].obj;
  p->price = 180;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 90;
  p->location = 18;
  pline = (int *)malloc(ll);
  put(pline, 6, 14, 70, 200, 550, 750, 950);
  p->priceline = pline;
  pgroups[3].properties[1] = p;
  p->group = 3;

  spaces[19].name = "New York Avenue";
  spaces[19].des = "Orange Property #3";
  spaces[19].act = &pact;
  spaces[19].obj = &properties[10];
  p = (property *)spaces[19].obj;
  p->price = 200;
  p->hcost = 100;
  p->houses = 0;
  p->mortgage = 100;
  p->location = 19;
  pline = (int *)malloc(ll);
  put(pline, 6, 16, 8, 220, 600, 800, 1000);
  p->priceline = pline;
  pgroups[3].properties[2] = p;
  p->group = 3;

  spaces[20].name = "Free Parking";
  spaces[20].des = "You Won the Pot!";
  spaces[20].act = &fpact;

  spaces[21].name = "Kentucky Avenue";
  spaces[21].des = "Red Property #1";
  spaces[21].act = &pact;
  spaces[21].obj = &properties[11];
  p = (property *)spaces[21].obj;
  p->price = 220;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 110;
  p->location = 21;
  pline = (int *)malloc(ll);
  put(pline, 6, 18, 90, 250, 700, 875, 1050);
  p->priceline = pline;
  pgroups[4].properties[0] = p;
  p->group = 4;

  spaces[22].name = "Chance";
  spaces[22].des = "Draw a Chance Card!";
  spaces[22].act = &chact;

  spaces[23].name = "Indiana Avenue";
  spaces[23].des = "Red Property #2";
  spaces[23].act = &pact;
  spaces[23].obj = &properties[12];
  p = (property *)spaces[23].obj;
  p->price = 220;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 110;
  p->location = 23;
  pline = (int *)malloc(ll);
  put(pline, 6, 18, 90, 250, 700, 875, 1050);
  p->priceline = pline;
  pgroups[4].properties[1] = p;
  p->group = 4;

  spaces[24].name = "Illinois Avenue";
  spaces[24].des = "Red Property #3";
  spaces[24].act = &pact;
  spaces[24].obj = &properties[13];
  p = (property *)spaces[24].obj;
  p->price = 240;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 120;
  p->location = 24;
  pline = (int *)malloc(ll);
  put(pline, 6, 20, 100, 300, 750, 925, 1100);
  p->priceline = pline;
  pgroups[4].properties[2] = p;
  p->group = 4;

  spaces[25].name = "B & O Railroad";
  spaces[25].des = "Railroad #3";
  spaces[25].act = &rract;
  spaces[25].obj = &railroads[2];
  r = (railroad *)spaces[25].obj;
  r->price = 200;
  r->mortgage = 100;
  r->location = 25;

  spaces[26].name = "Atlantic Avenue";
  spaces[26].des = "Yellow Property #1";
  spaces[26].act = &pact;
  spaces[26].obj = &properties[14];
  p = (property *)spaces[26].obj;
  p->price = 260;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 130;
  p->location = 26;
  pline = (int *)malloc(ll);
  put(pline, 6, 22, 110, 330, 800, 975, 1150);
  p->priceline = pline;
  pgroups[5].properties[0] = p;
  p->group = 5;

  spaces[27].name = "Ventnor Avenue";
  spaces[27].des = "Yellow Property #2";
  spaces[27].act = &pact;
  spaces[27].obj = &properties[15];
  p = (property *)spaces[27].obj;
  p->price = 260;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 130;
  p->location = 27;
  pline = (int *)malloc(ll);
  put(pline, 6, 22, 110, 330, 800, 975, 1150);
  p->priceline = pline;
  pgroups[5].properties[1] = p;
  p->group = 5;

  spaces[28].name = "Water Works";
  spaces[28].des = "Utility #2";
  spaces[28].act = &uact;
  spaces[28].obj = &utilities[1];
  u = (utility *)spaces[28].obj;
  u->price = 150;
  u->mortgage = 75;
  u->location = 28;

  spaces[29].name = "Marvin Gardens";
  spaces[29].des = "Yellow Property #3";
  spaces[29].act = &pact;
  spaces[29].obj = &properties[16];
  p = (property *)spaces[29].obj;
  p->price = 280;
  p->hcost = 150;
  p->houses = 0;
  p->mortgage = 140;
  p->location = 29;
  pline = (int *)malloc(ll);
  put(pline, 6, 24, 120, 360, 850, 1025, 1200);
  p->priceline = pline;
  pgroups[5].properties[2] = p;
  p->group = 5;

  spaces[30].name = "Go to Jail";
  spaces[30].des = "Go to Jail, Criminal!";
  spaces[30].act = &gjact;

  spaces[31].name = "Pacfic Avenue";
  spaces[31].des = "Green Property #1";
  spaces[31].act = &pact;
  spaces[31].obj = &properties[17];
  p = (property *)spaces[31].obj;
  p->price = 300;
  p->hcost = 200;
  p->houses = 0;
  p->mortgage = 150;
  p->location = 31;
  pline = (int *)malloc(ll);
  put(pline, 6, 26, 130, 390, 900, 1100, 1275);
  p->priceline = pline;
  pgroups[6].properties[0] = p;
  p->group = 6;

  spaces[32].name = "North Carolina Avenue";
  spaces[32].des = "Green Property #2";
  spaces[32].act = &pact;
  spaces[32].obj = &properties[18];
  p = (property *)spaces[32].obj;
  p->price = 300;
  p->hcost = 200;
  p->houses = 0;
  p->mortgage = 150;
  p->location = 32;
  pline = (int *)malloc(ll);
  put(pline, 6, 26, 130, 390, 900, 1100, 1275);
  p->priceline = pline;
  pgroups[6].properties[1] = p;
  p->group = 6;

  spaces[33].name = "Community Chest";
  spaces[33].des = "Draw a Community Chest Card!";
  spaces[33].act = &ccact;

  spaces[34].name = "Pennsylvania Avenue";
  spaces[34].des = "Green Property #3";
  spaces[34].act = &pact;
  spaces[34].obj = &properties[19];
  p = (property *)spaces[34].obj;
  p->price = 320;
  p->hcost = 200;
  p->houses = 0;
  p->mortgage = 160;
  p->location = 34;
  pline = (int *)malloc(ll);
  put(pline, 6, 28, 150, 450, 100, 1200, 1400);
  p->priceline = pline;
  pgroups[6].properties[2] = p;
  p->group = 6;

  spaces[35].name = "Short Line";
  spaces[35].des = "Railroad #4";
  spaces[35].act = &rract;
  spaces[35].obj = &railroads[3];
  r = (railroad *)spaces[35].obj;
  r->price = 200;
  r->mortgage = 100;
  r->location = 35;

  spaces[36].name = "Chance";
  spaces[36].des = "Draw a Chance Card!";
  spaces[36].act = &chact;

  spaces[37].name = "Park Place";
  spaces[37].des = "Blue Property #1";
  spaces[37].act = &pact;
  spaces[37].obj = &properties[20];
  p = (property *)spaces[37].obj;
  p->price = 350;
  p->hcost = 200;
  p->houses = 0;
  p->mortgage = 175;
  p->location = 37;
  pline = (int *)malloc(ll);
  put(pline, 6, 35, 175, 500, 1100, 1300, 1500);
  p->priceline = pline;
  pgroups[7].properties[0] = p;
  p->group = 7;

  spaces[38].name = "Luxury Tax";
  spaces[38].des = "Pay 75!";
  spaces[38].act = &ltact;

  spaces[39].name = "Boardwalk";
  spaces[39].des = "Blue Property #2";
  spaces[39].act = &pact;
  spaces[39].obj = &properties[21];
  p = (property *)spaces[39].obj;
  p->price = 400;
  p->hcost = 200;
  p->houses = 0;
  p->mortgage = 200;
  p->location = 39;
  pline = (int *)malloc(ll);
  put(pline, 6, 50, 200, 600, 1400, 1700, 2000);
  p->priceline = pline;
  pgroups[7].properties[1] = p;
  p->group = 7;
}

void run() { welcome(); }

void dealloc() {
  int i, j;
  for (i = 0; i < 8; i++) {
    pgroup pg = pgroups[i];
    for (j = 0; j < pg.length; j++) {
      free(pg.properties[j]->priceline);
    }
  }
  if (loads != 0) {
    for (i = 0; i < nump; i++)
      free(players[i].name);
  }
}

void pact(void) { printf("you landed on a property: \n"); }

void ccact(void) {}

void chact(void) { printf("you landed on chance!"); }

void fpact(void) { printf("You landed on free parking!"); }

void rract(void) { printf("you landed on a railroad!"); }

void ltact(void) {}

void itact(void) {}

void goact(void) {}

void jvact(void) {}

void uact(void) {}

void gjact(void) {}

// wip
void printb(void) {
  printf("\n\
|---------|-----|-----|-----|-----|-----|-----|-----|-----|---------|\n\
| * * * * | * * |     |     |     |     |     |     |     |         |\n\
| * * * * | * * |     |     |     |     |     |     |     |         |\n\
|---------|-----|-----|-----|-----|-----|-----|-----|-----|---------|\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|     |                                                       |     |\n\
|     |                                                       |     |\n\
|-----|                                                       |-----|\n\
|---------|-----|-----|-----|-----|-----|-----|-----|-----|---------|\n\
|         |     |     |     |     |     |     |     |     |         |\n\
|         |     |     |     |     |     |     |     |     |         |\n\
|---------|-----|-----|-----|-----|-----|-----|-----|-----|---------|\n\n");
}

void welcome(void) {
  system(CLEAR);
  int sel;
  printf("Welcome to Monopoly Console Edition!\n\n");
  printf("New Game (0)\nLoad Game (1)\nExit (2+)\n\n-> ");
  scanf("%d", &sel);
  if (sel == 0)
    ng();
  if (sel == 1)
    sfs();
}

void sfs(void) {
  system(CLEAR);
  printf("Save Files Detected:\n\nBack (0)\n\n");
  int sel;
  DIR *d;
  char* sf[21];
  struct dirent *dir;
  d = opendir(".");
  if (!d)
    return;
  dir = readdir(d);
  int i = 1;
  while (dir) {
    char *dname = dir->d_name;
    char *dnamec = (char*) malloc(50);
    strcpy(dnamec, dname);
    char *fname = strtok(dname, ".");
    char *ftype = strtok(NULL, "\0");
    if (ftype != NULL && strcmp("txt", ftype) == 0) {
      printf("Save file '%s' (%d)\n", dnamec, i);
      sf[i++] = dnamec;
      if (i == 20)
        break;
    }
    dir = readdir(d);
  }
  closedir(d);
  printf("\n-> ");
  scanf("%d", &sel);
  if (sel == 0) {
    welcome();
    return;
  }
  load(sf[sel]);
  int e;
  for (e = 1; e < i; e++)
    free(sf[e]);
  play();
}

void ng(void) {
  int i;
  if (loads != 0) {
    for (i = 0; i < nump; i++)
      free(players[i].name);
  }
  system(CLEAR);
  int sel = 0;
  int money = 0;
  printf("New Game:\n\nBack (0)\nContinue (1)\n\n-> ");
  scanf("%d", &sel);
  if (sel == 0) {
    welcome();
    return;
  }
  printf("\nNumber of Players: ");
  scanf("%d", &sel);
  nump = sel;
  for (i = 0; i < sel; i++) {
    printf("\n");
    scanf("%c", (char *)stdin);
    printf("-Player %d-\n", i);
    printf("Name: ");
    char* namebuf = (char*) malloc(50);
    fgets(namebuf, 50, stdin);
    printf("Starting Money: ");
    scanf("%d", &money);
    players[i].money = money;
    players[i].name = strtok(namebuf, "\n");
    players[i].bankrupt = 0;
    players[i].location = 0;
  }
  char ns[50];
  printf("\nSave to (end in .txt): ");
  scanf("%s", ns);
  wwrite(ns);
  loads++;
  play();
}

void play(void) {
  srand(time(NULL));

  int sel;
  while (1) {
    system(CLEAR);
    printf("- %s (%d)'s' turn -\n\n", pcurrent.name, turn);
    printf("Save and Exit (0)\n\nMove (1)\nStats (2)\nView Spaces (3)\n\n-> ");
    scanf("%d", &sel);

    if (sel == 0) break;
    if (sel == 1) move();
    if (sel == 2) stats();
    if (sel == 3) view_spaces();
  }
}

// you move with this method, don't delete it
void move(void) {
  system(CLEAR);
  printf("- Movement -\n\n");
  int roll = rand() % 12 + 1;
  int nlo = (pcurrent.location + roll) % 40;
  printf("You rolled a %d!\nFrom %d, you went to %d (%s)!\n\n",
    roll, pcurrent.location, nlo, spaces[nlo].name);
  pcurrent.location = nlo;

  int sel;
  printf("Continue (Any)\n\n-> ");
  scanf("%d", &sel);

  turn = (turn + 1) % nump;
  system(CLEAR);
  spaces[nlo].act();
}

void view_spaces(void) {
  system("clear");
  printf("- Spaces -\n\n");

  int li = 0;
  int i, e;
  for (i = 0; i < 40; i++) {
    space s = spaces[i];
    printf("%s (%d)\n", s.name, i);
    printf("Occupants:\n");
    for (e = 0; e < nump; e++) {
      if (players[e].location == i)
        printf("\t%s\n", players[e].name, e);
    }
    printf("\n");
  }

  int sel;
  printf("\nContinue (Any)\n\n-> ");
  scanf("%d", &sel);
}

void stats(void) {
  // can check all player's stats, sell, trade
  system(CLEAR);
  printf("- Statistics -\n\n");
  int i, j;
  for (i = 0; i < nump; i++) {
    player p = players[i];
    printf("Player %d (%s) ->\n\n", i, p.name);
    printf("\tProperties:\n");
    property** props = p.properties;
    for (j = 0; j < p.pnum; j++) {
      property* pr = props[j];
      int lo = pr->location;
      printf("\t\t%s (%d, %s)\n", spaces[lo].name, lo, pgroups[pr->group].name);
    }
    printf("\n\tUtilities:\n");
    utility** utils = p.utilities;
    for (j = 0; j < p.unum; j++) {
      utility* ut = utils[j];
      int lo = ut->location;
      printf("\t\t%s (%d)\n", spaces[lo].name, lo);
    }
    printf("\n\tRailroads:\n");
    railroad** rails = p.railroads;
    for (j = 0; j < p.rnum; j++) {
      railroad* rr = rails[j];
      int lo = rr->location;
      printf("\t\t%s (%d)\n", spaces[lo].name, lo);
    }
    printf("\n\tMoney: %d\n", p.money);
    printf("\n\n");
  }

  int sel;
  printf("Continue (0)\n\n");
  printf("Mortgage (1)\n");
  printf("Trade (2)\n");
  scanf("%d", &sel);

  if (sel == 1) mortgage();
  if (sel == 2) trade();
}

void mortgage(void) {

}

void trade(void) {

}

void put(int *arr, int args, ...) {
  va_list valist;
  va_start(valist, args);

  int i;
  for (i = 0; i < args; i++)
    arr[i] = va_arg(valist, int);

  va_end(valist);
}

void wwrite(char *fname) {
  FILE* fp;
  fp = fopen(fname, "w");
  int i;
  for (i = 0; i < nump; i++) {
    player p = players[i];
    char b[6];
    if (p.bankrupt)
      strcpy(b, "true");
    else
      strcpy(b, "false");
    fprintf(fp,
      "-Player %d:\nName:%s\nMoney:%d\nBankrupt:%s\nLocation:%d\n",
      i, p.name, p.money, b, p.location);

    // properties
    fprintf(fp, "Properties:");
    property** pr = p.properties;
    for (i = 0; i < p.pnum; i++) {
      int lo = pr[i]->location;
      int ho = pr[i]->houses;
      if (i == p.pnum - 1)
        fprintf(fp, "%d(%d)", lo, ho);
        else
        fprintf(fp, "%d(%d) ", lo, ho);
    }
    fprintf(fp, "\n");

    // utilities
    fprintf(fp, "Utilities:");
    utility** u = p.utilities;
    for (i = 0; i < p.unum; i++) {
      int lo = u[i]->location;
      if (i == p.unum - 1)
        fprintf(fp, "%d", lo);
      else
        fprintf(fp, "%d ", lo);
    }
    fprintf(fp, "\n");

    // railroads
    fprintf(fp, "Railroads:");
    railroad** r = p.railroads;
    for (i = 0; i < p.rnum; i++) {
      int lo = r[i]->location;
      if (i == p.rnum - 1)
        fprintf(fp, "%d", lo);
      else
        fprintf(fp, "%d ", lo);
    }
    fprintf(fp, "\n\n");
  }
  fprintf(fp, "^turn:%d", turn);
}

void load(char *fname) {
  int i;
  if (loads != 0) {
    for (i = 0; i < nump; i++)
      free(players[i].name);
  }
  FILE *fp;
  char buff[255];
  fp = fopen(fname, "r");
  int index = 0;
  while (fgets(buff, 255, fp)) {
    if (buff[0] == '-') {
      load_player(fp, index++);
    } else if (buff[0] == '^') {
      char* vname = strtok(buff, ":");
      char* value = strtok(NULL, "\n");
      int v = atoi(value);
      pcurrent = players[v];
      turn = v;
    }
  }
  nump = index;
  fclose(fp);
  loads++;
}

void load_player(FILE *fp, int index) {
  char namebuff[50];
  char moneybuff[50];
  char brbuff[20];
  char lobuff[20];
  char propertybuff[100];
  char utilitybuff[50];
  char railroadbuff[50];
  char *vname;
  char *value;

  char* namep = (char*) malloc(50);

  // name
  fgets(namebuff, 50, fp);
  vname = strtok(namebuff, ":");
  value = strtok(NULL, "\n");
  strcpy(namep, value);
  players[index].name = namep;

  // money
  fgets(moneybuff, 50, fp);
  vname = strtok(moneybuff, ":");
  value = strtok(NULL, "\n");
  players[index].money = atoi(value);

  // bankrupt status
  fgets(brbuff, 20, fp);
  vname = strtok(brbuff, ":");
  value = strtok(NULL, "\n");
  if (strcmp(value, "true") == 0)
    players[index].bankrupt = 1;
  else
    players[index].bankrupt = 0;

  // location status
  fgets(lobuff, 20, fp);
  vname = strtok(lobuff, ":");
  value = strtok(NULL, "\n");
  players[index].location = atoi(value);

  // properties
  int i = 0;
  fgets(propertybuff, 100, fp);
  vname = strtok(propertybuff, ":");
  value = strtok(NULL, "(");
  while (value) {
    int a = atoi(value);
    if (a == 0)
      break;
    int h = atoi(strtok(NULL, ")"));
    space s = spaces[a];
    s.owner = index;
    property *p = (property *)s.obj;
    p->houses = h;
    p->owner = index;
    p->is_owned = 1;
    players[index].properties[i++] = p;
    value = strtok(NULL, "( \n");
  }
  players[index].pnum = i;
  i = 0;

  // utilities
  fgets(utilitybuff, 50, fp);
  vname = strtok(utilitybuff, ":");
  value = strtok(NULL, " ");
  while (value) {
    int a = atoi(value);
    if (a == 0)
      break;
    space s = spaces[a];
    utility *u = (utility *)s.obj;
    players[index].utilities[i++] = u;
    value = strtok(NULL, " \n");
  }
  players[index].unum = i;
  i = 0;

  // railroads
  fgets(railroadbuff, 50, fp);
  vname = strtok(railroadbuff, ":");
  value = strtok(NULL, " ");
  while (value) {
    int a = atoi(value);
    if (a == 0)
      break;
    space s = spaces[a];
    railroad *r = (railroad *)s.obj;
    players[index].railroads[i++] = r;
    value = strtok(NULL, " \n");
  }
  players[index].rnum = i;

  // printf("\n\nPlayer %d\nName -> %s\nMoney -> %d\nBankrupt -> %d\n", index,
  // players[index].name, players[index].money, players[index].bankrupt);
}
