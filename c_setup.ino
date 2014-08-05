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
  i = 0;

  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR4B = TCCR4B & B11111000 | B00000101; // set timer 4 divisor to  1024 for PWM frequency of 30.64 Hz
  //sets Arduino Mega's pin 6,7,8 to diff PWM frequency
  TCCR2B = TCCR2B & 0b11111000 | 0x06; //122hz

  tempSetup();
  serialInitalize();
  scaleInitalize();

  clearLCD();
}




