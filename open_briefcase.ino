 /*______________________________
       
        100% Marinaat Warez
   ______________________________

  project: Briefcase opening
  startdate: 08/11/2020 
 
  INFO:
  LCD DISPLAY COMMANDS  (https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/)

  CONNECTIONS:
  _____________________
  NANO:
  GND = GND from display
  5V  = VCC from display
  A4  = SDA from display
  A5  = SDC from display
  D2  = Button1 and 1Kohm to ground. Other side of button to 5V.
  D3  = Button2 and 1Kohm to ground. Other side of button to 5V.
  D4  = Button3 and 1Kohm to ground. Other side of button to 5V.
  D5  = Button4 and 1Kohm to ground. Other side of button to 5V.
  _____________________
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>

/* LCD INIT */
LiquidCrystal_I2C lcd(0x27,16,2);
int usercode = 0000;
int mastercode = 1234;

/* BUTTONS INIT */
const int buttonPin1 = 2;  //button 1
const int buttonPin2 = 3;  //button 2
const int buttonPin3 = 4;  //button 3
const int buttonPin4 = 5;  //button 4
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

/* SERVO INIT */
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
uint8_t servonum1 = 0;
uint8_t servonum2 = 1;
//uint16_t leftservopos = SERVOMIN; 
//uint16_t rightservopos = SERVOMAX; 

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  pwm.setPWM(servonum1, 0, SERVOMIN);
  pwm.setPWM(servonum2, 0, SERVOMAX);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Acces Denied");
  lcd.setCursor(0,1);
  lcd.print("Enter Code: 0000");

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
}

void loop()
{
  while (mastercode != usercode) {
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    
    if (buttonState1 == HIGH) {
      count1++; // add 1 to the count1
      
      if (count1 >= 10) {
        count1 = 0;
      }
      lcd.setCursor(12,1);
      lcd.print(count1);
      delay(300);
      while(buttonState1==LOW);
    }
    
    if (buttonState2 == HIGH) {
      count2++; // add 1 to the count2
      
      if (count2 >= 10) {
        count2 = 0;
      }
      lcd.setCursor(13,1);
      lcd.print(count2);
      delay(300);
      while(buttonState2==LOW);
    }

    if (buttonState3 == HIGH) {
      count3++; // add 1 to the count3
      
      if (count3 >= 10) {
        count3 = 0;
      }
      lcd.setCursor(14,1);
      lcd.print(count3);
      delay(300);
      while(buttonState3==LOW);
    }
    
    if (buttonState4 == HIGH) {
      count4++; // add 1 to the count4
      
      if (count4 >= 10) {
        count4 = 0;
      }
      lcd.setCursor(15,1);
      lcd.print(count4);
      delay(300);
      while(buttonState4==LOW);
    }
    usercode = (count1*1000) + (count2*100) + (count3*10) + (count4);
  }
  lcd.clear();
  
  for (int flash = 0; flash <= 2; flash++) {
    lcd.setCursor(1,0);
    lcd.print("Code Accepted");
    lcd.setCursor(1,1);
    lcd.print("Acces Granted");
    delay(700);
    lcd.noDisplay();
    delay(300);
    lcd.display();
  }
  lcd.setCursor(1,0);
    lcd.print("Code Accepted");
    lcd.setCursor(1,1);
    lcd.print("Acces Granted");
    delay(1500);
    
  /* OPENING BRIEFCASE DISPLAY*/
  for (int flash = 0; flash <= 2; flash++) {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("WARNING !!");
    lcd.setCursor(0,1);
    lcd.print("");
    delay(1200);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("");
    lcd.setCursor(0,1);
    lcd.print("CASE OPENING !!!");
    delay(1200);
  }
    /* OPENING BRIEFCASE SERVOS*/  
  pwm.setPWM(servonum1, 0, SERVOMAX);
  pwm.setPWM(servonum2, 0, SERVOMIN);
     /* 
    rightservopos = SERVOMAX;              
    for (leftservopos = SERVOMIN; leftservopos < SERVOMAX; leftservopos++) {
        pwm.setPWM(servonum1, 0, leftservopos);
        pwm.setPWM(servonum2, 0, rightservopos);
        Serial.println(leftservopos);
        Serial.println(rightservopos);
        rightservopos--;
    }
    */ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BRIEFCASE OPENED");
  lcd.setCursor(4,1);
  lcd.print("HAVE FUN");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CASE IS CLOSING");
  lcd.setCursor(4,1);
  lcd.print("GOOD BYE");

  /* CLOSING BRIEFCASE SERVOS*/
  pwm.setPWM(servonum1, 0, SERVOMIN);
  pwm.setPWM(servonum2, 0, SERVOMAX);
  /* 
  rightservopos = SERVOMIN;
  for (leftservopos = SERVOMAX; leftservopos > SERVOMIN; leftservopos--) {
        pwm.setPWM(servonum1, 0, leftservopos);
        pwm.setPWM(servonum2, 0, rightservopos);
        Serial.println(leftservopos);
        Serial.println(rightservopos);
        rightservopos++;
  }
  */
  // Reset Code
  usercode = 0000;
  count1 = 0; 
  count2 = 0;  
  count3 = 0; 
  count4 = 0;
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Acces Denied");
  lcd.setCursor(0,1);
  lcd.print("Enter Code: 0000"); 
}
