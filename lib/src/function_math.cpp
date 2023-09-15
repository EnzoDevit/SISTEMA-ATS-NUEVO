/*************************************************

Source de function_math.h


*******************************************************/

#include "function_math.h"
#include "PIN.h"
#include <SoftwareSerial.h>
#include <Wire.h>
//#include <RTClib.h>
SoftwareSerial SIM800L(2,1); // RX, TX
String phoneNumber = "+541162882372"; // Número de teléfono para enviar
String textMessage = ""; //Variable para almacenar el mensaje entrante

void beginSetup(){
   pinMode(SER, OUTPUT);
   pinMode(SRCLK, OUTPUT);
   pinMode(RCLK, OUTPUT);
   pinMode(medicionMux, INPUT);
   pinMode(Buzzer,OUTPUT);
   SIM800L.begin(57600); // Iniciar comunicación con el módulo SIM8default
   Serial.begin(57600);
   Wire.begin(); //Modulo rtc
   //rtc.begin(); //Modulo rtc
   delay(50); //PREGUNTAR
   SIM800L.println("AT+CMGF=1"); // Establecer el modo de texto SMS
   delay(50); //PTRGUNTAR              
   SIM800L.println("AT+CNMI=2,2,0,0,0"); // Enviar los mensajes SMS recibidos al puerto serie
}



