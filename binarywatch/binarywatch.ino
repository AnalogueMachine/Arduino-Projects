//Code to run a binary watched based on an Adafruit Gemma running a NeoPixel 16 LED ring.

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 0);

uint32_t red = pixels.Color(150, 0, 0);
uint32_t green = pixels.Color(0, 150, 0);
uint32_t blue = pixels.Color(0, 0, 150);

byte seconds = 0;
byte minutes = 0;
byte hours = 12;

void setup() {
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {
  //Check time is within parameters and reset if necessary
  if(seconds >= 60)
  {
    seconds = 0;
    minutes++;
    
    if(minutes >= 60)
    {
      minutes = 0;
      hours++;
      
      if(hours >= 13)
      {
        hours = 1; //Hours start at 12, so when we go from 12 to 12 we then go to 1
      }
    }
  }
  
  //This is where the magic happens.
  //The bitRead() function is used here to read each individual bit of the 
  //seconds / minutes / hours byte. If the current bit is a 1, then the 
  //corresponding LED must be lit, otherwise it should be off.
  
  //Seconds - 6 bits required so 6 loops made
  for(int i=0; i < 7; i++) {
    int onoff = bitRead(seconds, i);
    if(onoff == 1)
    {
      pixels.setPixelColor(15-i, green); //"15-i" results in clockwise motion, remove for bitwise
    } 
    else 
    {
      pixels.setPixelColor(15-i, 0);
    }
  }
  
  //Put on minutes lights
  for(int i=0; i < 7; i++) {
    int onoff = bitRead(minutes, i);
    if(onoff == 1) 
    {
      pixels.setPixelColor(15-(i+6), red); //i+6 to skip seconds LEDs
    } 
    else 
    {
      pixels.setPixelColor(15-(i+6), 0);
    }
  }
  
  //Put on hours lights
  for(int i=0; i < 7; i++) {
    int onoff = bitRead(hours, i);
    if(onoff == 1) 
    {
      pixels.setPixelColor(15-(i+12), blue); //i+12 to skip secs/mins LEDs
    } 
    else 
    {
      pixels.setPixelColor(15-(i+12), 0);
    }
  }
  
  pixels.show();
  
  seconds++;

  delay(1000);
}
