#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Configurações do Blutooth
BluetoothSerial bluetooth;
char DEVICE_BAME_BLUETOOTH[] = "CarrinhoBluetooth"; // Nome do dispositivo para parear

// Configurações do Servo Motor usado na direção do carrinho
Servo motorDirecao;
int PIN_SERVO_MOTOR_DIRECAO = 13;
int MOTOR_DIRECAO_INITIAL_POSITION = 90;
int MOTOR_DIRECAO_MAX_LEFT_POSITION = 135;
int MOTOR_DIRECAO_MAX_RIGHT_POSITION = 45;

// Configurações dos motores para tração do carrinho
int PIN_MOTOR_A_1 = 14;
int PIN_MOTOR_A_2 = 12;
int PIN_MOTOR_B_1 = 26;
int PIN_MOTOR_B_2 = 27;

// Configurações de comunicação entre os devices
int MODULO_DIRECAO = 2000;
int MODULO_TRACAO  = 1000;

// Configurações iniciais
void setup() {
  Serial.begin(115200);
  bluetooth.begin(DEVICE_BAME_BLUETOOTH); 
  Serial.println("Conexão bluetooth disponível");  
  
  motorDirecao.setPeriodHertz(50);
  motorDirecao.attach(PIN_SERVO_MOTOR_DIRECAO, 500, 2400);
  motorDirecao.write(MOTOR_DIRECAO_INITIAL_POSITION);

  pinMode(PIN_MOTOR_A_1, OUTPUT);
  pinMode(PIN_MOTOR_A_2, OUTPUT);
  pinMode(PIN_MOTOR_B_1, OUTPUT);
  pinMode(PIN_MOTOR_B_2, OUTPUT);
}

/**
 * Movimenta o carrinho para a frente
 * @param int velocidade Velocidade de 0 a 255 => Tensão enviada para a ponte H
 */
void tracaoFrente(int velocidade) {
  digitalWrite(PIN_MOTOR_A_1, velocidade);
  digitalWrite(PIN_MOTOR_A_2, LOW);
  digitalWrite(PIN_MOTOR_B_1, velocidade);
  digitalWrite(PIN_MOTOR_B_2, LOW);
}

/**
 * Movimenta o carrinho para a trás
 * @param int velocidade Velocidade de 0 a 255 => Tensão enviada para a ponte H
 */
void tracaoTras(int velocidade) {
  digitalWrite(PIN_MOTOR_A_1, LOW);
  digitalWrite(PIN_MOTOR_A_2, velocidade);
  digitalWrite(PIN_MOTOR_B_1, LOW);
  digitalWrite(PIN_MOTOR_B_2, velocidade);
}

void loop() {
  if (bluetooth.available()){
    // Foi escolhido valores numéricos para comunicação por questões de performance
    int valor = bluetooth.parseInt();

    // Comunicação: 
    // Valor igual ou maior que 2000 ==> O que sobra do módulo representa o motor de direção de 0 a 255
    // Valor igual ou maior que 1000 ==> O que sobra do módulo representa a velocidade da tração de 0 a 255
    // Qualquer outro valor menor que 1000 poderá ser usado para controlar funcionalidades adicionais: LED, etc...
    if ( valor > MODULO_DIRECAO ) {
      int direcao = valor % MODULO_DIRECAO;
      direcao = map(direcao, 255, 0, MOTOR_DIRECAO_MAX_LEFT_POSITION, MOTOR_DIRECAO_MAX_RIGHT_POSITION);
      motorDirecao.write(direcao);
    } else if ( valor > MODULO_TRACAO ) {
      int tracao = valor % MODULO_TRACAO;
      if ( tracao > 127 ) {
        int velocidade = map(tracao, 127, 255, 0, 255);
        tracaoFrente(velocidade);
      } else {
        int velocidade = map(tracao, 127, 0, 255, 0);
        tracaoFrente(velocidade);
      }// if
    }// if
  }// if
}
