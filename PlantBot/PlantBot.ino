/* PlantBot Program 

  El robot dispone de unos sensores para medir:
    - la temperatura, 
    - la humedad y 
    - la conductividad de la tierra 
    
    para el cuidado de una planta.

*/

//Lo primero que hay que hacer es cargar las libreías de los sensores que realizan las medidas
#include "DHT11.h"  // El sensor de temperatura y Humedad se denomina DHT11
#include "TM1637Display.h" // El Display para visualizar el resultado es el modelo TM1637

//Guardamos en unas variables el numero de los pines que hemos conectado.
// Para la pantalla conectaremos el cable CLK en el pin amarillo 4 y DIO en el pin numero 5
int PIN_CLK = 4; //Pin CLK de la pantalla modelo TM1637
int PIN_DIO = 5; //Pin DIO de la pantalla modeloTM1637

// Creamos una instancia para la pantalla en los pines que hemos creado
TM1637Display pantalla ( PIN_CLK, PIN_DIO );//get Segment display controler

//Guardamos los pines de conexion de los sensores
int pin_sensorT = A0; //Pin de medicion del sensor de temperatura y humedad
int pin_sensorC = A1; //Pin de medicion del sensor de Conductividad

DHT11 sensor( pin_sensorT );

uint8_t letraH[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G            // H
};

uint8_t letraC[] = {
  SEG_A | SEG_F | SEG_E | SEG_D          // C
};

uint8_t letraS[] = {
  SEG_A | SEG_F | SEG_G | SEG_C |  SEG_D          // S
};
  
//Esta funcion solo se ejecuta al inicio y sirve para prepara nuestro robot al inicio
void setup(){
  Serial.begin(9600);
  //pantalla.init();
  //pantalla.set(BRIGHT_TYPICAL);
  pantalla.setBrightness(0x0f);
}

//Esta funcion se ejecuta en bucle y actualiza el valor de las medidas
void loop(){

  sensor.start();

  //Medimos la variable de temperatura y la visualizamos en pantalla
  int temperatura = (sensor.DHT11data)[2]%100 + (sensor.DHT11data)[2]%10 ;

  pantalla.showNumberDec( temperatura , false, 2 );
  pantalla.setSegments(letraC, 1, 3);
  Serial.print("Temp: ");Serial.println(temperatura);
  delay(1000);  //Esperamos un segundo
  
  //Medimos la variable de humedad y la visualizamos en pantalla
  pantalla.clear();
  int humedad = (sensor.DHT11data)[0]%100 + (sensor.DHT11data)[0]%10 ;

  pantalla.showNumberDec( humedad , false, 2);
  pantalla.setSegments(letraH, 1, 3);
  
  Serial.print("Humedad: ");Serial.println(humedad);
  delay(1000);  //Esperamos un segundo
  
  
  pantalla.clear();
  //Medimos la variable de humedad y la visualizamos en pantalla
  int humedadsuelo= analogRead(pin_sensorC); // Lee el valor del pin analogico que analiza la humedad del suelo
  //Los valores obtenidos van desde 0 sumergido en agua, a 1023 en el aire (o en un suelo muy seco). Un suelo ligeramente húmero daría valores típicos de 600-700. Un suelo seco tendrá valores de 800-1023.
  
  pantalla.showNumberDec( humedadsuelo , false, 3);
  pantalla.setSegments(letraS, 1, 3);
  Serial.print("Humedad del Suelo: ");Serial.println( humedadsuelo );
  
  delay(1000);
}
