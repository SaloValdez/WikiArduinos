//Sistema de estacionamiento automatizado
//Con 8 capacidad para 8 veehiculos
//Entrada y Salida independiente

#include <Servo.h>
Servo miservo;  // Definir un objeto
Servo miservo2; //Definir un objeto para el segundo servo

#define ServoM    10    //Indicar a que pin PWM se conectara 
#define ServoM2    9     //Indicar a que pin PWM se conectara
#define Bright    11     //pin vcc display
#define Exit      44    //Pin Salida
#define In        45     //Pin Entrada

#define BarLow    0       //Posicion servo "Cerrrado"
#define BarUp     90      //Posicion servo "Abierto"
#define CAPACITY  5        //Espacios disponibles del estacionamiento
#define INTEN     60       //Porcentaje de intensidad del display

//Configuracion de los pines para cada segmento
#define  segA  0
#define  segB  1
#define  segC  2
#define  segD  3
#define  segE  4
#define  segF  5
#define  segG  7


const int pinVERDE = 24;
const int pinROJO = 25;
const int pinAZUL = 26;


//Declarar arreglo de los segmentos para presentar los numeros (0-9)
byte segments[10] = {
  B00111111, // number 0
  B00000110, // number 1
  B01011011, // number 2
  B01001111, // number 3
  B01100110, // number 4
  B01101101, // number 5
  B01111101, // number 6
  B00000111, // number 7
  B01111111, // number 8
  B01101111  // number 9
};

void setup(){
  miservo.write(BarLow);
  miservo.write(BarLow);

      pinMode(pinROJO, OUTPUT);
       pinMode(pinVERDE, OUTPUT);
       pinMode(pinAZUL, OUTPUT);
    
  
  miservo.attach(ServoM);         

  pinMode(In, INPUT);             //Recibe pulso "Entrada"
  digitalWrite(In, HIGH);         //Envia señal al servo
  pinMode(segA,OUTPUT);
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
 // pinMode(segF,OUTPUT);
 // pinMode(segG,OUTPUT);
  pinMode(Bright,OUTPUT);
  analogWrite(Bright,255*INTEN/100);
  miservo.write(BarLow);    //Levanta la pluma       


  miservo2.attach(ServoM2);          

  pinMode(Exit, INPUT);           //Recibe pulso "Salida"
  digitalWrite(Exit, HIGH);       //Envia señal al servo
  pinMode(segA,OUTPUT);
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
 // pinMode(segF,OUTPUT);
 // pinMode(segG,OUTPUT);
  pinMode(Bright,OUTPUT);
  analogWrite(Bright,255*INTEN/100);
  miservo2.write(BarLow);           //Levanta la pluma

}



int  Available= 5;                    //Numero de espacios disponibles


int Incremento  = 0;

//Validacion de las posiciones disponibles del estacionamiento
void loop(){

  // digitalWrite(pinAZUL, HIGH);
  // digitalWrite(pinVERDE, HIGH);
   

Display(Available);


//Entrada
if(digitalRead(In)==0)
{
  if(Available != 0){
 
    Available--;
    Incremento++;
    
      //------SALO------------------------------ PARA LEDS
     if (Incremento >0  && Incremento <= 4 ){
        digitalWrite(pinVERDE, HIGH);
        digitalWrite(pinROJO, LOW);
        digitalWrite(pinAZUL, LOW);
    }else if(Incremento > 4 ){
        digitalWrite(pinVERDE, LOW);
        digitalWrite(pinROJO, HIGH);
    }
      //------SALO------------------------------
    
    miservo.write(BarUp);   
    delay(4000);
    miservo.write(BarLow);
    }

  }
  
//Salida
if(digitalRead(Exit)==0)
{
  if(Available != CAPACITY){
    Available++;
      Incremento--;
       
       //------SALO------------------------------  PARA LEDS
     if (Incremento >0  && Incremento <= 4 ){
        digitalWrite(pinVERDE, HIGH);
        digitalWrite(pinROJO, LOW);
        digitalWrite(pinAZUL, LOW);
        
    }else if(Incremento > 4 ){
        digitalWrite(pinVERDE, LOW);
        digitalWrite(pinROJO, HIGH);
      
    }
        //------SALO------------------------------

        
       if (Incremento == 0){
        digitalWrite(pinAZUL, HIGH);
        }
      
    miservo2.write(BarUp);
    delay(4000);
    miservo2.write(BarLow);
    }
  }
}


void Display(int number){
byte segs =  ~segments[number];        //"~" SE USA PARA ANODO COMUN.

digitalWrite(segA, bitRead(segs, 0) );
digitalWrite(segB, bitRead(segs, 1) );
digitalWrite(segC, bitRead(segs, 2) );
digitalWrite(segD, bitRead(segs, 3) );
digitalWrite(segE, bitRead(segs, 4) );
//digitalWrite(segF, bitRead(segs, 5) );
//digitalWrite(segG, bitRead(segs, 6) );
}
