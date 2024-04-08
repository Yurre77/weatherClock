#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <NTPClient.h>
#include <string.h>
#include <U8g2lib.h>

//Define pins
#define DHTPIN D4
//Define constants
#define FONTSIZE 8
//change to a NTP server in your region
#define NTPSERVER "0.nl.pool.ntp.org"
//change according to your timezone
#define TIMEOFFSET 7200

// static IP definitions
IPAddress staticIP(192, 168, 34, 34);
IPAddress gateway(145, 3, 249, 94);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

// Time constructors
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTPSERVER);

//Constructors
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();
  timeClient.begin();
  timeClient.setTimeOffset(TIMEOFFSET);
  connectWiFi();
  u8g2.setFont(u8g2_font_logisoso16_tf);
  Serial.println("Setup complete");
}

void loop() {
  //variables for sensor data
  float temp = 0.0;
  float hum = 0.0;

  timeClient.update();
  drawBorders();
  readDHT(&hum, &temp);
  drawSensor(temp, hum);
  drawTime();

  u8g2.sendBuffer();
  delay(10000);
  u8g2.clear();
}

//function to get data from a DHT11
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

//function to draw white borders around information
void drawBorders() {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  Serial.printf("Width: %i, Height %i\n", screenWidth, screenHeight);

  u8g2.drawRFrame(0, 0, (screenWidth/2), screenHeight, 2);
  u8g2.drawRFrame((screenWidth/2), 0, (screenWidth/2), (screenHeight/2), 2);
  u8g2.drawRFrame((screenWidth/2), (screenHeight/2), (screenWidth/2), (screenHeight/2), 2);
  Serial.println("drawn borders");
}

//function to draw sensor data on the screen
void drawSensor(float temp, float hum) {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  String tempStr = String(temp) + "C";
  String humStr = String(hum) + "%";

  u8g2.drawStr(((screenWidth/2)+(FONTSIZE/2)), ((screenHeight/2)-FONTSIZE), tempStr.c_str());
  u8g2.drawStr(((screenWidth/2)+(FONTSIZE/2)), (screenHeight-FONTSIZE), humStr.c_str());
}

//function to write time on the screen
void drawTime() {
  int screenWidth = u8g2.getDisplayWidth();
  int screenHeight = u8g2.getDisplayHeight();

  String hours = String(timeClient.getHours());
  if(timeClient.getHours() < 10){ 
    hours = "0" + hours;
  }
  String minutes = String(timeClient.getMinutes());
  if(timeClient.getMinutes() < 10){
    minutes = "0" + minutes;
  }

  String time = hours + ":" + minutes;

  u8g2.drawStr(FONTSIZE,((screenHeight/2)-FONTSIZE), "Time:");
  u8g2.drawStr(FONTSIZE, (screenHeight-FONTSIZE), time.c_str());
}

//function to connect to wifi
void connectWiFi(){
  // configure the WiFi mode (default = STA + AP)
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.hostname("WeatherClock");

  // WiFi manager, local initialisation, it is unneeded after it does it's thing
  WiFiManager wm;

  //uncomment the following line to wipe saved saved credentials
  //wm.resetSettings();

  // automatically connect using saved credentials
  // if the connection fails, start an accesspoint to configure new credentials
  bool res;
  res = wm.autoConnect("weatherClockAP");
  if(!res){
    Serial.println("Failed to connect");
  } else {
    Serial.println("Connected... https://youtu.be/JPgjTU5U52c");
  }
}
