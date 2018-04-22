//actuator--------------------------------------------------

void waterPumpActuate(){
  digitalWrite(waterPumpAct, LOW);
  Serial.println("water ON");
  delay(1000);
  digitalWrite(waterPumpAct, HIGH);
  Serial.println("water OFF");
}

//level--------------------------------------------------
void waterInit(){
  int tempLevel = analogRead(waterLevel);
  for(int i = 0; i < waterArrayLength; i++){
    waterLevelArray[i] = tempLevel;
  }
}

void waterLevelRead(){ 
  int waterTemp;
  waterTemp = analogRead(waterLevel);
  waterLevelValue = waterLevelAverageArray(waterTemp, waterArrayLength);
  Serial.print("water level value : ");
  //Serial.println(waterLevelValue);
  Serial.println(((float)waterLevelValue/1024)*100);
}

int waterLevelAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    waterLevelArray[i] = waterLevelArray[i-1];
    sum = sum + waterLevelArray[i];
  }
  waterLevelArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}
