#include <VirtualWire.h>


int valor_recebido_RF;
char recebido_RF_char[4]; 

void setup() 
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(5000); 
  //Inicia a recepcao  
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop()
{
  
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) 
    {
    int i;
        for (i = 0; i < buflen; i++)
       {            
          //Armazena os caracteres recebidos  
          recebido_RF_char[i] = char(buf[i]);
       }
       recebido_RF_char[buflen] = '\0';
       
       //Converte o valor recebido para integer
       valor_recebido_RF = atoi(recebido_RF_char);
         
       //Mostra no serial monitor o valor recebido
       Serial.print("Recebido: ");
       Serial.print(valor_recebido_RF);
       //Altera o estado do led conforme o numero recebido
       if (valor_recebido_RF == 0)
       {
            digitalWrite(2, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(9, LOW);
       }
       if (valor_recebido_RF == 1)
       {
            digitalWrite(2,HIGH);
            digitalWrite(4,HIGH);
            digitalWrite(9,LOW);
       }
              if (valor_recebido_RF == 2)
       {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(9, HIGH);
       }
    }
}
