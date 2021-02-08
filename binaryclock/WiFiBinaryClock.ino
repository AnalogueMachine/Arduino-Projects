#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

//Define Arduino pins to use for shift registers
#define DATA 6
#define LATCH 8
#define CLOCK 10

char ssid[] = "*********"; //Wifi SSID and password
char pass[] = "*********";
String readStr;
int secs = 0;
int mins = 0;
int hours = 12;

int wifiStatus = WL_IDLE_STATUS;
WiFiClient client;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  pinMode(DATA, OUTPUT);        //Register pins
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  
  Serial.begin(9600);
  
  while (wifiStatus != WL_CONNECTED) {
    wifiStatus = WiFi.begin(ssid, pass);
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi!");

  timeClient.begin();
}

void loop() {
  timeClient.update();

  readStr = timeClient.getFormattedTime();
  int str_len = readStr.length() + 1;
  char char_array[str_len];
  readStr.toCharArray(char_array, str_len);
  hours = atoi(strtok(char_array, ":"));
  mins = atoi(strtok(NULL, ":"));
  secs = atoi(strtok(NULL, ":"));

  if (hours >= 13) {
    hours -= 12;
  }

  //Write time to LEDs 
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, hours);
  shiftOut(DATA, CLOCK, MSBFIRST, mins);
  shiftOut(DATA, CLOCK, MSBFIRST, secs);
  digitalWrite(LATCH, HIGH);

  delay(1000);
}
