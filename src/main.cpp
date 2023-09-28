#include <PIN.h>
#include <function_math.h>
#include <Arduino.h>
#include <function_math.cpp>


int L = 0;
int N = 0;
int B = 0;
int H = 0;
int S = 0;
int J = 0;
bool xd = false;

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


        Medicion::TensionADC();
        Medicion::TensionRed();

      if(Cronometro(1000) == true){
        if(VredR <= TensionMax && VredR >= TensionMin && VredS <= TensionMax && VredS >= TensionMin && VredT <= TensionMax && VredT >= TensionMin){
        selectoraModoRedSum = 0;
          RedOn();
          flag0 = 0;
          N = 0;
          B = 0;
        }
      }
    }

      else if(VredR <= TensionMin || VredR >= TensionMax || VredS <= TensionMin || VredS >= TensionMax || VredT <= TensionMin || VredT >= TensionMax){
        RedSumOff();
        //Serial.println("ALGO EN LAS FASES FALLO"); //avisa si hay alguna fase o todas las fases sin electricidad
        periodoEncendido = millis() - tiempoAhora;
        
        if(N == 0){
        tiempoAhora = millis();
        N++;
      }

    if(Cronometro(1000) == true){
      if(B == 0){
        tiempoAhora = millis();
        B++;
      }

      while(Cronometro(1000) == false && flag0 == 0){ //DA ARRANQUE AL GRUPO POR 5 SEG
        bitSet(shadowRegister, 2);
        shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
        digitalWrite(RCLK, HIGH);
        digitalWrite(RCLK, LOW);
        periodoEncendido = millis() - tiempoAhora;
        L = 0;
        B = 0;
        H = 0;
        S = 1;
        J = 0;
    }
  }

  
      if(S == 1){ //CORTA EL ARRANQUE DEL GRUPO
        bitClear(shadowRegister, 2);
        shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
        digitalWrite(RCLK, HIGH);
        digitalWrite(RCLK, LOW);
        flag0 = 2;
        S = 0;
      }


      if(H == 0){
        tiempoAhora = millis();
        H++;
      }

      if(J == 0 && (Cronometro(1000) == true) && VsuministroR >= TensionMin && VsuministroR <= TensionMax && VsuministroS >= TensionMin && VsuministroS <= TensionMax && VsuministroT >= TensionMin && VsuministroT <= TensionMax){
          Serial.println("SE ENCENDIO EL GRUPO"); //avisa que se encendio el grupo electrogeno exitosamente
          Serial.println("se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey"); //avisa que se encendio el grupo electrogeno exitosamente y las fases del grupo estan okey
          selectoraModoRedSum = 1;
          SumOn();
          flag0 = 1;
          xd = true;
      }
      
      else{
        Serial.println("el encendido del grupo electrogeno fallo"); //avisa que el encendido del grupo electrogeno fallo
        if(xd == true){
          J = 1;
          xd = false;
        }

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