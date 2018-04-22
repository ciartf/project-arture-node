//actuator--------------------------------------------------

void stirActuate(){
  digitalWrite(stirAct, LOW);
  Serial.println("stir ON");
  //di uji coba sesuai kebutuhan : delay, catu daya
  delay(1000);
  digitalWrite(stirAct, HIGH);
  Serial.println("stir OFF");
}

