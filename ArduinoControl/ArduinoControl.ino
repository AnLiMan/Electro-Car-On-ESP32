#include <Servo.h> //Библиотека управления сервоприводами 

#define Servo1 6 // Пин сервопривода
#define ControlSignal A0 // Значение управляющего сигнала от ESP32

Servo myServo; // Объявляем переменную myServo как сервопривод
int val = 0; // Хранение значения потенциометра

void setup() {
  myServo.attach(Servo1); //Подключаем объект сервопривода
}

void loop() {
  val =  map(analogRead(ControlSignal), 0, 1019, 30, 85);
  myServo.write(val); // Задаем положение приводу
}
