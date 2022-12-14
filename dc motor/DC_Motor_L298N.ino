int enA = 6;
int in1 = 8;
int in2 = 9;
int button1 = 4;
int button2 = 5;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), motoroff, LOW);
  attachInterrupt(digitalPinToInterrupt(3), motoroff, LOW);
}

void loop() {
  if (digitalRead(button1) == LOW) {
    foward();
  }
  else if (digitalRead(button2) == LOW) {
    reverse();
  }
}

void foward() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  // Foward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
}

void reverse() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  // Reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
}

void motoroff() {
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    delay(20);
  }

  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    delay(20);
  }

  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
