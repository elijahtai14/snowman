#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Button.h"
#include "Buzzer.h"
#include "LCD.h"
#include "State.h"

SnowmanLCD* snowman;
LiquidCrystal_I2C* screen;

Button upButton(PB1);
Button downButton(PB3);
Buzzer buzzer(PB4);

void setup() {
  snowman = new SnowmanLCD();
  screen = new LiquidCrystal_I2C(0x27, 16, 2);
  
  //snowman -> screen = screen;
  //snowman -> 
  screen -> init();
  //snowman -> 
  screen -> backlight();
  //snowman -> 
  screen -> setCursor(3,0);
  //snowman -> 
  screen -> print("Hello, world!");
  //snowman -> 
  screen -> setCursor(2,1);
  //snowman -> 
  screen -> print("Ywrobot Arduino!");
}

void loop() {
  // upButton.updateButton();
  // downButton.updateButton();

  // bool upIsPressed = upButton.isPressed();
  // bool downIsPressed = downButton.isPressed();

  // if (upIsPressed) {
  //   buzzer.playBlockingNote(880, 1000, 500);
  // }

  // if (downIsPressed) {
  //   snowman -> screen.setCursor(2, 3);
  //   snowman -> screen.write(snowman -> DUCK);
  // }

  // snowman -> screen.setCursor(0, 0);
  // snowman -> screen.write(snowman -> DUCK);
  // delay(1000);
}
 