#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------------
// PINES
// -------------------------

const int boton1 = 2;
const int boton2 = 3;
const int boton3 = 4;

const int rele1 = 8;
const int rele2 = 9;
const int rele3 = 10;

const int ledBtn1 = 5;
const int ledBtn2 = 6;
const int ledBtn3 = 7;

const int ledGeneral = 11;
const int ledSiempre = 12;
const int buzzer = 13;

// -------------------------
// CONTROL
// -------------------------

bool ocupado = false;
unsigned long inicio = 0;
unsigned long duracion = 0;
int botonActivo = 0;

// -------------------------
// EFECTO LLUVIA
// -------------------------

unsigned long tiempoLluvia = 0;
int pasoLluvia = 0;
int intervaloLluvia = 150;

// -------------------------
// SETUP
// -------------------------

void setup() {

  Serial.begin(9600);

  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);
  pinMode(boton3, INPUT_PULLUP);

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);

  pinMode(ledBtn1, OUTPUT);
  pinMode(ledBtn2, OUTPUT);
  pinMode(ledBtn3, OUTPUT);

  pinMode(ledGeneral, OUTPUT);
  pinMode(ledSiempre, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Relés apagados (activo en LOW)
  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);

  digitalWrite(ledGeneral, LOW);
  digitalWrite(ledSiempre, HIGH);

  // LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Dispensador");

  lcd.setCursor(0, 1);
  lcd.print("Listo");
}

// -------------------------
// FUNCIONES
// -------------------------

void beepDoble() {

  for (int i = 0; i < 2; i++) {
    digitalWrite(buzzer, HIGH);
    delay(120);
    digitalWrite(buzzer, LOW);
    delay(120);
  }
}

void apagarTodo() {

  digitalWrite(rele1, HIGH);
  digitalWrite(rele2, HIGH);
  digitalWrite(rele3, HIGH);

  digitalWrite(ledGeneral, LOW);

  digitalWrite(ledBtn1, LOW);
  digitalWrite(ledBtn2, LOW);
  digitalWrite(ledBtn3, LOW);

  botonActivo = 0;

  beepDoble();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Listo");

  ocupado = false;
}

void efectoLluvia() {

  if (millis() - tiempoLluvia >= intervaloLluvia) {

    tiempoLluvia = millis();

    digitalWrite(ledBtn1, LOW);
    digitalWrite(ledBtn2, LOW);
    digitalWrite(ledBtn3, LOW);

    if (pasoLluvia == 0) digitalWrite(ledBtn1, HIGH);
    if (pasoLluvia == 1) digitalWrite(ledBtn2, HIGH);
    if (pasoLluvia == 2) digitalWrite(ledBtn3, HIGH);

    pasoLluvia++;

    if (pasoLluvia > 2) {
      pasoLluvia = 0;
    }
  }
}

void encenderLedSeleccionado() {

  digitalWrite(ledBtn1, botonActivo == 1);
  digitalWrite(ledBtn2, botonActivo == 2);
  digitalWrite(ledBtn3, botonActivo == 3);
}
// FUNCIÓN PRINCIPAL DE SERVIDO

void servirBebida(int num) {

  ocupado = true;
  botonActivo = num;

  encenderLedSeleccionado();

  inicio = millis();
  duracion = 4000;

  digitalWrite(ledGeneral, HIGH);

  lcd.clear();

  if (num == 1) {

    // Motor 1 + Motor 2
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, LOW);

    lcd.print("M1 + M2");
  }

  if (num == 2) {

    // Motor 1 + Motor 3
    digitalWrite(rele1, LOW);
    digitalWrite(rele3, LOW);

    lcd.print("M1 + M3");
  }

  if (num == 3) {

    // Motor 2 + Motor 3
    digitalWrite(rele2, LOW);
    digitalWrite(rele3, LOW);

    lcd.print("M2 + M3");
  }
}
// -------------------------
// LOOP
// -------------------------

void loop() {

  // Animación
  if (!ocupado) {
    efectoLluvia();
  }

  // BLUETOOTH (ESP32)
  if (Serial.available()) {

    char comando = Serial.read();

    Serial.print("Recibido: ");
    Serial.println(comando);

    if (!ocupado) {

      if (comando == '1') servirBebida(1);
      if (comando == '2') servirBebida(2);
      if (comando == '3') servirBebida(3);
    }
  }

  // 🔘 BOTONES FÍSICOS
  if (!ocupado && digitalRead(boton1) == LOW) {
    servirBebida(1);
  }

  if (!ocupado && digitalRead(boton2) == LOW) {
    servirBebida(2);
  }

  if (!ocupado && digitalRead(boton3) == LOW) {
    servirBebida(3);
  }

  // TIEMPO
  if (ocupado && (millis() - inicio >= duracion)) {
    apagarTodo();
  }
}