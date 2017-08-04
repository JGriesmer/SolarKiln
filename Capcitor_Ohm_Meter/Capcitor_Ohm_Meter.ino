
//calulations for how much resistance something has using a capacitor
//  tau = F*Ohms
//  tau/F = Ohms
#define capSens 10
#define startPin 11
#define uF 100
unsigned long tau;
unsigned long ohm;
void setup() {
  Serial.begin(115200);
  pinMode(capSens, INPUT_PULLDOWN);
  pinMode(startPin, OUTPUT);

}

void loop() {
   digitalWrite(startPin, HIGH);
   tau = pulseIn(capSens,HIGH);
   digitalWrite(startPin,LOW);
   Serial.println(tau);
   ohm = tau / uF;
   Serial.println(ohm);
   delay(5000);
   
   
}
