
int xPin = A0;      // x coordinate pin
int yPin = A1;      // y coordinate pin
int buttonPin = 8;  // button pin

void setup() {
  pinMode(buttonPin, INPUT);      // set button
  digitalWrite(buttonPin, HIGH);  // turn pullup on
  Serial.begin(9600);
}

void loop() {
  Serial.print("X: ");
  // write x coordinate in decimal
  Serial.print(analogRead(xPin), DEC);
  Serial.print("|Y: ");
  // write y coordinate in decimal
  Serial.print(analogRead(yPin), DEC);
  Serial.print("|Z: ");
  // write push button
  Serial.println(digitalRead(buttonPin));
  delay(500);
}
