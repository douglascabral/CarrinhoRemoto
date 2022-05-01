#include <ESP32Servo.h>

int PIN_SERVO_MOTOR_DIRECAO = 13;

Servo motorDirecao;
int MOTOR_DIRECAO_INITIAL_POSITION = 90;
int MOTOR_DIRECAO_MAX_LEFT_POSITION = 135;
int MOTOR_DIRECAO_MAX_RIGHT_POSITION = 45;

void setup() {
  motorDirecao.setPeriodHertz(50);
  motorDirecao.attach(PIN_SERVO_MOTOR_DIRECAO, 500, 2400);
  motorDirecao.write(MOTOR_DIRECAO_INITIAL_POSITION);
}

void loop() {
  
}
