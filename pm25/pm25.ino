#include "PMS.h"

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);
PMS::DATA data;

#define RXD2 23
#define TXD2 22

// ESP32 --> Pantower PMS7003   
// 22    --> RX
// 23    --> TX 
// GND   --> GND

void setup()
{
  Serial.begin(9600);
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);

}

void loop()
{
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }

  // Do other stuff...
}
