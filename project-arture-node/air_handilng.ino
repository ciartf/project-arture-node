//actuator--------------------------------------------------

void airPumpActuate(){
  if(millis() - airActingTime > airActingInterval){
    digitalWrite(airPumpAct, LOW);
    Serial.println("air ON");
    //disesuaikan proposal
    delay(200);
    digitalWrite(airPumpAct, HIGH);
    Serial.println("air OFF");
    airActingTime = millis();
  }
}
