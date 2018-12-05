#include "gba.h"
#include "logic.h"
#include "graphics.h"
// TA-TODO: Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
#include "images/garbage.h"
#include "images/title.h"
#include "images/frogger.h"
#include "images/loading2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AppState enum definition


int main(void) {
    // TA-TODO: Manipulate REG_DISPCNT here to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    //rect a1 = {0, 40, 50, 20, RED};
    // rect a2 = {0, 100, 100, 30, WHITE};
    //rect a3 = {(int)(WIDTH/2), (int)(HEIGHT/2), 20, 10, CYAN};

    while(1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // TA-TODO: Manipulate the state machine below as needed.
        switch(state) {
        case START:
            // Wait for vblank
            waitForVBlank();
            //setPixel(40,30, 0xFFFF);
            //drawImageDMA(10,10, 50, 37, garbage);
            //drawRectDMA(60, 60, 40, 50, GREEN);
            drawFullScreenImageDMA(TitleScreen2);
            currentAppState.death = 0;
            //fillScreenDMA(WHITE);
            init();
            // TA-TODO: Draw the start state here.
           
            //drawRectDMA(1, 70, REG_CAR_LENGTH, CAR_WIDTH, CYAN);
            state = START_NODRAW;
            break;
        case START_NODRAW:
          
            if(KEY_DOWN(BUTTON_A, BUTTONS)){
                state = APP_INIT;
                previousButtons = BUTTON_A; 
                fillScreenDMA(BLACK);
            }
            
            break;
        case APP_INIT:
            // Initialize the app. Switch to the APP state.           
            initializeAppState(&currentAppState);
            //drawRectDMA(40, HEIGHT/2-1, 2*CAR_WIDTH, CAR_WIDTH+2, BLACK);
         
         
            //state = APP;
           
            if(KEY_DOWN(BUTTON_A, BUTTONS)){
                state = APP;
                previousButtons = BUTTON_A; 
                fillScreenDMA(BLACK);
                //drawRectDMA(PADDING, HEIGHT/2-1, WIDTH-2*PADDING, CAR_WIDTH+2, BLUE );
                drawRectDMA(PADDING,lvl2, 40-PADDING, CAR_WIDTH+2, BLUE);
                drawRectDMA(PADDING+40 + 3*CAR_WIDTH, lvl2, WIDTH - (2*PADDING)-(40+2*CAR_WIDTH), CAR_WIDTH+2, BLUE);
            }
            
            break;
        case APP:
            // Process the app for one frame, store the next statef
            nextAppState = processAppState(&currentAppState, previousButtons, currentButtons); 
   // Draw the initial state of the app
            fullDrawAppState(&state);
            undrawAppState(&currentAppState);            
            if(KEY_DOWN(BUTTON_UP, BUTTONS)){
                frogger_move (BUTTON_UP);
                previousButtons = BUTTON_UP;
            } if(KEY_DOWN(BUTTON_RIGHT, BUTTONS)){
                frogger_move(BUTTON_RIGHT);
                previousButtons = BUTTON_RIGHT;
            } if(KEY_DOWN(BUTTON_DOWN, BUTTONS)){
                frogger_move(BUTTON_DOWN);
                previousButtons = BUTTON_DOWN;
            } if(KEY_DOWN(BUTTON_LEFT, BUTTONS)){
                frogger_move(BUTTON_LEFT);
                previousButtons = BUTTON_LEFT;
            }


            //drawRectDMA(frogger.x, frogger.y, frogger.sizex, frogger.sizey, frogger.color);
            if(currentAppState.death == 1){
                state = APP_EXIT;
            }
            waitForVBlank();
            if(frogger.y <= -CAR_WIDTH){
                previousButtons = BUTTON_B;
                //currentAppState = APP;
                state = APP_EXIT;
            }
            
            // Wait for vblank before we do any drawing.
            waitForVBlank();

            // Undraw the previous state
            //undrawAppState(&currentAppState);

            // Draw the current state
           

            // Now set the current state as the next state for the next iter.
            currentAppState = nextAppState;

            // Check if the app is exiting. If it is, then go to the exit state.
            if (nextAppState.gameOver) state = APP_EXIT;

            break;
        case APP_EXIT:
            // Wait for vblank  
            if(vBlankCounter % 120 != 0){
                drawFullScreenImageDMA(loading);
            }
            else{
                fillScreenDMA(BLACK);
                if(currentAppState.death != 0)
                    drawCenteredString(WIDTH/2 - 25, HEIGHT/2-25, 50, 50, "GAME OVER", GREEN);
                else
                    drawCenteredString(WIDTH/2 - 25, HEIGHT/2-25, 50, 50, "GLORY TO ARSTORZKA", GREEN);
                state = APP_EXIT_NODRAW;
            }
            //fillScreenDMA(RED); 
            
            waitForVBlank();

            // TA-TODO: Draw the exit / gameover screen
          
            
            break;
        case APP_EXIT_NODRAW:
            // TA-TODO: Check for a button press here to go back to the start screen
            if(KEY_DOWN(BUTTON_B, BUTTONS)){
                state = START;
            }
            break;
        }
        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)){
            state = START;
        }
        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
