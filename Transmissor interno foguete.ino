
#include <VirtualWire.h>

//Define pinos Led e Botao
const int ledPin = 13;
char Valor_CharMsg[4]; 
//Armazena estado led = ligar/desligar
int estado = 0;

void setup() 
{
  Serial.begin(9600);   
  pinMode(2,OUTPUT);
  pinMode(6,OUTPUT);
  //Pino ligado ao pino DATA do transmissor RF
  vw_set_tx_pin(4);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(5000);
  Serial.println("Trasmissao modulo RF");
}

void loop() 
{
    //Altera o estado do led
    estado = 0;
    //Converte valor para envio
    itoa(estado,Valor_CharMsg,10);
    //Liga o led da porta 13 para indicar envio dos dados
    digitalWrite(13, true);
    //Envio dos dados
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    //Aguarda envio dos dados
    vw_wait_tx();
    //Desliga o led da porta 13 ao final da transmissao
    Serial.println(Valor_CharMsg);
    delay(5000);
    //

    // 1 buzzer ativado

    estado = 1;
    digitalWrite(6,HIGH);
    delay(10);
    itoa(estado,Valor_CharMsg,10);
    //Liga o led da porta 13 para indicar envio dos dados
    digitalWrite(13, true);
    //Envio dos dados
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    //Aguarda envio dos dados
    vw_wait_tx();
    //Desliga o led da porta 13 ao final da transmissao
    Serial.println(Valor_CharMsg);
     digitalWrite(6,LOW);
    delay(5000);

    // 2 buzzer

    estado = 2;
    digitalWrite(6,HIGH);
    digitalWrite(2,HIGH);
    delay(10);
    itoa(estado,Valor_CharMsg,10);
    //Liga o led da porta 13 para indicar envio dos dados
    digitalWrite(13, true);
    //Envio dos dados
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    //Aguarda envio dos dados
    vw_wait_tx();
    //Desliga o led da porta 13 ao final da transmissao
    Serial.println(Valor_CharMsg);
    digitalWrite(6,LOW);
    digitalWrite(2,LOW);
    delay(5000);
     
     
     //
   
}
