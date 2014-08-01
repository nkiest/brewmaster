//mechanical state variables
boolean engage = false;
int elementPowerLevelPercent = 0;
//pumps
boolean wortPump = false;
boolean CIPPump = false;
//valves
boolean whirlpoolValve = false;
boolean wortPipeValve = false;
boolean drainValve = false;
boolean filteredWaterValve = false;
boolean coolingWaterInValve = false;
boolean coolingWaterOutValve = false;
//sensors
float kettleTemp = 0;
float whirlpoolTemp = 0;
float coolingTemp = 0;
float circuitTemp = 0; //in F
float weight = 0;
boolean lidFloatSensor = 0;
boolean coolingBottomFloatSensor = 0;
boolean coolingTopFloatSensor = 0;

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
