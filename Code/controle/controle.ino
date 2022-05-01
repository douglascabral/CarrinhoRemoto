int PIN_JOYSTICK_EIXO_Y = 36; // Pino número 3 da placa
int PIN_JOYSTICK_EIXO_X = 39; // Pino número 4 da placa

void setup() {
  pinMode(PIN_JOYSTICK_EIXO_Y, INPUT);
  pinMode(PIN_JOYSTICK_EIXO_X, INPUT);    
}

void loop() {
  int x = analogRead(PIN_JOYSTICK_EIXO_X);
  int y = analogRead(PIN_JOYSTICK_EIXO_Y);

  x = map(x, 0, 4095, 0, 255);
  y = map(y, 0, 4095, 0, 255);
  
  Serial.print("X: ");
  Serial.println(x);

  Serial.print("Y: ");
  Serial.println(y);
}
