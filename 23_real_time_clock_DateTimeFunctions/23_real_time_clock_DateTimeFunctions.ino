#include <LiquidCrystal_I2C.h> // lib for LCD with I2C interface
#include <Wire.h>              // lib for I2C interface
#include <RtcDS1302.h>         // lib for Real Time Clock based on DS1302
#include <DateTimeFunctions.h> // lib for Time and Date functions

ThreeWire myWire(3, 4, 2);          // define I2C with IO = data, SCLK = clock interval, CE = reset
RtcDS1302<ThreeWire> Rtc(myWire);   // define RTC device with I2C settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // define LCD device with (address, row length, row count)

DateTimeFunctions dtf;  // define object for date and time functions

void setup() {
  Serial.begin(9600);

  lcd.init();      // init lcd
  lcd.backlight(); // turn baklight on

  Rtc.Begin();                                      // init RTC
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__)); // set date and time of this sketch compilation

  lcd.print("RTC aktivovan");
  delay(500);
  lcd.clear();

}

void loop() {

  // get datetime from RTC
  RtcDateTime rtc = Rtc.GetDateTime();
  
  // show time on first line
  lcd.setCursor(3, 0);
  print2digits(rtc.Hour());
  lcd.print(":");
  print2digits(rtc.Minute());
  lcd.print(":");
  print2digits(rtc.Second());

  // show short day of week on second line
  lcd.setCursor(0, 1);
  lcd.print(dtf.getDOWNS(rtc.DayOfWeek()));

  // show date on second line
  lcd.setCursor(5, 1);
  lcd.print(" ");
  print2digits(rtc.Day());
  lcd.print(".");
  print2digits(rtc.Month());
  lcd.print(".");
  lcd.print(rtc.Year());
  
  delay(1000);
}

 
void print2digits(int number ) { 
 // add zero before 0 - 9
 if (number >= 0 && number < 10) { 
  lcd.write('0'); 
 } 
 lcd.print(number); 
} 
