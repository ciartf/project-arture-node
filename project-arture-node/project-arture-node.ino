//pH--------------------------------------------------
//sensor
#define pHSensor A0
#define pHOffset -3.00
#define pHSamplingInterval 20
#define pHArrayLength 10
int pHSensorArray[pHArrayLength];
int pHArrayIndex = 0;
int pHSensorValue;
unsigned long pHSamplingTime;
//actuator
#define pHUpAct 2
#define pHDownAct 3
//level
#define pHUpLevel A1
#define pHDownLevel A2
int pHUpLevelArray[pHArrayLength];
int pHDownLevelArray[pHArrayLength];
int pHLowerBound;
int pHUpperBound;
int pHUpLevelValue;
int pHDownLevelValue;

//TDS--------------------------------------------------
//sensor
#define TDSSensor A3
#define TDSArrayLength 10
int TDSSensorArray[TDSArrayLength];
int TDSSensorValue;
//actuator
#define TDSAct 4
//level
#define TDSLevel A4
int TDSLevelArray[TDSArrayLength];
int TDSLevelValue;  
int TDSLowerBound;
int TDSUpperBound;

//stirrer--------------------------------------------------
//actuator
#define stirAct 5

//water--------------------------------------------------
//level
#define waterArrayLength 10
#define waterLevel A5
int waterLevelArray[waterArrayLength];
int waterLevelValue;
//perlu diukur ulang
#define waterMaxLevel 100;
int waterUpperBound = (90/100) * waterMaxLevel;
int waterLowerBound = (60/100) * waterMaxLevel;
//actuator
#define waterPumpAct 6

//air--------------------------------------------------
//sensor
//disesuaikan proposal
#define airActingInterval 20
unsigned long airActingTime;
//actuator
#define airPumpAct 7

//transfer--------------------------------------------------
//esp belum bisa :(

//setup--------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(pHSensor, INPUT);
  pinMode(pHUpAct, OUTPUT);
  digitalWrite(pHUpAct, HIGH);
  pinMode(pHDownAct, OUTPUT);
  digitalWrite(pHDownAct, HIGH);
  pinMode(TDSSensor, INPUT);
  pinMode(TDSAct, OUTPUT);
  digitalWrite(TDSAct, HIGH);
  pinMode(waterPumpAct, OUTPUT);
  digitalWrite(waterPumpAct, HIGH);
  pinMode(airPumpAct, OUTPUT);
  digitalWrite(airPumpAct, HIGH);
  pinMode(stirAct, OUTPUT);
  digitalWrite(stirAct, HIGH);
  pHSamplingTime = millis();
  airActingTime = millis();
}

//run process--------------------------------------------------
void loop() {
  //sensor measurement

  //receive : pHLowerBound, pHUpperBound, TDSLowerBound, TDSUpperBound

  TDSInit();
  pHInit();
  waterInit();
  
  pHSensorRead();
  pHUpLevelRead();
  pHDownLevelRead();
  TDSSensorRead();
  TDSLevelRead();
  waterLevelRead();

  delay(1000);
  
  //TDSActuate();
  //pHUpActuate();
  //pHDownActuate();
  //waterPumpActuate();
  //delay(5000);

  
  //send notif : pHUpLevel, pHDownLevel, waterLevel, pHValue, TDSValue
  
  /*if(pHSensorValue < pHLowerBound){
    pHUpActuate();
  }else if(pHSensorValue > pHUpperBound){
    pHDownActuate();
  }
  
  if(TDSSensorValue < TDSLowerBound){
    TDSActuate();
  }else if(TDSSensorValue > TDSUpperBound){
    if(waterLevelValue < waterUpperBound){
      waterPumpActuate();
    }else if(waterLevelValue > waterUpperBound){
      //do nothing
    }
  }

  if(waterLevelValue < waterLowerBound){
    waterPumpActuate();
  }else{
    //do nothing
  }*/
}
