# 🍸 LA MÁQUINA DEL PECADO 3000

### *"La dispensadora que convierte tu cocina en un antro con luz propia."*

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-Bluetooth-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Bluetooth](https://img.shields.io/badge/Bluetooth-Dispensador-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![Pecaminosa](https://img.shields.io/badge/100%25-Pecaminosa-FF69B4?style=for-the-badge)
![Estado](https://img.shields.io/badge/Estado-Funcionando%20(alguien%20mejore%20la%20letra)-green?style=for-the-badge)

```
   ________________________
  |  ____________________  |
  | |  SIRVIENDO PECADO  | |
  | |____________________| |
  |  __  __  __  __  __  | |
  | |__||__||__||__||__| | |
  |     (  ) (  ) (  )    | |
  |     |  | |  | |  |    | |
  |     |  | |  | |  |    | |
  |     |  | |  | |  |    | |
  |  ___|__|_|__|_|__|__  | |
  | |  3 SEÑORITAS       | |
  | |  LLENÁNDOSE        | |
  | |____________________| |
  |________________________|
      ||  ||  ||  ||
      ||  ||  ||  ||
      ----  ----  ----
```

---

## 📖 ¿Qué es esto?

¿Alguna vez quisiste un bar en tu casa pero no tenías espacio ni para el mini-fridge?
¿Alguna vez quisiste servirte un trago sin levantarte del sillón, pero el único que te
ayuda es el perro y él no sabe hacer cocteles?

**La Máquina del Pecado 3000** nace de esa crisis existencial (y etílica).

Es una **dispensadora automática de 3 bebidas** construida con lo que había en el
cajón del desorden: un Arduino Uno, un ESP32, unos relés que sobraban, un LCD que
tiraba el polvo y un buzzer que nadie sabía por qué estaba ahí.

Tú le pegas al botón (o le hablas por Bluetooth), y la máquina hace magia:
activa los motores, hace un beep doble de ceremonia y te sirve el pecado en 4
segundos exactos. Ni uno más, ni uno menos. Como debe ser.

## ✨ Características

- 🎛️ **3 botones físicos** con LED propio (los que brillan en sequía, luego en lluvia).
- 🔥 **3 relés que funcionan en pares**: M1+M2, M1+M3, M2+M3 — puro caos controlado.
- 🌧️ **Efecto lluvia**: cuando la máquina está "libre", los LEDs hacen secuencia de
  lluvia zen. Sí, es tan profundo como suena.
- 📟 **LCD 16x2** que te dice "Dispensador / Listo" y luego las combinaciones servidas.
- 🔔 **Buzzer con beep doble**: el "brindis" sonoro de cada servido. Sin brindis, no es pecado.
- 🎵 **Control por Bluetooth** vía ESP32: prendes tu celular, mandas `1`, `2` o `3` y
  la máquina obedece de inmediato. ¡La tecnología nos lleva al antro!
- 🔒 **Bloqueo anti-doble-servido**: mientras está ocupada, no te deja servir otra.
  La conciencia moral de la máquina.

## 🔩 Materiales

| Componente          | Cantidad | Descripción                                          |
|---------------------|:--------:|------------------------------------------------------|
| Arduino Uno         | 1        | El cerebro. Se despierta con la idea.                |
| ESP32               | 1        | El traductor Bluetooth. Hace que el celular y la máquina se entiendan. |
| Relé 2 canales      | 2        | Los guardias que abren la puerta del pecado.         |
| LCD 16x2 I2C        | 1        | El periodista que anuncia lo que se está sirviendo.  |
| Botones             | 3        | El acelerador del vicio.                             |
| LEDs                | 5        | Iluminación perfecta para el after.                  |
| Buzzer              | 1        | La campana de la victoria.                           |
| Motores (bombas)    | 3        | Los homies que empujan la bebida.                    |
| Cable y estaño      | mucho    | La maza, como toda obra de arte.                     |

## 🔌 Mapa de pines (Arduino Uno)

| Señal          | Pin | Notas                                    |
|----------------|:---:|------------------------------------------|
| **boton1**     | 2   | INPUT_PULLUP — punto 1 del vicio         |
| **boton2**     | 3   | INPUT_PULLUP — punto 2 del vicio         |
| **boton3**     | 4   | INPUT_PULLUP — punto 3 del vicio         |
| **ledBtn1**    | 5   | Luz de espera del botón 1                |
| **ledBtn2**    | 6   | Luz de espera del botón 2                |
| **ledBtn3**    | 7   | Luz de espera del botón 3                |
| **rele1**      | 8   | Motor 1 (activo en **LOW**, ¡ojo!)       |
| **rele2**      | 9   | Motor 2 (activo en LOW)                  |
| **rele3**      | 10  | Motor 3 (activo en LOW)                  |
| **ledGeneral** | 11  | Luz de fiesta = máquina sirviendo        |
| **ledSiempre** | 12  | Ambience eterno (nunca se apaga)         |
| **buzzer**     | 13  | El himno de la dispensadora              |
| **LCD I2C**    | A4/A5 (SDA/SCL) | Pantalla del chisme                |

### 🧠 Combinaciones de servido

| Botón | Combinación | Muestra en LCD | El resultado                |
|:-----:|:-----------:|:--------------:|-----------------------------|
| 1     | Motor 1 + 2 | `M1 + M2`      | Una dosis de pecado         |
| 2     | Motor 1 + 3 | `M1 + M3`      | El clásico de la casa       |
| 3     | Motor 2 + 3 | `M2 + M3`      | La confesión al tercer botón |

> **⚠️ Atención:** los relés son **activos en LOW**. Si los conectas distinto y
> se enciende el show antes de tiempo, no decimos que fue la máquina.

## 🚀 ¿Cómo se sirve el pecado?

1. La máquina está en modo **"Lluvia"**: sus LEDs titilan melancólicamente.
2. Tú presionas un botón (o mandas `1`, `2`, `3` por Bluetooth).
3. ¡`ocupado = true`! Los relés de la combinación se activan, el `ledGeneral`
   prende como baliza de fiesta, y el LCD confiesa la combinación.
4. El servido dura **4000 ms** exactos. Ni un milisegundo de misericordia.
5. Suena el **beep doble** de victoria, todo se apaga, y el LCD vuelve a decir "Listo".
6. Repite hasta que la conciencia (o el hígado) diga basta.

## 📱 Modo Bluetooth (ESP32)

El ESP32 es el cartero entre tu celular y la máquina:

- Nombre del dispositivo: **`Dispensador`** 🔵
- Baud del puerto serie a la máquina: `9600`
- Comandos: `'1'`, `'2'`, `'3'` — cada uno dispara su combinación.

```cpp
if (SerialBT.available()) {
  char dato = SerialBT.read();
  if (dato == '1' || dato == '2' || dato == '3') {
    ArduinoSerial.write(dato);  // el cartero entrega el pecado
  }
}
```

## 🛠️ Instalación

**Librerías que debes tener en el Arduino IDE:**

| Librería               | ¿Para qué?                    |
|------------------------|-------------------------------|
| `Wire.h`               | Viene en el IDE. El que paga el cable I2C. |
| `LiquidCrystal_I2C.h`  | Pa' reventar el LCD.          |
| `BluetoothSerial.h`    | Viene con la placa ESP32 (Board Manager: `esp32` by Espressif). |

**Pasos (versión "que funcione de volada"):**

1. Clona el repo:
   ```bash
   git clone git@github.com:Ulises-Gtz-Mtz/MaquinaDispensadora_MaquinaDelPecado3000.git
   ```
2. Abre `Maquina_del_PecadoArduino.ino` en el Arduino IDE y súbelo a tu Uno.
3. Instala el soporte ESP32 (`esp32`), abre `Maquina_del_PecadoESP32.ino`,
   pínchalo a tu ESP32 y súbelo.
4. Conecta el ESP32 al Arduino (TX/RX con su tierra bien puesta, no seas salvaje).
5. Prende, toma tu bebida favorita, y que empiece el espectáculo.

## ⚖️ Disclaimer del siglo

> Esta máquina no se hace responsable de: noches que "se iban a quedar a la casa",
> karaoke improvisado, confesiones a las 3 a.m., ni de que tu cuarto roomie diga
> "ya no me sirvas otra". Úsese con moderación. El pecado, servido con responsabilidad.
>
> Si la desarmas, no es culpa de nadie más. No rifiragues el código.

## 🥂 Contribuciones

¿Tienes una idea para que la máquina también haga el ice breaker o llame un Uber?
Haz un PR. El pecado siempre acepta más socios.

---

*Hecho con demasiado cariño (y minimización de resaca) por*
**[Ulises](https://github.com/Ulises-Gtz-Mtz)** 🎸