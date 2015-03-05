#include <RFduinoBLE.h>

int led = 2;
int buttonHit = 3;
int buttonMiss = 4;
int buttonIsland = 5;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(led, OUTPUT);
  pinMode(buttonHit, INPUT);
  pinMode(buttonMiss, INPUT);
  pinMode(buttonIsland, INPUT);
  RFduinoBLE.deviceName = "BrewmasterHank";
  RFduinoBLE.advertisementInterval = 675;
  RFduino_pinWakeCallback(buttonHit, LOW, buttonWakeCallbackHit);
  RFduino_pinWakeCallback(buttonMiss, LOW, buttonWakeCallbackHit);
  RFduino_pinWakeCallback(buttonIsland, LOW, buttonWakeCallbackHit);
  digitalWrite(led, LOW);
  RFduinoBLE.begin();
  Serial.begin(9600);
}

void loop() {
//  Serial.println(analogRead(buttonHit));
//  delay(500);
  RFduino_ULPDelay(INFINITE);
}

long lastCallbackTime = 0;
long callbackDelay = 250;

int buttonWakeCallbackHit(uint32_t pin){
  if(millis() - lastCallbackTime > callbackDelay){
    int hit = digitalRead(buttonHit);
    int miss = digitalRead(buttonMiss);
    int isle = digitalRead(buttonIsland);
    if(hit == LOW){
      RFduinoBLE.send(0);
    } else if (miss == LOW) {
      RFduinoBLE.sendInt(1);
    } else if (isle == LOW){
      RFduinoBLE.sendInt(2);
    }
    lastCallbackTime = millis();
    Serial.println(lastCallbackTime);
  }
  return 0;
}

void RFduinoBLE_onReceive(char *data, int len){
  Serial.println("Received: "+data[0]);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}
