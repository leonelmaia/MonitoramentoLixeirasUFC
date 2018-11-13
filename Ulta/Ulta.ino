/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

#include <SoftwareSerial.h>
#include "HX711.h"                    // Biblioteca HX711 
 
#define DOUT  A0                      // HX711 DATA OUT = pino A0 do Arduino 
#define CLK  A1                       // HX711 SCK IN = pino A1 do Arduino 
 
HX711 balanca(DOUT, CLK);             // instancia Balança HX711
 
float calibration_factor = 49630;     // fator de calibração aferido na Calibraçao 
 
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
SoftwareSerial s(5,6);
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
s.begin(9600);
balanca.set_scale(calibration_factor);             // ajusta fator de calibração
balanca.tare();                                    // zera a Balança
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
float peso = balanca.get_units();
Serial.print("Peso: ");                            // imprime no monitor serial
Serial.print(peso, 3);                             // imprime peso na balança com 3 casas decimais 
Serial.println(" kg");                             // imprime no monitor serial 
if (Serial.available())                            // se a serial estiver disponivel
{
  char temp = Serial.read();                       // le carcter da serial 
  if (temp == 't' || temp == 'T')                  // se pressionar t ou T
  {
    balanca.tare();                                // zera a balança
    Serial.println(" Balança zerada");             // imprime no monitor serial
  }
}
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

if (distance < 5)
{
  s.print('d');
  Serial.print("Lotacao da lixeira enviada ao Node Devido ao espaco da lixeira\n");

}

if (peso > 0.5)
{
  s.print('d');
  Serial.print("Lotacao da lixeira enviada ao Node Devido ao Peso\n");

}
delay(1000);
}

/* Programa para Balança com o HX711
  Blog Eletrogate - http://blog.eletrogate.com/balanca-digital-com-arduino-aprenda-a-usar-a-celula-de-carga
  Arduino UNO - IDE 1.8.5 - Modulo HX711 - celulas de Carga 50 Kg
  Gustavo Murta   31/maio/2018
  Biblioteca https://github.com/bogde/HX711
  Baseado em https://www.hackster.io/MOHAN_CHANDALURU/hx711-load-cell-amplifier-interface-with-arduino-fa47f3
*/

/*
#include "HX711.h"                    // Biblioteca HX711 
 
#define DOUT  A0                      // HX711 DATA OUT = pino A0 do Arduino 
#define CLK  A1                       // HX711 SCK IN = pino A1 do Arduino 
 
HX711 balanca(DOUT, CLK);             // instancia Balança HX711
 
float calibration_factor = 102130;     // fator de calibração aferido na Calibraçao 
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Balança com HX711 - celula de carga 50 Kg");            
  Serial.println("Pressione t para Tara");           // imprime no monitor serial
  balanca.set_scale(calibration_factor);             // ajusta fator de calibração
  balanca.tare();                                    // zera a Balança
}
 
void loop()
{
  Serial.print("Peso: ");                            // imprime no monitor serial
  Serial.print(balanca.get_units(), 3);              // imprime peso na balança com 3 casas decimais 
  Serial.println(" kg");                             // imprime no monitor serial 
  delay(500) ;                                       // atraso de 0,5 segundos 
  if (Serial.available())                            // se a serial estiver disponivel
  {
    char temp = Serial.read();                       // le carcter da serial 
    if (temp == 't' || temp == 'T')                  // se pressionar t ou T
    {
      balanca.tare();                                // zera a balança
      Serial.println(" Balança zerada");             // imprime no monitor serial
    }
  }
}
*/

