
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin GPIO18 as an output.
  pinMode(18, OUTPUT);
  pinMode(16, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(18, HIGH); // turns the LED on by running a high voltage through the GPIO pin 18
  digitalWrite(16, HIGH);//Does the same for GPIO pin 16
  delay(500);//Delay next line by 500 milliseconds
  digitalWrite(16,LOW);//run low voltage through pin 16 turning it off due to the resistor
  delay(500);             // wait for 500 milliseconds

  digitalWrite(18, LOW);  // turn the LED connected to pin 18 off
  delay(500);             //wait 500 milliseconds
}
