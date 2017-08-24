/*
This example shows how to retrieve a button status on PS2 Controller.

Function:
  readButton(button); // Read button status, it will return corresponding data
                      // Digital button: 0 = pressed, 1 = released
                      // Analog button: return a value

  Digital button:
    PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UP
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE

  Analog button:
    PS2_JOYSTICK_LEFT_X_AXIS
    PS2_JOYSTICK_LEFT_Y_AXIS
    PS2_JOYSTICK_RIGHT_X_AXIS
    PS2_JOYSTICK_RIGHT_Y_AXIS
    PS2_JOYSTICK_LEFT_UP
    PS2_JOYSTICK_LEFT_DOWN
    PS2_JOYSTICK_LEFT_LEFT
    PS2_JOYSTICK_LEFT_RIGHT
    PS2_JOYSTICK_RIGHT_UP
    PS2_JOYSTICK_RIGHT_DOWN
    PS2_JOYSTICK_RIGHT_LEFT
    PS2_JOYSTICK_RIGHT_RIGHT

Product page:
  Cytron PS2 Shield: http://www.cytron.com.my/p-shield-ps2
  PS2 Controller: http://www.cytron.com.my/p-ps-gp-1
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

//#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include <LiquidCrystal.h>
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int maxIm=0;
int minIm=2220;



//Cytron_PS2Shield ps2(8, 9); // SoftwareSerial: Rx and Tx pin
Cytron_PS2Shield ps2; // HardwareSerial

#define LEDPIN  13

void setup()
{
  Serial.begin(9600);
  //pinMode(9, OUTPUT); 
  pinMode(11, OUTPUT);
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

    lcd.begin(16, 2);
    lcd.print("DD");
   lcd.setCursor(0, 1);
   lcd.print("Waiting...!");


}

void LCDPrint1(){
//lcd.clear();
int val = analogRead(A5);
if(val>20){
  if(val>maxIm)
  maxIm=val;

  if(val<minIm)
  minIm=val;

 lcd.print(val);
 lcd.print(" ");
 return;

 }lcd.clear();
  lcd.print(maxIm);
  lcd.print(" ");
  lcd.print(minIm);
  
 
 delay(2000);
   
   maxIm=0;
   minIm=2000;

  
}

void  LCDPrintComand(){

  int val = analogRead(A5);

  if(val>100)
  lcd.print("SELECT");

  if(val>250)
  lcd.print("TRIANGLE");

  if(val>450)
  lcd.print("CIRCLE");

  if(val>700)
  lcd.print("X");

  if(val>800)
  lcd.print("SQUARE");

delay(50);
  lcd.clear();


  
}

void LCDPrint(){
  
}

void loop()
{

  analogWrite(11, 255);
  //Serial.print("HEY");
  // LED on main board will light up if 'Select' button is pressed
  if(ps2.readButton(PS2_SELECT) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
    analogWrite(11, 50);
  //  Serial.print("HEY");
  LCDPrint();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
        analogWrite(11, 0);
        LCDPrint();

  }

  if(ps2.readButton(PS2_TRIANGLE) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
    analogWrite(11, 100);
    LCDPrint();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
        analogWrite(11, 0);
        LCDPrint();

  }

 if(ps2.readButton(PS2_CIRCLE) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
    analogWrite(11, 150);
    LCDPrint();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
        analogWrite(11, 0);
        LCDPrint();

  }

  if(ps2.readButton(PS2_CROSS) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
    analogWrite(11, 200);
    LCDPrint();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
        analogWrite(11, 0);
        LCDPrint();

  }

  if(ps2.readButton(PS2_SQUARE) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
    analogWrite(11, 255);
    LCDPrint();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
        analogWrite(11, 0);
        LCDPrint();

  }
  LCDPrintComand();
}
