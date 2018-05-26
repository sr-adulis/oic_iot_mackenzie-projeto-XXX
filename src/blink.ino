/*
  Código de execução de movimentação do servo
*/

#include <Servo.h>

int Ex_key = 0;

int controller_key = 0;

int ghost_ex_key = 0;

Servo servo_A2;

long readUltrasonicDistance(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}

void setup()
{
  pinMode(7, INPUT);
  servo_A2.attach(A2);

  pinMode(A1, INPUT);
  controller_key = -1;
}

void loop()
{
  
  // Determina qual piro recebe o sinal externo
  Ex_key = digitalRead(7);
  // verifica a atualização do status de entrada e faz a função de chave de controle
  if (Ex_key < HIGH && ghost_ex_key != HIGH) {
    controller_key = (controller_key * -1);
  }
  //
  // Deixa) o servo no estado "Idle"
  servo_A2.write(0);
  //
  // Valida  chave de controle
  while (0.01723 * readUltrasonicDistance(A1) <= 30 || controller_key == 1) {
    // muda estado do servo para abertura 
    servo_A2.write(90);
    delay(1000);
  }
  //salva qual foi o estado da chave externa nessa sequencia
  ghost_ex_key = Ex_key;
}
