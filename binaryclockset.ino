//Binary clock with 3 shift registers

//Define Arduino pins to use for shift registers
#define DATA 6
#define LATCH 8
#define CLOCK 10

//Time variables
int secs = 0;
int mins = 0;
int hours = 12; //12 hour clock has either 1 or 12 showing, never 0

//Button variables
int minButton = 2;
int hourButton = 4;
int minButPress, hourButPress = 0;
static unsigned long lastTime = 0;

void setup()
{
  pinMode(DATA, OUTPUT);        //Register pins
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  
  pinMode(minButton, INPUT);    //Button pins
  pinMode(hourButton, INPUT);
}

//Function to check that the time values are within necessary limits
void checkTime()
{ 
  if(secs >= 60) //If we've reached a minute
  {
    secs = 0; //Reset seconds
    mins++;   //Add a minute
    
    if(mins >= 60) //If we've reached an hour
    {
      mins = 0; //Reset minutes
      hours++;  //Add an hour
      
      if(hours >= 13) //If we've reached 1pm
      {
        hours = 1; //Reset hours to 1pm 12-hour style
      }
    }
  }
}

//Function to check for button presses (because I like a tidy loop)
void checkButtons()
{
  minButPress = digitalRead(minButton);
  if(minButPress == HIGH) //Add a minute if button is pressed and constrain accordingly
  {
    mins++;
    if(mins >= 60)
    {
      mins = 0;
    }
    delay(250);
  }
  
  hourButPress = digitalRead(hourButton);
  if(hourButPress == HIGH) //Add an hour if button is pressed and constrain accordingly
  {
    hours++;
    if(hours >= 13)
    {
      hours = 1;
    }
    delay(250);
  }
}

void loop()
{
  //Write time to LEDs 
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, hours);
  shiftOut(DATA, CLOCK, MSBFIRST, mins);
  shiftOut(DATA, CLOCK, MSBFIRST, secs);
  digitalWrite(LATCH, HIGH);
  
  //lastTime stores the milliseconds since the last increment, so if there is a 1000ms difference
  //between it and the elapsed time then we need to add a second
  if(millis() - lastTime >= 1000)
  {
    lastTime = millis();
    secs++;
  }
  
  checkButtons(); //Check for button presses
  
  checkTime(); //Check time variables are within limits
}
