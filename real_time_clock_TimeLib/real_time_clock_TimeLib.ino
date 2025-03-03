#include <LiquidCrystal_I2C.h>
#include <RtcDS1302.h>
#include <TimeLib.h>
#include <Wire.h>

ThreeWire myWire(3, 4, 2);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  Rtc.Begin();
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  }

  lcd.print("RTC aktivovan");
  delay(500);
  lcd.clear();

  setSyncProvider(getSyncProvider);
  setSyncInterval(5);
  Serial.print("TimeLib Synced");
}

time_t getSyncProvider() {
  return Rtc.GetDateTime().Unix64Time();
}

void loop() {


  Serial.println("RCT Times: ");
  time_t unixTime = Rtc.GetDateTime().TotalSeconds64() + c_UnixEpoch32;
  Serial.println(unixTime);
  unsigned long unix64time = Rtc.GetDateTime().Unix64Time();
  Serial.println(unixTime);
  Serial.println(Rtc.GetDateTime().Day());
  Serial.println(Rtc.GetDateTime().Month());
  Serial.println(Rtc.GetDateTime().Year());

  Serial.println("--------------------");
  Serial.println("From TimeLib Day: ");
  Serial.println(dayStr(weekday()));
  Serial.println(day());
  Serial.println(month());
  Serial.println(year());
  Serial.println(now());
  Serial.println("--------------------");

  tmElements_t te;
  breakTime(unixTime, te);

  Serial.println("Time from elements:");
  Serial.println(te.Day);
  Serial.println(te.Month);
  Serial.println(tmYearToCalendar(te.Year));
  Serial.println("---------------------");


  // zobrazit čas na displeji
  lcd.setCursor(3, 0);
  print2digits(hour());
  lcd.print(":");
  print2digits(minute());
  lcd.print(":");
  print2digits(second());

  // zobrazit den v týdnu
  lcd.setCursor(0, 1);
  lcd.print(dayShortStr(weekday()));

  // zobrazit datum
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
  // přidaní "0" u čísel do 10
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}
