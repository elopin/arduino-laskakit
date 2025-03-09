int relayPin = 4;

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, HIGH); // turn relay on
  delay(1000);
  digitalWrite(relayPin, LOW ); // turn relay off
  delay(1000);
}
