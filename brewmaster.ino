//  *
//  *

#include <OneWire.h> // http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <DallasTemperature.h> // https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Streaming.h> // http://arduiniana.org/libraries/streaming/
#include <Metro.h> // Include Metro library https://github.com/thomasfredericks/Metro-Arduino-Wiring/wiki

//define pins

#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 11
#define on true
#define off false
const int AlarmPin = 3;
const int ElementPowerPin = 8;
const int wortPumpPin = 22;
const int CIPPumpPin = 23;
const int whirlpoolValvePin = 24;
const int wortPipeValvePin = 25;
const int drainValvePin = 26;
const int filteredWaterValvePin = 27;
const int coolingWaterInValvePin = 28;
const int coolingWaterOutValvePin = 29;

// Declare your program variables here

//mechanical state variables
boolean engage = off;
int elementPowerLevelPercent = 0;
//pumps
boolean wortPump = off;
boolean CIPPump = off;
//valves
boolean whirlpoolValve = off;
boolean wortPipeValve = off;
boolean drainValve = off;
boolean filteredWaterValve = off;
boolean coolingWaterInValve = off;
boolean coolingWaterOutValve = off;

//sensors
float kettleTemp = 0;
float whirlpoolTemp = 0;
float coolingTemp = 0;
float weight = 0;
boolean lidFloatSensor = 0;
boolean coolingBottomFloatSensor = 0;
boolean coolingTopFloatSensor = 0;




//calculated state variables
float mashWeight = 0;
float wortWeight = 0;
float baseWeight = 0;
float tapWaterTemp = 0;
int elementPowerLevel = 0; //should be elementPowerLevelPercent times 2.55


float T1Temp = 0; //in F
float T2Temp = 0; //in F
float setpoint = 65; //in F
float diff = 1; // allowable differential
int i = 0; //loop counter
unsigned int sirenState = LOW;

boolean stringComplete = false; // whether the string is complete
String keypadInputString = ""; // a string to hold incoming data
String serialInputString = ""; // a string to hold incoming data
String delayedMessageBuffer = "";
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
// arrays to hold device addresses
DeviceAddress  T1Thermometer = { 
  0x28, 0x55, 0xA3, 0xF2, 0x04, 0x00, 0x00, 0x4E }; //1 2855A3F20400004E
DeviceAddress  T2Thermometer =  { 
  0x28, 0x60, 0x22, 0xF3, 0x04, 0x00, 0x00, 0xC1 }; //2 286022F3040000C1
unsigned long lastTempRequest = 0;
int delayInMillis = 0;
int idle = 0;

Metro metro1000 = Metro(1000);
Metro metro100 = Metro(100);
Metro metro500 = Metro(500);

void switchWortPump(boolean command){
  if (engage == off){
    Serial.write("System Disengaged");
  }
  else {
    if (command == on){
      if (wortPumpPin == on){
        Serial.write("Wort Pump already on");
      }
      else if (delayedMessageBuffer != ""){
        Serial.write("Other command pending");
      }
      else {
        digitalWrite(wortPumpPin, on);
        //add non blocking wait command}
      }
      if (command == off){
        digitalWrite(wortPumpPin, off);
      }
    }
  }


}

//  MAIN CODE
void loop()
{ 
  if (metro500.check() == 1) readTempsAndUpdate();

  if (metro100.check() == 1){
    analogWrite(AlarmPin, sirenState);
    analogWrite(ElementPowerPin, elementPowerLevel);
  }

  if (stringComplete) {
    Serial.println(serialInputString); 
    if (serialInputString.toInt() != 0){
      setpoint = serialInputString.toInt();
      clearLCD();
      updateDisplay();
    }
    serialInputString = "";
    stringComplete = false;
  }

  if (metro1000.check() == 1) {
    updateDisplay();
    Serial << (millis()/1000) << ", " << T1Temp << ", " << T2Temp << ", " << setpoint <<", " << elementPowerLevelPercent << endl; //write status to serial

  }

}

