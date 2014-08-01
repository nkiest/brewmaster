void commands(){
  if (currentCommand == "whirlpoolValve"){
    if ((commandArg1 == "on" )|| (commandArg1 == "off")){
      if (commandArg1 == "on" ){
        valve(whirlpoolValvePin, 1);
      }
      if (commandArg1 == "off" ){
        valve(whirlpoolValvePin, 0);
      }
    }
    else {
      Serial << commandNumber << ": Error: Invalid argument" << endl;
      clearCommand();
      return;
    }
  }
}

//const int whirlpoolValvePin = 24;
//const int wortPipeValvePin = 25;
//const int drainValvePin = 26;

void valve(int PIN, bool on){
  if ((on == true) && (digitalRead(PIN) == HIGH)){
    Serial << commandNumber << ": Error: " << currentCommand << ": " << commandArg1 << " already ON" << endl;
    clearCommand();
    return;
  }
  else if ((on == false) && (digitalRead(PIN) == LOW)){
    Serial << commandNumber << ": Error: " << currentCommand << ": " << commandArg1 << " already OFF" << endl;
    clearCommand();
    return;
  }
  else if (on == true){
    digitalWrite(PIN, HIGH);
  }
  else if (on == false){
    digitalWrite(PIN, LOW);
  }
  commandDelay = 2200;
  Serial << commandNumber << ": " << currentCommand << ": " << commandArg1 << " received" << endl;

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
  if (engage == false){
    Serial.write("System Disengaged");
  }
  else {
    if (command == true){
      if (wortPumpPin == HIGH){
        Serial.write("Wort Pump already on");
      }
      else if (delayedMessageBuffer != ""){
        Serial.write("Other command pending");
      }
      else {
        digitalWrite(wortPumpPin, HIGH);
        //add non blocking wait command}
      }
      if (command == false){
        digitalWrite(wortPumpPin, LOW);
      }
    }
  }
}

