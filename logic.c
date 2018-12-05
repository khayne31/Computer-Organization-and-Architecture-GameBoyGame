#include "logic.h"
#include "graphics.h"
#include "gba.h"

void initializeAppState(AppState* appState) {
    appState -> death = 0;
    appState -> gameOver = 0;
    frogger.x = (int)(WIDTH/2);
    frogger.y = HEIGHT - PADDING-CAR_WIDTH;
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    UNUSED(appState);
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that vblank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */
    for(int i = 0; i < capacity; i++){
        for( int j = 0; j < frogger.sizex; j++){
            int newX = frogger.x + j;
            int newY = frogger.y + frogger.sizey;
            if(newX > level1_cars[i] -> x && newX < level1_cars[i] -> x + level1_cars[i] -> sizex && 
                ((newY > level1_cars[i] -> y && newY < level1_cars[i] -> y + level1_cars[i] -> sizey) ||
                 (frogger.y > level1_cars[i] -> y && frogger.y < level1_cars[i] -> y + level1_cars[i] -> sizey))){
                currentAppState -> death = 1;
            }

             if(newX > level3_cars[i] -> x && newX < level3_cars[i] -> x + level3_cars[i] -> sizex && 
                ((newY > level3_cars[i] -> y && newY < level3_cars[i] -> y + level3_cars[i] -> sizey) ||
                 (frogger.y > level3_cars[i] -> y && frogger.y < level3_cars[i] -> y + level3_cars[i] -> sizey))){
                currentAppState -> death = 1;            }

             if(newX > level4_cars[i] -> x && newX < level4_cars[i] -> x + level4_cars[i] -> sizex && 
                ((newY > level4_cars[i] -> y && newY < level4_cars[i] -> y + level4_cars[i] -> sizey) ||
                 (frogger.y > level4_cars[i] -> y && frogger.y < level4_cars[i] -> y + level4_cars[i] -> sizey))){
                currentAppState -> death = 1;
            }
        }
        
    }

     if(((frogger.y > lvl2 && frogger.y < lvl2 + CAR_WIDTH+2) || (frogger.y + frogger.sizey > lvl2 && frogger.y+frogger.sizey < lvl2 + CAR_WIDTH+2)) 
        && !(frogger.x > 40 && frogger.x < 40+3*CAR_WIDTH)){
        currentAppState -> death = 1;
     }  
    AppState nextAppState = *currentAppState;

    UNUSED(keysPressedBefore);
    UNUSED(keysPressedNow);

    return nextAppState;
}
