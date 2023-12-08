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

uint8_t empty[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0,    0x0};
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0,   0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc,   0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4,  0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6,   0x0};
uint8_t check[8] = {0x0, 0x1 ,0x3, 0x16, 0x1c, 0x8,  0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b,  0x0};
uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8,0x4};
uint8_t uparrow[8] = {0x00, 0x00, 0x04, 0x0E, 0x1F, 0x00, 0x00, 0x00};

void drawScreenCustom(uint8_t screenCustom[]) {
  screen -> clear();
  for (uint8_t col = 0; col < 16; col++) {
    for (uint8_t row = 0; row < 2; row++) {
      if (screenCustom[col + row * 16] != 0) {
        screen -> setCursor(col, row);
        screen -> write(screenCustom[col + row * 16]);
      }
    }
  }
}

void initPage(String page) {
  screen -> clear();
  if (page == String("home")) {
    
    uint8_t homeScreenCustom[32] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    drawScreenCustom(homeScreenCustom);
    state -> x = 1;
    state -> y = 1;
    screen -> setCursor(1, 1);
    screen -> write(9);
    return;
  }

  if (page == String("duck")) {
    screen -> print("duck");
    return;
  }
}

void navigateTo (String page) {
  state -> currentPage = page;
  initPage(page);
}

void doPage(String page) {
  // homepage
  if (page == String("home")) {
    if (upButton.isPressed()) {
      screen -> setCursor(state -> x, state -> y);
      screen -> print(" ");
      state -> x = (state -> x + 2) % 16;
      screen -> setCursor(state -> x, state -> y);
      screen -> write(9);
    }

    if (downButton.isPressed()) {
      if (state -> x == 1) {
        navigateTo(String("duck"));
      }
    }
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
    
  screen -> createChar(1, note);
  screen -> createChar(2, clock);
  screen -> createChar(3, heart);
  screen -> createChar(4, duck);
  screen -> createChar(5, check);
  screen -> createChar(6, cross);
  screen -> createChar(7, retarrow);
  screen -> createChar(8, bell);
  screen -> createChar(9, uparrow);

  navigateTo(String("home"));
}

void loop() {
  upButton.updateButton();
  downButton.updateButton();
  doPage(state -> currentPage);
}
