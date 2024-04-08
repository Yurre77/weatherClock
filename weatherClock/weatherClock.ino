#include <DHT.h>
#include <string.h>
#include <U8g2lib.h>

//Define pins
#define DHTPIN D4
//Define constants
#define FONTSIZE 8

//Constructors
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();

  u8g2.setFont(u8g2_font_logisoso16_tf);
  Serial.println("Setup complete");
}

void loop() {
  //variables for sensor data
  float temp = 0.0;
  float hum = 0.0;

  drawBorders();
  readDHT(&hum, &temp);
  drawSensor(temp, hum);

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

void drawSensor(float temp, float hum) {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  String tempStr = string(temp) + " C";
  String humStr = string(hum) + " %";

  u8g2.drawStr(((screenWidth/2)+(FONTSIZE/2)), ((screenHeight/2)-FONTSIZE), tempStr.c_str());
  u8g2.drawStr(((screenWidth/2)+(FONTSIZE/2)), (screenHeight-FONTSIZE), humStr.c_str());
}