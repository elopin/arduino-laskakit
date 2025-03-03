#include <LiquidCrystal_I2C.h>
#include <RtcDS1302.h>
#include <DateTimeFunctions.h>
#include <Wire.h>

ThreeWire myWire(3, 4, 2);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

DateTimeFunctions dtf;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  lcd.print("RTC aktivovan");
  delay(500);
  lcd.clear();

}

void loop() {

  
  RtcDateTime rtc = Rtc.GetDateTime();
  
  // zobrazit čas na displeji
  lcd.setCursor(3, 0);
  print2digits(rtc.Hour());
  lcd.print(":");
  print2digits(rtc.Minute());
  lcd.print(":");
  print2digits(rtc.Second());

  // zobrazit den v týdnu
  lcd.setCursor(0, 1);
  lcd.print(dtf.getDOWNS(rtc.DayOfWeek()));

  // zobrazit datum
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
 // přidaní "0" u čísel do 10 
 if (number >= 0 && number < 10) { 
  lcd.write('0'); 
 } 
 lcd.print(number); 
} 
