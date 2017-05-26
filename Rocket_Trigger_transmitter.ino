/*
  ROCKET TRIGGER TRANSMITTER

 use a RF 433 MHZ Transmitter
The code transmits three different numbers according to the buttons that are pressed. 

If the buttons won't be pressed, it will send "0".
If the security button and the launch button won't be pressed, it will send "1".
If the security button and the launch button are pressed, it will send "2".


You can use the sinal 0 to make sure that the reciever and transmitter are in range.
The sinal 1 can be used by your discretion. For instance, you can use it to record the temperature data after the launching, stopping the record when you release the security button. 
The sinal 2 is used to launch the rocket.
*/

/*
  ACIONADOR DE FOGUETE- TRANSMISSOR
  
  utiliza um RF 433 MHZ Transmitter
  
O código transmite 3 números diferentes de acordo com os botões que são pressionados.

Se os botões não forem pressionados, ele enviará "0".
Se o botão de segurança e o botão de inicialização não forem pressionados, ele enviará "1".
Se o botão de segurança e o botão de inicialização forem pressionados, ele enviará "2".

Você pode usar o sinal 0 para se certificar de que o receptor e o transmissor estão no alcance.
O sinal 1 pode ser usado por sua discrição. Por exemplo, você pode usá-lo para gravar os dados de temperatura após o lançamento, interrompendo o registro quando você liberar o botão de segurança.
O sinal 2 é usado para lançar o foguete.
*/

#include <VirtualWire.h>
int bot1 = 2; //botão de segurança  
int bot2 = 6; //botão lançador 
int led = 8;
char msg[4];
int txt = 0;
void setup() {
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
  pinMode(led, OUTPUT);
  vw_set_tx_pin(4);
  vw_setup(5000);
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
}
void loop() {
  if (digitalRead(bot1) == HIGH) {
    if (digitalRead(bot2) == HIGH) {
      txt = 2;
      digitalWrite(led, HIGH);
      delay(250);
    }
    else {
      txt = 1;
      delay(150);
      digitalWrite(led, HIGH);
      delay(150);
      digitalWrite(led, LOW);
    }
  }
  else {
    delay(300);
    txt = 0;
  }
  itoa(txt, msg, 10);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
  digitalWrite(led, LOW);
}
