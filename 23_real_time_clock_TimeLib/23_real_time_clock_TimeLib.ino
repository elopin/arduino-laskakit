#include <LiquidCrystal_I2C.h> // lib for LCD with I2C interface
#include <Wire.h>              // lib for I2C interface
#include <RtcDS1302.h>         // lib for Real Time Clock based on DS1302
#include <TimeLib.h>           // lib for Time and Date functions


ThreeWire myWire(3, 4, 2);          // define I2C with IO = data, SCLK = clock interval, CE = reset
RtcDS1302<ThreeWire> Rtc(myWire);   // define RTC device with I2C settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // define LCD device with (address, row length, row count)

void setup() {
  Serial.begin(9600); 

  lcd.init();      // init lcd
  lcd.backlight(); // turn baklight on

  Rtc.Begin();                                      // init RTC
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__)); // set date and time of this sketch compilation
  
  lcd.print("RTC active");
  delay(500);
  lcd.clear();

  setSyncProvider(getSyncProvider);  // define datetime provider for TimeLib, must be function returning time_t
  setSyncInterval(5);                // every five second will TimeLib update its internal datetime   
  Serial.print("TimeLib Synced");
}

// RTC datetime provider for TimeLib
time_t getSyncProvider() {
  return Rtc.GetDateTime().Unix64Time();
}

void loop() {

  // show time on first line
  lcd.setCursor(3, 0);
  print2digits(hour());
  lcd.print(":");
  print2digits(minute());
  lcd.print(":");
  print2digits(second());

  // show short day of week on second line
  lcd.setCursor(0, 1);
  lcd.print(dayShortStr(weekday()));

  // show date on second line
  lcd.setCursor(5, 1);
  lcd.print(" ");
  print2digits(day());
  lcd.print(".");
  print2digits(month());
  lcd.print(".");
  lcd.print(year());
  
  delay(1000);
}


void print2digits(int number) {
  // add zero before 0 - 9
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}
