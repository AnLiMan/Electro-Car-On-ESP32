//GPIO 2, 4, 12, 14, 13, 15, 16, 17, 25, 25, 27, 32, 33
//------Библиотеки----------
#include <DabbleESP32.h>

//----Постоянные----
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define NumberOfModes 1 // Количество режимов работы
#define Forward 14 // Пин для движения вперёд
#define Back 12 // Пин для движения назад
#define ServoPin 13 // Пин серво
#define PWMFrequency  15000 // Частота ШИМ
#define PWMChannel_0 0 // Канал ШИМ
#define PWMResolution 8 // Разрешение ШИМ

//----Переменные----
int CurrentMode = 0; // Текущий режим
bool GoForward = false; // Разрешение ехать вперёд
bool GoBack = false; // Разрешение ехать назад
uint32_t myTimer1; // Переменная прощедшего времени
int TimeOut = 100; //Таймаут времени работы для сброса флагов
int ServoPosition = 0; // Переменная хранения угла поворота серво

//-------------------------
//---------Setup-----------
//-------------------------
void setup() {
  Serial.begin(115200);

  //ledcSetup(PWMChannel_0, PWMFrequency, PWMResolution); // Создаем ШИМ с определенной частотой на опредлённом канале
  //ledcAttachPin(ServoPin, PWMChannel_0);  // Подключаем ШИМ к каналу

  pinMode(Forward, OUTPUT);
  pinMode(Back, OUTPUT);
  digitalWrite(Forward, LOW);
  digitalWrite(Back, LOW);

  Dabble.begin("Lambo_Car_Control"); //Название устройства
  GoForward = false;
  GoBack = false;
}

//---------------------------------
//---------Основной цикл-----------
//---------------------------------

void loop() {
  GamepadProssed();
  CarControl();

  if (millis() - myTimer1 >= TimeOut) {
    myTimer1 += TimeOut;
    GoForward = false;
    GoBack = false;
  }
}

//---------------------------------
//---------1. Основные режимы------
//---------------------------------

//----1.1 Чтение значений кнопок с геймпада---
void GamepadProssed () {
  Dabble.processInput(); // Функция обновления данных со смартфона

  //Кнопка вниз
  if (GamePad.isDownPressed()) {
    GoBack = true;
  }

  //Кнопка вверх
  if (GamePad.isUpPressed()) {
    GoForward = true;
  }

  //Кнопка влево
  if (GamePad.isLeftPressed()) {
    //ledcWrite(PWMChannel_0, 0);
  }

  //Кнопка вправо
  if (GamePad.isRightPressed()) {
    //ledcWrite(PWMChannel_0, 255);
  }

  //Кнопка выбора
  if (GamePad.isSelectPressed()) {
    CurrentMode++;
    if (CurrentMode > NumberOfModes) {
      CurrentMode = 0;
    }
  }
}

// ----1.2. Управление машиной----

void CarControl() {
  // Едем вперёд
  if (GoForward) {
    digitalWrite(Forward, HIGH);
    digitalWrite(Back, LOW);
  }

  // Едем назад
  else if (GoBack) {
    digitalWrite(Forward, LOW);
    digitalWrite(Back, HIGH);
  }
  else if (GoForward == false && GoBack == false) {
    digitalWrite(Forward, LOW);
    digitalWrite(Back, LOW);
  }
  //MyServo.write(ServoPosition); // Поворачиваем серво на заданный угол
}


//---------------------------------
//---2. Вспомогательные функции----
//---------------------------------


/*

   //Кнопка "крест"
  if (GamePad.isCrossPressed()) {
  }

  //Кнопка "круг"
  if (GamePad.isCirclePressed()) {
  }
  //Кнопка "квадрат"
  if (GamePad.isSquarePressed()) {
    CurrentMode
  }

  //Кнопка "треугольник"
  if (GamePad.isTrianglePressed()) {
  }
*/
