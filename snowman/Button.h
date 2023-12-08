class Button {
  public:
    uint8_t PIN;
    bool isHigh = false; // Whether the debounced value is high or not
    const unsigned long HIGH_DURATION = 50; // How long the button is high after pressing
    unsigned long lastPressed = millis(); // The last time the button was pressed
    
    const unsigned long READ_INTERVAL = 160;
    unsigned long lastReadHigh = millis(); // When we last queried and recieved a high value

    void updateButton() { // Updates if the button is high or not
      if (digitalRead(PIN) == HIGH) {
        isHigh = true;
        lastPressed = millis();
      }
      else if (millis() - lastPressed > HIGH_DURATION) {
        isHigh = false;
      }
    }

    bool isPressed() { // Gets the current value of the button. Return high once every READ_INTERVAL milliseconds
      if (isHigh && millis() - lastReadHigh > READ_INTERVAL) {
        lastReadHigh = millis();
        return true;
      }
      else {
        return false;
      }
    }

    Button (uint8_t pinNum) {
      PIN = pinNum;
      pinMode(pinNum, INPUT);
    }
};