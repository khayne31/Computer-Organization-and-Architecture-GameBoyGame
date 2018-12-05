#ifndef GRAPHICS_SEEN
#define GRAPHICS_SEEN

#include "logic.h"
#define INCREMENT 1


// This function will be used to draw everything about the state of your app
// including the background and whatnot.

#define CAR_WIDTH 10
#define SMALL_CAR_LENGTH 20
#define SEMI_LENGTH 50
#define REG_CAR_LENGTH 30		
#define SMALL_CAR_SPEED 3
#define SEMI_SPEED 1
#define REG_SPEED 2
#define PADDING 10

enum roadLevels{
	lvl1 = HEIGHT - 4*CAR_WIDTH,
	lvl2 = lvl1 - 3*CAR_WIDTH,
	lvl3 = lvl2 - 3*CAR_WIDTH,
	lvl4 = lvl3 - 3*CAR_WIDTH,
	lvl5 = lvl4 - 2*CAR_WIDTH
};
void fullDrawAppState(GBAState *state);

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state);

//void add(rect* addrect);

void init(void);
void frogger_move(int move);
// If you have anything else you need accessible from outside the graphics.c
// file, you can add them here. You likely won't.
extern rect *level4_cars[15];
extern int capacity;
extern rect *level2_cars[15];
extern rect *level3_cars[15];
extern rect *level1_cars[15];
extern rect *level5_cars[15];
extern rect frogger;
#endif
