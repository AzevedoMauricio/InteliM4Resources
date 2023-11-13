#include <EEPROM.h>

long previousMillis = 0;
long interval = 1000;
int timeControl = 0;
int led[4] = {12, 14, 27, 26}; // Respectivamente: Azul, Vermelho, Verde, Amarelo
int but[5] = {4, 16, 18, 19, 15}; // Respectivamente: Azul, Vermelho, Verde, Amarelo, RESET
int sequence[100];
int countGame = 0;
int countInput = 0;
int maxScore = EEPROM.read(0);
boolean play = true;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(but[i], INPUT);
  }
  randomSeed(analogRead(0));
  score();
  start();
}

void loop() {
  unsigned long currentMillis = millis();

  if (digitalRead(15) == 1) {
    delay(200);
    blinkLeds(8, 150);
    score();
    delay(3000);
    start();
  }

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    timeControl++;
    if (timeControl >= 10) {
      start();
    }
  }

  if (play == true) {
    game();
  } else {
    player();
  }
}

void game() {
  countGame++;
  sequence[countGame] = random(4);
  for (int i = 1; i <= countGame; i++) {
    digitalWrite(led[sequence[i]], HIGH);
    delay(400);
    digitalWrite(led[sequence[i]], LOW);
    delay(150);
  }
  play = false;
}

void player() {
  int input = 4;
  int t = 300;

  for (int b = 0; b < 4; b++) {
    if (digitalRead(but[b]) == 1) {
      digitalWrite(led[b], HIGH);
      delay(t);
      input = b;
    }
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(led[i], LOW);
  }

  if (input != 4) {
    timeControl = 0;
    countInput++;
    if (sequence[countInput] != input) {
      delay(t);
      blinkLeds(8, 150);
      score();
      delay(3000);
      start();
    } else if (countInput == countGame) {
      countInput = 0;
      play = true;
      delay(t);
      blinkLeds(1, 1000);
    }
  }
}

void start() {
  countGame = 0;
  countInput = 0;
  timeControl = 0;
  play = true;

  for (int i = 0; i < 15; i++) {
    int x = random(4);
    digitalWrite(led[x], HIGH);
    delay(20);
    digitalWrite(led[x], LOW);
    delay(100);
  }

  for (int y = 0; y < 3; y++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(led[i], LOW);
      delay(80);
    }
    for (int i = 0; i < 4; i++) {
      digitalWrite(led[i], HIGH);
      delay(80);
    }
  }
  delay(1000);

  for (int i = 0; i < 4; i++) {
    digitalWrite(led[i], LOW);
  }
  delay(1000);
}

void blinkLeds(int qtd, int t) {
  for (int y = 0; y < qtd; y++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(led[i], HIGH);
    }
    delay(t);
    for (int i = 0; i < 4; i++) {
      digitalWrite(led[i], LOW);
    }
    delay(t);
  }
}

void score() {
  if (maxScore > 100) {
    EEPROM.write(0, 0);
    maxScore = 0;
  }
  if (countGame - 1 > maxScore) {
    EEPROM.write(0, countGame - 1);
    maxScore = countGame - 1;
    for (int i = 0; i < 100; i++) {
      digitalWrite(led[0], HIGH);
      delay(50);
      digitalWrite(led[0], LOW);
      delay(50);
    }
  } else if (digitalRead(but[0]) == 1) {
    for (int i = 0; i < maxScore; i++) {
      digitalWrite(led[0], HIGH);
      delay(500);
      digitalWrite(led[0], LOW);
      delay(500);
    }
    delay(1000);
    if (digitalRead(but[0]) == 1) {
      EEPROM.write(0, 0);
      maxScore = 0;
    }
  }
}

//Grande parte da lógica eu peguei feita