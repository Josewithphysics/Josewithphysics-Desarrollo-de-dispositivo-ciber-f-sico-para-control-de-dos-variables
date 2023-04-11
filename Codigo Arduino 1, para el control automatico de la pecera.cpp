// Incluimos la librería para el uso de los pines del Arduino
#include <Arduino.h>

// Definimos los pines a utilizar para cada componente
const int SensorTemperatura = A0; // Pin analógico para el sensor de nivel
const int SensorNivel = A1; // Pin analógico para el sensor de temperatura
const int ValvulaDesague = 0; // Pin digital para la válvula de desagüe
const int ValvulaAguaCaliente = 1; // Pin digital para la válvula de agua caliente
const int ValvulaAguaFria = 2 ; // Pin digital para la válvula de agua fría


// Definimos las constantes para los valores ideales de temperatura y nivel de agua
const int TemperaturaIdeal = 25; // Temperatura ideal de la pecera
const int NivelAguaIdeal = 10; // Nivel ideal de agua en la pecera

// Variables para los valores leídos por los sensores
int Temperatura = 0; // Valor de temperatura leído por el sensor
int NivelAgua = 0; // Valor de nivel de agua leído por el sensor

void setup() 
{
  // Configuración de los pines como entrada o salida
  pinMode(SensorTemperatura, INPUT);
  pinMode(SensorNivel, INPUT);
  pinMode(ValvulaAguaCaliente, OUTPUT);
  pinMode(ValvulaAguaFria, OUTPUT);
  pinMode(ValvulaDesague, OUTPUT);
  // Inicializamos la comunicación serial para la depuración
  Serial.begin(9600);
}

void loop() 
{
  // Leemos los valores de los sensores y los transformamos a los valores correspondientes 
  // map(valor, ValorMinimoEntrada, ValorMaximoEntrada, ValorMinimoSalida, ValorMaximoSalida)
  Temperatura = map(analogRead(SensorTemperatura), 0, 1023, 0, 50);
  NivelAgua = map(analogRead(SensorNivel), 0, 1023, 0, 50);

  // Comprobamos si la temperatura está por debajo de lo ideal
  if (Temperatura < TemperaturaIdeal) 
  {
    // Abrimos la válvula de agua caliente
    digitalWrite(ValvulaAguaCaliente, HIGH);
    // Enviamos un mensaje de depuración
    Serial.println("Calentando agua");
    // Esperamos 5 segundos para permitir que la temperatura se estabilice
    delay(5000);
    // Cerramos la válvula de agua caliente
    digitalWrite(ValvulaAguaCaliente, LOW);
    // Enviamos un mensaje de depuración
    Serial.println("Temperatura estabilizada");
  }
  // Comprobamos si la temperatura está por encima de lo ideal
  else if (Temperatura > TemperaturaIdeal) 
  {
    // Abrimos la válvula de agua fría
    digitalWrite(ValvulaAguaFria, HIGH);
    // Enviamos un mensaje de depuración
    Serial.println("Enfriando agua");
    // Esperamos 5 segundos para permitir que la temperatura se estabilice
    delay(5000);
    // Cerramos la válvula de agua fría
    digitalWrite(ValvulaAguaFria, LOW);
    // Enviamos un mensaje de depuración
    Serial.println("Temperatura estabilizada");
  }
}
  // Comprobamos si el nivel de agua está por debajo de lo ideal

else if (NivelAgua < NivelAguaIdeal) 
{
    // Abrimos la válvula de agua para aumentar el nivel de agua
    digitalWrite(ValvulaAguaFria, HIGH);
    digitalWrite(ValvulaAguaCaliente, HIGH);
    // Enviamos un mensaje de depuración
    Serial.println("Añadiendo agua");
    // Esperamos hasta que el nivel de agua sea el ideal
    while (NivelAgua < NivelAguaIdeal) 
    {
      NivelAgua = map(analogRead(SensorNivel), 0, 1023, 0, 50);
    }
    // Cerramos las válvulas de agua
    digitalWrite(ValvulaAguaFria, LOW);
    digitalWrite(ValvulaAguaCaliente, LOW);
    // Enviamos un mensaje de depuración
    Serial.println("Nivel de agua ideal alcanzado");
  }

  // Comprobamos si el nivel de agua está por encima de lo ideal
  else if (NivelAgua > NivelAguaIdeal) 
  {
    // Abrimos la válvula de desagüe
    digitalWrite(ValvulaDesague, HIGH);
    // Enviamos un mensaje de depuración
    Serial.println("Drenando agua");
    // Esperamos hasta que el nivel de agua sea el ideal
    while (NivelAgua > NivelAguaIdeal) 
    {
      NivelAgua = map(analogRead(SensorNivel), 0, 1023, 0, 50);
    }
    // Cerramos la válvula de desagüe
    (digitalWritealvulaDesague, LOW);
    // Enviamos un mensaje de depuración
    Serial.println("Nivel de agua ideal alcanzado");
  }

  // Esperamos 1 segundo antes de volver a comprobar los sensores
  delay(1000);


