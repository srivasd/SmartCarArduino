#include <IRremote.h>
#include <IRremoteInt.h>



// look for IR codes and print them as they are received

#define IRPIN 3    // pin that IR detector is connected to
#define ZPIN 7
#define LIGHTPIN 8
#define LDRPIN 0
#define FORWARD 16718055
#define FORWARDLEFT 16724175
#define FORWARDRIGHT 16743045
#define REVERSE 16730805
#define REVERSELEFT 16728765
#define REVERSERIGHT 16732845
#define RIGHT 16734885
#define LEFT 16716015
#define STOP 16726215
#define HORN 16754775

#define DO 261.626
#define RE 293.665
#define MI 300
#define FA 349.228
#define SOL 391.995
#define LA 440.000
#define SI 493.883
#define DO2 523.251

float cancion[]={DO,RE,MI,FA,SOL,LA,SI,DO2};

int valorLDR = 0;
const int LEFT_FORWARD = 2;
const int LEFT_BACKWARD = 6;
const int RIGHT_FORWARD = 4;
const int RIGHT_BACKWARD = 5;

const int LEFT_FORWARD2 = 9;
const int LEFT_BACKWARD2 = 10;
const int RIGHT_FORWARD2 = 11;
const int RIGHT_BACKWARD2 = 12;

const int pinecho = A5;
const int pintrigger = A4;
const int pinechoatras = A3;
const int pintriggeratras = A2;

// VARIABLES PARA CALCULOS
unsigned int tiempo, distancia = 50;
unsigned int tiempoatras, distanciaatras = 50;

int is_stopped = 1;

IRrecv irrecv(IRPIN);

decode_results results;

void setup()
{
  pinMode(ZPIN, OUTPUT);
  pinMode(LEFT_FORWARD , OUTPUT);
  pinMode(LEFT_BACKWARD , OUTPUT);
  pinMode(RIGHT_FORWARD , OUTPUT);
  pinMode(RIGHT_BACKWARD , OUTPUT);
  pinMode(LEFT_FORWARD2 , OUTPUT);
  pinMode(LEFT_BACKWARD2 , OUTPUT);
  pinMode(RIGHT_FORWARD2 , OUTPUT);
  pinMode(RIGHT_BACKWARD2 , OUTPUT);
  pinMode(LIGHTPIN, OUTPUT);
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
  pinMode(pinechoatras, INPUT);
  pinMode(pintriggeratras, OUTPUT);
  
  Serial.begin(9600) ;
  Serial.println("NEC IR code reception") ;
  irrecv.enableIRIn();  
}

void loop()
{
  // ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER"
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;
 //distancia = 150;

  // ENVIAR EL RESULTADO AL MONITOR SERIAL
  //Serial.print(distancia);
  //Serial.println(" cm");
  //delay(200);

  // ENCENDER EL LED CUANDO SE CUMPLA CON CIERTA DISTANCIA
  if (distancia <= 25 && is_stopped == 0) {
    warning();
    //stopMotors();
    reverse();
    Serial.println("Entra") ;
    delay(100);
  } 

// ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER"
  digitalWrite(pintriggeratras, LOW);
  delayMicroseconds(2);
  digitalWrite(pintriggeratras, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintriggeratras, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempoatras = pulseIn(pinechoatras, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distanciaatras = tiempoatras / 58;

  // ENVIAR EL RESULTADO AL MONITOR SERIAL
  //Serial.print(distanciaatras);
  //Serial.println(" cm atras");
  //delay(200);

  // ENCENDER EL LED CUANDO SE CUMPLA CON CIERTA DISTANCIA
  if (distanciaatras <= 25 && is_stopped == 0) {
    warning();
    //stopMotors();
    forward();
    Serial.println("Entra froward") ;
    delay(100);
  } 
  
  digitalWrite(LIGHTPIN, LOW);
  valorLDR = analogRead(LDRPIN);
  //Serial.println(valorLDR) ;

  // Encender los leds apropiados de acuerdo al valor de ADC
  if(valorLDR < 350)
  {
    digitalWrite(LIGHTPIN, HIGH);
  }

  if(valorLDR > 350)
  {
    digitalWrite(LIGHTPIN, LOW);
  }
  
  if (irrecv.decode(&results)) // have we received an IR signal
  {
    Serial.println(results.value) ;
    switch(results.value)
    {
      case RIGHT: // 6 button pressed
                      right();
                      Serial.println("Derecha") ;
                      break;
      case FORWARD: // 2 button pressed
                      forward();
                      Serial.println("Adelante") ;
                      break;
      case FORWARDLEFT: // 1 button pressed
                      forwardLeft();
                      Serial.println("Adelante Izquierda") ;
                      break;
      case FORWARDRIGHT: // 3 button pressed
                      forwardRight();
                      Serial.println("Adelante Derecha") ;
                      break;
      case REVERSE: // 8 button pressed
                      reverse();
                      Serial.println("Atras") ;
                      break;
      case REVERSELEFT: // 7 button pressed
                      reverseLeft();
                      Serial.println("Atras") ;
                      break;
      case REVERSERIGHT: // 9 button pressed
                      reverseRight();
                      Serial.println("Atras") ;
                      break;
      case LEFT: // 4 button pressed
                      left();
                      Serial.println("Izquierda") ; 
                      break; 
       case STOP: // 5 button pressed
                      stopMotors();
                      Serial.println("Parado") ;
                      break;   
      case HORN: // + button pressed
                      horn();
                      Serial.println("Claxon");
                      break;       
    }
    
      irrecv.resume(); // receive the next value
  }  
}

void forward(){
    is_stopped = 0;
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , LOW);
    digitalWrite(LEFT_BACKWARD , HIGH);
    digitalWrite(RIGHT_FORWARD , HIGH);
    digitalWrite(RIGHT_BACKWARD , LOW);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , LOW);
    digitalWrite(LEFT_BACKWARD2 , HIGH);
    digitalWrite(RIGHT_FORWARD2 , LOW);
    digitalWrite(RIGHT_BACKWARD2 , HIGH);

}

