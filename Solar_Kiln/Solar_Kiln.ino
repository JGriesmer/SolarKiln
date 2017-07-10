//code to use the AM2301/DHT11 sensor with the CC3200
//Start length: .8-20mSec
//0 high length: 22-30uSec
//1 high length: 68-75uSec
#define AM2301 8
#define dataLength 40
long dataTime[dataLength];
int temp = 0;
int humidity = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Begin");

}

void loop() {
  //reset values
  temp = 0;
  humidity = 0;
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
  for (int i = 0; i < 16; i++) {
    humidity += ((2 ^ (15 - i)) * ((dataTime[i] < 40) ? 0 : 1));
    temp += ((2 ^ (15 - i)) * ((dataTime[i + 16] < 40) ? 0 : 1));
  }
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" Temp: ");
  Serial.println(temp);
  delay(5000);
}
