#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

HardwareSerial ArduinoSerial(2);

void setup() {

  Serial.begin(115200);

  ArduinoSerial.begin(9600, SERIAL_8N1, 16, 17);

  SerialBT.begin("Dispensador");

  Serial.println("Bluetooth listo");
}

void loop() {

  if (SerialBT.available()) {

    char dato = SerialBT.read();

    Serial.print("Recibido BT: ");
    Serial.println(dato);

    if (dato == '1' || dato == '2' || dato == '3') {

      ArduinoSerial.write(dato);
    }
  }
}