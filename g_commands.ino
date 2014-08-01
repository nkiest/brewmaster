String validCommands[10] = {"grind","fill","heatTo","boil","wortPump","whirlpoolValve","drainValve","wortPipeValve","CIPPump","holdAt"};
String zeroArgCommands[] = {"grind"};
String singleNumericArgCommands[] = {"fill","heatTo","boil"};
String boolCommands[5] = {"wortPump","whirlpoolValve","drainValve","wortPipeValve","CIPPump"};
String doubleNumericCommands[] = {"holdAt"};
String highLevelCommands[] = {"recirculate","whirlpool","drain","liftMash","dumpMash","CIP","lid"}; //not implemented yet

//checks for valid command number, runs commands();
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
  
  if (delayedMessageBuffer != ""){
        Serial << commandNumber << ": Error: Other command pending" << endl;
        clearCommand();
        return;
      }
  
  commandArg1 = commandPart[2];
  commandArg2 = commandPart[3];
  
  int j;
  bool valid;
  for (j = 0; j < 10; j += 1){
    if (validCommands[j] == currentCommand){
      valid = true;
    }
  }
  if (valid == false){
  Serial << commandNumber << ": Error: Invalid Command" << endl;
    clearCommand();
    return;
  }
  
  //on off commands
  bool isBoolCommand;
  for (j = 0; j < 5; j += 1){
    if (boolCommands[j] == currentCommand){
      isBoolCommand = true;
    }
  }
  if (isBoolCommand == true){
  boolCommand();}
}

void boolCommand(){
  int PIN;
  bool on;
  if (currentCommand == "whirlpoolValve") {
    PIN = whirlpoolValvePin;
  }
  else if (currentCommand == "wortPipeValve") {
    PIN = wortPipeValvePin;
  }
  else if (currentCommand == "drainValve") {
    PIN = drainValvePin;
  }
  else if (currentCommand == "wortPump") {
    PIN = wortPumpPin;
  }
  else if (currentCommand == "CIPPump") {
    PIN = CIPPumpPin;
  }
  if (commandArg1 == "on") {
    on = true;
  }
  else if (commandArg1 == "off") {
    on = false;
  }
  else {
    Serial << commandNumber << ": Error: Invalid argument" << endl;
    clearCommand();
    return;
  }
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


