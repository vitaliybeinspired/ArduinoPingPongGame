
/* The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 
*/

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  }
 void loop(){
  int ScoreplrA = 12;
  int ScoreplrB = 10;
  int SetplrA = 2;
  int SetplrB = 5;
  lcd.setCursor(0, 0);
  // Print game score.
  lcd.print("Score A:  - B: ");
  // Set Player A score.
  lcd.setCursor(8, 0);
  // inputs Player A Score to score board.
  lcd.print(ScoreplrA);
  // Sets player B score.
  lcd.setCursor(14,0);
  // inputs Player B Score to score board.
  lcd.print(ScoreplrB);
   lcd.setCursor(0, 2);
  // Print set score
  lcd.print("Set   A:  - B: ");
  // Set Player A set points.
  lcd.setCursor(8, 2);
  // inputs Player A Score to score board.
  lcd.print(SetplrA);
  // Sets player B set points.
  lcd.setCursor(14,2);
  // inputs Player B Score to score board.
  lcd.print(SetplrB);
  }



/*
int ledPin = 5;
int buttonApin = 9;
int buttonBpin = 8;

byte leds = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
}
*/
