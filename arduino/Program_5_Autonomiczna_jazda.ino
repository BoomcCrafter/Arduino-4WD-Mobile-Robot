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

const int PREDKOSC_NORMALNA = 145;

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

float pomiar(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(3);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long czas = pulseIn(echo, HIGH, 25000);

  if (czas == 0) {
    return 300;
  }

  float dystans = czas * 0.0343 / 2.0;

  if (dystans < 2 || dystans > 300) {
    return 300;
  }

  return dystans;
}

float mediana3(float a, float b, float c) {
  if ((a >= b && a <= c) || (a <= b && a >= c)) {
    return a;
  }

  if ((b >= a && b <= c) || (b <= a && b >= c)) {
    return b;
  }

  return c;
}

float odleglosc(int trig, int echo) {
  float a = pomiar(trig, echo);
  delay(25);

  float b = pomiar(trig, echo);
  delay(25);

  float c = pomiar(trig, echo);

  return mediana3(a, b, c);
}

void stopRobot() {
  silniki(0, 0);
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

  stopRobot();

  delay(2000);
}

void loop() {
  float przod = odleglosc(TRIG_FRONT, ECHO_FRONT);

  delay(60);

  float lewo = odleglosc(TRIG_LEFT, ECHO_LEFT);

  delay(60);

  float prawo = odleglosc(TRIG_RIGHT, ECHO_RIGHT);

  delay(60);

  if (przod < 18) {
    stopRobot();
    delay(250);

    silniki(-120, -120);
    delay(450);

    stopRobot();
    delay(250);

    lewo = odleglosc(TRIG_LEFT, ECHO_LEFT);
    delay(60);

    prawo = odleglosc(TRIG_RIGHT, ECHO_RIGHT);

    if (lewo > prawo) {
      silniki(-150, 150);
    } else {
      silniki(150, -150);
    }

    delay(600);

    stopRobot();
    delay(200);

    return;
  }

  if (przod < 35) {
    if (lewo > prawo + 5) {
      silniki(90, 140);
    } else if (prawo > lewo + 5) {
      silniki(140, 90);
    } else {
      silniki(110, 110);
    }

    return;
  }

  if (lewo < 18 && prawo > 18) {
    silniki(145, 95);
    return;
  }

  if (prawo < 18 && lewo > 18) {
    silniki(95, 145);
    return;
  }

  if (lewo < 25 && prawo < 25) {
    int roznica = (int)(prawo - lewo);

    int korekta = constrain(roznica * 3, -50, 50);

    int lewy = PREDKOSC_NORMALNA + korekta;
    int prawy = PREDKOSC_NORMALNA - korekta;

    silniki(lewy, prawy);

    return;
  }

  silniki(PREDKOSC_NORMALNA, PREDKOSC_NORMALNA);
}