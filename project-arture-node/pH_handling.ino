//sensor--------------------------------------------------

//perlu kalibrasi menggunakan pH meter
void pHInit(){
  int tempSensor = analogRead(pHSensor);
  int tempUp = analogRead(pHUpLevel);
  int tempDown = analogRead(pHDownLevel);
  for(int i = 0; i < pHArrayLength; i++){
    pHSensorArray[i] = tempSensor;    
    pHUpLevelArray[i] = tempUp;
    pHDownLevelArray[i] = tempDown;
  }
}

void pHSensorRead(){
  int voltage;
  if(millis() - pHSamplingTime > pHSamplingInterval){
    pHSensorArray[pHArrayIndex++] = analogRead(pHSensor);
    if(pHArrayIndex == pHArrayLength){
      pHArrayIndex = 0;
    }
    voltage = pHSensorAverageArray(pHSensorArray, pHArrayLength) * 5.0 / 1024;
    pHSensorValue = 3.5 * voltage + pHOffset;
    Serial.print("pH sensor value : ");
    Serial.println(pHSensorValue);
    pHSamplingTime = millis();
  }
}

int pHSensorAverageArray(int* arr, int number){
  int i;
  int max, min;
  float avg;
  float sum = 0;
  if(number <= 0){
    Serial.println("Error number for the pH array to averaging!/n");
    return (int)0;
  }
  if(number < 5){
    for(i = 0; i < number; i++){
      sum += arr[i];
    }
    avg = sum / number;
    return (int)avg;
  }else{
    if(arr[0] < arr[1]){
      min = arr[0]; max = arr[1];
    }else{
      min = arr[1]; max = arr[0];
    }
    for(i = 2; i < number; i++){
      if (arr[i] < min){
        sum += min;
        min = arr[i];
      }else{
        if(arr[i] > max){
          sum += max;
          max = arr[i];
        }else{
          sum += arr[i];
        }
      }
    }
    avg = sum / (number - 2);
  }
  return (int)avg;
}

//actuator--------------------------------------------------

void pHUpActuate(){
  digitalWrite(pHUpAct, LOW);
  Serial.println("pH Up ON");
  //di uji coba sesuai kebutuhan : delay, catu daya
  delay(200);
  digitalWrite(pHUpAct, HIGH);
  Serial.println("pH Up OFF");
  stirActuate();
}

void pHDownActuate(){
  digitalWrite(pHDownAct, LOW);
  Serial.println("pH Down ON");
  //di uji coba sesuai kebutuhan : delay, catu daya
  delay(200);
  digitalWrite(pHDownAct, HIGH);
  Serial.println("pH Down OFF");
  stirActuate();
}

//level--------------------------------------------------

void pHUpLevelRead(){ 
  int pHUpTemp;
  pHUpTemp = analogRead(pHUpLevel);
  pHUpLevelValue = pHUpLevelAverageArray(pHUpTemp, pHArrayLength);
  Serial.print("pH Up level value : ");
  //Serial.println(pHUpLevelValue);
  Serial.println(((float)pHUpLevelValue/1024)*100);
}

int pHUpLevelAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    pHUpLevelArray[i] = pHUpLevelArray[i-1];
    sum = sum + pHUpLevelArray[i];
  }
  pHUpLevelArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}

void pHDownLevelRead(){ 
  int pHDownTemp;
  pHDownTemp = analogRead(pHDownLevel);
  pHDownLevelValue = pHDownLevelAverageArray(pHDownTemp, pHArrayLength);
  Serial.print("pH Down level value : ");
  //Serial.println(pHDownLevelValue);
  Serial.println(((float)pHDownLevelValue/1024)*100);
}

int pHDownLevelAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    pHDownLevelArray[i] = pHDownLevelArray[i-1];
    sum = sum + pHDownLevelArray[i];
  }
  pHDownLevelArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}
