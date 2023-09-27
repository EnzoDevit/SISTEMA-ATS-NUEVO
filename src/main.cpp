#include <PIN.h>
#include <function_math.h>
#include <Arduino.h>
#include <function_math.cpp>


int L = 0;


void setup(){
  beginSetup();
  digitalWrite(Buzzer, HIGH);
  delay(500);
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
      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
      
    if(VredR <= TensionMax && VredR >= TensionMin && VredS <= TensionMax && VredS >= TensionMin && VredT <= TensionMax && VredT >= TensionMin){
      if(L == 0){
        tiempoAhora = millis();
        L++;
      }

      do{
        Medicion::TensionADC();
        Medicion::TensionRed();
        digitalWrite(Buzzer, HIGH);
        delay(500);
        digitalWrite(Buzzer, LOW);
        delay(500);
      }
      while(Cronometro(5000) == false);

      if(VredR <= TensionMax && VredR >= TensionMin && VredS <= TensionMax && VredS >= TensionMin && VredT <= TensionMax && VredT >= TensionMin){
        selectoraModoRedSum = 0;
          RedOn();
          flag0 = 0;
      }
    }

      else if(VredR <= TensionMin || VredR >= TensionMax || VredS <= TensionMin || VredS >= TensionMax || VredT <= TensionMin || VredT >= TensionMax){
        RedSumOff();
        //Serial.println("ALGO EN LAS FASES FALLO"); //avisa si hay alguna fase o todas las fases sin electricidad
        periodoEncendido = millis() - tiempoAhora;
        

      while(periodoEncendido < timeTransOn && flag0 == 0){ //DA ARRANQUE AL GRUPO POR 5 SEG
        bitSet(shadowRegister, 2);
        shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
        digitalWrite(RCLK, HIGH);
        digitalWrite(RCLK, LOW);
        digitalWrite(Buzzer, HIGH);
        delay(500);
        digitalWrite(Buzzer, LOW);
        delay(500);
        periodoEncendido = millis() - tiempoAhora;
        L = 0;
             
    }

if(periodoEncendido >= timeTransOn){ //CORTA EL ARRANQUE DEL GRUPO
        bitClear(shadowRegister, 2);
        shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
        digitalWrite(RCLK, HIGH);
        digitalWrite(RCLK, LOW);
        flag0 = 2;
      }

      periodoEncendido = millis() - tiempoAhora;

      if(periodoEncendido >= timeTransOn && periodoEncendido <= TimeStabilitySum && VsuministroR >= TensionMin && VsuministroR <= TensionMax && VsuministroS >= TensionMin && VsuministroS <= TensionMax && VsuministroT >= TensionMin && VsuministroT <= TensionMax){
          Serial.println("SE ENCENDIO EL GRUPO"); //avisa que se encendio el grupo electrogeno exitosamente
          Serial.println("se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey"); //avisa que se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey
          selectoraModoRedSum = 1;
          SumOn();
          flag0 = 1;
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