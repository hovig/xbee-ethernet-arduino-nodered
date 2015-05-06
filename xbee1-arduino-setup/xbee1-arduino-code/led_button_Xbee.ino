/**
* @author - hovig ohannessian
* @date   - 25-Mar-15
* xbee module #1
*/

int buttonInput = 2;
int buttonState = 0;
int ledOutput = 13;
char readChar;


void setup() {
  Serial.begin(9600);
  pinMode(ledOutput, OUTPUT);
  pinMode(buttonInput, INPUT);
  digitalWrite(buttonInput, HIGH);
}

void loop() {
  buttonState = digitalRead(buttonInput);
  if (buttonState == HIGH) {
    digitalWrite(ledOutput, LOW);
  } else {
    Serial.print('H');
    digitalWrite(ledOutput, HIGH);
    delay(1000);
  }
}
