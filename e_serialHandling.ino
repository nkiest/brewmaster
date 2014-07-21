//This file controls all serial0 (USB) serial handling

String commandSequence = ""; 
String currentCommand = "";
boolean stringComplete = false; // whether the string is complete
int     commaPosition;
String  commandPart[4];
String commandArg1;
String commandArg2;
int commandNumber;
int commandDelay = 0;


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
  commandSequence = "";
  stringComplete = false;
  i = 0;
  commandHandler();
  clearLCD();
  updateDisplay();

}

void serialStatusMessage(){
  Serial << (millis()/1000) << ", " << T1Temp << ", " << T2Temp << ", " << setpoint <<", " << elementPowerLevelPercent << endl; //write status to serial
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
  Serial.begin(9600);
  // locate devices on the bus
  Serial << endl << "Found " << _DEC(sensors.getDeviceCount()) << " devices." << endl;

  // display line one of CSV format to serial
  Serial << "Time, T1 Temp, T2 Temp, Setpoint, Power Level" << endl;

}
