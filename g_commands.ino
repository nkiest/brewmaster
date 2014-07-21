void commands(){
  if (currentCommand == "valve"){
    if ((commandArg1 == "on" )|| (commandArg1 == "off")){
      if (commandArg1 == "on" ){
        if (digitalRead(valve) == HIGH){
          Serial << commandNumber << ": Error: " << currentCommand << ": " << commandArg1 << " already ON" << endl;
          clearCommand();
          return;
        }
        else {
          digitalWrite(valve, HIGH);
        }
      }
      if (commandArg1 == "off" ){
        if (digitalRead(valve) == LOW){
          Serial << commandNumber << ": Error: " << currentCommand << ": " << commandArg1 << " already OFF" << endl;
          clearCommand();
          return;
        }
        else {
          digitalWrite(valve, LOW);
        }
      }
      commandDelay = 2200;
      Serial << commandNumber << ": " << currentCommand << ": " << commandArg1 << " received" << endl;
    }
    else {
      Serial << commandNumber << ": Error: Invalid argument" << endl;
      clearCommand();
      return;
    }
  }
}

void commandHandler(){
  commandNumber = commandPart[0].toInt();
  if (commandNumber == 0){
    Serial << "Error: Invalid command number" << endl;
    clearCommand();
    return;
  }
  currentCommand = commandPart[1];
  if (currentCommand == ""){
    Serial << commandNumber << ": Error: No command given" << endl;
    clearCommand();
    return;
  }
  commandArg1 = commandPart[2];
  commandArg2 = commandPart[3];
  commands();
}
void clearCommand(){
  commandPart[0] = "";
  commandNumber = 0;
  commandPart[1] = "";
  currentCommand = "";
  commandPart[2] = "";
  commandArg1 = "";
  commandPart[3] = "";
  commandArg2 = "";
}


void switchWortPump(boolean command, int commandCode){
	//need to add command code messages to serial
  if (engage == off){
    Serial.write("System Disengaged");
  }
  else {
    if (command == on){
      if (wortPumpPin == on){
        Serial.write("Wort Pump already on");
      }
      else if (delayedMessageBuffer != ""){
        Serial.write("Other command pending");
      }
      else {
        digitalWrite(wortPumpPin, on);
        //add non blocking wait command}
      }
      if (command == off){
        digitalWrite(wortPumpPin, off);
      }
    }
  }
}
