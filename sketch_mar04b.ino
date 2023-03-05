#include <Servo.h>

Servo horizontal; // horizontal servo
int servoh = 180;
int servohLimitHigh = 155;
int servohLimitLow = 25;
// 65 degrees MAX

// LDR pin connections
// name = analogpin;
int ldrt = A2; // LDR top - TOP LEFT <--- BDG
int ldrb = A1; // LDR bottom - BOTTOM LEFT

void setup() {
  Serial.begin(115200);
  horizontal.attach(9);
  horizontal.write(180);
  delay(250);
}

void loop() {
  int lt = analogRead(ldrt); // top left
  int lb = analogRead(ldrb); // bottom left
  int dtime = 10;
  int tol = 90; // tolerance
  int av = (lt + lb) / 2; // average value

  int dhoriz = lt - lb; // check the difference of left and right

  if (-1*tol > dhoriz || dhoriz > tol) { // check if the difference is in the tolerance else change horizontal angle
    if (lt > lb) {
      servoh = --servoh;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    } else if (lt < lb) {
      servoh = ++servoh;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    }
    horizontal.write(servoh);
  }
  delay(dtime);
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.print("voltage ");
  Serial.println(voltage);
//  delay(250);
}
