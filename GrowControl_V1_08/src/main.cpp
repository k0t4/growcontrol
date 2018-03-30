#include <Arduino.h>

// VERSION_1_08 ===================> GrowControl
// Estable con 3 dth22, 2 ds18b20, 2 higrometros, 1 reloj ds3231
// Creado 30 de marzo 2018 AMDG.

// Instrucciones:
// Cambiar la version en el número de la pantalla del final del código para que coincida con el nombre del archivo.
// Si se añaden sensores en el loop, hay que añadirlos también en la confi de la pantalla.



// _________________________________________________________________pantalla
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

//___________________________________________________________________ds18b20
#include <OneWire.h>
#include <DallasTemperature.h>
// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 6;
// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
// Variables con las direcciones únicas de los 4 sensores DS18B20
DeviceAddress temperatura_tierra = {0x28, 0xFF, 0xB6, 0x4C, 0xA1, 0x17, 0x04, 0xD7};
DeviceAddress temperatura_agua = {0x28, 0xFF, 0xE7, 0xDC, 0xA0, 0x17, 0x05, 0x9B};
//DeviceAddress sensorDelante = {0x28, 0xA4, 0x29, 0xE6, 0x08, 0x00, 0x00, 0xF0};// CAMBIAR EL NOMBRE DE SENSOEDELANTE Y METER CODIGO
//DeviceAddress sensorAtras = {0x28, 0x45, 0x92, 0xE6, 0x08, 0x00, 0x00, 0xD1};// CAMBIAR EL NOMBRE DE SENSOEDELANTE Y METER CODIGO

//___________________________________________________________________DTH
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define HT1 44
#define HT2 45
#define HT3 46
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

//const int DHTPin = 5;     // what digital pin we're connected to

DHT dht1(HT1, DHTTYPE);
DHT dht2(HT2, DHTTYPE);
DHT dht3(HT3, DHTTYPE);

//__________________________________________________________________RELOJ 3231

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//__________________________________________________________________HIGROMETROS
const int sensorPin0 = A0;
const int sensorPin1 = A1;


//__________________________________________________________________COPIAR?


void setup() {

  // Iniciamos la comunicación serie
  Serial.begin(9600);
  delay(3000); // wait for console opening

  //___________________________________________________________ds18b20


  // Iniciamos el bus 1-Wire
  sensorDS18B20.begin();
  // Buscamos los sensores conectados
  Serial.println("Buscando dispositivos...");
  Serial.println("Encontrados: ");
  Serial.print(sensorDS18B20.getDeviceCount());
  Serial.println(" sensores");

  //___________________________________________________________________DTH

  //Serial.begin(9600);
   Serial.println("AMGD ADRIAN TFG");

   dht1.begin();//Inicializamos los sensores
   dht2.begin();
   dht3.begin();

  //__________________________________________________________________RELOJ 3231

     //delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //___________________________________________________________pantalla

  //Serial.begin(9600);
  Serial.println("ILI9341 Test!");
  tft.begin();

}//FIN SETUP


