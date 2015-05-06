/**
* @author - Hovig Ohannessian
* @date   - 25-Mar-15
* xbee module #2
*/
int buzzer = 11;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() == 0);
    if(Serial.read() == 'H') {
      digitalWrite(buzzer, HIGH);
      delay(3000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
}
