class Buzzer {
  public:
    uint8_t PIN;

    void playBlockingNote(uint16_t freq, unsigned long duration = 500,  unsigned long pause = 0) {
      tone(PIN, duration);
      delay(pause);
      noTone(PIN);
    }

    Buzzer (uint8_t pinNum) {
      PIN = pinNum;
      pinMode(pinNum, OUTPUT);
    }
};