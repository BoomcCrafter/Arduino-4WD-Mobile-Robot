const int L_RPWM = 9;
const int L_LPWM = 10;
const int L_REN = 11;
const int L_LEN = 12;

const int R_RPWM = 3;
const int R_LPWM = 5;
const int R_REN = 2;
const int R_LEN = 4;

const int TRIG_FRONT = 6;
const int ECHO_FRONT = 7;

void silniki(int lewy, int prawy) {
  lewy = constrain(lewy, -255, 255);
  prawy = constrain(prawy, -255, 255);

  if (lewy > 0) {
    analogWrite(L_RPWM, 0);
    analogWrite(L_LPWM, lewy);
  } else if (lewy < 0) {
    analogWrite(L_RPWM, -lewy);
    analogWrite(L_LPWM, 0);
  } else {
    analogWrite(L_RPWM, 0);
    analogWrite(L_LPWM, 0);
  }

  if (prawy > 0) {
    analogWrite(R_RPWM, prawy);
    analogWrite(R_LPWM, 0);
  } else if (prawy < 0) {
    analogWrite(R_RPWM, 0);
    analogWrite(R_LPWM, -prawy);
  } else {
    analogWrite(R_RPWM, 0);
    analogWrite(R_LPWM, 0);
  }
}

float odleglosc() {
  digitalWrite(TRIG_FRONT, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_FRONT, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_FRONT, LOW);

  unsigned long czas = pulseIn(ECHO_FRONT, HIGH, 30000);

  if (czas == 0) {
    return 300;
  }

  return czas * 0.0343 / 2.0;
}

void setup() {
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(L_REN, OUTPUT);
  pinMode(L_LEN, OUTPUT);

  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);
  pinMode(R_REN, OUTPUT);
  pinMode(R_LEN, OUTPUT);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  digitalWrite(L_REN, HIGH);
  digitalWrite(L_LEN, HIGH);
  digitalWrite(R_REN, HIGH);
  digitalWrite(R_LEN, HIGH);

  delay(2000);
}

void loop() {
  float przod = odleglosc();

  if (przod > 30) {
    silniki(140, 140);
  } else {
    silniki(0, 0);
  }

  delay(100);
}