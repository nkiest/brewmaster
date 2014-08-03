//calculated state variables
float tapWaterTemp = 0;

void readTempsAndUpdate(){
  // get temperature
  whirlpoolTemp = getTemperature(whirlpoolThermometer);
  coolingTemp = getTemperature(coolingOutThermometer);
  kettleTemp = getTemperature(kettleThermometer);
  circuitTemp = getTemperature(circuitThermometer);
  sensors.requestTemperatures();  //async temp conversion request
  //set siren
  if (kettleTemp > setpoint){
    sirenState = (kettleTemp - setpoint) * 8;
  }
  else {
    sirenState = LOW;
  }
  //update burner
  if (setpoint == 212){
    if (kettleTemp < (setpoint - 2)){
      elementPowerLevelPercent = 100;
    }
    else if(kettleTemp < setpoint){
      elementPowerLevelPercent = 50;
    }
    else {
      elementPowerLevelPercent = LOW;
    }
  }
  else if (kettleTemp < (setpoint - 2)){
    elementPowerLevelPercent = 100;
  }
  else if (kettleTemp < (setpoint - 1.5)){
    elementPowerLevelPercent = 50;
  }
  else if (kettleTemp < (setpoint - .5)){
    elementPowerLevelPercent = 25;
  }
  else  if (kettleTemp < (setpoint)){
    elementPowerLevelPercent = 10;
  }
  else {
    elementPowerLevelPercent = LOW;
  }
}


float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  return tempF;
}
