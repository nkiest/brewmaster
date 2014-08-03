int outputPins[8] = {
  wortPumpPin,CIPPumpPin,whirlpoolValvePin,wortPipeValvePin,drainValvePin,filteredWaterValvePin,coolingWaterInValvePin,coolingWaterOutValvePin};

void setup(void)
{
  LCDSetup();

  pinMode(AlarmPin, OUTPUT);
  analogWrite(AlarmPin, sirenState);
  pinMode(ElementPowerPin, OUTPUT);
  analogWrite(ElementPowerPin, LOW);

  for (i = 0; i < 8; i += 1){
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }


  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR4B = TCCR4B & B11111000 | B00000101; // set timer 4 divisor to  1024 for PWM frequency of 30.64 Hz
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR2B = TCCR2B & 0b11111000 | 0x06; //122hz
  
  // Start up the 1wire library
  const int TEMPERATURE_PRECISION = 11;
  sensors.begin();
  sensors.setWaitForConversion(false);  // makes it async
  sensors.setResolution(whirlpoolThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(coolingOutThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(kettleThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(circuitThermometer, TEMPERATURE_PRECISION);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - TEMPERATURE_PRECISION)); 
  lastTempRequest = millis(); 

  serialInitalize();
  scaleInitalize();

  clearLCD();
}



