#define ETX 0x03
String scaleString = ""; 
boolean scaleStringComplete = false;
int startingWeight;
int targetWeight;

//calculated state variables
int mashWeight = 0;
int wortWeight = 0;
int baseWeight = 0;

//takes input in oz
void startFill(int vol){
  startingWeight = weight;
  targetWeight = startingWeight + vol;
  filling = true;
  digitalWrite(filteredWaterValvePin,HIGH);
  Serial3 << "~";
  commandDelay = 10000; 
}

void fill(){
  if (weight > targetWeight){
    digitalWrite(filteredWaterValvePin,LOW);
    filling = false;   
    int tempDatabaseID = databaseID;
    Serial << tempDatabaseID << ",complete" << endl;
    delay(1000);
    clearCommand();
    commandDelay = 0;
    Serial3 << "~";
  }
  else {
    Serial3 << "~";
    commandDelay = 10000;
  }
}

void readScale(){
  int interWeight = (scaleString.substring(3,5).toInt())*16 + scaleString.substring(10,11).toInt();
  if ((interWeight > 0) && (interWeight < 1920)){ //sanity check
    weight = interWeight;
  }
  scaleStringComplete = false;
  scaleString = "";
}

void scaleInitalize(){
  scaleString.reserve(25);
  Serial3.begin(9600);
  // request starting weight
  Serial3 << "~";
}

void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read(); 
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == ETX) {
      scaleStringComplete = true;
    } 
    else
      // add it to the commandSequence:
      scaleString += inChar; 
  }
}


