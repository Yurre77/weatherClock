#include <DHT.h>
#include <U8g2lib.h>

//Define pins
#define DHTPIN = D4;

//Constructors
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  Serial.println("Setup complete");
}

void loop() {
  drawBorders();

  delay(1000);
  u8g2.clear();
}

void drawBorders() {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  Serial.printf("Width: %i, Height %i\n", screenWidth, screenHeight);

  u8g2.drawRFrame(64, 32, 32, 16, 5);
  Serial.println("drawn borders");
}