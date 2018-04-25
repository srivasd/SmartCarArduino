/****************************************/
/************ EMISOR INFRARROJOS ***********/
/****************************************/
/* Autor: Sergio Rivas Degado. */
/****************************************/


#include <IRLib.h>
#include <IRLibMatch.h>
#include <IRLibTimer.h>

IRsend emitter;
int count;
const int boton_adelante = 12;
int val_adelante;
const int boton_atras = 8;
int val_atras;
const int boton_stop = A1;
int val_stop;
const int boton_izquierda = A0;
int val_izquierda;
const int boton_derecha = A2;
int val_derecha;
const int boton_claxon = A3;
int val_claxon;
const int boton_adelante_izquierda = 5;
int val_adelante_izquierda;
const int boton_adelante_derecha = 4;
int val_adelante_derecha;
const int boton_atras_izquierda = 9;
int val_atras_izquierda;
const int boton_atras_derecha = 7;
int val_atras_derecha;

void setup() {
  Serial.begin(9600);
  pinMode(boton_adelante, INPUT);
  pinMode(boton_atras, INPUT);
  pinMode(boton_stop, INPUT);
  pinMode(boton_izquierda, INPUT);
  pinMode(boton_derecha, INPUT);
  pinMode(boton_claxon, INPUT);
  pinMode(boton_adelante_izquierda, INPUT);
  pinMode(boton_adelante_derecha, INPUT);
  pinMode(boton_atras_izquierda, INPUT);
  pinMode(boton_atras_derecha, INPUT);
  
  count = 0;
}

void loop() {
  val_adelante = digitalRead(boton_adelante);
  val_atras = digitalRead(boton_atras);
  val_stop = digitalRead(boton_stop);
  val_izquierda = digitalRead(boton_izquierda);
  val_derecha = digitalRead(boton_derecha);
  val_claxon = digitalRead(boton_claxon);
  val_adelante_izquierda = digitalRead(boton_adelante_izquierda);
  val_adelante_derecha = digitalRead(boton_adelante_derecha);
  val_atras_izquierda = digitalRead(boton_atras_izquierda);
  val_atras_derecha = digitalRead(boton_atras_derecha);
  
  if(val_adelante == HIGH){
    count++;
    emitter.send(NEC, 16718055, 32);
    Serial.print("SENDING DATA ADELANTE: ");
    Serial.println(count);
  }

  if(val_atras == HIGH){
    count++;
    emitter.send(NEC, 16730805, 32);
    Serial.print("SENDING DATA ATRAS: ");
    Serial.println(count);
  }

  if(val_stop == HIGH){
    count++;
    emitter.send(NEC, 16726215, 32);
    Serial.print("SENDING DATA STOP: ");
    Serial.println(count);
  }

  if(val_izquierda == HIGH){
    count++;
    emitter.send(NEC, 16716015, 32);
    Serial.print("SENDING DATA IZQUIERDA: ");
    Serial.println(count);
  }

  if(val_derecha == HIGH){
    count++;
    emitter.send(NEC, 16734885, 32);
    Serial.print("SENDING DATA DERECHA: ");
    Serial.println(count);
  }

  if(val_claxon == HIGH){
    count++;
    emitter.send(NEC, 16754775, 32);
    Serial.print("SENDING DATA CLAXON: ");
    Serial.println(count);
  }

  if(val_adelante_izquierda == HIGH){
    count++;
    emitter.send(NEC, 16724175, 32);
    Serial.print("SENDING DATA ADELANTE IZQUIERDA: ");
    Serial.println(count);
  }

  if(val_adelante_derecha == HIGH){
    count++;
    emitter.send(NEC, 16743045, 32);
    Serial.print("SENDING DATA ADELANTE DERECHA: ");
    Serial.println(count);
  }

  if(val_atras_izquierda == HIGH){
    count++;
    emitter.send(NEC, 16728765, 32);
    Serial.print("SENDING DATA ATRAS IZQUIERDA: ");
    Serial.println(count);
  }

  if(val_atras_derecha == HIGH){
    count++;
    emitter.send(NEC, 16732845, 32);
    Serial.print("SENDING DATA ATRAS DERECHA: ");
    Serial.println(count);
  }
}
