/*
 * Team Members: Noura Jaamour, Samuel Faulkner, Vitaliy Stepanov
 * CS351 Assignment 3
 * 
 * This program keeps track of players score and sets for a Ping Pong Game. The arduino is controlled using high and low states to display LCD information
 * turn lights on and off, and reads button inputs.
 * 
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int ledLeft = 4; // the left player LED
const int ledRight = 7; // the right player LED

const int  LeftSideAdd = 2; // the pin that the Up pushbutton A
const int  LeftSideSub = 3; // the pin that the Down pushbutton B
const int  RightSideAdd = 5; // the pin that the Up pushbutton C
const int  RightSideSub = 6; // the pin that the Down pushbutton D

bool servingTurnLeft = false; // when false indicates it is A's turn to serve, otherwise B  serves
bool positionPlrALeft = true; //true if A is on the  left side
boolean playerAWinner = false; //true when A is the final game winner
boolean playerBWinner = false;  //true when B is the final game winner
boolean winnerLedBlinkOn = true; //used as condition to help the  blink function

// int buttonPushCounter = 0; // counter for the number of button presses

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
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  
  pinMode(LeftSideAdd, INPUT_PULLUP);
  pinMode(LeftSideSub, INPUT_PULLUP);
  pinMode(RightSideAdd, INPUT_PULLUP);
  pinMode(RightSideSub, INPUT_PULLUP);
  lcd.begin(16, 2); // setup LCD

  switchServingTurn(); //  initialize the starting condtion so that one of the players led is on for  serving
}

//function to incrrement the left side score by one when pushing the button
void increaseScoreLeft() { 
  lastButtonStateRightSub = buttonStateRightSub; 
  buttonStateLeftAdd = digitalRead(LeftSideAdd); // read the pushbutton up input pin:
  if (buttonStateLeftAdd != lastButtonStateLeftAdd) {  // compare the buttonState to its previous state
    if (buttonStateLeftAdd == HIGH) {  // if the state has changed, increment the counter
      if (positionPlrALeft) {
        increaseScoreA();  
      } else {
        increaseScoreB();
      }
      checkAndUpdateSetWinner();  //check if there is a winner for this  set
    }
    delay(50);
  }
}
//function to increase the score for player A
void increaseScoreA() {
  ScoreplrA++;
  if ((ScoreplrA + ScoreplrB) % 2 == 0 || ScoreplrA >=10 && ScoreplrB >=10) { // every two turns we switch the serving lights  (if not both players score are 10)
    switchServingTurn(); 
  }
}

//function to decrement the left side score if needed
void decreaseScoreLeft() {
  lastButtonStateLeftAdd = buttonStateLeftAdd;   // save the current state as the last state for next time through the loop
  buttonStateLeftSub = digitalRead(LeftSideSub);  // read the pushbutton up input pin:
  if (buttonStateLeftSub != lastButtonStateLeftSub) {  // compare the buttonState to its previous state
    if (buttonStateLeftSub == HIGH) {  // if the state has changed, increment the counter
      if (positionPlrALeft && ScoreplrA > 0) {  //check if player  A on the left and score >0
        ScoreplrA--;  
      } else if (ScoreplrB > 0 && ScoreplrB > 0 ) { //Player B is on the left and score >0
        ScoreplrB--;
      }
       checkAndUpdateSetWinner(); //check if there is a winner  for  this set
       }
    delay(50);
  }
}

//function to increment player on the right side
void increaseScoreRight() {
  lastButtonStateLeftSub = buttonStateLeftSub;   // save the current state as the last state for next time through the loop
  buttonStateRightAdd = digitalRead(RightSideAdd);    // read the pushbutton up input pin:
  if (buttonStateRightAdd != lastButtonStateRightAdd) {   // compare the buttonState to its previous state
    if (buttonStateRightAdd == HIGH) {     // if the state has changed, increment the counter
      if (positionPlrALeft) { //if player B is on the right
        increaseScoreB();
      } else {
        increaseScoreA();  //player A is on the right
      }
      checkAndUpdateSetWinner(); //check if there is a winner  for  this set
    }
    delay(50);
  }
}
//function to insrease  the  player  B
void increaseScoreB() {
  ScoreplrB++;
  if ((ScoreplrA + ScoreplrB) % 2 == 0 || ScoreplrA >=10 && ScoreplrB >=10) { // every two turns we switch the serving lights
    switchServingTurn();
  }
}
//function  to decrease the score for player  on the right  side
void decreaseScoreRight() {
  lastButtonStateRightAdd = buttonStateRightAdd; // save the current state as the last state for next time through the loop
  buttonStateRightSub = digitalRead(RightSideSub); // read the pushbutton up input pin:
  if(buttonStateRightSub != lastButtonStateRightSub) {  // compare the buttonState to its previous state
    if (buttonStateRightSub == HIGH) { // if the state has changed, increment the counter
      if (!positionPlrALeft && ScoreplrA > 0) {  //if the player A  is on the right side and >0
        ScoreplrA--;
      } else if (ScoreplrB > 0) { //then player B is on  the right, check if >0
        ScoreplrB--;
      }
       checkAndUpdateSetWinner(); //check if there is a winner  for  this set
       }
    delay(50);
  }
  lastButtonStateRightSub = buttonStateRightSub;   // save the current state as the last state for next time through the loop
}

//function to switch who the server side
void switchServingTurn() {
  if (servingTurnLeft) { //left side player turn to serve
    digitalWrite(ledLeft, HIGH); 
    digitalWrite(ledRight, LOW);
    servingTurnLeft = false; 
  } else {      //right  side player turn to serve
    digitalWrite(ledRight, HIGH);
    digitalWrite(ledLeft, LOW);
    servingTurnLeft = true;
  }
}
//function to display results on LCD
void printDisplay() {
  if (positionPlrALeft) { //player A is on the left
    lcd.setCursor(0, 0); // Score board set up
    lcd.print("Score A:"); // Print game score.
    lcd.setCursor(10, 0); 
    lcd.print("- B:"); // Print game score.
    lcd.setCursor(0, 2);
    lcd.print("Set   A:"); // Print set score
    lcd.setCursor(10, 2);
    lcd.print("- B:"); // Print set score
  
    lcd.setCursor(8, 0);
    lcd.print(ScoreplrA);
    lcd.setCursor(14, 0);
    lcd.print(ScoreplrB);
        
    lcd.setCursor(8, 2);
    lcd.print(SetplrA); 
    lcd.setCursor(14, 2);
    lcd.print(SetplrB);
  } else { // player B is on the right
    lcd.setCursor(0, 0); // Score board set up
    lcd.print("Score B:"); // Print game score.
    lcd.setCursor(10, 0); 
    lcd.print("- A:"); // Print game score.
    lcd.setCursor(0, 2);
    lcd.print("Set   B:"); // Print set score
    lcd.setCursor(10, 2);
    lcd.print("- A:"); // Print set score
    lcd.setCursor(8, 0);
    lcd.print(ScoreplrB);
    lcd.setCursor(14, 0);
    lcd.print(ScoreplrA);
    lcd.setCursor(8, 2);
    lcd.print(SetplrB); 
    lcd.setCursor(14, 2);
    lcd.print(SetplrA);
  }
}
//function to compare scores  between players and set a winner if there is one
void checkAndUpdateSetWinner(){                
  if(ScoreplrA >= 11 || ScoreplrB >= 11) {   // one of the player reaches 11 points
    if ((ScoreplrA - ScoreplrB) >= 2) {    // check if diffenece between scores is more than 2 and A is  bigger
      SetplrA++;    //A won  this set
      resetScores();  //call the  reset function to reset the points  for each player to zero AND switch players position on the LCD
      if (servingTurnLeft && positionPlrALeft || !servingTurnLeft && !positionPlrALeft) { //if player A (who just won) is on  the left/or right side and the serving LED is on left/ or right side 
        switchServingTurn();  //switch LED to start serving from the other side
      }
    } else if((ScoreplrB - ScoreplrA) >= 2){ //if player B win the set
      SetplrB++;
      resetScores(); //call the  reset  function to reset  the points  for each player to zero AND switch  players position on LCD
      if (servingTurnLeft && !positionPlrALeft || !servingTurnLeft && positionPlrALeft) { //if player B is on the left/ or right and the server LED is on LEFT/or right 
        switchServingTurn(); //switch LED to start serving from the other side
      }
    }
  }
}
//resert the scores after a player wins one set also switch player positions
void resetScores() {
  delay(1000);
  ScoreplrA = ScoreplrB = 0;  //reset the scores
  lcd.setCursor(8, 0);
  lcd.print("  "); //overwrite the digit on the LCD from the old set scores otherwise it will remain on the LCD
  lcd.setCursor(14, 0);
  lcd.print("  ");
  
  //switch player positions
  if (SetplrA + SetplrB >= 5) { //if total count to sets player is less than 5
    if (SetplrA > SetplrB) {
        playerAWinner = true;
      } else {
        playerBWinner = true;
      }
    return; // exit the execution from the function so that we do not switch positions after the final game is won by one of the players
  }
  if (positionPlrALeft) {
    positionPlrALeft = false; //switch the  player A position from left to right after one set is over
  } else {
    positionPlrALeft = true;
  }
 
}

//function to blink LED for the winner side
void blinkWinner() {
  if (playerAWinner && positionPlrALeft || playerBWinner && !positionPlrALeft) {  //winner is on the LEFT
    if (winnerLedBlinkOn) { // to blink switch HIGHT/LOW
      digitalWrite(ledLeft, HIGH);
      winnerLedBlinkOn = false;
    } else {
      digitalWrite(ledLeft, LOW);
      winnerLedBlinkOn = true;
    }
  } else if (playerAWinner && !positionPlrALeft || playerBWinner && positionPlrALeft) { //winner is on the right
    if (winnerLedBlinkOn) {
      digitalWrite(ledRight, HIGH);
      winnerLedBlinkOn = false;
    } else {
      digitalWrite(ledRight, LOW);
      winnerLedBlinkOn = true;
    }
  }
  delay(100);
}

void loop() { // this is like main that calls functions in a loop 
  printDisplay();
  if (playerAWinner || playerBWinner) { //when there is a winner exite the game
    blinkWinner();
    return;
  }
  increaseScoreLeft();
  decreaseScoreLeft();
  increaseScoreRight();
  decreaseScoreRight();
}