void readTempsAndUpdate(){
  // get temperature
  T1Temp = getTemperature(T1Thermometer);
  T2Temp = getTemperature(T2Thermometer);
  sensors.requestTemperatures();  //async temp conversion request
  //set siren
  if (T1Temp > setpoint){
    sirenState = (T1Temp - setpoint) * 8;
  }
  else {
    sirenState = LOW;
  }
  //update burner
  if (setpoint == 212){
    if (T1Temp < (setpoint - 2)){
      elementPowerLevelPercent = 100;
    }
    else if(T1Temp < setpoint){
      elementPowerLevelPercent = 50;
    }
    else {
      elementPowerLevelPercent = off;
    }
  }
  else if (T1Temp < (setpoint - 2)){
    elementPowerLevelPercent = 100;
  }
  else if (T1Temp < (setpoint - 1.5)){
    elementPowerLevelPercent = 50;
  }
  else if (T1Temp < (setpoint - .5)){
    elementPowerLevelPercent = 25;
  }
  else  if (T1Temp < (setpoint)){
    elementPowerLevelPercent = 10;
  }
  else {
    elementPowerLevelPercent = off;
  }
  elementPowerLevel = elementPowerLevelPercent * 2.55;
}

void updateDisplay(){
  clearLCD();
  cursorSet(0,1);
  Serial1.print("Set:");
  Serial1.print(setpoint, 1);
  Serial1.write(0);
  cursorSet(12,1);
  if (elementPowerLevelPercent > 0){
    Serial1.print("H:");
    Serial1.print(elementPowerLevelPercent);
  }
  else {
    Serial1.print("      ");
  }
  cursorSet(0,2);
  Serial1.print("1:");
  Serial1.print(T1Temp, 1);
  Serial1.write(0);
  cursorSet(9,2);
  Serial1.print("2:");
  Serial1.print(T2Temp, 1);
  Serial1.write(0);
}

float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  return tempF;
}

void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read(); 
    // add it to the keypadInputString:
    keypadInputString += inChar;
    //turn keypadInputString into setpoint once 3 chars come in
    if (keypadInputString.length() > 2) {
      setpoint = keypadInputString.toInt();
      clearLCD();
      updateDisplay();
      keypadInputString = "";
    } 
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    serialInputString += inChar;
    //turn inputstring into setpoint once 3 chars come in
    if (inChar == ',') {
      stringComplete = true;
    } 
  }
}

void setup(void)
{
  keypadInputString.reserve(8);
  serialInputString.reserve(100);
  Serial1.begin(19200);
  Serial.begin(9600);
  LCDSetup();

  pinMode(AlarmPin, OUTPUT);
  analogWrite(AlarmPin, sirenState);
  
  pinMode(wortPumpPin, OUTPUT);
  digitalWrite(wortPumpPin, LOW);
  pinMode(CIPPumpPin, OUTPUT);
  digitalWrite(CIPPumpPin, LOW);
  pinMode(whirlpoolValvePin, OUTPUT);
  digitalWrite(whirlpoolValvePin, LOW);
  pinMode(wortPipeValvePin, OUTPUT);
  digitalWrite(wortPipeValvePin, LOW);
  pinMode(drainValvePin, OUTPUT);
  digitalWrite(drainValvePin, LOW);
  pinMode(filteredWaterValvePin, OUTPUT);
  digitalWrite(filteredWaterValvePin, LOW);
  pinMode(coolingWaterInValvePin, OUTPUT);
  digitalWrite(coolingWaterInValvePin, LOW);
  pinMode(coolingWaterOutValvePin, OUTPUT);
  digitalWrite(coolingWaterOutValvePin, LOW);


  // Start up the library
  sensors.begin();
  sensors.setWaitForConversion(false);  // makes it async
  sensors.setResolution(T1Thermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(T2Thermometer, TEMPERATURE_PRECISION);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - TEMPERATURE_PRECISION)); 
  lastTempRequest = millis(); 

  // locate devices on the bus
  Serial << endl << "Found " << _DEC(sensors.getDeviceCount()) << " devices." << endl;

  // display line one of CSV format to serial
  Serial << "Time, T1 Temp, T2 Temp, Setpoint, Power Level" << endl;

  clearLCD();
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR4B = TCCR4B & B11111000 | B00000101; // set timer 4 divisor to  1024 for PWM frequency of 30.64 Hz
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR2B = TCCR2B & 0b11111000 | 0x06; //122hz
}

