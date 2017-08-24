 //  UGCI 1st version by Aleksandar Miladinovic


#//include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Joystick.h>
#include <Brain.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  12, 2,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  false, false, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

#define PIN_SELECT  13

#define PIN_UP 2
#define PIN_DOWN 11
#define PIN_RIGHT 3
#define PIN_LEFT 13
//#define PIN_START 1
#define PIN_CROSS 2

#define PIN_CIRCLE 6
#define PIN_SQUARE 5
#define PIN_TRIANGLE 11
#define PIN_L1 3
#define PIN_R1 2

#define CONTROL_PIN 12

const String spin[4] = { "-", "/", "|", "\\" };
int spinCounter=0;
boolean noiseIndicator=false;

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisCommand = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 100;
const long ACC_CORRECTION = 0;
int ledState = LOW; 
boolean accelarationState=false;

boolean upButtonReleased=true;
boolean downButtonReleased=true;
boolean rightButtonReleased=true;
boolean leftButtonReleased=true;
boolean crossButtonReleased=true;
boolean triangleButtonReleased=true;
boolean triangleButtonPressed=true;
//boolean triangleButtonReleased=true;

boolean directMode=true;
boolean directModeToggle=false;



//SoftwareSerial BTSerial(11,1);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte meditation = 0;
int blinker=0;


byte attention = 0;
// system variables
boolean bigPacket = false;



String HC05_Responce = "";

void setup() {
  pinMode(0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(CONTROL_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN,LOW);
  

  pinMode(PIN_UP, INPUT);
  pinMode(PIN_TRIANGLE, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_CROSS, INPUT);
  //pinMode(PIN_START, INPUT);
  
  Serial.begin(57600);
  Serial1.begin(57600);
  //Serial.print("HOLA");
  lcd.begin(16, 2);
 // pinMode(3, OUTPUT);
   lcd.print("No BT signal!");
   lcd.setCursor(0, 1);
   lcd.print("Turn on the EEG!");
Joystick.begin();
/*   
   Joystick.setXAxisRange(0, 255);
Joystick.setZAxisRange(0, 255);
Joystick.setYAxisRange(0, 255);
Joystick.setRzAxisRange(0, 255);*/

  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  
}

void pinVoltage(byte attention){
 // analogWrite(3, attention*2.55);
}

void blinkPin(int pin){
  unsigned long currentMillis = millis();
   if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
 


    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(pin, ledState);
  }

  
}

void accelarationModulation2(long delayTime){

  if((delayTime==-200)){
    

  //Joystick.pressButton(0);
  Joystick.setButton(0,1);
  digitalWrite(CONTROL_PIN,HIGH);
  triangleButtonPressed=true;
  return;

    }

  if((delayTime==-1)){
  Joystick.setButton(0,0);
  digitalWrite(CONTROL_PIN,LOW);
  return;

    }

  Serial.print(attention);Serial.print(" delay:");Serial.println(delayTime);
  Joystick.setButton(0,1);
  digitalWrite(CONTROL_PIN, HIGH);
  delay(delayTime);
  digitalWrite(CONTROL_PIN, LOW);
  Joystick.setButton(0,0);
  /*unsigned long currentMillis = millis();
   if (currentMillis - previousMillis >= delayTime) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
 


    // if the LED is off turn it on and vice-versa:
    if (accelarationState) {
      accelarationState = false;
    } else {
      accelarationState = true;
    }

    // set the LED with the ledState of the variable:
    if(accelarationState){

      digitalWrite(0, HIGH);
      
    } else {

      digitalWrite(0, LOW);
      
    }
    
  }*/

  
}

void accelarationModulation(long delayTime){

  if((delayTime==-200)){
    

  //Joystick.pressButton(0);
  Joystick.setButton(0,1);
  digitalWrite(CONTROL_PIN,HIGH);
  triangleButtonPressed=true;
  return;

    }

  if((delayTime==-1)){
  Joystick.setButton(0,0);
  digitalWrite(CONTROL_PIN,LOW);
  return;

    }


  unsigned long currentMillis = millis();
   if (currentMillis- previousMillisCommand >= delayTime) {
    // save the last time you blinked the LED
    previousMillisCommand = currentMillis;
 


    // if the LED is off turn it on and vice-versa:
    if (accelarationState) {
      accelarationState = false;
    } else {
      accelarationState = true;
    }

    // set the LED with the ledState of the variable:
    if(accelarationState){

      Joystick.setButton(0,1);

      digitalWrite(CONTROL_PIN, HIGH);
      
    } else {

      Joystick.setButton(0,0);

      digitalWrite(CONTROL_PIN, LOW);
      
    }
    
  }

  
}


