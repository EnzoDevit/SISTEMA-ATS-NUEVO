/******************************************************
 
 PINES DEL MICROCOTROLADOR
 

******************************************************/

#ifndef PIN_H
#define PIN_H

#include <Adafruit_ILI9341.h>
#include <SPI.h>



#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

uint16_t textColor = ILI9341_GREEN;
uint16_t textColor1 = ILI9341_RED;
uint16_t textColor2 = ILI9341_BLUE;
//PANTALLA

int circleX = 160;  // Coordenada X del centro del círculo
int circleY = 55;  // Coordenada Y del centro del círculo
  int radius = 35;


  int circleX2 = 55;  // Coordenada X del segundo círculo
int circleY2 = 55;  // Coordenada Y del segundo círculo
int radius2 = 35;


 int circleX3 = 265;  // Coordenada X del segundo círculo
int circleY3 = 55;  // Coordenada Y del segundo círculo
int radius3 = 35;




 int circleX4 = 55;  // Coordenada X del segundo círculo
int circleY4 = 180;  // Coordenada Y del segundo círculo
int radius4 = 35;



 int circleX5 = 160;  // Coordenada X del segundo círculo
int circleY5 = 180;  // Coordenada Y del segundo círculo
int radius5 = 35;


 int circleX6 = 265;  // Coordenada X del segundo círculo
int circleY6 = 180;  // Coordenada Y del segundo círculo
int radius6= 35;




//ENTRADA ANALOGICA MUX
const int medicionMux = A0;

//SALIDAS A SHIFT REGISTER
const int SER = A1;
const int RCLK = A2;
const int SRCLK = A3;

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

int flag0 = 0;


int periodoEncendido = 0;
const int timeTransOn = 5000; //tiempo Transcurrido Para Encender
const int periodoRetraso = 5000; //constante de tiempo para el retraso en la transferencia de energia
const int TimeStabilitySum = 15000; //tiempo de estabilidad del suministro
int TensionMax = 260;
int TensionMin = 200;
unsigned long int tiempoAhora = 0;

int L = 0;
int N = 0;
int B = 0;
int H = 0;
int S = 0;
int J = 0;
bool xd = false;
bool flagGrupo = false;
#endif //PIN_H