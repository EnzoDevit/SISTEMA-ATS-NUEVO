#include <PIN.h>
#include <function_math.h>
#include <Arduino.h>
#include <function_math.cpp>

int periodoEncendido = 0; //para caluclo de tiempo de encendido
const int timeTransOn = 5000; //tiempo Transcurrido Para Encender
const int periodoRetraso = 5000; //constante de tiempo para el retraso en la transferencia de energia
const int TimeStabilitySum = 15000; //tiempo de estabilidad del suministro
int TensionMax = 260;
int TensionMin = 210;

void setup(){
  beginSetup();
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
}

void loop(){

    while (SIM800L.available()) { // Leer el mensaje entrante
    char c = SIM800L.read();
    textMessage += c;
  }
 // RTC();

  switch(selectoraModoAutoManual){

      case 0: //MODO AUTOMATICO
      {
      CambioModos();
      /*
      Serial.print(VredR);
      Serial.print("\t");
      Serial.print(VredS);
      Serial.print("\t");
      Serial.println(VredT);
      */

      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
/*
      Serial.print(VsuministroR);
      Serial.print("\t");
      Serial.print(VsuministroS);
      Serial.print("\t");
      Serial.println(VsuministroT);
*/
      long unsigned int tiempoAhora = 0; 
      tiempoAhora = millis();
      if(VredR <= TensionMax && VredR >= TensionMin && VredS <= TensionMax && VredS >= TensionMin && VredT <= TensionMax && VredT >= TensionMin){
          selectoraModoRedSum = 0;
          RedOn();
          digitalWrite(Buzzer, HIGH);
          delay(200);
          digitalWrite(Buzzer, LOW);
        }

      else if(VredR <= TensionMin || VredR >= TensionMax || VredS <= TensionMin || VredS >= TensionMax || VredT <= TensionMin || VredT >= TensionMax){
        RedSumOff();
        Serial.println("ALGO EN LAS FASES FALLO"); //avisa si hay alguna fase o todas las fases sin electricidad
        periodoEncendido = millis() - tiempoAhora;

      if(tiempoAhora <= timeTransOn){ //DA ARRANQUE AL GRUPO POR 5 SEG
          bitSet(shadowRegister, 2);
          shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
          digitalWrite(RCLK, HIGH);
          digitalWrite(RCLK, LOW);
      }

      else{ //CORTA EL ARRANQUE DEL GRUPO
          bitClear(shadowRegister, 2);
          shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
          digitalWrite(RCLK, HIGH);
          digitalWrite(RCLK, LOW);
        }

      if(tiempoAhora >= timeTransOn && tiempoAhora <= TimeStabilitySum && VsuministroR >= TensionMin && VsuministroR <= TensionMax && VsuministroS >= TensionMin && VsuministroS <= TensionMax && VsuministroT >= TensionMin && VsuministroT <= TensionMax){
          Serial.println("SE ENCENDIO EL GRUPO"); //avisa que se encendio el grupo electrogeno exitosamente
          Serial.println("se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey"); //avisa que se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey
          selectoraModoRedSum = 1;
          SumOn();
      }
      
      else{
        Serial.println("el encendido del grupo electrogeno fallo"); //avisa que el encendido del grupo electrogeno fallo
      }

      /*
      if(textMessage.indexOf("APAGAR GRUPO") != -1){
        SIM800L.println("APAGAR GRUPO");
        textMessage = "";
        //CORTA EL ARRANQUE DEL GRUPO
          bitClear(shadowRegister, 2);
          shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
          digitalWrite(RCLK, HIGH);
          digitalWrite(RCLK, LOW); //EN REALIDAD HAY Q SUMAR OTRA SALIDA PARA PODER CORTAR EL CONTACTO DEL GRUPO



      }
    */
    
  }
}
break;
  
  case 1:
    if(selectoraModoAutoManual == 1){
      CambioModos();
      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
      modRedSum();



  }

 break;

  }
}