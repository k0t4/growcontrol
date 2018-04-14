

// VERSION_3.01 ===================> GrowControl
// Estable con 3 dth22, 2 ds18b20, 2 higrometros, 1 reloj ds3231, 1 LDR
// Creado 11 de abril 2018 AMDG.

// Instrucciones:
// Cambiar la version en el número de la pantalla del final del código para que coincida con el nombre del archivo.
// Si se añaden sensores en el loop, hay que añadirlos también en la confi de la pantalla.

#include <Arduino.h>

#include "pantalla.h"

#include "rele1.h"

// PARA VER QUE FUNCIONA ARDUINO MEGA
const int ledPin = 13;  //LDR sensor LUZ


void setup(){

    pinMode(ledPin, OUTPUT);  //LED PIN 13 FUNCIONAMIENTO
    digitalWrite(ledPin, HIGH);  //LED PIN 13 FUNCIONAMIENTO
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    delay(3000); // wait for console opening

    vsDS18B20();
    vsDTH();
    vsRELOJ3231();
    vsPANTALLA();

    vsRele1();

}


void loop()
{

  vlPANTALLA();
  vlDS18B20();
  vlDTH();
  vlHIGROMETROS();
  vlLDR();

  vlRele1();


}
