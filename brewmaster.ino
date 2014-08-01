//  *
//  *

#include <OneWire.h> // http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <DallasTemperature.h> // https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Streaming.h> // http://arduiniana.org/libraries/streaming/
#include <Metro.h> // Include Metro library https://github.com/thomasfredericks/Metro-Arduino-Wiring/wiki
#include <avr/pgmspace.h>

//define pins
const int ONE_WIRE_BUS = 30;
const int TEMPERATURE_PRECISION = 11;
const int AlarmPin = 3;
const int ElementPowerPin = 8;
const int wortPumpPin = 32; //Above 240V AC on side
const int grainMillPin = 33; //2 above 240V AC on side
const int CIPPumpPin = 34; //On bottom corner, next to power in
const int whirlpoolValvePin = 35; //RJ 8
const int wortPipeValvePin = 36; //RJ 9
const int drainValvePin = 37; //RJ 10
const int filteredWaterValvePin = 38;
const int coolingWaterInValvePin = 39;
const int coolingWaterOutValvePin = 40;



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
int delayUntilMessage = 0; //Countdown to wait until sending success message for delayed valves, etc

String keypadInputString = ""; // a string to hold incoming data
String delayedMessageBuffer = ""; //to hold future success message

//1wire and temp
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
// arrays to hold device addresses
// need to change names
DeviceAddress  T1Thermometer = { 
  0x28, 0x55, 0xA3, 0xF2, 0x04, 0x00, 0x00, 0x4E }; //1 2855A3F20400004E 
DeviceAddress  T2Thermometer =  { 
  0x28, 0x60, 0x22, 0xF3, 0x04, 0x00, 0x00, 0xC1 }; //2 286022F3040000C1
DeviceAddress  kettleThermometer = {  
  0x28, 0x83, 0x4B, 0x46, 0x02, 0x00, 0x00, 0x92 }; //kettle 28834B4602000092
DeviceAddress  circuitThermometer =  {  
  0x28, 0x8F, 0xEE, 0x7B, 0x05, 0x00, 0x00, 0xA1 }; //circuit 288FEE7B050000A1
unsigned long lastTempRequest = 0;
int delayInMillis = 0;
int idle = 0;

Metro metro1000 = Metro(1000);
Metro metro100 = Metro(100);
Metro metro500 = Metro(500);















