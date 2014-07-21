
void setup(void)
{
  keypadInputString.reserve(8);
  Serial1.begin(19200);
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


  // Start up the 1wire library
  sensors.begin();
  sensors.setWaitForConversion(false);  // makes it async
  sensors.setResolution(T1Thermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(T2Thermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(kettleThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(circuitThermometer, TEMPERATURE_PRECISION);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - TEMPERATURE_PRECISION)); 
  lastTempRequest = millis(); 
  
    serialInitalize();

  clearLCD();
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR4B = TCCR4B & B11111000 | B00000101; // set timer 4 divisor to  1024 for PWM frequency of 30.64 Hz
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR2B = TCCR2B & 0b11111000 | 0x06; //122hz
}


