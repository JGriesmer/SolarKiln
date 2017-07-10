//code to use the AM2301/DHT11 sensor with the CC3200
//Start length: .8-20mSec
//0 high length: 22-30uSec
//1 high length: 68-75uSec
#define AM2301 8
#define dataLength 40
long dataTime[dataLength];
double temp = 0;
double humidity = 0;

void setup() {
  Serial.begin(115200);
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
    Serial.print(dataTime[i + 16]);
    Serial.println(temp);
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
  delay(5000);
}
