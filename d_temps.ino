
void readTempsAndUpdate(){
  // get temperature
  T1Temp = getTemperature(T1Thermometer);
  T2Temp = getTemperature(T2Thermometer);
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
  elementPowerLevel = elementPowerLevelPercent * 2.55;
}


float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  return tempF;
}