void ledSignal(byte attention){
/*A1 =19
 * A2=20
 * A3=21
 * A4=22
 * A5=23 ACC_CORRECTION
 */
if(attention<10){
  blinkPin(A5);
  digitalWrite(A4, LOW);
  digitalWrite(A3, LOW);
   digitalWrite(A2, LOW);
   digitalWrite(A1, LOW);
   //ADD NO PRESS
 
} else if((attention>10) && (attention<20)){

digitalWrite(A5,HIGH);
digitalWrite(A4, LOW);
     digitalWrite(A3, LOW);
     digitalWrite(A2, LOW);
     digitalWrite(A1, LOW);

  
} else if((attention>20) && (attention<30)){

  digitalWrite(A5,HIGH);
blinkPin(A4);
     digitalWrite(A3, LOW);
     digitalWrite(A2, LOW);
     digitalWrite(A1, LOW);

  
} else if((attention>30) && (attention<40)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, LOW);
     digitalWrite(A2, LOW);
     digitalWrite(A1, LOW);

  
}else if((attention>40) && (attention<50)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     blinkPin(A3);
     digitalWrite(A2, LOW);
     digitalWrite(A1, LOW);


  
}else if((attention>50) && (attention<60)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, HIGH);
     digitalWrite(A2, LOW);
     digitalWrite(A1, LOW);


  
}else if((attention>60) && (attention<70)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, HIGH);
     blinkPin(A2);
     digitalWrite(A1, LOW);


  
}else if((attention>70) && (attention<80)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, HIGH);
     digitalWrite(A2, HIGH);
     digitalWrite(A1, LOW);


  
}else if((attention>80) && (attention<90)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, HIGH);
     digitalWrite(A2, HIGH);
     blinkPin(A1);


  
}else if((attention>90) && (attention<100)) {
 digitalWrite(A5,HIGH);
digitalWrite(A4, HIGH);
     digitalWrite(A3, HIGH);
     digitalWrite(A2, HIGH);
     digitalWrite(A1, HIGH);


  
}






  
}
void commandSignal2(byte attention){

if(attention<10){

   accelarationModulation(-1);
   return;
}

if((attention>90) && (attention<100)) {
 

   accelarationModulation(-200);
   return;
  
}

accelarationModulation((1500+ACC_CORRECTION)-((1500+ACC_CORRECTION)/100)*attention);


  
}


void commandSignal3(byte attention){

if(attention<20){

   accelarationModulation(-1);
   return;
}

if((attention>90) && (attention<100)) {
 

   accelarationModulation(-200);
   return;
  
}



accelarationModulation(pow((1/1.05),(attention-170)));


  
}



void commandSignal4(byte attention){
/*A1 =19
 * A2=20
 * A3=21
 * A4=22
 * A5=23 ACC_CORRECTION
 */
if(attention<10){

   accelarationModulation(-1);
} else if((attention>10) && (attention<20)){



     accelarationModulation(1500+ACC_CORRECTION);
  
} else if((attention>20) && (attention<30)){

 
     accelarationModulation(1300+ACC_CORRECTION);
  
} else if((attention>30) && (attention<40)) {
 
     accelarationModulation(1100+ACC_CORRECTION);
  
}else if((attention>40) && (attention<50)) {

      accelarationModulation(900+ACC_CORRECTION);

  
}else if((attention>50) && (attention<60)) {
 
     accelarationModulation(700+ACC_CORRECTION);

  
}else if((attention>60) && (attention<70)) {
 

     accelarationModulation(500+ACC_CORRECTION);

  
}else if((attention>70) && (attention<80)) {
 

     accelarationModulation(300+ACC_CORRECTION);

  
}else if((attention>80) && (attention<90)) {
 

     accelarationModulation(200+ACC_CORRECTION);

  
}else if((attention>90) && (attention<100)) {
 

   accelarationModulation(-200);
  
}




  
}

void commandSignal(byte attention){
/*A1 =19
 * A2=20
 * A3=21
 * A4=22
 * A5=23 ACC_CORRECTION
 */
if(attention<10){

   accelarationModulation(-1);
} else if((attention>10) && (attention<20)){



     accelarationModulation(200+ACC_CORRECTION);
  
} else if((attention>20) && (attention<30)){

 
     accelarationModulation(500+ACC_CORRECTION);
  
} else if((attention>30) && (attention<40)) {
 
     accelarationModulation(800+ACC_CORRECTION);
  
}else if((attention>40) && (attention<50)) {

      accelarationModulation(1200+ACC_CORRECTION);

  
}else if((attention>50) && (attention<60)) {
 
     accelarationModulation(1500+ACC_CORRECTION);

  
}else if((attention>60) && (attention<70)) {
 

     accelarationModulation(1800+ACC_CORRECTION);

  
}else if((attention>70) && (attention<80)) {
 

     accelarationModulation(2100+ACC_CORRECTION);

  
}else if((attention>80) && (attention<90)) {
 

     accelarationModulation(2500+ACC_CORRECTION);

  
}else if((attention>90) && (attention<100)) {
 

   accelarationModulation(-200);
  
}
}




