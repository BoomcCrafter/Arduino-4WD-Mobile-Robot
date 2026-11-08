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

const int TRIG_LEFT = A0;
const int ECHO_LEFT = A1;

const int TRIG_RIGHT = A2;
const int ECHO_RIGHT = A3;

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

float odleglosc(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long czas = pulseIn(echo, HIGH, 30000);

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

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  digitalWrite(L_REN, HIGH);
  digitalWrite(L_LEN, HIGH);
  digitalWrite(R_REN, HIGH);
  digitalWrite(R_LEN, HIGH);

  delay(2000);
}

void loop() {
  float przod = odleglosc(TRIG_FRONT, ECHO_FRONT);

  if (przod > 30) {
    silniki(140, 140);
    delay(80);
    return;
  }

  silniki(0, 0);
  delay(300);

  float lewo = odleglosc(TRIG_LEFT, ECHO_LEFT);
  delay(70);

  float prawo = odleglosc(TRIG_RIGHT, ECHO_RIGHT);
  delay(70);

  if (lewo > prawo) {
    silniki(-145, 145);
    delay(600);
  } else {
    silniki(145, -145);
    delay(600);
  }

  silniki(0, 0);
  delay(200);
}