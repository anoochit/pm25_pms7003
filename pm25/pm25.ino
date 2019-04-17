#include "PMS.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold24pt7b.h>

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);
PMS::DATA data;

#define RXD2 26
#define TXD2 25

// ESP32 --> Pantower PMS7003
// 26    --> RX
// 25    --> TX
// GND   --> GND

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1// Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  Serial.begin(9600);
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();

  display.setFont(&FreeSansBold24pt7b);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop()
{
  //Serial.println("Waking up, wait 30 seconds for stable readings...");
  pms.wakeUp();
  delay(3000);

  //Serial.println("Send read request...");
  pms.requestRead();

  //Serial.println("Wait max. 1 second for read...");
  if (pms.readUntil(data))
  {

//    Serial.print("PM 1.0 (ug/m3): ");
//    Serial.println(data.PM_AE_UG_1_0);
//
//    Serial.print("PM 2.5 (ug/m3): ");
//    Serial.println(data.PM_AE_UG_2_5);
//
//    Serial.print("PM 10.0 (ug/m3): ");
//    Serial.println(data.PM_AE_UG_10_0);

    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);  //Text is white ,background is black
    display.setTextSize(1);
    display.setCursor(35, 50);
    display.print(data.PM_AE_UG_2_5);
    display.display();
    delay(10000);

  }
  else
  {
    Serial.println("No data.");
  }

  //  Serial.println("Going to sleep for 60 seconds.");
  pms.sleep();
  delay(60000);

  // Do other stuff...
}
