#include <SoftwareSerial.h>     //using software serial so as not to conflict with serial download
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

int temp = 0;
int humi = 0;

double tempF = 0;
double humiF = 0;

TM1637Display display(CLK, DIO);
SoftwareSerial mySerial(7, 8);  // RX, TX

void setup() {

  mySerial.begin(9600);  //setup software serial
  Serial.begin(9600);    //setup serial monitor
    display.setBrightness(0x0f);
}

void loop() {

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  while (mySerial.available() == 0) {}

  humi = mySerial.parseInt();
  humiF = humi / 100.00;
  temp = mySerial.parseInt();
  tempF = temp / 100.00;


    //print received values to serial monitor
  Serial.println(tempF);

  display.showNumberDec(temp);
  delay(200);
}