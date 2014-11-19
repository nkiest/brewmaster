
int wortPumpDutyCycle = 0; // 0= off, 1-100 percent on, 101+ invalid
int wortPumpPeriod = 100; // seconds
int wpi = 0; //wortpumpincrementer

void setWortPump(int param) {
  if (param < 0 || param > 100) {
    Serial << databaseID << ",error,invalid parameter-shutting off pump" << endl;
    digitalWrite(wortPumpPin, 0);
    wortPumpDutyCycle = 0;
    clearCommand();
    return;
  }
  if (param == 0) {
    digitalWrite(wortPumpPin, 0);
    wortPumpDutyCycle = 0;
    commandDelay = 1000;
  }
  else {
  wortPumpDutyCycle = param;
  commandDelay = 1000; 
  }
  

}
