#include <Servo.h>

Servo scanServo;
int angle;

int getTFMiniDistance() {
  while (Serial1.available() >= 9) {
    if (Serial1.read() == 0x59) {
      if (Serial1.read() == 0x59) {
        int low  = Serial1.read();
        int high = Serial1.read();
        int dist = low + (high << 8);
        for (int i = 0; i < 5; i++) Serial1.read();
        return dist;
      }
    }
  }
  return -1;
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  scanServo.attach(9);
  Serial.println("Setup complete");
}

void loop()
{
  for (angle = 0; angle <= 180; angle += 2)
  {
    scanServo.write(angle);
    delay(100);

    int dist = getTFMiniDistance();

    if (dist > 0) {
      float rad = angle * 3.14159 / 180.0;
      float x = dist * cos(rad);
      float y = dist * sin(rad);

      Serial.print(dist);
      Serial.print(",");
      Serial.println(angle);
    }
  }
}