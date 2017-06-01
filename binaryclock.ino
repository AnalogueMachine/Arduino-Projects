//Binary clock with 3 shift registers

//Define Arduino pins to use for shift registers
#define DATA 6
#define LATCH 8
#define CLOCK 10

//Time variables
int secs = 0;
int mins = 0;
int hours = 12; //12 hour clock has either 1 or 12 showing, never 0

void setup()
{
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  
  attachInterrupt(0, addMin, RISING);
  attachInterrupt(1, addHour, RISING);
}

void incrementTime()
{
  secs++;
  
  if(secs >= 60) //If we've reached a minute
  {
    secs = 0; //Reset seconds
    mins++;   //Add a minute
    
    if(mins >= 60) //If we've reached an hour
    {
      mins = 0; //Reset minutes
      hours++;  //Add an hour
      
      if(hours >= 13) //If we've reached 1am (24-hour style)
      {
        hours = 1; //Reset hours to 1am 12-hour style
      }
    }
  }
}

void addMin()
{
  mins++;
  if(mins >= 60)
  {
    mins = 0;
  }
}

void addHour()
{
  hours++;
  if(hours >= 13)
  {
    hours = 1;
  }
}

void loop()
{ 
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, hours);
  shiftOut(DATA, CLOCK, MSBFIRST, mins);
  shiftOut(DATA, CLOCK, MSBFIRST, secs);
  digitalWrite(LATCH, HIGH);
  
  delay(1000);
  
  incrementTime();
}
