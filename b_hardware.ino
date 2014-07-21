const int valve = 52;



//mechanical state variables
boolean engage = off;
int elementPowerLevelPercent = 0;
//pumps
boolean wortPump = off;
boolean CIPPump = off;
//valves
boolean whirlpoolValve = off;
boolean wortPipeValve = off;
boolean drainValve = off;
boolean filteredWaterValve = off;
boolean coolingWaterInValve = off;
boolean coolingWaterOutValve = off;
//sensors
float kettleTemp = 0;
float whirlpoolTemp = 0;
float coolingTemp = 0;
float circuitTemp = 0; //in F
float weight = 0;
boolean lidFloatSensor = 0;
boolean coolingBottomFloatSensor = 0;
boolean coolingTopFloatSensor = 0;
