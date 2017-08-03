//Schematic
//CC3200 VCC to Power
//33 kOhm Resistor between VCC and signal
//Signal to P62 on CC3200
//GND to GND 

//Library Includes
#include <SPI.h>
#include <WiFi.h>
#include <UbidotsCC3200.h>

//UbiDotsCode
#define TOKEN "fDmCLQ7smRI2kTKp2qgbZO0PRCV6ap"
#define Variable2 "Humidity"

Ubidots client(TOKEN);

//Wifi Stuffs
#define SSID "P7S59"
#define Pass "****"

//code to use the AM2301/DHT11 sensor with the CC3200
//Start length: .8-20mSec
//0 high length: 22-30uSec
//1 high length: 68-75uSec
#define AM2301 8
#define dataLength 40
long dataTime[dataLength];
float temp = 0;
float humidity = 0;

void setup() {
  Serial.begin(115200);
  //connect to the wifi
  client.wifiConnection(SSID, Pass);
  Serial.println("Begin");

}

void loop() {
  //reset values

  pinMode(AM2301, OUTPUT);
  digitalWrite(AM2301, HIGH);
  //data read loop
  Serial.println("requesting data");
  digitalWrite(AM2301, LOW);
  delay(2);
  pinMode(AM2301, INPUT);
  delayMicroseconds(150);
  for (int i = 0; i < dataLength; i++) {
    dataTime[i] = pulseIn(AM2301, HIGH);
  }
  //data decode loop
  temp = 0;
  humidity = 0;
  for (int i = 0; i < 16; i++) {
    humidity += ((pow(2 , (15 - i))) * ((dataTime[i] < 30) ? 0 : 1));
    temp += ((pow(2, (15 - i))) * ((dataTime[i + 16] < 30) ? 0 : 1));
    //Serial.print(dataTime[i + 16]);
    //Serial.println(temp);
  }
  humidity /= 10;
  temp /= 10;
  //Convert Celsius to Fahrenheit
  temp = (temp * 1.8) + 32;
  //Print values to the serial port
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" Temp: ");
  Serial.println(temp);
  //wait for 5 seconds. sensor maximum requests per minute is 30
  client.add("Humidity", humidity);
  client.add("Temperature", temp);
  client.sendAll();
  delay(10000);
}
