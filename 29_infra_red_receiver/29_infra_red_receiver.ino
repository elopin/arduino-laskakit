#include <IRremote.hpp>

int irPin = 8;    // IR pin
int ledPin = 13;  // built led pin

int code = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(irPin, false);
}

void loop() {

  if (IrReceiver.decode()) {  // if data received
    code = IrReceiver.decodedIRData.command;
    Serial.print("IR code: ");
    Serial.print(code);
    Serial.print(", bits: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();// wait for next data
  };
  delay(500);
                    
  if (code == 21) {  // code of "Play"
    digitalWrite(ledPin, HIGH);     // LED on
  } else {
    digitalWrite(ledPin, LOW);  // LED off
  }
}
