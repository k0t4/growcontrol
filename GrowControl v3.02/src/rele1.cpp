// Ventilador por rango de temperatura
#include <DHT.h>  //DTH
#include <Adafruit_Sensor.h>  //DTH
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//const int DHTPin = 5;     // what digital pin we're connected to
#define HT1 44  //DTH
const int ledRele = 2; // PWM que activa el rele para activar ventilador
const int tempmin = 23; // Rango temperatura minima
const int tempmax = 25; // Rango temperatura maxima
bool state = 0; // Ventilador activo o inactivo
//float temp1();
DHT dht11(HT1, DHTTYPE);  //DTH


void vsRele1()
{
  // Ventilador por rango de temperatura
  //dht1.begin();//Inicializamos los sensores  //DTH
  pinMode(ledRele, OUTPUT); // El pin anteriormente definido enciende el rele
}



void vlRele1()
{
  float t11 = dht11.readTemperature();
  //float currentTemperature = GetTemperature();

  if(state == 0 && t11 > tempmax)
  {
      state = 1;
      digitalWrite(ledRele, HIGH);   // encender ventilador
  }

  if(state == 1 && t11 < tempmin)
  {
      state == 0;
      digitalWrite(ledRele, LOW);   // apagar ventilador
  }
}
