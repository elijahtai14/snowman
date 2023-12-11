#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#include "Button.h"
#include "Buzzer.h"
#include "State.h"

LiquidCrystal_I2C* screen = new LiquidCrystal_I2C(0x27, 16, 2);
State* state = new State();

Button upButton(PB1);
Button downButton(PB3);
Buzzer buzzer(PB4);

const uint8_t EMPTY_CHAR = (uint8_t)' ';
const uint8_t BOX_CHAR = B11011011;
const uint8_t A_CHAR = B01000001;
const uint8_t B_CHAR = B01000010;
const uint8_t UP_CHAR = B01011110;
const uint8_t DOWN_CHAR = B01110110;
const uint8_t LEFT_CHAR = B00111100;
const uint8_t RIGHT_CHAR = B00111110;
const uint8_t LINE_CHAR = B10110000;
const uint8_t PLAYER_CHAR = B11111100;

const int LEVEL_ADDR = 0;

const uint8_t INITIAL_PAGE = 0;
const uint8_t CODE_PAGE = 1;
const uint8_t DUCK_PAGE = 2;
const uint8_t TRIVIA_PAGE = 3;


void initEEPROM() {
  EEPROM.update(LEVEL_ADDR, 2);

  if (EEPROM.read(LEVEL_ADDR) == 0xFF) {
    EEPROM.update(LEVEL_ADDR, 0);
  }  
}

// void createChars(){
//       //uint8_t underArrowChar[] = {B10101, B01010, B10101, B01010, B10101, B01010, B10101, B01010}; screen -> createChar(UNDER_ARROW_CHAR, underArrowChar);
// }

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

void initPage(uint8_t page) {
  screen -> clear();

  // Initial Screen Init
  if (page == INITIAL_PAGE) {
    screen -> setCursor(0, 0);
    screen -> print("Merry Christmas,");
    screen -> setCursor(0, 1);
    screen -> print("Alberto!");

    if (EEPROM.read(LEVEL_ADDR) > 0) {
      for (uint8_t col = 15; col >= 12; col--) {
        screen -> setCursor(col, 1);
        if (col + EEPROM.read(LEVEL_ADDR) > 15) {
          screen -> write((uint8_t)'x');
        }
        else {
          screen -> write(BOX_CHAR);
        }
      }
    }
  }

  // Code Screen Init
  else if (page == CODE_PAGE) {
    uint8_t codeScreen[] = {EMPTY_CHAR, LEFT_CHAR, EMPTY_CHAR, UP_CHAR, 
                            EMPTY_CHAR, DOWN_CHAR, EMPTY_CHAR, RIGHT_CHAR, 
                            EMPTY_CHAR, (uint8_t)'A', EMPTY_CHAR, (uint8_t)'B', 
                            EMPTY_CHAR, (uint8_t)'S', EMPTY_CHAR, EMPTY_CHAR,
                            EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR,
                            EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR,
                            EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR,
                            EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR};
    state -> x = 1; // will store the cursor column
    state -> y = 0; // will store the current stage we are on.
    drawScreenCustom(codeScreen);
  }

  // Duck Screen Init
  else if (page == DUCK_PAGE) {
    state -> x = 0; // This is our time also our x value because it is linear with time.
    state -> y = 1; // This is our current position or row for collisions.
    state -> timeStamp = millis(); // when we last updated
    state -> timeDuration = 360; // update freq

    screen -> setCursor(0, state -> y); screen -> write(PLAYER_CHAR); 
    return;
  }

  // Trivia Screen Init
  else if (page == TRIVIA_PAGE) {
    state -> x = 0;
    state -> y = 0;
  } 
}

void navigateTo (uint8_t page) {
  state -> currentPage = page;
  initPage(page);
}

