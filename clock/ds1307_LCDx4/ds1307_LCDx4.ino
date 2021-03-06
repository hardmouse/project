// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String d1;
String d2;

byte smiley[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup () {
  //while (!Serial); // for Leonardo/Micro/Zero
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!Serial) {
    Serial.println("...");
  }else{
    Serial.println("Pluged into PC, sync up the time to PC!");
    // following line sets the RTC to the date & time this sketch was compiled
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2017, 11, 21, 21, 48, 0));
  }
}

void loop () {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days and 30 seconds into the future
  DateTime future (now + TimeSpan(7, 12, 30, 6));

  Serial.print(" now + 7d + 30s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();

  Serial.println();

  d1 = "";
  d1 += now.year();
  d1 += "/";
  d1 += now.month();
  d1 += "/";
  d1 += now.day();
  d1 += " ";
  d1 += daysOfTheWeek[now.dayOfTheWeek()];
  d1 += "  ";

  d2 = " === ";
  d2 += now.hour();
  d2 += ":";
  d2 += now.minute();
  d2 += ":";
  d2 += now.second();
  d2 += " === ";
  lcd.setCursor(0, 0);
  lcd.print(d1);
  lcd.setCursor(0, 1);
  lcd.print(d2);
  lcd.setCursor(0, 2);
  lcd.print("=== MakerFun.ca ===");
  lcd.setCursor(0, 3);
  lcd.print(" Arduino + DS1307 ");
  delay(1000);
}
