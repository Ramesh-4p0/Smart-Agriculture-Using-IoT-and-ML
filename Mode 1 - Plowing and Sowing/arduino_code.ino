#include <Servo.h>

int in1 = 3, in2 = 4, in3 = 5, in4 = 6;
int reset = 9;
int pl = 0, so = 0;

Servo plow;
// Servo sow;
int pos = 0;

void setup() {
  plow.attach(11);
  // sow.attach(10);

  pinMode(13, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(2, INPUT);
  pinMode(12, INPUT);

  pinMode(10, INPUT);
  // pinMode(1, INPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(11, LOW);
}

void loop() {
  delayMicroseconds(1);

  int x = digitalRead(13);
  int y = digitalRead(8);
  int z = digitalRead(7);
  int a = digitalRead(2);
  int s = digitalRead(12);

  int pl = digitalRead(10);
  // int so = digitalRead(1);

  // delay(2000);
  // Serial.println(pl);
  // Serial.println(so);


  if (x == HIGH) {
    Serial.println("front");
    //digitalWrite(en1,HIGH);
    //digitalWrite(en2,HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    plowing(pl);

    //   front
  } else if (y == HIGH) {
    Serial.println("back");
    //       digitalWrite(en1,HIGH);
    //digitalWrite(en2,HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    plowing(pl);

    //   back
  } else if (z == HIGH) {
    Serial.println("right");
    //     digitalWrite(en1,HIGH);
    //digitalWrite(en2,HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    plowing(pl);

    //   right
  } else if (a == HIGH) {
    Serial.println("left");
    //       digitalWrite(en1,HIGH);
    //digitalWrite(en2,HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    plowing(pl);

    //   left
  } else if (s == HIGH) {
    Serial.println("stop");
    //       digitalWrite(en1,HIGH);
    //digitalWrite(en2,HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(reset, HIGH);

    plowing(pl);

    // stop
  }
}

int plowing(int pl) {
  if (pl == HIGH) {
    Serial.println("plow");
    for (pos = 0; pos <= 180; pos += 1) {
      plow.write(pos);
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      plow.write(pos);
      delay(15);
    }
  }
}
