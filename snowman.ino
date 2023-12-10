#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Button.h"
#include "Buzzer.h"
#include "State.h"

LiquidCrystal_I2C* screen = new LiquidCrystal_I2C(0x27, 16, 2);
State* state = new State();

Button upButton(PB1);
Button downButton(PB3);
Buzzer buzzer(PB4);

const uint8_t EMPTY_CHAR = ' ';
const uint8_t BOX_CHAR = B11011011;
const uint8_t A_CHAR = B01000001;
const uint8_t B_CHAR = B01000010;
const uint8_t UP_CHAR = B01011110;
const uint8_t DOWN_CHAR = B01110110;
const uint8_t LEFT_CHAR = B00111100;
const uint8_t RIGHT_CHAR = B00111110;


void createChars(){
      //uint8_t underArrowChar[] = {B10101, B01010, B10101, B01010, B10101, B01010, B10101, B01010}; screen -> createChar(UNDER_ARROW_CHAR, underArrowChar);
}

void drawScreenCustom(uint8_t screenCustom[]) {
  screen -> clear();
  for (uint8_t col = 0; col < 16; col++) {
    for (uint8_t row = 0; row < 2; row++) {
      if (screenCustom[col + row * 16] != EMPTY_CHAR) {
        screen -> setCursor(col, row);
        screen -> write(screenCustom[col + row * 16]);
      }
    }
  }
}

void initPage(String page) {
  screen -> clear();
  // Initial Screen Init
  if (page == String("initial")) {
    screen -> setCursor(0, 0);
    screen -> print("Merry Christmas,");
    screen -> setCursor(0, 1);
    screen -> print("Alberto!");
  }

  // Code Screen Init
  else if (page == String("code")) {
    uint8_t codeScreen[] = {EMPTY_CHAR, LEFT_CHAR, EMPTY_CHAR, UP_CHAR, 
                            EMPTY_CHAR, DOWN_CHAR, EMPTY_CHAR, RIGHT_CHAR, 
                            EMPTY_CHAR, 'A', EMPTY_CHAR, 'B', 
                            EMPTY_CHAR, 'S', EMPTY_CHAR, EMPTY_CHAR,
                            0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
    state -> x = 1; // will store the cursor column
    state -> y = 0; // will store the current stage we are on.
    drawScreenCustom(codeScreen);
  }

  // Home Screen Init
  else if (page == String("home")) {
    uint8_t homeScreen[] = {EMPTY_CHAR, EMPTY_CHAR, LEFT_CHAR, EMPTY_CHAR, 
                                  EMPTY_CHAR, EMPTY_CHAR, UP_CHAR, EMPTY_CHAR, 
                                  EMPTY_CHAR, EMPTY_CHAR, DOWN_CHAR, EMPTY_CHAR, 
                                  EMPTY_CHAR, EMPTY_CHAR, RIGHT_CHAR, EMPTY_CHAR,
                                  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
    drawScreenCustom(homeScreen);
  }

  // Duck Screen Init
  else if (page == String("duck")) {
    screen -> print("duck");
    return;
  }
}

void navigateTo (String page) {
  state -> currentPage = page;
  initPage(page);
}

void doPage(String page) {
  // initial_page 
  if (page == String("initial")) {
    if (downButton.isPressed() || upButton.isPressed()) {
      buzzer.playBlockingNote(880, 500, 500);
      navigateTo(String("code"));
    }
  }

  else if (page == String("code")) {
    if (upButton.isPressed()) {
      screen -> setCursor(state -> x, 1); screen -> write(EMPTY_CHAR);
      state -> x = (state -> x + 2) % 14;
      screen -> setCursor(state -> x, 1); screen -> write(BOX_CHAR);
    }
    if (downButton.isPressed()) {
      const uint8_t up_col = 3; 
      const uint8_t down_col = 5; 
      const uint8_t left_col = 1; 
      const uint8_t right_col = 7;
      const uint8_t b_col = 11; 
      const uint8_t a_col = 9;
      const uint8_t s_col = 13;
      if (state -> y == 0 && state -> x == 3) {state -> y++;}
      else if (state -> y == 1 && state -> x == 3) {state -> y++;}
      else if (state -> y == 2 && state -> x == 5) {state -> y++;}
      else if (state -> y == 3 && state -> x == 5) {state -> y++;}
      else if (state -> y == 4 && state -> x == 1) {state -> y++;}
      else if (state -> y == 5 && state -> x == 7) {state -> y++;}
      else if (state -> y == 6 && state -> x == 1) {state -> y++;}
      else if (state -> y == 7 && state -> x == 7) {state -> y++;}
      else if (state -> y == 8 && state -> x == 11) {state -> y++;}
      else if (state -> y == 9 && state -> x == 9) {state -> y++;}
      else if (state -> y == 10 && state -> x == 13) {navigateTo(String("home"));}
      else {navigateTo(String("initial"));}
    }
  }

  // homepage
  if (page == String("home")) {
    screen -> setCursor(0, 0);
    screen -> print("home");
    // if (upButton.isPressed()) {
    //   screen -> setCursor(state -> x, state -> y);
    //   screen -> print(" ");
    //   state -> x = (state -> x + 2) % 16;
    //   screen -> setCursor(state -> x, state -> y);
    //   screen -> write(9);
    // }

    // if (downButton.isPressed()) {
    //   if (state -> x == 1) {
    //     navigateTo(String("duck"));
    //   }
    // }
    return;
  }

  // duckpage
  if (page == String("duck")) {
    if (downButton.isPressed() || upButton.isPressed()) {
      navigateTo(String("home"));
    }
  }
}


void setup() {
  screen -> init(); screen -> init();
  screen -> backlight();
  createChars();
  navigateTo(String("initial"));
}

void loop() {
  upButton.updateButton();
  downButton.updateButton();
  doPage(state -> currentPage);
}
