/****************************************/
/************ EMISOR INFRARROJOS ***********/
/****************************************/
/* Autor: Sergio Rivas Degado. */
/****************************************/


/*#define FORWARD 16718055
#define REVERSE 16730805
#define RIGHT 16734885
#define LEFT 16716015
#define STOP 16726215
#define HORN 16754775
*/

#include <IRLib.h>
#include <IRLibMatch.h>
#include <IRLibTimer.h>

IRsend emitter;
int count;

const int BOTON_ATRAS_DERECHA = 4;
const int BOTON_ATRAS_IZQUIERDA = 5;
const int BOTON_ADELANTE_DERECHA = 6;
const int BOTON_ADELANTE_IZQUIERDA = 7;
const int BOTON_ADELANTE = 8;
const int BOTON_ATRAS = 9;
const int BOTON_IZQUIERDA = 11;
const int BOTON_DERECHA = 10;
const int BOTON_CLAXON = 12;
const int BOTON_STOP = 13;

int val_adelante = 0; //val se emplea para almacenar el estado del boton
int state_adelante = 0; 
int old_val_adelante = 0; // almacena el antiguo valor de val

int val_adelante_izquierda = 0; //val se emplea para almacenar el estado del boton
int state_adelante_izquierda = 0; 
int old_val_adelante_izquierda = 0; // almacena el antiguo valor de val

int val_adelante_derecha = 0; //val se emplea para almacenar el estado del boton
int state_adelante_derecha = 0; 
int old_val_adelante_derecha = 0; // almacena el antiguo valor de val

int val_atras = 0; //val se emplea para almacenar el estado del boton
int state_atras = 0; 
int old_val_atras = 0; // almacena el antiguo valor de val

int val_atras_izquierda = 0; //val se emplea para almacenar el estado del boton
int state_atras_izquierda = 0; 
int old_val_atras_izquierda = 0; // almacena el antiguo valor de val

int val_atras_derecha = 0; //val se emplea para almacenar el estado del boton
int state_atras_derecha = 0; 
int old_val_atras_derecha = 0; // almacena el antiguo valor de val

int val_izquierda = 0; //val se emplea para almacenar el estado del boton
int state_izquierda = 0; 
int old_val_izquierda = 0; // almacena el antiguo valor de val

int val_derecha = 0; //val se emplea para almacenar el estado del boton
int state_derecha = 0; 
int old_val_derecha = 0; // almacena el antiguo valor de val

int val_claxon = 0; //val se emplea para almacenar el estado del boton
int state_claxon = 0; 
int old_val_claxon = 0; // almacena el antiguo valor de val

int val_stop = 0; //val se emplea para almacenar el estado del boton
int state_stop = 0; 
int old_val_stop = 0; // almacena el antiguo valor de val

void setup() {
  Serial.begin(9600);
  count = 0;

  pinMode(BOTON_ADELANTE,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_ADELANTE_IZQUIERDA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_ADELANTE_DERECHA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_ATRAS,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_ATRAS_IZQUIERDA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_ATRAS_DERECHA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_IZQUIERDA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_DERECHA,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_CLAXON,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON_STOP,INPUT); // y BOTON como señal de entrada
}