void forwardLeft(){
    is_stopped = 0;
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , LOW);
    digitalWrite(LEFT_BACKWARD , HIGH);
    digitalWrite(RIGHT_FORWARD , LOW);
    digitalWrite(RIGHT_BACKWARD , HIGH);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , LOW);
    digitalWrite(LEFT_BACKWARD2 , HIGH);
    digitalWrite(RIGHT_FORWARD2 , LOW);
    digitalWrite(RIGHT_BACKWARD2 , HIGH);

}

void forwardRight(){
    is_stopped = 0;
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , HIGH);
    digitalWrite(LEFT_BACKWARD , LOW);
    digitalWrite(RIGHT_FORWARD , HIGH);
    digitalWrite(RIGHT_BACKWARD , LOW);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , LOW);
    digitalWrite(LEFT_BACKWARD2 , HIGH);
    digitalWrite(RIGHT_FORWARD2 , LOW);
    digitalWrite(RIGHT_BACKWARD2 , HIGH);

}

void right(){
    is_stopped = 0;
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , HIGH);
    digitalWrite(LEFT_BACKWARD , LOW);
    digitalWrite(RIGHT_FORWARD , HIGH);
    digitalWrite(RIGHT_BACKWARD , LOW);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , LOW);
    digitalWrite(LEFT_BACKWARD2 , HIGH);
    digitalWrite(RIGHT_FORWARD2 , HIGH);
    digitalWrite(RIGHT_BACKWARD2 , LOW);
}

void left(){
    is_stopped = 0;
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , LOW);
    digitalWrite(LEFT_BACKWARD , HIGH);
    digitalWrite(RIGHT_FORWARD , LOW);
    digitalWrite(RIGHT_BACKWARD , HIGH);
 
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , HIGH);
    digitalWrite(LEFT_BACKWARD2 , LOW);
    digitalWrite(RIGHT_FORWARD2 , LOW);
    digitalWrite(RIGHT_BACKWARD2 , HIGH);

}

void reverse(){
    is_stopped = 0;
    
    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , HIGH);
    digitalWrite(LEFT_BACKWARD , LOW);
    digitalWrite(RIGHT_FORWARD , LOW);
    digitalWrite(RIGHT_BACKWARD , HIGH);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , HIGH);
    digitalWrite(LEFT_BACKWARD2 , LOW);
    digitalWrite(RIGHT_FORWARD2 , HIGH);
    digitalWrite(RIGHT_BACKWARD2 , LOW);
}

void reverseLeft(){
    is_stopped = 0;
    
    //Ruedas de atrás

    digitalWrite(LEFT_FORWARD , HIGH);
    digitalWrite(LEFT_BACKWARD , LOW);
    digitalWrite(RIGHT_FORWARD , HIGH);
    digitalWrite(RIGHT_BACKWARD , LOW);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , HIGH);
    digitalWrite(LEFT_BACKWARD2 , LOW);
    digitalWrite(RIGHT_FORWARD2 , HIGH);
    digitalWrite(RIGHT_BACKWARD2 , LOW);
}

void reverseRight(){
    is_stopped = 0;

    //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , LOW);
    digitalWrite(LEFT_BACKWARD , HIGH);
    digitalWrite(RIGHT_FORWARD , LOW);
    digitalWrite(RIGHT_BACKWARD , HIGH);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , HIGH);
    digitalWrite(LEFT_BACKWARD2 , LOW);
    digitalWrite(RIGHT_FORWARD2 , HIGH);
    digitalWrite(RIGHT_BACKWARD2 , LOW);
}

void stopMotors(){
  is_stopped = 1;
  //Ruedas de atrás
    digitalWrite(LEFT_FORWARD , LOW);
    digitalWrite(LEFT_BACKWARD , LOW);
    digitalWrite(RIGHT_FORWARD , LOW);
    digitalWrite(RIGHT_BACKWARD , LOW);
  
    //Ruedas de delante
    digitalWrite(LEFT_FORWARD2 , LOW);
    digitalWrite(LEFT_BACKWARD2 , LOW);
    digitalWrite(RIGHT_FORWARD2 , LOW);
    digitalWrite(RIGHT_BACKWARD2 , LOW);
}

void horn(){
  Serial.println("Claxon");
  tone(ZPIN, DO); 
  delay(1000);
  noTone(ZPIN);
}

void warning(){
  Serial.println("Claxon");
  for (int i=0; i<3; i++){
    tone(ZPIN, SI);
    delay(100);
    noTone(ZPIN);
  }
}


