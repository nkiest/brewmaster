
void readTempsAndUpdate(){
  // get temperature
  T1Temp = getTemperature(T1Thermometer);
  T2Temp = getTemperature(T2Thermometer);
  kettleTemp = getTemperature(kettleThermometer);
  circuitTemp = getTemperature(circuitThermometer);
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


float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  return tempF;
}
