class State {
  public:
    uint8_t currentPage;
    uint8_t x; uint8_t y; uint8_t h;
    unsigned long timeStamp;
    unsigned long timeDuration;

    // DuckPage
    const uint8_t duckPageObstacles[20] = {16, 31, 45, 58, 70, 
                                    81, 91, 100, 108, 115,
                                    121, 126, 132, 135, 137, 
                                    140, 142, 145, 147, 150};
    
    State () {}
};