/* Programa para Calibração do HX711
  Blog Eletrogate - http://blog.eletrogate.com/balanca-digital-com-arduino-aprenda-a-usar-a-celula-de-carga
  Arduino UNO - IDE 1.8.5 - Modulo HX711 - celulas de Carga 50 Kg
  Gustavo Murta   31/maio/2018
  Biblioteca https://github.com/bogde/HX711
  Baseado em https://www.hackster.io/MOHAN_CHANDALURU/hx711-load-cell-amplifier-interface-with-arduino-fa47f3

 
#include "HX711.h"                    // Biblioteca HX711 
 
#define DOUT  A0                      // HX711 DATA OUT = pino A0 do Arduino 
#define CLK  A1                       // HX711 SCK IN = pino A1 do Arduino 
 
HX711 balanca(DOUT, CLK);             // instancia Balança HX711
 
float calibration_factor = 42130;     // fator de calibração para teste inicial
 
void setup()
{
  Serial.begin(9600);                                              // monitor serial 9600 Bps
  Serial.println();                                                // salta uma linha
  Serial.println("HX711 - Calibracao da Balança");                 // imprime no monitor serial
  Serial.println("Remova o peso da balanca");
  Serial.println("Depois que as leituras começarem, coloque um peso conhecido sobre a Balança");
  Serial.println("Pressione a,s,d,f para aumentar Fator de Calibração por 10,100,1000,10000 respectivamente");
  Serial.println("Pressione z,x,c,v para diminuir Fator de Calibração por 10,100,1000,10000 respectivamente");
  Serial.println("Após leitura correta do peso, pressione t para TARA(zerar) ");
 
  balanca.set_scale();                                             // configura a escala da Balança
  zeraBalanca ();                                                  // zera a Balança
}
 
void zeraBalanca ()
{
  Serial.println();                                               // salta uma linha
  balanca.tare();                                                 // zera a Balança
  Serial.println("Balança Zerada ");
}
 
void loop()
{
  balanca.set_scale(calibration_factor);                     // ajusta fator de calibração
  Serial.print("Peso: ");                                    // imprime no monitor serial
  Serial.print(balanca.get_units(), 3);                      // imprime peso da balança com 3 casas decimais
  Serial.print(" kg");
  Serial.print("      Fator de Calibração: ");               // imprime no monitor serial
  Serial.println(calibration_factor);                        // imprime fator de calibração
  delay(500) ;                                               // atraso de 0,5 segundo
 
  if (Serial.available())                                    // reconhece letra para ajuste do fator de calibração
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')                // a = aumenta 10
      calibration_factor += 10;
    else if (temp == '-' || temp == 'z')           // z = diminui 10
      calibration_factor -= 10;
    else if (temp == 's')                          // s = aumenta 100
      calibration_factor += 100;
    else if (temp == 'x')                          // x = diminui 100
      calibration_factor -= 100;
    else if (temp == 'd')                          // d = aumenta 1000
      calibration_factor += 1000;
    else if (temp == 'c')                          // c = diminui 1000
      calibration_factor -= 1000;
    else if (temp == 'f')                          // f = aumenta 10000
      calibration_factor += 10000;
    else if (temp == 'v')                          // v = dimuni 10000
      calibration_factor -= 10000;
    else if (temp == 't') zeraBalanca ();          // t = zera a Balança
  }
}
*/

/*
void setup()
{
  Serial.begin(9600);
  Serial.println("Balança com HX711 - celula de carga 50 Kg");            
  Serial.println("Pressione t para Tara");           // imprime no monitor serial
  balanca.set_scale(calibration_factor);             // ajusta fator de calibração
  balanca.tare();                                    // zera a Balança
}
 
void loop()
{
  Serial.print("Peso: ");                            // imprime no monitor serial
  Serial.print(balanca.get_units(), 3);              // imprime peso na balança com 3 casas decimais 
  Serial.println(" kg");                             // imprime no monitor serial 
  delay(500) ;                                       // atraso de 0,5 segundos 
  if (Serial.available())                            // se a serial estiver disponivel
  {
    char temp = Serial.read();                       // le carcter da serial 
    if (temp == 't' || temp == 'T')                  // se pressionar t ou T
    {
      balanca.tare();                                // zera a balança
      Serial.println(" Balança zerada");             // imprime no monitor serial
    }
  }
}
*/
