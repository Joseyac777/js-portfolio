#define T_SALIDA 13
#define E_SALIDA 10
#define T_ENTRADA 12
#define E_ENTRADA 11
#define S_ENTRADA A0
#define S_SALIDA A1

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>


float sonido = 34300.0;
int dentro = 0;
bool entrando = false;
bool saliendo = false;
bool entroOSalio = false;
int segundosEntrando = 0;
int segundosSaliendo = 0;
bool contra;
char letra; 
byte contadorLetras = 0; 

int alarma = 0;

Servo servoEntrada;
Servo servoSalida;

void setup() {

  Serial.begin(9600);
  servoEntrada.attach(S_ENTRADA);
  servoSalida.attach(S_SALIDA);
  servoEntrada.write(0);
  servoSalida.write(0);
  pinMode(T_ENTRADA,OUTPUT);
  pinMode(T_SALIDA,OUTPUT);
  pinMode(E_ENTRADA,INPUT);
  pinMode(E_SALIDA,INPUT);
 
}

void loop() {
  digitalWrite(T_ENTRADA,HIGH);
  delayMicroseconds(1);
  digitalWrite(T_ENTRADA,LOW);
  
  long tiempoEntrada = pulseIn(E_ENTRADA,HIGH);
  int distanciaEntrada = tiempoEntrada * 0.000001 * sonido / 2.0;
  
  digitalWrite(T_SALIDA,HIGH);
  delayMicroseconds(1);
  digitalWrite(T_SALIDA,LOW);
  
  long tiempoSalida = pulseIn(E_SALIDA,HIGH);
  int distanciaSalida = tiempoSalida * 0.000001 * sonido / 2.0;
  
  contra = false;
  
  if(distanciaEntrada > 25 && distanciaEntrada < 90 && entrando == false && dentro < 5){
    entrando = true;
    servoEntrada.write(100);
    
    Serial.println("BIENVENIDO");

    segundosEntrando = segundosEntrando + 1;
  }
  else{
    if(distanciaEntrada > 25 && distanciaEntrada < 90 && entrando == true){
     
      Serial.println("BIENVENIDO");
     
      segundosEntrando = segundosEntrando + 1;
    }
    if(dentro == 5 && distanciaEntrada > 25 && distanciaEntrada < 90){
      Serial.println("ESPERE");
      Serial.println("PARQUEO LLENO");
    }
  }
  
  if(distanciaEntrada < 25 && entrando == true && dentro < 5){ //|| distanciaEntrada > 90
    servoEntrada.write(0);
    dentro = dentro + 1;
    entrando = false;
    entroOSalio = true;
    segundosEntrando = 0;
    Serial.println("ENTRO");
    
  }
  
  if(distanciaSalida > 75 && distanciaSalida < 170 && saliendo == false && dentro > 0){
    saliendo = true;
    servoSalida.write(100);
    
    Serial.println("BUEN VIAJE");
    
    Serial.println("SALIENDO");

    segundosSaliendo = segundosSaliendo + 1;
  }
  else{
    if(distanciaSalida > 55 && distanciaSalida < 170 && saliendo == true){
      
      Serial.println("BUEN VIAJE");
      
      Serial.println("SALIENDO");
     
      segundosSaliendo = segundosSaliendo + 1;
    }
    if(dentro <= 0 && distanciaSalida > 25 && distanciaSalida < 170){ 
      Serial.println("ESPACIO DISPONIBLE");      
    }
  }
  
  if(distanciaSalida > 200  && saliendo == true && dentro > 0){ //|| distanciaSalida < 120
    servoSalida.write(0);
    dentro = dentro - 1;
    saliendo = false;
    entroOSalio = true;
    segundosSaliendo = 0;
    
  }
  
  if(entroOSalio == true){
    
    Serial.println("AUTOS");
    
    Serial.println(dentro);
    
    entroOSalio = false;
  }
  delay(800);
  
}
  