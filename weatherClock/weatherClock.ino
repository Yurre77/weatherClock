#include <DHT.h>
#include <U8g2lib.h>

//Define pins
#define DHTPIN = D4;

//Constructors
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
