//  *
//  *

#include <OneWire.h> // http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <DallasTemperature.h> // https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Streaming.h> // http://arduiniana.org/libraries/streaming/
#include <Metro.h> // Include Metro library https://github.com/thomasfredericks/Metro-Arduino-Wiring/wiki
#include <avr/pgmspace.h>

//define pins
const int ONE_WIRE_BUS = 30;
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

int databaseID;
int commandDelay = 0;

int i = 0; //loop counter
unsigned int sirenState = LOW;
int delayUntilMessage = 0; //Countdown to wait until sending success message for delayed valves, etc

String keypadInputString = ""; // a string to hold incoming data
String delayedMessageBuffer = ""; //to hold future success message

unsigned long lastTempRequest = 0;
int delayInMillis = 0;
int idle = 0;

Metro metro1000 = Metro(1000);
Metro metro100 = Metro(100);
Metro metro500 = Metro(500);

