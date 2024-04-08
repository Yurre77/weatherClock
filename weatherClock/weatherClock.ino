#include <DHT.h>
#include <U8g2lib.h>

//Define pins
#define DHTPIN = D4;

//Constructors
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  sht.begin();
  u8g2.begin();
  Serial.println("Setup complete");
}

void loop() {
  drawBorders();

  u8g2.sendBuffer();
  delay(10000);
  u8g2.clear();
}

void readDHT(float* humidity, float* temperature) {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    *humidity = h;
    *temperature = t;
  } else {
    *humidity = -1;
    *temperature = -1;
  }
}

void drawBorders() {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  Serial.printf("Width: %i, Height %i\n", screenWidth, screenHeight);

  u8g2.drawRFrame(0, 0, (screenWidth/2), screenHeight, 2);
  u8g2.drawRFrame((screenWidth/2), 0, (screenWidth/2), (screenHeight/2), 2);
  u8g2.drawRFrame((screenWidth/2), (screenHeight/2), (screenWidth/2), (screenHeight/2), 2);
  Serial.println("drawn borders");
}