/*
void sendCommand(byte attention){

   if(attention>80){  
         Joystick.setButton(0,1);
          }else if(attention>70){
            Joystick.setButton(0,0);
            //delay(300);
            Joystick.setButton(0,1);
          } else if(attention>60){
            Joystick.setButton(0,0);
           // delay(600);
            Joystick.setButton(0,1);
          }else if(attention>50){
            Joystick.setButton(0,0);
           // delay(800);
            Joystick.setButton(0,1);
          }
          else if(attention>40){
            Joystick.setButton(0,0);
           // delay(1000);
            Joystick.setButton(0,1);
          } else Joystick.setButton(0,0);
}
*/
void displayPrint(byte attention, byte signal){

lcd.clear();

if(signal!=200){
      
          lcd.print("EEG Quality: ");
          lcd.print(((signal-200)/(-2)), DEC);
          lcd.print("%");
          if(((signal-200)/(-2))==100)
          lcd.print(" :)");
          lcd.setCursor(0, 1);
          if(attention>2 && attention<=100){
          if(!directMode){
            lcd.print("<--");
            lcd.print(spin[spinCounter++]);
              if (spinCounter>=3) spinCounter=0;
            lcd.print("--> Att: ");
          }
          else {lcd.print("<--*");
          
              lcd.print("--> Att: ");}

           lcd.print(attention, DEC);}
           else {
            lcd.print(spin[spinCounter]);
            lcd.print(" Please wait! ");
              lcd.print(spin[spinCounter++]);
              if (spinCounter>=3) spinCounter=0;
           }
           
           
  }else{

    if(!noiseIndicator){
      
    
   lcd.print("High noise level! :(");
   lcd.setCursor(0, 1);
   lcd.print("Check electrodes!");
   noiseIndicator=true;
  } else {

    if(directMode){

      lcd.print("Direct mode ON");
      lcd.setCursor(0, 1);
      lcd.print("-no modulation-");

      
    }

    noiseIndicator=false;
  }


   
  }
}

///////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte() 

