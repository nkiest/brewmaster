//  MAIN CODE
void loop() { 
  if (metro500.check() == 1) readTempsAndUpdate();

  if (metro100.check() == 1){
    analogWrite(AlarmPin, sirenState);
    analogWrite(ElementPowerPin, elementPowerLevelPercent * 2.55);
    if (filling == true){
      fill();
    }
    if (currentCommand != "") {
      commandDelay = commandDelay - 100;
      if (commandDelay == 0){
        Serial << databaseID << ",complete" << endl;
        clearCommand();
      }
    }
  }

  if (stringComplete == true) {
    inputHandler();
  }
  if (scaleStringComplete == true) {
    readScale();
  }

  //need to add command decomposition and subrouting switching section

  if (metro1000.check() == 1) {
    updateDisplay();
    serialStatusMessage();
    Serial3 << "~";
    if (heatTimeSec > 0){
      heatTimeSec -= 1;
      if (heatTimeSec = 0){
        if (setpoint == 212){
          endBoil();
        }
        else{
          endHoldAt();
        }
      }
    }

  }
}



