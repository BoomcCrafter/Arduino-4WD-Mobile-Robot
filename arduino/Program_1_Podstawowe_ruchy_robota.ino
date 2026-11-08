const int L_RPWM = 9;
const int L_LPWM = 10;
const int L_REN = 11;
const int L_LEN = 12;

const int R_RPWM = 3;
const int R_LPWM = 5;
const int R_REN = 2;
const int R_LEN = 4;

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

void setup() {
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(L_REN, OUTPUT);
  pinMode(L_LEN, OUTPUT);

  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);
  pinMode(R_REN, OUTPUT);
  pinMode(R_LEN, OUTPUT);

  digitalWrite(L_REN, HIGH);
  digitalWrite(L_LEN, HIGH);
  digitalWrite(R_REN, HIGH);
  digitalWrite(R_LEN, HIGH);

  delay(2000);
}

void loop() {
  silniki(80, 80);
  delay(2000);

  silniki(140, 140);
  delay(2000);

  silniki(210, 210);
  delay(2000);

  silniki(80, 160);
  delay(1500);

  silniki(160, 80);
  delay(1500);

  silniki(-150, 150);
  delay(1000);

  silniki(150, -150);
  delay(1000);

  silniki(0, 0);
  delay(3000);
}