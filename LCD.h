class SnowmanLCD {
  public:
    LiquidCrystal_I2C* screen; 
    const uint8_t EMPTY = 0;

    const uint8_t HEART = 1;
    const uint8_t DUCK = 2;
    const uint8_t MEM = 3;
    const uint8_t TRIV = 4;
    const uint8_t MUSIC = 5;
    const uint8_t MESSAGE = 6;
    const uint8_t SECRET = 7;
    const uint8_t SCORE = 8;

    const uint8_t TREE = 9;
    const uint8_t UNDER_ARROW = 10;
    const uint8_t CHECK = 11;
    const uint8_t CROSS = 12;
    const uint8_t BACK_ARROW = 13;

    uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
    uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
    uint8_t mem[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t triv[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t music[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
    uint8_t message[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t secret[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t score[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
  
    uint8_t tree[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t underArrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
    uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
    uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
    uint8_t backArrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

    SnowmanLCD () {
      screen -> init();
      screen -> backlight();

      screen -> createChar(HEART, heart);
      screen -> createChar(DUCK, duck);
      screen -> createChar(MEM, mem);
      screen -> createChar(TRIV, triv);
      screen -> createChar(MUSIC, music);
      screen -> createChar(MESSAGE, message);
      screen -> createChar(SECRET, secret);
      screen -> createChar(SCORE, score);
      screen -> createChar(TREE, secret);
      screen -> createChar(UNDER_ARROW, underArrow);
      screen -> createChar(CHECK, check);
      screen -> createChar(CROSS, cross);
      screen -> createChar(BACK_ARROW, backArrow);
    }
};