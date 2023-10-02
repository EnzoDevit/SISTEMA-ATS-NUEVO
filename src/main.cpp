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
bool flagGrupo = false;

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

 if(textMessage.indexOf("APAGAR GRUPO") != -1){
          //CORTA EL ARRANQUE DEL GRUPO
          bitClear(shadowRegister, 2);
          shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
          digitalWrite(RCLK, HIGH);
          digitalWrite(RCLK, LOW); //EN REALIDAD HAY Q SUMAR OTRA SALIDA PARA PODER CORTAR EL CONTACTO DEL GRUPO
          flagGrupo = true;
          SIM800L.println("GRUPO APAGADO");
          sendSMS(phoneNumber, "GRUPO APAGADO");
          textMessage = "";
      }

  if(textMessage.indexOf("ENCENDER GRUPO") != -1){
          //ARRANQUE DEL GRUPO
          SumStart();
          flagGrupo = false;
          SIM800L.println("GRUPO ENCENDIDO");
          sendSMS(phoneNumber, "GRUPO ENCENDIDO");
          textMessage = "";
      }

  switch(selectoraModoAutoManual){

      case 0: //MODO AUTOMATICO
      {
      printCambioModo(0);
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
        FunctionsSMS(true, false);
        //Serial.println("ALGO EN LAS FASES FALLO"); //avisa si hay alguna fase o todas las fases sin electricidad
        periodoEncendido = millis() - tiempoAhora;
        
        if(N == 0){
        tiempoAhora = millis();
        N++;
      }

      SumStart();

    if(flagGrupo == false){
      if(S == 1){ //CORTA EL ARRANQUE DEL GRUPO
        bitClear(shadowRegister, 2);
        shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
        digitalWrite(RCLK, HIGH);
        digitalWrite(RCLK, LOW);
        flag0 = 2;
        S = 0;
        flagGrupo = true;
      }
    }


      if(H == 0){
        tiempoAhora = millis();
        H++;
      }

    if(Cronometro(1000) == true){
      Medicion::TensionADC();
      Medicion::TensionSuministro();
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
        FunctionsSMS(false, true);
        Serial.println("el encendido del grupo electrogeno fallo"); //avisa que el encendido del grupo electrogeno fallo
        if(xd == true){
          J = 1;
          xd = false;
        }

    }
  }
}

break;
  
  case 1:
  {
    printCambioModo(0);
    if(selectoraModoAutoManual == 1){
      CambioModos();
      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
      modRedSum();
  }
}

break;

  }
}