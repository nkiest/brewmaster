//calculated state variables
float tapWaterTemp = 0;
boolean heat = false;
boolean heatToActive = false;
int heatTimeSec = 0;

//1wire and temp
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
// arrays to hold device addresses
// need to change names
DeviceAddress  whirlpoolThermometer = { 
  0x28, 0x55, 0xA3, 0xF2, 0x04, 0x00, 0x00, 0x4E }; //1 2855A3F20400004E 
DeviceAddress  coolingOutThermometer =  { 
  0x28, 0x60, 0x22, 0xF3, 0x04, 0x00, 0x00, 0xC1 }; //2 286022F3040000C1
DeviceAddress  circuitThermometer = {  
  0x28, 0x83, 0x4B, 0x46, 0x02, 0x00, 0x00, 0x92 }; //kettle 28834B4602000092
DeviceAddress kettleThermometer  =  {  
  0x28, 0x8F, 0xEE, 0x7B, 0x05, 0x00, 0x00, 0xA1 }; //circuit 288FEE7B050000A1

float setpoint = 65; //in F
const float diff = 1; // allowable differential

//sensors
float kettleTemp = 0;
float whirlpoolTemp = 0;
float coolingOutTemp = 0;
float circuitTemp = 0; //in F

void tempSetup(){
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
}

void readTempsAndUpdate(){
  // get temperature
  whirlpoolTemp = getTemperature(whirlpoolThermometer);
  coolingOutTemp = getTemperature(coolingOutThermometer);
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
  if (heat == false){
    elementPowerLevelPercent = LOW;
  }
  else {
    if (heatToActive == true){
      if (kettleTemp > setpoint){
        heat = false;
        elementPowerLevelPercent = LOW;
        commandDelay = 0;
        Serial << databaseID << ",complete" << endl;
        heatToActive = false;
        clearCommand();
      }
      else {
        commandDelay = 10000;
      }
    }
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
      if (heatToActive == true){
        elementPowerLevelPercent = 20;
      }
      else elementPowerLevelPercent = 10;
    }
    else {
      elementPowerLevelPercent = LOW;
    }
  }
}

float getTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  return tempF;
}

void startHeatTo(int goal){
  if (setpoint > kettleTemp){    
    Serial << databaseID << ",error,already exceeded setpoint" << endl;
    clearCommand();
    return;
  }
  Serial << databaseID << ",received" << endl;
  heatToActive = true;
  heat = true;
  setpoint = goal;
  commandDelay = 10000;
}

void startBoil(int minutes){
  Serial << databaseID << ",received" << endl;
  heatTimeSec = minutes*60;
  heat = true;
  setpoint = 212;
  commandDelay = minutes*1000*90;
}

void endBoil(){
  heat = false;
  elementPowerLevelPercent = LOW;
  commandDelay = 0;
  Serial << databaseID << ",complete" << endl;
  clearCommand();
}

void startHoldAt(int goal, int minutes){
  Serial << databaseID << ",received" << endl;
  heatTimeSec = minutes*60;
  heat = true;
  setpoint = goal;
  commandDelay = minutes*1000*90;
}

void endHoldAt(){
  heat = false;
  elementPowerLevelPercent = LOW;
  commandDelay = 0;
  Serial << databaseID << ",complete" << endl;
  clearCommand();
}


