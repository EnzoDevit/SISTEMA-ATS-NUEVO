/******************************************************
 
 PINES DEL MICROCOTROLADOR
 

******************************************************/

#ifndef PIN_H
#define PIN_H
#include <SPI.h>
/*#include <UTouch.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>*/

//SOFTWARE SERIAL Y VARIABLES PARA MODULO SM800L (SMS)


//ENTRADA ANALOGICA MUX
const int medicionMux = A0;

//SALIDAS A SHIFT REGISTER
const int SER = A1;
const int SRCLK = A2;
const int RCLK = A3;

//SALIDAS A PANTALLA SPI
const int DC = 9;
const int CS = 10;
const int SDI_MOSI = 11;
const int SDO_MISO = 12;
const int SCK1 = 13;


//SALIDAS A PANTALLA SPI TOUCH
const int T_CLK = 3;
const int T_CS = 4;
const int T_DIN = 5;
const int T_DO = 6;
const int T_IRQ = 7;

/*//Instanciamos la TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//Instancimos el Touch
UTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);*/


//VARIABLES CASOS DE SWITCH
int selectoraModoAutoManual = 0;

//VARIABLES PARA RED/SUMS
int selectoraModoRedSum = 0;

//SELECTOR SWITCH
int selector = 0;

//VARIABLE BYTE
byte shadowRegister = 0;

//VARIABLES MEDICION TENSION ADC
float tensionArduinoInputRed_R = 0;
float tensionArduinoInputRed_S = 0;
float tensionArduinoInputRed_T = 0;
float tensionArduinoInputSum_R = 0;
float tensionArduinoInputSum_S = 0;
float tensionArduinoInputSum_T = 0;


//VARIABLES DE TENSION AC RED/SUMINISTRO
int VredR = 0;
int VredS = 0;
int VredT = 0;
int VsuministroR = 0;
int VsuministroS = 0;
int VsuministroT = 0;

//BUZZER
int Buzzer = 6;


#endif //PIN_H