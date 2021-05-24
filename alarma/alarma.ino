#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Su authtoken generado por la aplicacion Blynk
char auth[] = "mm4tCtkiWlEXHwcRNrNr2lLTlJStpoKk";

//Datos para la conexion de Red Wifi.
char ssid[] = "DENNYS_QUINTO";
char pass[] = "70192771"; 

const int buzzer = 4;
const int PIR = 5;
const int salida = 14;   
const int entrada = 12;
const int salida2 = 13;     
const int entrada2 = 15;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Envia correo electrónico cuando el hardware se conecte al servidor de Blynk
  //Parametros por defecto "Correo electronico", "Asunto", "Mensaje a enviar"
  
  Blynk.email("dennys.el@hotmail.com","Subject", "My Blynk project is online.");
  pinMode(PIR, INPUT);// pin D1(GPIO5) como entrada
  pinMode(buzzer,OUTPUT);// pin D2(GPIO4) como Salida
  pinMode(salida, OUTPUT);
  pinMode(entrada, INPUT);
  pinMode(salida2, OUTPUT);
  pinMode(entrada2, INPUT);
}

void Alarma()
{
  // si la alarma se activa este envia un correo y espera 15 segundos.

  int Sensor = digitalRead(PIR); // variable para almacenar los estados del PIR
  int HAB = digitalRead(entrada);
  int HAB2 = digitalRead(entrada2);
  if (HAB == 1){ // forzar el sonido de buzer
    digitalWrite(buzzer, HIGH);
  }else{
    if (HAB2 == 1 && Sensor == 0){
      digitalWrite(buzzer, LOW);
      
    }
    if (HAB2 == 1 && Sensor == 1){ // encender el sensor y buzer
      digitalWrite(buzzer, HIGH);
     
    }
    if (HAB2 == 0){
      digitalWrite(buzzer, LOW);
    }
  }

  if (Sensor == 1) // si el sensor detecta movimiento
  {
    Serial.println("Alarma Activada"); //Imprime por el monitor serial
    Blynk.email("dennys.ortiz10@gmail.com", "Asunto:", "Alerta Ingeniero bailarin detectado");
    delay(200);
  }
  
}
void loop()
{
  Alarma();// llama a ejecutar la funcion
  Blynk.run();
}
