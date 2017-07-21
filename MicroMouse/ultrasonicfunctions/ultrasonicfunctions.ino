const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
void setup() {
pinMode(trigger1, OUTPUT);
pinMode(echo1, INPUT);
pinMode(trigger2, OUTPUT);
pinMode(echo2, INPUT);
pinMode(trigger3, OUTPUT);
pinMode(echo3, INPUT);
Serial.begin(9600);
}

void loop() {
  if (pulseRight() > 20){
    Serial.println("Can turn RIGHT and engage BOTH or ONE motor.");
  }
  if (pulseLeft() > 20){
    Serial.println("Can turn LEFT and engage BOTH or ONE motor.");
  }
  if (pulseMiddle() > 20){
    Serial.println("Can move FORWARD and engage BOTH motors.");
  }
  delay(500);
}

int pulseRight() {
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);

  //Read the echo pin
  duration = pulseIn(echo1, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Right distance: "); Serial.println(distance);
  return distance;
}

int pulseLeft() {
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  //Read the echo pin
  duration = pulseIn(echo2, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Left distance: "); Serial.println(distance);
  return distance;
}

int pulseMiddle() {
  digitalWrite(trigger3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3, LOW);

  //Read the echo pin
  duration = pulseIn(echo3, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Middle distance: "); Serial.println(distance);
  return distance;
}