void loop(void) {

  //_____________________________________________________pantalla

  //for(uint8_t rotation=0; rotation<4; rotation++) {
  //tft.setRotation(rotation);
  tft.setRotation(1);//0 y 4 vertical , 1 y 3 horizontal, 6 vertical con texto en pines.
    int testText();
    testText();
    delay(2000);

  //_____________________________________________________ds18b20

  // Wait a few seconds between measurements.
   delay(1000);
    // Mandamos comandos para toma de temperatura a los sensores
  Serial.println("Mandando comandos a los sensores");
  sensorDS18B20.requestTemperatures();
  // Leemos y mostramos los datos de los sensores DS18B20 por dirección única
  Serial.print("Temperatura de la tierra ds18b20: ");
  Serial.print(sensorDS18B20.getTempC(temperatura_tierra));
  Serial.println(" C");
  Serial.print("Temperatura del agua ds18b20: ");
  Serial.print(sensorDS18B20.getTempC(temperatura_agua));
  Serial.println(" C");
  //Serial.print("Temperatura sensor delante: ");
  //Serial.print(sensorDS18B20.getTempC(sensorDelante));
  //Serial.println(" C");
  //Serial.print("Temperatura sensor detras: ");
  //Serial.print(sensorDS18B20.getTempC(sensorAtras));
  //Serial.println(" C");

  //__________________________________________________________________RELOJ 3231

   delay(1000);
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.println();

    Serial.println();
    delay(3000);

  //___________________________________________________________________DTH

  // Wait a few seconds between measurements.
   delay(1000);

   // Reading temperature or humidity takes about 250 milliseconds!
   float h1 = dht1.readHumidity(); //para sensor 1 dht1 HT1 44
   float t1 = dht1.readTemperature();

   if (isnan(h1) || isnan(t1)) {
      Serial.println("Failed DHT 1!");
      return;
   }

   Serial.print("H 1: "); //del sensor 1
   Serial.print(h1);
   Serial.print(" %\t");
   Serial.print("T 1: ");
   Serial.print(t1);
   Serial.print(" *C ");
   Serial.print("\t");


   float h2 = dht2.readHumidity(); //para sensor 2 dht2 HT2 45
   float t2 = dht2.readTemperature();

   if (isnan(h2) || isnan(t2)) {
      Serial.println("Failed DHT 2!");
      return;
   }

   Serial.print("H 2: ");// del sensor 2
   Serial.print(h2);
   Serial.print(" %\t");
   Serial.print("T 2: ");
   Serial.print(t2);
   Serial.print(" *C ");
   Serial.print("\t");

  float h3 = dht3.readHumidity(); //para sensor 3 dht3 HT3 46
   float t3 = dht3.readTemperature();

   if (isnan(h3) || isnan(t3)) {
      Serial.println("Failed DHT 3!");
      return;
   }

   Serial.print("H 3: "); // del sensor 3
   Serial.print(h3);
   Serial.print(" %\t");
   Serial.print(" 3: ");
   Serial.print(t3);
   Serial.print(" *C ");
   Serial.print("\n");

//__________________________________________________________________HIGROMETROS

  delay(1000);
  // Confi del sensor 1 en pin analogico 0 medidor de humedad de tierra
  int val0 = analogRead(0);
  val0 = map(val0, 300, 1023, 100, 0);
  //analogWrite(0, val);
  Serial.print("Humedad_1 ");
  Serial.print(val0);
  Serial.println("% ");

  int humedad1 = analogRead(sensorPin0);
  //   Serial.print("Humedad ");
  Serial.println(humedad1);

  //   Serial.println(humedad);
  //   if(humedad < 500)
  //   {
  //      Serial.println("Encendido");
  //      //hacer las acciones necesarias

  // Confi del sensor 2 en pin analogico 1 medidor de humedad de tierra
  int val1 = analogRead(1);
  val1 = map(val1, 300, 1023, 100, 0);
  //analogWrite(0, val);
  Serial.print("Humedad_2: ");
  Serial.print(val1);
  Serial.println("% ");

  int humedad2 = analogRead(sensorPin1);
  //   Serial.print("Humedad ");
  Serial.println(humedad2);

  //   Serial.println(humedad);
  //   if(humedad2 < 500)
  //   {
  //      Serial.println("Encendido");
  //      //hacer las acciones necesarias
  //   }

   delay(1000);


}//_______________________________________FIN LOOP

//unsigned long testFillScreen() {
  //unsigned long start = micros();
  //tft.fillScreen(ILI9341_BLACK);
  //yield();
  //tft.fillScreen(ILI9341_RED);
  //yield();
  //tft.fillScreen(ILI9341_GREEN);
  //yield();
  //tft.fillScreen(ILI9341_BLUE);
  //yield();
  //tft.fillScreen(ILI9341_BLACK);
  //yield();
  //return micros() - start;
