#include <SoftwareSerial.h>  //using software serial so as not to conflict with serial download
#include <Wire.h>
#include "AHT20.h"

SoftwareSerial hubConnection(7, 8);  // RX, TX
AHT20 AHT;

void setup() {
  hubConnection.begin(9600);
  Serial.begin(115200);  // debug

  AHT.begin();
}

void loop() {
  float humi, temp;

  int ret = AHT.getSensor(&humi, &temp);

  if (ret)  // GET DATA OK
  {
    Serial.print("humidity: ");
    Serial.print(humi * 100);
    Serial.print("%\t temerature: ");
    Serial.println(temp);

    int humi1 = humi * 10000;
    int temp1 = temp * 100;
    hubConnection.print(humi1);
    hubConnection.print(" ");
    hubConnection.println(temp1);

  } else  // GET DATA FAIL
  {
    Serial.println("GET DATA FROM AHT20 FAIL");
  }

  delay(100);
}

// END FILE