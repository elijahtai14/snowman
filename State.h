class State {
  public:
    String currentPage;
    bool needToInit;
    uint8_t x; uint8_t y;
    unsigned long timeStamp;
    unsigned long timeDuration;
    
    State () {}
};