//}
//_______________________________________________________________________________________________________CONFIGURACION PANTALLA ESCRITURA
unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);// para loop con pantalla en negro
  //unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.print("AMDG  +++             ");
  //_______________________________________________________________para ver la fecha en la cabezera
  DateTime now = rtc.now();
  tft.print("    ");
  tft.print(now.year(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.print(now.day(), DEC);
  tft.print(" (");
  tft.print(daysOfTheWeek[now.dayOfTheWeek()]);
  tft.print(") ");
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);


  tft.println(" ");
  tft.println(" ");

  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(2);
  tft.print("GrowControl ___v1_08_");//____________________________________________________________ versión del proyecto
  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(1);
  tft.println("VERSION");//____________________________________________________________ versión del proyecto estable / version beta con cambios
  tft.println("                                              PRUEBA");//____________________________________________________________ versión del proyecto estable / version beta con cambios
  //tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
 // tft.println(0xDEADBEEF, HEX);
 // tft.println();
 // tft.setTextColor(ILI9341_GREEN);
 // tft.setTextSize(5);
 // tft.println("Groop");

 // tft.setTextColor(ILI9341_GREEN);
  //tft.setTextSize(5);
 // tft.println("hola irene!!");

  //tft.setTextSize(1);
  //tft.println("I implore thee,");
  //_______________________________________________________________ para ver en pantalla ds18b20
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(1);
  tft.println(" ");
  tft.println(" ");
  tft.println(" SENSORES DS18B20");
  tft.println(" ");

  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.print(" TT: ");
  tft.print(sensorDS18B20.getTempC(temperatura_tierra));
  tft.print(" C ");
  tft.print(" TA: ");
  tft.print(sensorDS18B20.getTempC(temperatura_agua));
  tft.print(" C  ");


  //________________________________________________________________ para ver en pantalla DTHs
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  //tft.println(" ");

    // Reading temperature or humidity takes about 250 milliseconds!
   float h1 = dht1.readHumidity(); //para sensor 1 dht1 HT1 44
   float t1 = dht1.readTemperature();
 tft.println(" ");
   tft.print(" SENSORES DTH"); //del sensor 1
   tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
  tft.println(" ");

   tft.print(" H1: "); //del sensor 1
   tft.print(h1);
   tft.print(" % ");
   tft.print(" T1: ");
   tft.print(t1);
   tft.println(" C ");

   float h2 = dht2.readHumidity(); //para sensor 2 dht2 HT2 45
   float t2 = dht2.readTemperature();

   tft.print(" H2: ");// del sensor 2
   tft.print(h2);
   tft.print(" % ");
   tft.print(" T2: ");
   tft.print(t2);
   tft.println(" C ");

  float h3 = dht3.readHumidity(); //para sensor 3 dht3 HT3 46
  float t3 = dht3.readTemperature();

   tft.print(" H3: "); // del sensor 3
   tft.print(h3);
   tft.print(" % ");
   tft.print(" T3: ");
   tft.print(t3);
   tft.println(" C ");

  //_______________________________________________________________ para ver higrómetros

  tft.setTextColor(ILI9341_GREEN); tft.setTextSize(1);
  tft.println(" ");
  tft.setTextColor(ILI9341_GREEN); tft.setTextSize(1);
  tft.println(" ");
  tft.println(" SENSORES HUMEDAD DEL SUELO");
  tft.println(" ");

  tft.setTextColor(ILI9341_GREEN); tft.setTextSize(2);

    // Confi del sensor 1 en pin analogico 0 medidor de humedad de tierra
  int val0 = analogRead(0);
  val0 = map(val0, 300, 1023, 100, 0);
  //analogWrite(0, val);
  tft.print(" HS_1 ");
  tft.print(val0);
  tft.print("%   ");

  // Confi del sensor 2 en pin analogico 1 medidor de humedad de tierra
  int val1 = analogRead(1);
  val1 = map(val1, 300, 1023, 100, 0);
  //analogWrite(0, val);
  tft.print(" HS_2: ");
  tft.print(val1);
  tft.print("% ");

  //___________________letras finales de la pantalla

  tft.println(" ");
  tft.println(" ");
  tft.print("hola mundo");




  //_______________________________________________________________ copiar?

  //tft.setTextSize(1);
 // tft.println("my foonting turlingdromes.");
  //tft.println("And hooptiously drangle me");
  //tft.println("with crinkly bindlewurdles,");
  //tft.println("Or I will rend thee");
  //tft.println("in the gobberwarts");
  //tft.println("with my blurglecruncheon,");
  //tft.println("see if I don't!");
  //return micros() - start;
  //delay (5000);// ya tiene delay en el loop propio
}
