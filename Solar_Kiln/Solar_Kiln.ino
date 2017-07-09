//code to use the AM2301/DHT11 sensor with the CC3200
//Start length: .8-20mSec
//0 high length: 22-30uSec
//1 high length: 68-75uSec
#define AM2301 8
#define dataLength 40
long dataTime[dataLength];
bool data[dataLength];

void setup() {
  Serial.begin(115200);
  pinMode(AM2301, OUTPUT);
  digitalWrite(AM2301, HIGH); 
  Serial.println("Begin");

}

void loop() {
  //data read loop
  Serial.println("requesting data");
  digitalWrite(AM2301,LOW);
  delay(2);
  pinMode(AM2301, INPUT);
  delayMicroseconds(150);
  for (int i = 0; i < dataLength; i++) {
    dataTime[i] = pulseIn(AM2301, HIGH);
  }
  //data decode loop
  for (int i = 0; i < dataLength; i++) {
    if (dataTime[i] >= 67) data[i] = 1;
    if (dataTime[i] <= 31) data[i] = 0;
    Serial.print(data[i]);
    }
   delay(5000);
}
