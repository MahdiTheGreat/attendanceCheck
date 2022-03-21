

#include <LiquidCrystal.h> //Header file for LCD from https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Keypad.h> //Header file for Keypad from https://github.com/Chris--A/Keypad
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>

struct User{
   int username;
   bool teacher;
   bool attendance;
};
Servo myservo;  // create servo object to control a servo
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
const int userNum=2;
User user1={1,true,false};
User user2={2,false,false};
User users[userNum]={user1,user2};
int Num1,Number;
char key,action;
const byte rs = 35, en = 34, d4 = 33, d5 = 32, d6 = 31, d7 = 30; //Pins to which LCD is connected
const byte ledOutput=45;
const byte buzzerOutput=36;
const byte servoOutput=14;
int startTime=0;
const int buzzerTime=1000;
const int openTime=1000;
const int lcdTime=50;
const int lateTime=0;
byte rowPins[ROWS] = { 22, 23, 24, 25 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 26, 27, 28, 29 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
boolean result = false;
// Define the Keymap
char keys[ROWS][COLS] = {

  {'7','8','9','D'},

  {'4','5','6','C'},

  {'1','2','3','B'},

  {'*','0','#','A'}

};

SoftwareSerial mySerial(18,19);

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  myservo.attach(servoOutput);
  myservo.write(0);
  //myservo.writeMicroseconds(1000);    
  mySerial.begin(9600);
  Serial1.begin(9600);
  Wire.begin();
  mySerial.println("test"); //We are using a 16*2 LCD display
  pinMode(ledOutput,OUTPUT);
  pinMode(buzzerOutput,OUTPUT);
  digitalWrite(ledOutput,LOW);
  lcd.begin(16, 4);
  printOnLcd(1,"attendance check"); //Display a intro message
  mySerial.println("start up");
  delay(10); //Wait for display to show info
  lcd.clear();
  
}
void loop() {
  
key = kpd.getKey(); //storing pressed key value in a char

if (key!=NO_KEY)
DetectButtons();

if (result==true)
CalculateResult();

DisplayResult();   
}

void DetectButtons()
{ 
     lcd.clear(); //Then clean it
    if (key=='*') //If cancel Button is pressed
    {mySerial.println ("Button Cancel"); Number=Num1=0; result=false;}
    
     if (key == '1') //If Button 1 is pressed
    {mySerial.println ("Button 1"); 
    if (Number==0)
    Number=1;
    else{
    long temp=Number;
    Number = (Number*10) + 1; //Pressed twice
    if (String(temp,DEC ).length()>=4){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(1,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '4') //If Button 4 is pressed
    {mySerial.println ("Button 4"); 
    if (Number==0)
    Number=4;
    else{
    long temp=Number;
    Number = (Number*10) + 4; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(4,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '7') //If Button 7 is pressed
    {mySerial.println ("Button 7");
    if (Number==0)
    Number=7;
    else{
    long temp=Number;
    Number = (Number*10) + 7; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(7,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
  

    if (key == '0')
    {mySerial.println ("Button 0"); //Button 0 is Pressed
    if (Number==0)
    Number=0;
    else{
      
    long temp=Number;
    Number = (Number*10) + 0; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(0,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '2') //Button 2 is Pressed
    {mySerial.println ("Button 2"); 
     if (Number==0)
    Number=2;
    else{
    long temp=Number;
    
    Number = (Number*10) + 2; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(2,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '5')
    {mySerial.println ("Button 5"); 
     if (Number==0)
    Number=5;
    else{
    long temp=Number;
    
    Number = (Number*10) + 5; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(5,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '8')
    {mySerial.println ("Button 8"); 
     if (Number==0)
    Number=8;
    else{
    long temp=Number;
    Number = (Number*10) + 8; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(8,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }   
  

    if (key == '#')
    {mySerial.println ("Button Equal"); 
    result = true;
    }
    
     if (key == '3')
    {mySerial.println ("Button 3"); 
     if (Number==0)
    Number=3;
    else
    {
    long temp=Number;
    
    Number = (Number*10) + 3; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(3,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '6')
    {mySerial.println ("Button 6"); 
    if (Number==0)
    Number=6;
    else{
    long temp=Number;
    
    Number = (Number*10) + 6; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(6,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }
    
     if (key == '9')
    {mySerial.println ("Button 9");
    if (Number==0)
    Number=9;
    else{
    long temp=Number;
    
    Number = (Number*10) + 9; //Pressed twice
    if (String(temp,DEC ).length()>=4 ){
      String temp1=String(temp,DEC);
      temp1 = temp1.substring(1, (temp1.length()))+String(9,DEC);
      Number=atol(temp1.c_str());
    }
    }
    }  

  if (key == 'D') //Detecting Buttons on Column 4
  {
    Num1 = Number;    
    Number =0;
    mySerial.println ("Devesion");
    action = '/';  
    delay(10);
  }
  
}

void CalculateResult()
{
 if (action=='/'){
  bool Open=false;
  int lateness=0;
  for (int i = 0; i < userNum; i++) {
    lateness=millis()-startTime;
    
    if (Num1==users[i].username){
      mySerial.println ("username is");
      mySerial.println (users[i].username );
      if (users[i].teacher){
        startTime=millis();
        mySerial.println ("it was teacher");
        Open=true;
      }
      else if (lateness<lateTime and startTime!=0){
        Open=true;                
      }
  
      if(Open){
       users[i].attendance=true;
       mySerial.println ("servo is moved");
       myservo.write(180);
       digitalWrite(ledOutput,HIGH);
       delay(openTime);
       myservo.write(0); 
       digitalWrite(ledOutput,LOW);
       Open=false;  
      }
       else{
        mySerial.println ("lateness is");
        mySerial.println (lateness);
        digitalWrite(buzzerOutput,HIGH);
        printOnLcd(0,"you are "+String(lateness)+" late");
        delay(buzzerTime);
        digitalWrite(buzzerOutput,LOW);
        lcd.clear();
       }
    }
  }
  Num1=Number=0;
  result=false;  
}
}


void DisplayResult()
{
     // set the cursor to column 0, line 1
  printOnLcd(0,"username: "+String(Num1));
  printOnLcd(1,String(Number));
  delay(lcdTime); //Wait for display to show info
  lcd.clear();
}

void pinIoDefiner(byte arr[],bool input)
{
  int l=sizeof(arr);
  for (int i = 0; i <= l; i++) {
    int pin=int(arr[i]);
    if(input)pinMode(pin, INPUT);
    else pinMode(pin, OUTPUT);
  } 
}

void pinLowHighWriter(byte arr[],bool low)
{
  int l=sizeof(arr);
  for (int i = 0; i <= l; i++) {
    if(low)digitalWrite(arr[i], LOW);
    else digitalWrite(arr[i], HIGH);

  }
}

void printOnLcd(int lineNumber, String message) {
  lcd.setCursor(0, lineNumber);
  lcd.print(message);
}




    
 
