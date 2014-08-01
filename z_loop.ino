//  MAIN CODE
void loop()
{ 
  if (metro500.check() == 1) readTempsAndUpdate();

  if (metro100.check() == 1){
    analogWrite(AlarmPin, sirenState);
    analogWrite(ElementPowerPin, elementPowerLevelPercent * 2.55);
  }

  if (stringComplete == true) {
    inputHandler();
  }
  
  
  //need to add command decomposition and subrouting switching section

  if (metro1000.check() == 1) {
    updateDisplay();
   serialStatusMessage();
  }
}
