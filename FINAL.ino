
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int  LeftSideAdd = 2; // the pin that the Up pushbutton A
const int  LeftSideSub = 3; // the pin that the Down pushbutton B
const int  RightSideAdd = 5; // the pin that the Up pushbutton C
const int  RightSideSub = 6; // the pin that the Down pushbutton D

int buttonPushCounter = 0; // counter for the number of button presses

int buttonStateLeftAdd = 0; // current state of the button
int buttonStateLeftSub = 0; // current state of the button
int buttonStateRightAdd = 0; // current state of the button
int buttonStateRightSub = 0; // current state of the button

int lastButtonStateLeftAdd = 0; // previous state of the button
int lastButtonStateLeftSub = 0; // previous state of the button
int lastButtonStateRightAdd = 0; // previous state of the button
int lastButtonStateRightSub = 0; // previous state of the button

int ScoreplrA = 0; //Score for player A
int ScoreplrB = 0; //Score for player B
int SetplrA = 0; //Set score for player A
int SetplrB = 0; //Set score for player B

void setup() { // initialize the button pin as a input:
  pinMode(LeftSideAdd, INPUT_PULLUP);
  pinMode(LeftSideSub, INPUT_PULLUP);
  pinMode(RightSideAdd, INPUT_PULLUP);
  pinMode(RightSideSub, INPUT_PULLUP);
  lcd.begin(16, 2); // setup LCD
}

void increaseScoreA() {
  buttonStateLeftAdd = digitalRead(LeftSideAdd); // read the pushbutton up input pin:
  if (buttonStateLeftAdd != lastButtonStateLeftAdd) {  // compare the buttonState to its previous state
    if (buttonStateLeftAdd == HIGH) {  // if the state has changed, increment the counter
      buttonPushCounter++;
      ScoreplrA++;
      lcd.setCursor(8, 0);
      lcd.print(ScoreplrA);
    }
    delay(50);
  }
}

void decreaseScoreA() {
  lastButtonStateLeftAdd = buttonStateLeftAdd;   // save the current state as the last state for next time through the loop
  buttonStateLeftSub = digitalRead(LeftSideSub);  // read the pushbutton up input pin:
  if (buttonStateLeftSub != lastButtonStateLeftSub) {  // compare the buttonState to its previous state
    if (buttonStateLeftSub == HIGH) {  // if the state has changed, increment the counter
      buttonPushCounter--;
      ScoreplrA--;
      lcd.setCursor(8, 0);
      lcd.print(ScoreplrA);
    }
    delay(50);
  }
}

void increaseScoreB() {
  lastButtonStateLeftSub = buttonStateLeftSub;   // save the current state as the last state for next time through the loop
  buttonStateRightAdd = digitalRead(RightSideAdd);    // read the pushbutton up input pin:
  if (buttonStateRightAdd != lastButtonStateRightAdd) {   // compare the buttonState to its previous state
    if (buttonStateRightAdd == HIGH) {     // if the state has changed, increment the counter
      buttonPushCounter++;
      ScoreplrB++;
      lcd.setCursor(15, 0);
      lcd.print(ScoreplrB);
    }
    delay(50);
  }
}

void decreaseScoreB() {
  lastButtonStateRightAdd = buttonStateRightAdd; // save the current state as the last state for next time through the loop
  buttonStateRightSub = digitalRead(RightSideSub); // read the pushbutton up input pin:
  if (buttonStateRightSub != lastButtonStateRightSub) {  // compare the buttonState to its previous state
    if (buttonStateRightSub == HIGH) { // if the state has changed, increment the counter
      buttonPushCounter--;
      ScoreplrB--;
      lcd.setCursor(15, 0);
      lcd.print(ScoreplrB);
    }
    delay(50);
  }
  lastButtonStateRightSub = buttonStateRightSub;   // save the current state as the last state for next time through the loop
}

void printDisplay() {
  lcd.setCursor(0, 0); // Score board set up
  lcd.print("Score A:  - B: "); // Print game score.
  lcd.setCursor(0, 2);
  lcd.print("Set   A:  - B: "); // Print set score
}

void loop() { // this is like main that calls functions in a loop
  printDisplay();
  increaseScoreA();
  decreaseScoreA();
  increaseScoreB();
  decreaseScoreB();
}


/*
 * TO DO:
 *    void endGame() { // check if there is a winner
 *      If player A + player B set == 5
          If player A > player B
              flash light player A winner
          else 
              flash light player B winner   
      }
              
 *    void serve() { // 2 serves, then 1 serve at 10 
 *    make score methods less redundant
 *    
 * Questions:
 *    why delay(50)???
 *    necessary to call every function in loop or check "if" need to call it?
 */
