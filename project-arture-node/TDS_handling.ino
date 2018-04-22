//sensor--------------------------------------------------

//di uji coba sesuai kebutuhan : perpaduan volume air dan pupuk, pengukuran NTU
void TDSInit(){
  int tempSensor = analogRead(TDSSensor);
  int tempLevel = analogRead(TDSLevel);
  for(int i = 0; i < TDSArrayLength; i++){
    TDSSensorArray[i] = tempSensor;
    TDSLevelArray[i] = tempLevel;
  }
}

void TDSSensorRead(){ 
  int TDSTemp;
  TDSTemp = analogRead(TDSSensor);
  TDSSensorValue = TDSSensorAverageArray(TDSTemp, TDSArrayLength);
  Serial.print("TDS sensor value : ");
  Serial.println(TDSSensorValue);
}

int TDSSensorAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    TDSSensorArray[i] = TDSSensorArray[i-1];
    sum = sum + TDSSensorArray[i];
  }
  TDSSensorArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}

//actuator--------------------------------------------------

void TDSActuate(){
  digitalWrite(TDSAct, LOW);
  Serial.println("TDS ON");
  //di uji coba sesuai kebutuhan : delay, catu daya
  delay(200);
  digitalWrite(TDSAct, HIGH);
  Serial.println("TDS OFF");
  stirActuate();
}

//level--------------------------------------------------

void TDSLevelRead(){ 
  int TDSTemp;
  TDSTemp = analogRead(TDSLevel);
  TDSLevelValue = TDSLevelAverageArray(TDSTemp, TDSArrayLength);
  Serial.print("TDS level value : ");
  //Serial.println(TDSLevelValue);
  Serial.println(((float)TDSLevelValue/1024)*100);
}

int TDSLevelAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    TDSLevelArray[i] = TDSLevelArray[i-1];
    sum = sum + TDSLevelArray[i];
  }
  TDSLevelArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}
