const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;
const int pulse_timeout_duration = 3000;
double duration;
int distance;
void setup() {
  // put your setup code here, to run once:
pinMode(trigger1, OUTPUT);
pinMode(echo1, INPUT);
pinMode(trigger2, OUTPUT);
pinMode(echo2, INPUT);
pinMode(trigger3, OUTPUT);
pinMode(echo3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulseRight();
  delay(1000);
  pulseLeft();
  pulseMiddle();
}

void pulseRight() {
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);

  //Read the echo pin
  duration = pulseIn(echo1, HIGH);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Right distance: "); Serial.println(distance);
}

void pulseLeft() {
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  //Read the echo pin
  duration = pulseIn(echo2, HIGH, pulse_timeout_duration);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Left distance: "); Serial.println(distance);
}

void pulseMiddle() {
  //Send ultrsonic sound wave
  digitalWrite(trigger3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3, LOW);

  //Read the echo pin
  duration = pulseIn(echo3, HIGH);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Middle distance: "); Serial.println(distance);
}