//------------------------------------------
//  LCD  FUNCTIONS-- keep the ones you need. 

// clear the LCD
void clearLCD(){
  Serial1.write(12);
}

// start a new line
void newLine() { 
  Serial1.write(10); 
}

// move the cursor to the home position
void cursorHome(){
  Serial1.write(254);
  Serial1.write(72);
}

// move the cursor to a specific place
// e.g.: cursorSet(3,2) sets the cursor to x = 3 and y = 2
void cursorSet(int xpos, int ypos){  
  Serial1.write(254);
  Serial1.write(71);               
  Serial1.write(xpos);   //Column position   
  Serial1.write(ypos); //Row position 
} 

// backspace and erase previous character
void backSpace() { 
  Serial1.write(8); 
}

// move cursor left
void cursorLeft(){    
  Serial1.write(254); 
  Serial1.write(76);   
}

// move cursor right
void cursorRight(){
  Serial1.write(254); 
  Serial1.write(77);   
}

// set LCD contrast
void setContrast(int contrast){
  Serial1.write(254); 
  Serial1.write(80);   
  Serial1.write(contrast);   
}


// turn on backlight
void backlightOn(int minutes){
  Serial1.write(254); 
  Serial1.write(66);   
  Serial1.write(minutes); // use 0 minutes to turn the backlight on indefinitely   
}

// turn off backlight
void backlightOff(){
  Serial1.write(254); 
  Serial1.write(70);   
}

void LCDSetup(){
  //       Turn OFF AUTO line wrap
  Serial1.write(254); 
  Serial1.write(68); 
  delay(200);

  //       Turn OFF the block cursor    
  //       Note that setting both block and underline 
  //       cursors may give unpredictable results. 
  Serial1.write(254);
  Serial1.write(84);   
  delay(200);  

  //Enable Keypad Mode / Already default
  //Serial1.write(254);
  //  Serial1.write(37);
  //  Serial1.write(0);


  //Turn off auto transmit keypress
  //Serial1.write(254);
  //Serial1.write(79);

  //Turn on auto transmit keypress
  Serial1.write(254);
  Serial1.write(65);

  //       Turn ON the block cursor
  //         Serial1.write(254);
  //         Serial1.write(83);  

  //       Turn ON the underline cursor
  //         Serial1.write(254);
  //         Serial1.write(74);               

  //       Turn OFF the underline cursor
  //         Serial1.write(254);
  //         Serial1.write(75);               

  // Custom Character for ° symbol
  Serial1.write(254);
  Serial1.write(78);   
  Serial1.write(0); 
  Serial1.write(8); 
  Serial1.write(20); 
  Serial1.write(20); 
  Serial1.write(8); 
  Serial1.write(0); 
  Serial1.write(0);  
  Serial1.write(0); 
  Serial1.write(0);
  delay(200);

  // Update keypad keys
  Serial1.write(254);
  Serial1.write(213);
  Serial1.write(48);
  Serial1.write(57);
  Serial1.write(54);
  Serial1.write(51);
  Serial1.write(56);
  Serial1.write(53);
  Serial1.write(53);
  Serial1.write(50);
  Serial1.write(55);
  Serial1.write(57);
  Serial1.write(52);
  Serial1.write(49);
  Serial1.write(48);
  Serial1.write(57);
  Serial1.write(54);
  Serial1.write(51);
  Serial1.write(56);
  Serial1.write(53);
  Serial1.write(53);
  Serial1.write(50);
  Serial1.write(55);
  Serial1.write(57);
  Serial1.write(52);
  Serial1.write(49);

  clearLCD();
  Serial1.print("Booting"); 
}












