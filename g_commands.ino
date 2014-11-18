String validCommands[10] = {
  "grind","fill","heatTo","boil","wortPump","whirlpoolValve","drainValve","wortPipeValve","CIPPump","holdAt"};
String zeroArgCommands[] = {
  "grind"};
String singleNumericArgCommands[4] = {
  "wortPump","fill","heatTo","boil"};
String boolCommands[5] = {
  "whirlpoolValve","drainValve","wortPipeValve","CIPPump","cooling"};
String doubleNumericCommands[1] = {
  "holdAt"};
String highLevelCommands[] = {
  "recirculate","cool","whirlpool","drain","liftMash","dumpMash","CIP","lid"}; //not implemented yet



//checks for valid command number, runs commands();
void commandHandler(){
  databaseID = commandPart[0].toInt();
  currentCommand = commandPart[1];

  if (currentCommand == ""){
    Serial << databaseID << ",error,no command given,1st" << endl;
    Serial << currentCommand << endl;
    clearCommand();
    return;
  }

  if (delayedMessageBuffer != ""){
    Serial << databaseID << ",error,other command pending" << endl;
    clearCommand();
    return;
  }
  commandArg1 = commandPart[2];
  commandArg2 = commandPart[3];

  int j;
  boolean valid;
  for (j = 0; j < 10; j += 1){
    if (validCommands[j] == currentCommand){
      valid = true;
    }
  }
  if (valid == false){
    Serial << databaseID << "error,invalid command" << endl;
    clearCommand();
    return;
  }

  //on off commands
  for (j = 0; j < 6; j += 1){
    if (boolCommands[j] == currentCommand){
      boolCommand();
    }
  }
  for (j = 0; j < 3; j += 1){
    if (singleNumericArgCommands[j] == currentCommand){
      singleNumericArgCommand();
    }
  }
  for (j = 0; j < 1; j += 1){
    if (doubleNumericCommands[j] == currentCommand){
      doubleNumericCommand();
    }
  }




}


void boolCommand(){
  int PIN;
  boolean on;
  if (currentCommand == "whirlpoolValve") {
    PIN = whirlpoolValvePin;
  }
  else if (currentCommand == "wortPipeValve") {
    PIN = wortPipeValvePin;
  }
  else if (currentCommand == "drainValve") {
    PIN = drainValvePin;
  }
  else if (currentCommand == "CIPPump") {
    PIN = CIPPumpPin;
  }
  else if (currentCommand == "cooling") {
    PIN = coolingWaterInValvePin;
  }
  
  
  if (commandArg1 == "on") {
    on = true;
  }
  else if (commandArg1 == "off") {
    on = false;
  }
  else {
    Serial << databaseID << ",error,invalid argument" << endl;
    clearCommand();
    return;
  }
  if ((on == true) && (digitalRead(PIN) == HIGH)){
    Serial << databaseID << ",error,already on" << endl;
    clearCommand();
    return;
  }
  else if ((on == false) && (digitalRead(PIN) == LOW)){
    Serial << databaseID << ",error,already off" << endl;
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
  Serial << databaseID << ",received" << endl;
}

void singleNumericArgCommand(){
  //int PIN;
  //int arg;
  int param = commandArg1.toInt();
  if (param == 0){
    Serial << databaseID << ",error,nil argument" << endl;
    clearCommand();
    return;
  }
  if (currentCommand == "fill") {
    Serial << databaseID << ",received" << endl;
    startFill(param);
  }
  else if (currentCommand == "heatTo") {
    Serial << databaseID << ",received" << endl;
    startHeatTo(param);
  }
  else if (currentCommand == "boil") {
    Serial << databaseID << ",received" << endl;
    startBoil(param);
  }
  else if (currentCommand == "wortPump") {
    Serial << databaseID << ",received" << endl;
    setWortPump(param);
  }
}

void doubleNumericCommand(){
  int one = commandArg1.toInt();
  if (one == 0){
    Serial << databaseID << ",error,nil argument" << endl;
    clearCommand();
    return;
  }
  int two = commandArg2.toInt();
  if (two == 0){
    Serial << databaseID << ",error,nil argument" << endl;
    clearCommand();
    return;
  }
  if (currentCommand == "holdAt") { 
    startHoldAt(one,two);
  }
}

void clearCommand(){
  commandPart[0] = "";
  databaseID = 0;
  commandPart[1] = "";
  currentCommand = "";
  commandPart[2] = "";
  commandArg1 = "";
  commandPart[3] = "";
  commandArg2 = "";
}







