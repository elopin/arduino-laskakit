#include <LiquidCrystal_I2C.h>  // lib for LCD with I2C interface
#include <Wire.h>               // lib for I2C interface
#include <DHT_U.h>              // lib for operate with DHT sensor data

LiquidCrystal_I2C lcd(0x27, 16, 2);  // define LCD device with (address, row length, row count)

DHT_Unified dht(4, DHT11);  // define object for DHT data (data pin, DHT device type)
uint32_t delayMS;           // delay between sensor data sent

void setup() {
  Serial.begin(9600);

  lcd.init();       // init lcd
  lcd.backlight();  // turn baklight on

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("°C"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("°C"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print(F("Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("%"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  lcd.setCursor(0, 0); // set lcd cursor
  // get temperature data
  sensors_event_t eventTemperature;
  dht.temperature().getEvent(&eventTemperature);
  // check temperature data available
  if (isnan(eventTemperature.temperature)) {
    lcd.print("Temp: ERROR!");
  } else {
    lcd.print("Temp: OK!");
  }
  delay(500);
  lcd.clear();

  Serial.println(eventTemperature.temperature);

  // get humidity data
  sensors_event_t eventHumidity;
  dht.humidity().getEvent(&eventHumidity);
  // check humidity data available
  if (isnan(eventHumidity.relative_humidity)) {
    lcd.print("Humid: ERROR!");
  } else {
    lcd.print("Humid: OK!");
    
  }
  delay(500);
  lcd.clear();

  // print data
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(eventTemperature.temperature, 1);  // print temperature displeji
  lcd.print(char(223));           // print sign "°"
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humid:");
  lcd.print(eventHumidity.relative_humidity, 1);  // print humidity
  lcd.print(" %");

  delay(delayMS); // wait for next sensor event
  lcd.clear();
}