{
  int ByteRead;
  while(!Serial1.available()){}
  ByteRead = Serial1.read();
  //Serial.write(ByteRead);
  return ByteRead;
}
void loop() {
  //Serial.print((char)ReadOneByte());   // echo the same byte out the USB serial (for debug purposes)
// accelarationModulation(1000);
if(analogRead(A0)<850) {
  if(directMode){
    lcd.clear();
    lcd.print("- Direct Mode -");
    lcd.setCursor(0, 1);
    lcd.print("    ACTIVATED");
    directMode=false;
    delay(1000);
    
    
  }else{
    lcd.clear();
    lcd.print("- Direct Mode -");
    lcd.setCursor(0, 1);
    lcd.print("   DEACTIVATED");
    accelarationModulation(-1);
    directMode=true;
    delay(1000);


    
  }
  
  
}

  // checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte battery = 0;
int p=0;

  if(ReadOneByte() == 170) {
  if(ReadOneByte() == 170){
 payloadLength = ReadOneByte();
      
        if(payloadLength > 169)                      //Payload length can not be greater than 169
        return;
        generatedChecksum = 0;  
        
        for(int i = 0; i < payloadLength; i++) 
        {  
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
        } 

        checksum = ReadOneByte();                      //Read checksum byte from stream      
        generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) 
        { 
          poorQuality = 200;
          //attention = 0;
          meditation = 0;
          for(int i = 0; i < payloadLength; i++) 
          {                                          // Parse the payload



            switch (payloadData[i]) {
            case 0x1:
                i++;            
                battery = payloadData[i];
                Serial.print(battery);
                //bigPacket = true;   
                break;
            case 0x2:
                i++;            
                poorQuality = payloadData[i];
                bigPacket = true;   
                break;
            case 0x4:
                attention = payloadData[++i];
                break;
            case 0x5:
                meditation = payloadData[++i];
                break;
            case 0x83:
                // ASIC_EEG_POWER: eight big-endian 3-uint8_t unsigned integer values representing delta, theta, low-alpha high-alpha, low-beta, high-beta, low-gamma, and mid-gamma EEG band power values
                // The next uint8_t sets the length, usually 24 (Eight 24-bit numbers... big endian?)
                // We dont' use this value so let's skip it and just increment i
                i++;

                // Extract the values
                for (int j = 0; j < 8; j++) {
                //  Serial.print("-->");
                   //Serial.println( ((uint32_t)payloadData[++i] << 16) | ((uint32_t)payloadData[++i] << 8) | (uint32_t)payloadData[++i]);
                   ((uint32_t)payloadData[++i] << 16) | ((uint32_t)payloadData[++i] << 8) | (uint32_t)payloadData[++i];
                }

              //  hasPower = true;
                // This seems to happen once during start-up on the force trainer. Strange. Wise to wait a couple of packets before
                // you start reading.
                break;
            case 0x80:
                // We dont' use this value so let's skip it and just increment i
                // uint8_t packetLength = payloadData[++i];
                i++;
              // Serial.print( ((int)payloadData[++i] << 8) | payloadData[++i]);
               ((int)payloadData[++i] << 8) | payloadData[++i];

                break;
            default:
                // Broken packet ?
                /*
                Serial.print(F("parsePacket UNMATCHED data 0x"));
                Serial.print(payloadData[i], HEX);
                Serial.print(F(" in position "));
                Serial.print(i, DEC);
                printPacket();
                */
//                parseSuccess = false;
                break;
        }
 /*         switch (payloadData[i]) 
          {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;   
            break;
          case 4:
            i++;
            attention = payloadData[i];  
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
         //   i++;
          //  Serial.print(((int)payloadData[++i] << 8) | payloadData[++i]); Serial.print("   ");
            break;
          case 0x83:
            i = i + 25; 
           p=i;
                 // ASIC_EEG_POWER: eight big-endian 3-uint8_t unsigned integer values representing 1 delta, 2 theta, 3 low-alpha 4 high-alpha, 5 low-beta, 6 high-beta, 7 low-gamma, and 8 mid-gamma EEG band power values
                // The next uint8_t sets the length, usually 24 (Eight 24-bit numbers... big endian?)
                // We dont' use this value so let's skip it and just increment i
                i++;

                

                // Extract the values
                for (int j = 0; j < 8; j++) {
                    Serial.print("-->");
                    Serial.print(j); 
                    Serial.println( ((uint32_t)payloadData[++i] << 16) | ((uint32_t)payloadData[++i] << 8) | (uint32_t)payloadData[++i]);

                    if(j==9){
                      Serial.println("-------- BREAK ---------");
                    }
                }
                Serial.println(i);
                i=p+25;
                                Serial.println(i);

   
            
            break;
          default:
            break;
          } // switch */

        } // for loop

        if(bigPacket) 
        {

        // Serial.print("PoorQuality: ");
       //   Serial.print(poorQuality, DEC);
       //   Serial.print(" Attention: ");
       //   Serial.print(attention, DEC);
          displayPrint(attention,poorQuality);
         // pinVoltage(attention);
//          sendCommand(attention);
         
        
        /*  Serial.print("Attention");
          Serial.println(attention);
          Serial.print("Meditation");

          Serial.println(meditation);*/
         
      //    Serial.print("\n");
          
        }

        bigPacket = false;
          
        } // add else for eerors

         
    
  }

   
  }
  ledSignal(attention);
   if(!directMode)
          commandSignal(attention);
 
//UP

  if(digitalRead(PIN_UP)) {      //will be TRUE as long as button is pressed
    // Joystick.setYAxis(-1);
     upButtonReleased=false;
    } else {

      if(!upButtonReleased)
       //   Joystick.setYAxis(0);
      
      upButtonReleased=true;
      
    }


//right
    
    if(digitalRead(PIN_RIGHT)){
     Joystick.setXAxis(1);
     rightButtonReleased=false;
    }
    else {

     if(!rightButtonReleased)
       Joystick.setXAxis(0);
       rightButtonReleased=true;
       
    }

//left   
    if(digitalRead(PIN_LEFT)){
           Joystick.setXAxis(-1);
            leftButtonReleased=false;

           

    } else {
      if(!leftButtonReleased)
      Joystick.setXAxis(0);
      leftButtonReleased=true;
    }

//down  
 /*   if(digitalRead(PIN_DOWN)){
      Joystick.setYAxis(1);
      downButtonReleased=false;
    } else {

      if(!downButtonReleased)
        Joystick.setYAxis(0);
        downButtonReleased=true;
    }*/

//cross
    if(digitalRead(PIN_CROSS)){
      Joystick.setButton(2,1);
      crossButtonReleased=false;
    } else {

      if(!crossButtonReleased)
        Joystick.setButton(2,0);
        crossButtonReleased=true;
    }

 //triangle in direct mode
if(directMode){
  

     if(digitalRead(PIN_TRIANGLE)){
      Joystick.setButton(0,1);
      digitalWrite(CONTROL_PIN,HIGH);
      triangleButtonReleased=false;
    } else {

      if(!triangleButtonReleased)
        Joystick.setButton(0,0);
              digitalWrite(CONTROL_PIN,LOW);

        triangleButtonReleased=true;
    }
}

//Serial.print(attention);
}
