#include <LiquidCrystal.h>


LiquidCrystal lcd(8,9,10,11,12, 13);



const int  LeftSideAdd = 2;    // the pin that the Up pushbutton A 

const int  LeftSideSub = 3;    // the pin that the Down pushbutton B 

const int  RightSideAdd = 5;    // the pin that the Up pushbutton C

const int  RightSideSub = 6;    // the pin that the Down pushbutton D



int buttonPushCounter = 0;   // counter for the number of button presses
int buttonStateLeftAdd = 0;         // current state of the button
int buttonStateLeftSub = 0;         // current state of the button
int buttonStateRightAdd = 0;         // current state of the button
int buttonStateRightSub = 0;         // current state of the button

int lastButtonStateLeftAdd = 0;     // previous state of the button
int lastButtonStateLeftSub = 0;     // previous state of the button
int lastButtonStateRightAdd = 0;     // previous state of the button
int lastButtonStateRightSub = 0;     // previous state of the button


int ScoreplrA = 0;                  //Score for player A
int ScoreplrB = 0;                  //Score for player B
int SetplrA = 0;                    //Set score for player A
int SetplrB = 0;                    //Set score for player B


void setup() {


  // initialize the button pin as a input:
   
   pinMode(LeftSideAdd, INPUT);
   pinMode(LeftSideSub, INPUT);
   pinMode(RightSideAdd, INPUT);
   pinMode(RightSideSub, INPUT);
   
  // setup LCD
   lcd.begin(16,2);
   
  
  
}


void loop() {

   // Score board set up 
   lcd.setCursor(0, 0);
   // Print game score.
   lcd.print("Score A:  - B: ");
   lcd.setCursor(0,2);
   // Print set score
   lcd.print("Set   A:  - B: ");

   // read the pushbutton up input pin:
   
   buttonStateLeftAdd = digitalRead(LeftSideAdd);

  // compare the buttonState to its previous state

   if (buttonStateLeftAdd != lastButtonStateLeftAdd) {
     
     // if the state has changed, increment the counter
     
     if (buttonStateLeftAdd == HIGH)
     
     {
       
      buttonPushCounter++;
      ScoreplrA++;
      lcd.setCursor(8,0);
           
      lcd.print(ScoreplrA);
     }
     
      delay(50);

   }
   // save the current state as the last state,
  //for next time through the loop
   lastButtonStateLeftAdd = buttonStateLeftAdd;
   
 
  // read the pushbutton up input pin:
   
   buttonStateLeftSub = digitalRead(LeftSideSub);

  // compare the buttonState to its previous state

   if (buttonStateLeftSub != lastButtonStateLeftSub) {
     
     // if the state has changed, increment the counter
     
     if (buttonStateLeftSub == HIGH)
     
     {
       
      buttonPushCounter--;
      ScoreplrA--;
      lcd.setCursor(8,0);
           
      lcd.print(ScoreplrA);
     }
     delay(50);
   }
   // save the current state as the last state,
  //for next time through the loop
   lastButtonStateLeftSub = buttonStateLeftSub;

   
    // read the pushbutton up input pin:
   
   buttonStateRightAdd = digitalRead(RightSideAdd);

  // compare the buttonState to its previous state

   if (buttonStateRightAdd != lastButtonStateRightAdd) {
     
     // if the state has changed, increment the counter
     
     if (buttonStateRightAdd == HIGH)
     
     {
       
      buttonPushCounter++;
      ScoreplrB++;
      lcd.setCursor(15,0);
           
      lcd.print(ScoreplrB);
     }
      delay(50);
   }
   // save the current state as the last state,
  //for next time through the loop
   lastButtonStateRightAdd = buttonStateRightAdd;

  
    // read the pushbutton up input pin:
   
   buttonStateRightSub = digitalRead(RightSideSub);

  // compare the buttonState to its previous state

   if (buttonStateRightSub != lastButtonStateRightSub) {
     
     // if the state has changed, increment the counter
     
     if (buttonStateRightSub == HIGH)
     
     {
       
      buttonPushCounter--;
      ScoreplrB--;
      lcd.setCursor(15,0);
           
      lcd.print(ScoreplrB);
     }
      delay(50);
     

   }
   // save the current state as the last state,
  //for next time through the loop
  
   lastButtonStateRightSub = buttonStateRightSub;
}