/*!
  @brief se encarga de modificar una variable del tipo byte, llamada shadowRegister, estas funciones modifican sus ultimos 4 bits, que modifican la salida de los ultimos 4 bits de la salida del shift register, que controlan las entradas del multiplexor que controlan sus 16 entradas salidas
  @return si bien es una funcion que no retorna un valor, ustedes lo van a incluir dentro del loop y de los casos de switch para que la funcion pueda ser llamada en esos espacios del codigo, es simplemente una funcion que trabaja con datos del codigo, no hay que pasarle valores
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto.Como agregado, todas las funciones que se llamen adcRed_X, aplican a esta descripcion para chanchez y emo, con amor encito.
*/
void adcRed_R(void){ //0000
    bitClear(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void adcRed_S(void){ //0001 ETSAN AL REVEZ POR ELMUX QUE LOS LEE ASI
    bitSet(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void adcRed_T(void){ //0010 ESTAN AL REVEZ POR ELMUX QUE LOS LEE ASI
    bitClear(shadowRegister, 5); 
    bitSet(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void adcSum_R(void){ //0011 ESTAN AL REVEZ POR ELMUX QUE LOS LEE ASI
    bitSet(shadowRegister, 5);
    bitSet(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}
void adcSum_S(void){ //0100 ESTAN AL REVEZ POR ELMUX QUE LOS LEE ASI
    bitClear(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitSet(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}
void adcSum_T(void){ //0101 ESTAN AL REVEZ POR ELMUX QUE LOS LEE ASI
    bitSet(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitSet(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void Vbat(void){ //0110
    bitClear(shadowRegister, 5);
    bitSet(shadowRegister, 6);
    bitSet(shadowRegister, 7);
    bitClear(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void modManAuto(void){ //1000 ESTAN AL REVEZ POR EL MUX QUE LOS LEE ASI
    bitClear(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitSet(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void modRedSum(void){ //1001
    bitSet(shadowRegister, 5);
    bitClear(shadowRegister, 6);
    bitClear(shadowRegister, 7);
    bitSet(shadowRegister, 4);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

void RedOn(void){ //1000 primeros 4 bits
  if(selectoraModoRedSum == 0){
    bitClear(shadowRegister, 1);
    bitSet(shadowRegister, 0);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
  }
}

void SumOn(void){ //1000 primeros 4 bits
  if(selectoraModoRedSum == 1){
    bitClear(shadowRegister, 0);
    bitSet(shadowRegister, 1);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
  }
}

void RedSumOff(void){ //0000 primeros 4 bits
    bitClear(shadowRegister, 0);
    bitClear(shadowRegister, 1);
    bitClear(shadowRegister, 3);
    shiftOut(SER, SRCLK, MSBFIRST, shadowRegister);
    digitalWrite(RCLK, HIGH);
    digitalWrite(RCLK, LOW);
}

/*void RTC (void){
  DateTime now = rtc.now();
  
  if (now.day() == 25){
    SumOn();
  }
}
*/


/*!
  @brief se encarga de recorrer la matriz para realizar la interpolacion en cada valor de tension que ingresa al arduino y se value en la funcion "TensionADC"
  @return si bien es una funcion que no retorna un valor, ustedes lo van a incluir dentro del loop y de los casos de switch para que la funcion pueda ser llamada en esos espacios del codigo, es simplemente una funcion que trabaja con datos del codigo, no hay que pasarle valores
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto. para chanchez y emo, con amor encito.
*/
void Medicion:: TensionSuministro(void){
   
   for (unsigned int i = 0; i<filas; i++)
  {
    if (tensionArduinoInputSum_R>=matrizTabla[i][1] && tensionArduinoInputSum_R<= matrizTabla[i+1][1])
      {
        VsuministroR = Interpolacion::Suministro(tensionArduinoInputSum_R, matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }

      if (tensionArduinoInputSum_S>=matrizTabla[i][1] && tensionArduinoInputSum_S<= matrizTabla[i+1][1])
      {
         VsuministroS = Interpolacion::Suministro(tensionArduinoInputSum_S, matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }

      if (tensionArduinoInputSum_T>=matrizTabla[i][1] && tensionArduinoInputSum_T<= matrizTabla[i+1][1])
      {
        VsuministroT = Interpolacion::Suministro(tensionArduinoInputSum_T, matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }
  }
}

/*!
  @brief se encarga de recorrer la matriz para realizar la interpolacion en cada valor de tension que ingresa al arduino y se value en la funcion "TensionADC"
  @return si bien es una funcion que no retorna un valor, ustedes lo van a incluir dentro del loop y de los casos de switch para que la funcion pueda ser llamada en esos espacios del codigo, es simplemente una funcion que trabaja con datos del codigo, no hay que pasarle valores
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto. para chanchez y emo, con amor encito.
*/
void Medicion::TensionRed(void){
   for (unsigned int i = 0; i<filas; i++)
   {
      if (tensionArduinoInputRed_R >= matrizTabla[i][1] && tensionArduinoInputRed_R <= matrizTabla[i+1][1])
      {
         VredR = Interpolacion::Red(tensionArduinoInputRed_R, matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }

      if (tensionArduinoInputRed_S >= matrizTabla[i][1] && tensionArduinoInputRed_S <= matrizTabla[i+1][1])
      {
         VredS = Interpolacion::Red(tensionArduinoInputRed_S, matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }
  
      if (tensionArduinoInputRed_T >= matrizTabla[i][1] && tensionArduinoInputRed_T <= matrizTabla[i+1][1])
      {
         VredT = Interpolacion::Red(tensionArduinoInputRed_T , matrizTabla[i][1],matrizTabla[i+1][1], matrizTabla[i][0], matrizTabla [i+1][0]);
      }
   }
}

/*!
  @brief se encarga de hacer las mediciones de tension de red y del suministro, es para la tension despues del ADC del arduino
  @return si bien es una funcion que no retorna un valor en especial, ustedes lo van a incluir dentro del loop y de los casos de switch para que la funcion pueda ser llamada en esos espacios del codigo
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto. para chanchez y emo, con amor encito.
*/
void Medicion::TensionADC(void)
  {
    adcRed_R();
    int tensionAdcRed_R = analogRead(medicionMux);
    adcRed_S();
    int tensionAdcRed_S = analogRead(medicionMux);
    adcRed_T();
    int tensionAdcRed_T = analogRead(medicionMux);
    adcSum_R();
    int tensionAdcSuministro_R = analogRead(medicionMux);
    adcSum_S();
    int tensionAdcSuministro_S = analogRead(medicionMux);
    adcSum_T();
    int tensionAdcSuministro_T = analogRead(medicionMux);

    tensionArduinoInputRed_R = ((tensionAdcRed_R * 5.0) / 1024);
    tensionArduinoInputRed_S = ((tensionAdcRed_S * 5.0) / 1024);
    tensionArduinoInputRed_T = ((tensionAdcRed_T * 5.0) / 1024);
    tensionArduinoInputSum_R = ((tensionAdcSuministro_R * 5.0) / 1024);
      //Serial.print(tensionArduinoInputSum_R);
      //Serial.print("\t");
    tensionArduinoInputSum_S = ((tensionAdcSuministro_S * 5.0) / 1024);
      //Serial.print(tensionArduinoInputSum_S);
      //Serial.print("\t");
    tensionArduinoInputSum_T = ((tensionAdcSuministro_T * 5.0) / 1024);
      //Serial.println(tensionArduinoInputSum_T);
  }


  /*!
  @brief se encarga de relaizar la interpolacion en si, la palabra inline hace que la funcion se ejecute en una sola linea y no vaya a buscar la informacion de ejecucion de la funcion a donde esta definida, es como una macro. Genera que sea mas rapida su accion
  @return Esta funcion si retorna un valor, en este caso la Tension de red, le tenemos que pasar algunos valores de la matriz precargada para poder ejecutar la ecuacion lineal con el valor X a interpolar para encontrar un valor Y (Valor de tension de Red o suministro)
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto. para chanchez y emo, con amor encito.
*/
inline float Interpolacion::Red(float x, float x1, float x2, float y1, float y2){
      return y1 + ((x - x1) * (y2 - y1)) / (x2 - x1);
   }

/*!
  @brief se encarga de relaizar la interpolacion en si, la palabra inline hace que la funcion se ejecute en una sola linea y no vaya a buscar la informacion de ejecucion de la funcion a donde esta definida, es como una macro. Genera que sea mas rapida su accion
  @return Esta funcion si retorna un valor, en este caso la Tension de red, le tenemos que pasar algunos valores de la matriz precargada para poder ejecutar la ecuacion lineal con el valor X a interpolar para encontrar un valor Y (Valor de tension de Red o suministro)
  @note tienen que tener cuidado si modifican esta funcion (mejor si no lo hacen) debido a que esta funcion es uno de los corazones del codigo y por ende del proyecto. para chanchez y emo, con amor encito.
*/
inline float Interpolacion::Suministro(float j, float j1, float j2, float p1, float p2){
      return p1 + ((j - j1) * (p2 - p1)) / (j2 - j1);
   }

  void CambioModos(void){
    modManAuto();
    if(digitalRead(medicionMux) == LOW){
      selectoraModoAutoManual = 0;
    }
  
    if(digitalRead(medicionMux) == HIGH){
      selectoraModoAutoManual = 1;
    }
    
  if(selectoraModoAutoManual == 1){
    modRedSum();
    if(digitalRead(medicionMux) == LOW){
      selectoraModoRedSum = 0; //PARA ASEGURAR QUE NO ESTEN PRENDIDOS LOS DOS CONTACTORES JUNTOS
      RedOn();
    }

    if(digitalRead(medicionMux) == HIGH){
      selectoraModoRedSum = 1; //PARA ASEGURAR QUE NO ESTEN PRENDIDOS LOS DOS CONTACTORES JUNTOS
      SumOn();
    }
  }
}

void balanceoDeFasesRed(void){
  float promedioRed = (VredR + VredS + VredT) / 3;

  //calculo desviacion porcentual
  float desviacion_Rred = ((VredR - promedioRed) / promedioRed) * 100; //desviacion R
  float desviacion_Sred = ((VredS - promedioRed) / promedioRed) * 100; //desviacion S
  float desviacion_Tred = ((VredT - promedioRed) / promedioRed) * 100; //desviacion T

  if(desviacion_Rred >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE R RED DESBALANCEADA, 'porcentaje de desviacion' "
  }
  if(desviacion_Sred >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE s RED DESBALANCEADA, 'porcentaje de desviacion' "
  }
  if(desviacion_Tred >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE T RED DESBALANCEADA, 'porcentaje de desviacion' "
  }
}

void balanceoDeFasesSum(void){
  float promedioSum = (VsuministroR + VsuministroS + VsuministroT) / 3;

  //calculo desviacion porcentual
  float desviacion_Rsum = ((VsuministroR - promedioSum) / promedioSum) * 100; //desviacion R
  float desviacion_Ssum = ((VsuministroS - promedioSum) / promedioSum) * 100; //desviacion S
  float desviacion_Tsum = ((VsuministroT - promedioSum) / promedioSum) * 100; //desviacion T

  if(desviacion_Rsum >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE R SUMINISTRO DESBALANCEADA, 'porcentaje de desviacion' "
  }
  if(desviacion_Ssum >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE S SUMINISTRO DESBALANCEADA, 'porcentaje de desviacion' "
  }
  if(desviacion_Tsum >= 7){
      //escribir en pantalla "FASES DESBALANCEADAS" "FASE T SUMINISTRO DESBALANCEADA, 'porcentaje de desviacion' "
  }

}


void sendSMS(String number, String message) { //ENVIAR SMS, si no funciona cambiar todos los delay a 100
  SIM800L.println("AT+CMGF=1"); // Establecer el modo de texto SMS
  delay(50);
  SIM800L.print("AT+CMGS=\"");
  SIM800L.print(number);
  SIM800L.println("\"");
  delay(50);
  SIM800L.print(message);
  delay(50);
  SIM800L.write(26);
  delay(50);
}



void FunctionsSMS(bool estadoRed, bool estadoGrupo, bool estadoSum){

  if (estadoRed == true){
    SIM800L.println("RED CORTADA POR DESPERFECTO EN LAS FASES");
    sendSMS(phoneNumber, "RED CORTADA POR DESPERFECTO EN LAS FASES"); // Enviar mensaje SMS de confirmación al teléfono
    textMessage = "";
  }

  if (estadoGrupo == true && estadoRed == false){
    SIM800L.println("GRUPO ACCIONADO");
    sendSMS(phoneNumber, "GRUPO ACCIONADO"); // Enviar mensaje SMS de confirmación al teléfono
    textMessage = "";
  }

  if (estadoGrupo == false && estadoRed == false){
    SIM800L.println("GRUPO FALLO");
    sendSMS(phoneNumber, "GRUPO FALLO"); // Enviar mensaje SMS de confirmación al teléfono
    textMessage = "";
  }

  if (estadoSum == true && estadoGrupo == true){
    SIM800L.println("GRUPO FALLO");
    sendSMS(phoneNumber, "GRUPO FALLO"); // Enviar mensaje SMS de confirmación al teléfono
    textMessage = "";
  }

}