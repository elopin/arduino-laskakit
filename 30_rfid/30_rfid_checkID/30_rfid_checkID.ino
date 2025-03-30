#include <rfid1.h>

RFID1 rfid;  //RFID1 object

uchar serNum[5];  //array for serial number of rfid chip

int relayPin = 8;

void setup() {
  Serial.begin(9600);
  //setup rfid (irqPin, sckPin, mosiPin, misoPin, sdaPin, rstPin)
  rfid.begin(7, 5, 4, 3, 6, 2);
  delay(100);
  rfid.init();  //init rfid

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // relay off
}

void loop() {
  uchar status;
  uchar str[MAX_LEN];
  
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK) {
    return;
  }
  // show chip type
  rfid.showCardType(str);
  // ID bytes
  status = rfid.anticoll(str);

  if (status == MI_OK) {
    
    Serial.print("ID: ");
    memcpy(serNum, str, 5);
    rfid.showCardID(serNum);  // show ID
    Serial.println();

    // if ID chip 83651e2d, relay on
    uchar* id = serNum;
    if (id[0] == 0x83 && id[1] == 0x65 && id[2] == 0x1e && id[3] == 0x2d) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Welcome CHIP! ");
      delay(2000);
      digitalWrite(relayPin, LOW);
    }
    // if ID card 2c833403, relay on
    else if (id[0] == 0x2c && id[1] == 0x83 && id[2] == 0x34 && id[3] == 0x03) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Welcome CARD!");
      delay(2000);
      digitalWrite(relayPin, LOW);
    } else {
      Serial.println("Unknown ID!");
      delay(2000);
    }
  }
  rfid.halt();  // sleep rfid
}
