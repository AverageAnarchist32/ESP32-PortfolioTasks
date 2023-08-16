
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}//so we can get a whole number value from a 12bit scaling see online for other scaling versions

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin GPIO4:
  int analogValue = analogRead(4);
  // Rescale to potentiometer's voltage (from 0V to 3.3V) *we do this because it's organised into 12 bits:
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  // print out the value read in in the number range:
  Serial.print("Analog: ");
  Serial.print(analogValue);

  //Prints out the voltage corresponding to that range
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  delay(1000);
}

//credit to esp32io voltage reader