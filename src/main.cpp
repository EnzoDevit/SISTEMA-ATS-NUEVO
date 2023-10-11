#include <PIN.h>
#include <function_math.h>
#include <Arduino.h>
#include <function_math.cpp>




void setup(){
  beginSetup();
 // digitalWrite(Buzzer, HIGH);
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

 muestreo();
  switch(selectoraModoAutoManual){

      case 0: //MODO AUTOMATICO
      {
      printCambioModo(0);
      CambioModos();
      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
      muestreo();
      
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

      if(Cronometro(1000) == true){
      if(B == 0){
        tiempoAhora = millis();
        B++;
      }

      while(Cronometro(5000) == false && flag0 == 0 && flagGrupo == false){ //DA ARRANQUE AL GRUPO POR 5 SEG
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
        if(F==0)
          tft.fillScreen(ILI9341_WHITE);
        F = 1;
        muestreo();
    }
  }

  if(F==1){
    tft.fillScreen(ILI9341_WHITE);
    F = 0;
  }

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
    printCambioModo(1);
    if(selectoraModoAutoManual == 1){
      CambioModos();
      Medicion::TensionADC();
      Medicion::TensionRed();
      Medicion::TensionSuministro();
      modRedSum();
      muestreo();
  }
}

break;

  }
}