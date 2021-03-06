//This file controls all serial0 (USB) serial handling
String commandSequence = ""; 
String currentCommand = "";
boolean stringComplete = false; // whether the string is complete
int commaPosition;
String commandPart[4];
String commandArg1;
String commandArg2;


void inputHandler(){
  do {
    commaPosition = commandSequence.indexOf(',');
    if(commaPosition != -1)
    {
      commandPart[i] = commandSequence.substring(0,commaPosition);
      commandSequence = commandSequence.substring(commaPosition+1, commandSequence.length());
      i++;
    }
    else
    {  // here after the last comma is found
      if(commandSequence.length() > 0)
        commandPart[i] = commandSequence;              
    }
  }
  while    (commaPosition >=0 && i < 4);  
  // clear the string:
  i = 0;
  commandSequence = "";
  stringComplete = false;
  commandHandler();
  clearLCD();
  updateDisplay();
}

void serialStatusMessage(){
  Serial << "status," << (millis()/1000) << "," << databaseID <<","<< freeRam() <<","<< kettleTemp << ","<< digitalRead(wortPumpPin) <<","<< whirlpoolTemp <<","<< coolingOutTemp <<","<< circuitTemp <<","<< weight <<","<< setpoint <<","<< elementPowerLevelPercent <<","<< filling << ","<< digitalRead(wortPumpPin) <<","<< digitalRead(CIPPumpPin) <<","<< digitalRead(grainMillPin) <<","<< digitalRead(whirlpoolValvePin) <<","<< digitalRead(wortPipeValvePin) <<","<< digitalRead(drainValvePin) << endl;
  //elapsed_time, command_logs_id: cmd, free_ram: ram,kettle_degrees_fahrenheit: kettle_temp, wort_pump_on: wort_pump_on
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
    else
      // add it to the commandSequence:
      commandSequence += inChar; 
  }
}

void serialInitalize(){
  commandSequence.reserve(200);
  Serial.begin(57600);
  delay(1000);
  // locate devices on the bus
  Serial << endl << "Found " << _DEC(sensors.getDeviceCount()) << " devices." << endl;
  // display line one of CSV format to serial
  //Serial << "time,currentCommand,freeRam,kettleTemp,whirlpoolTemp,coolingOutTemp,circuitTemp,weight,setpoint,elementPowerLevelPercent,filling,wortPump,CIPPump,grainMill,whirlpoolValve,wortPipeValve,drainValve" << endl;
}



