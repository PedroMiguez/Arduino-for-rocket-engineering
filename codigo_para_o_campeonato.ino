#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
double pp, h , hmax;
long t,ti;
int estagio = 1,i; 
/*
estagio 1 antes do lançamento
estagio 2 lançamento 
estagio 3 paraquedas ativado
estagio 4 recuperação
 */
 // SD Card
#include <SPI.h>
#include <SD.h>
File arquivo;
void setup() {
  Serial.begin(115200);
  bmp.begin(1);
   pinMode(2, OUTPUT); //buzzer
 pinMode(6, OUTPUT); // ingnitor
 digitalWrite(3, LOW);
       for(i = 0; i < 10; i++){   //aviso de ligado coloque o valor que achar nescessario 
         digitalWrite( 2 , HIGH);
         delay(1000); 
         digitalWrite( 2 , LOW); 
         delay(2500);    
    }
    i=0; 
  pp=bmp.readPressure();
  hmax = 0;
  SD.begin(9);
 arquivo = SD.open("config.txt", FILE_WRITE);
 while(!SD.open("config.txt", FILE_WRITE) || !bmp.begin(1)){  //se o sd ou o barometro falharem o buzzer ficará constantemente ligado
 digitalWrite(2, HIGH);
 }
 digitalWrite(2,LOW);
 
 arquivo.print("Presao utilizada para calculo: ");
 arquivo.println(pp);
 arquivo.print("Medida no solo: ");
 h = bmp.readAltitude(pp);
 arquivo.println(h);
 arquivo.close();
 arquivo = SD.open("dados.csv", FILE_WRITE);
 arquivo.println("altura ; Tempo");
 
}

void loop() {
if(estagio==1){
  if (h > 3){
    estagio = 2;
    ti=millis();
    }
  }
if (estagio < 4){
h = bmp.readAltitude(pp);t = millis() ;
}
if(estagio==2){
  if(hmax<h){
    hmax=h;
    }
   if((h+10)<hmax){
    estagio = 3;
    if(h > 20){ //questão de segurança para não ativar em solo 
    digitalWrite(6,HIGH);
   }
   }
  }
if(estagio==3){
  if (h < 6){
    i++;
      if(i > 279){ 
    estagio=4;
    }
    }
  }
  //gravar
 if( estagio >=2){
  if(estagio <4){
  t = t - ti;
 arquivo.print(h);arquivo.print(" ; ");arquivo.println(t);
 }
 }
if (estagio == 4){
  arquivo.close();
  digitalWrite(3, LOW);
  }
  
while(estagio==4){
   digitalWrite( 2 , HIGH);
   delay(1000); 
   digitalWrite(2, LOW);
   delay(1500);
  }
  
}
