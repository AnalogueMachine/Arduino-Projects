/* This is a simple sketch that notifies Twitter if a switch is triggered */

#include <SPI.h>
#include <Twitter.h>
#include <WiFi.h>

char ssid[] = "O2wireless857895"; //Wifi SSID and password
char pass[] = "**********";

Twitter twitter("900669205-rnRU5Fn2RsPpfHynad7h2OATjARAc3GdGrgrorEo"); //Twitter token
char msg[] = "@bunglenutter @GrumbleSG9 You have post!"; //Message to tweet

int wifiStatus = WL_IDLE_STATUS; //

boolean postArrived;

const int boxPin = 2; //Set pin 2 as the input trigger from the letter box
int buttonState = 0;

void setup() {
  
  postArrived = false;
  
  pinMode(boxPin, INPUT); //Set the pin to receive info
  
  while (wifiStatus != WL_CONNECTED) {
    
    wifiStatus = WiFi.begin(ssid, pass);
    
    delay(5000);
    
  }
  
}

void loop() {
  
  if(postArrived == false) {              //If post hasn't arrived
    
    buttonState = digitalRead(boxPin);    //Check input
  
    if (buttonState == LOW) {            //If there is post coming in
      
      twitter.post(msg);                  //Notify Twitter
      
      postArrived = true;                 //Flag that today's post is here
          
    }
  
    else {                                //If there is no post coming in
    
      delay(500); //Wait half a second before checking again
    
    }
    
  }
  
  //Loop will do nothing if postArrived == true.
  
}