void loop() {

  val_adelante= digitalRead(BOTON_ADELANTE); // lee el estado del Boton
  val_adelante_izquierda= digitalRead(BOTON_ADELANTE_IZQUIERDA); // lee el estado del Boton
  val_adelante_derecha= digitalRead(BOTON_ADELANTE_DERECHA); // lee el estado del Boton
  val_atras= digitalRead(BOTON_ATRAS); // lee el estado del Boton
  val_atras_izquierda= digitalRead(BOTON_ATRAS_IZQUIERDA); // lee el estado del Boton
  val_atras_derecha= digitalRead(BOTON_ATRAS_DERECHA); // lee el estado del Boton
  val_izquierda= digitalRead(BOTON_IZQUIERDA); // lee el estado del Boton
  val_derecha= digitalRead(BOTON_DERECHA); // lee el estado del Boton
  val_claxon= digitalRead(BOTON_CLAXON); // lee el estado del Boton
  val_stop= digitalRead(BOTON_STOP); // lee el estado del Boton

  //ADELANTE
  if ((val_adelante == HIGH) && (old_val_adelante == LOW)){
    state_adelante = 1-state_adelante;
    delay(10);
  }
  old_val_adelante = val_adelante; // valor del antiguo estado
  if (state_adelante==1){
    state_atras = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16718055, 32);
    Serial.print("SENDING DATA ADELANTE: ");
    Serial.println(count);
  }

  //ADELANTE IZQUIERDA
  if ((val_adelante_izquierda == HIGH) && (old_val_adelante_izquierda == LOW)){
    state_adelante_izquierda = 1-state_adelante_izquierda;
    delay(10);
  }
  old_val_adelante_izquierda = val_adelante_izquierda; // valor del antiguo estado
  if (state_adelante_izquierda==1){
    state_atras = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16724175, 32);
    Serial.print("SENDING DATA ADELANTE IZQUIERDA: ");
    Serial.println(count);
  }

  //ADELANTE DERECHA
  if ((val_adelante_derecha == HIGH) && (old_val_adelante_derecha == LOW)){
    state_adelante_derecha = 1-state_adelante_derecha;
    delay(10);
  }
  old_val_adelante_derecha = val_adelante_derecha; // valor del antiguo estado
  if (state_adelante_derecha==1){
    state_atras = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16743045, 32);
    Serial.print("SENDING DATA ADELANTE DERECHA: ");
    Serial.println(count);
  }

  //ATRAS
  if ((val_atras == HIGH) && (old_val_atras == LOW)){
    state_atras=1-state_atras;
    delay(10);
  }
  old_val_atras = val_atras; // valor del antiguo estado
  if (state_atras==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16730805, 32);
    Serial.print("SENDING DATA ATRAS: ");
    Serial.println(count);
  }  

  //ATRAS IZQUIERDA
  if ((val_atras_izquierda == HIGH) && (old_val_atras_izquierda == LOW)){
    state_atras_izquierda=1-state_atras_izquierda;
    delay(10);
  }
  old_val_atras_izquierda = val_atras_izquierda; // valor del antiguo estado
  if (state_atras_izquierda==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16728765, 32);
    Serial.print("SENDING DATA ATRAS IZQUIERDA: ");
    Serial.println(count);
  }  

  //ATRAS DERECHA
  if ((val_atras_derecha == HIGH) && (old_val_atras_derecha == LOW)){
    state_atras_derecha=1-state_atras_derecha;
    delay(10);
  }
  old_val_atras_derecha = val_atras_derecha; // valor del antiguo estado
  if (state_atras_derecha==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras = 0;
    count++;
    emitter.send(NEC, 16732845, 32);
    Serial.print("SENDING DATA ATRAS DERECHA: ");
    Serial.println(count);
  }  

  //IZQUIERDA
  if ((val_izquierda == HIGH) && (old_val_izquierda == LOW)){
    state_izquierda=1-state_izquierda;
    delay(10);
  }
  old_val_izquierda = val_izquierda; // valor del antiguo estado
  if (state_izquierda==1){
    state_adelante = 0;
    state_atras = 0;
    state_derecha = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16716015, 32);
    Serial.print("SENDING DATA IZQUIERDA: ");
    Serial.println(count);
  }  

  //DERECHA
  if ((val_derecha == HIGH) && (old_val_derecha == LOW)){
    state_derecha=1-state_derecha;
    delay(10);
  }
  old_val_derecha = val_derecha; // valor del antiguo estado
  if (state_derecha==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_atras = 0;
    state_stop = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16734885, 32);
    Serial.print("SENDING DATA DERECHA: ");
    Serial.println(count);
  }  

  //CLAXON
  if ((val_claxon == HIGH) && (old_val_claxon == LOW)){
    state_claxon=1-state_claxon;
    delay(10);
  }
  old_val_claxon = val_claxon; // valor del antiguo estado
  if (state_claxon==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_stop = 0;
    state_atras = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16754775, 32);
    Serial.print("SENDING DATA CLAXON: ");
    Serial.println(count);
  } 

  //STOP
  if ((val_stop == HIGH) && (old_val_stop == LOW)){
    state_stop=1-state_stop;
    delay(10);
  }
  old_val_stop = val_stop; // valor del antiguo estado
  if (state_stop==1){
    state_adelante = 0;
    state_izquierda = 0;
    state_derecha = 0;
    state_atras = 0;
    state_claxon = 0;
    state_adelante_izquierda = 0;
    state_adelante_derecha = 0;
    state_atras_izquierda = 0;
    state_atras_derecha = 0;
    count++;
    emitter.send(NEC, 16726215, 32);
    Serial.print("SENDING DATA STOP: ");
    Serial.println(count);
    Serial.println(state_stop);
  }  
  
}
