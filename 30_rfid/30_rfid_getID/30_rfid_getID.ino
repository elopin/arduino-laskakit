#include <rfid1.h>

RFID1 rfid;  //RFID1 object

uchar serNum[5];  //array for serial number of rfid chip

void setup() {
  Serial.begin(9600);
  //setup rfid (irqPin, sckPin, mosiPin, misoPin, sdaPin, rstPin)
  rfid.begin(7, 5, 4, 3, 6, 2);
  delay(100);
  rfid.init();  //init rfid
}

void loop() {

  uchar status;
  uchar str[MAX_LEN];
  
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK) {
    return;
  }
  // Show chip type
  rfid.showCardType(str);
  //return bytes of chip
  status = rfid.anticoll(str);

  if (status == MI_OK) {
    Serial.print("The card's number is: ");
    memcpy(serNum, str, 5);
    rfid.showCardID(serNum);  // show chip ID
    Serial.println();
  }
  delay(500);
  rfid.halt(); // sleep chip
}