void doPage(uint8_t page) {
  // initial_page 
  if (page == INITIAL_PAGE) {
    if (downButton.isPressed() || upButton.isPressed()) {
      if (EEPROM.read(LEVEL_ADDR) == 0) {
        navigateTo(CODE_PAGE); return;
      }
      else if (EEPROM.read(LEVEL_ADDR) == 1) {
        navigateTo(DUCK_PAGE); return;
      } 
      else if (EEPROM.read(LEVEL_ADDR) == 2) {
        navigateTo(TRIVIA_PAGE); return;
      }
      else if (EEPROM.read(LEVEL_ADDR) == 3) {

      }
      else {
        screen -> print("wtf");
      }
    }
  }

  else if (page == CODE_PAGE) {
    if (upButton.isPressed()) {
      screen -> setCursor(state -> x, 1); screen -> write(EMPTY_CHAR);
      state -> x = (state -> x + 2) % 14;
      screen -> setCursor(state -> x, 1); screen -> write(LINE_CHAR);
    }
    if (downButton.isPressed()) {
      // up_col = 3; down_col = 5; left_col = 1; right_col = 7; b_col = 11; a_col = 9; s_col = 13;
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
      else if (state -> y == 10 && state -> x == 13) {EEPROM.update(LEVEL_ADDR, 1); navigateTo(INITIAL_PAGE); return;}
      else {navigateTo(INITIAL_PAGE); return;}
    }
  }

  // duck page
  else if (page == DUCK_PAGE) {
    // check win
    if (state -> x > 155) {
      EEPROM.update(LEVEL_ADDR, 2);
      navigateTo(INITIAL_PAGE); return;
    }
 
    // redraw
    if (millis() - state -> timeStamp > state -> timeDuration) {
      state -> timeStamp = millis();

      // erase old
      for (unsigned i = 0; i < 16; i++) {
        uint8_t obstX = state -> duckPageObstacles[i] - state -> x; uint8_t obstY = (i + state -> x) % 2;
        if (0 <= obstX && obstX <= 15) {screen -> setCursor(obstX, obstY); screen -> write(EMPTY_CHAR);}
      }

      // draw new
      state -> x++;
      for (unsigned i = 0; i < 16; i++) {
        uint8_t obstX = state -> duckPageObstacles[i] - state -> x; uint8_t obstY = (i + state -> x) % 2;
        if (0 <= obstX && obstX <= 15) {
          // we lose...
          if (obstX == 0 && obstY == state -> y) {
            navigateTo(INITIAL_PAGE); return;
          } 
          // we draw box
          screen -> setCursor(obstX, obstY); screen -> write(BOX_CHAR);
        }
      }
    }

    // move player
    if (upButton.isPressed()) {
      screen -> setCursor(0, state -> y);  screen -> write(EMPTY_CHAR);
      state -> y = 0;
      screen -> setCursor(0, state -> y);  screen -> write(PLAYER_CHAR);
    }
    if (downButton.isPressed()) {
      screen -> setCursor(0, state -> y);  screen -> write(EMPTY_CHAR);
      state -> y = 1;
      screen -> setCursor(0, state -> y);  screen -> write(PLAYER_CHAR); 
    }
  }

  // quiz page
  else if (page == TRIVIA_PAGE) {
    if (state -> y == 0) {
      screen -> clear();
      screen -> setCursor(0, 0); screen -> print("Instructions:");
      screen -> setCursor(0, 1); screen -> print("Choose wisely!");
      delay(5000);

      screen -> clear();
      screen -> setCursor(0, 0); screen -> print("cabbage");
      screen -> setCursor(0, 1); screen -> print("steak");
      state -> y++;
    }
    
    else if (state -> y == 1) {
      if (upButton.isPressed()) {
        screen -> clear();
        screen -> setCursor(0, 0); screen -> print("ooooookkkkayyy");
        screen -> setCursor(0, 1); screen -> print("okay");
        state -> y++;
      } 
      else if (downButton.isPressed()) {
        navigateTo(INITIAL_PAGE); return;
      }
    }
    
    else if (state -> y == 2) {
      if (upButton.isPressed()) {
        screen -> clear();
        screen -> setCursor(0, 0); screen -> print("cupcake");
        screen -> setCursor(0, 1); screen -> print("malasada");
        state -> y++;
      } 
      else if (downButton.isPressed()) {
        navigateTo(INITIAL_PAGE); return;
      }
    }

    
    else if (state -> y == 3) {
      if (downButton.isPressed()) {
        screen -> clear();
        screen -> setCursor(0, 0); screen -> print("charizard");
        screen -> setCursor(0, 1); screen -> print("mudkip");
        state -> y++;
      } 
      else if (upButton.isPressed()) {
        navigateTo(INITIAL_PAGE); return;
      }
    }
    

    else if (state -> y == 4) {
      if (downButton.isPressed()) {
        screen -> clear();
        screen -> setCursor(0, 0); screen -> print("acrostic");
        screen -> setCursor(0, 1); screen -> print("word search");
        state -> y++;
      } 
      else if (upButton.isPressed()) {
        navigateTo(INITIAL_PAGE); return;
      }
    }
  

    else if (state -> y == 5) {
      if (upButton.isPressed()) {
        screen -> clear();
        for (uint8_t i = 0; i < 16; i++) {
          screen -> setCursor(i, 0); screen -> write((uint8_t)(B00100000 + i));
        }
        screen -> setCursor(state -> x, 1); screen -> write(LINE_CHAR);
        state -> y++;
      } 
      else if (downButton.isPressed()) {
        navigateTo(INITIAL_PAGE); return;
      }
    }
  
    else if (state -> y == 6) {
      if (upButton.isPressed()) {
        screen -> setCursor(state -> x, 1); screen -> write(EMPTY_CHAR);
        state -> x = (state -> x + 1) % 16;
        screen -> setCursor(state -> x, 1); screen -> write(LINE_CHAR);
      }
      else if (downButton.isPressed()) {
        if (state -> x == 12) {
          EEPROM.update(LEVEL_ADDR, 3);
          navigateTo(INITIAL_PAGE); return;
        }
        else {
          navigateTo(INITIAL_PAGE); return;
        }
      }
    }
    
  }
}

void setup() {
  screen -> init(); screen -> init();
  screen -> backlight();
  initEEPROM();
  //createChars();
  navigateTo(INITIAL_PAGE); return;
}

void loop() {
  upButton.updateButton();
  downButton.updateButton();
  doPage(state -> currentPage);
  delay(5);
}
