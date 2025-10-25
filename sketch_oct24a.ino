#include <Servo.h>

Servo servoMotor;

int ldrPins[4] = {A0, A1, A2, A3};     // LDR connections
int servoPin = 9;                      // Servo pin
int servoPos[4] = {0, 45, 90, 110};    // Positions for each LDR

void setup() {
  Serial.begin(9600);
  servoMotor.attach(servoPin);
  servoMotor.write(90);  // Start centered
  delay(500);
}

void loop() {
  int ldrValues[4];
  int maxValue = 0;
  int maxIndex = 0;

  // Read all LDRs
  for (int i = 0; i < 4; i++) {
    ldrValues[i] = analogRead(ldrPins[i]);
    if (ldrValues[i] > maxValue) {  // move to the greatest LDR value
      maxValue = ldrValues[i];
      maxIndex = i;
    }
  }

  // Move servo toward the brightest LDR
  servoMotor.write(servoPos[maxIndex]);

  // Print readings for explanation
  Serial.print("LDRs: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(ldrValues[i]);
    Serial.print(" ");
  }
  Serial.print(" -> Light at LDR");
  Serial.println(maxIndex + 1);

  delay(200);
}
