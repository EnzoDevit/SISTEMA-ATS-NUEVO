    /*************************************************




    *******************************************************/
    #ifndef FUNCTION_MATH_H //si no esta definida, sigue para abajo hasta encontrar el "endif"
    #define FUNCTION_MATH_H //define
    #include <Arduino.h>
    extern String phoneNumber; // Número de teléfono para enviar
    extern String textMessage; //Variable para almacenar el mensaje entrante

    //VARIABLES PARA PASAR VALOR A FUNCION DE INTERPOLACION
    extern float x;  //extern hace que solo se declare la variable
    extern float j;

    //VARIABLES


    namespace Medicion{ 
        void TensionSuministro(void); //MEDIR TENSION SUMINISTRO
        void TensionRed(void);  //MEDIR TENSION RED
        void TensionADC(void);  //FUNCION PARA MEDIR TENSION DE LOS BITS DEL ADC, SE LE PASA BYTE PARA HACER LA OPERACION DE SELECCION DE PIN CON shiftOut(); Y EL MUX
    };

    //MATRIZ DATOS SENSORES
    const float matrizTabla [27] [2] = {
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {60.0, 0.317},
        {70.0, 0.452},
        {80.0, 0.595},
        {90.0, 0.735},
        {100.0, 0.875},
        {110.0, 1.000},
        {120.0, 1.142},
        {130.0, 1.251},
        {140.0, 1.373},
        {150.0, 1.411},
        {160.0, 1.483},
        {170.0, 1.579},
        {180.0, 1.690},
        {190.0, 1.805},
        {200.0, 1.955},
        {210.0, 2.245},
        {220.0, 2.384},
        {230.0, 2.530},
        {240.0, 2.600},
        {250.0, 2.715},
        {260.0, 2.830},
        {270.0, 2.960},
    };


    #define filas sizeof(matrizTabla)/sizeof(matrizTabla[0])
    #define columnas sizeof(matrizTabla[0])/sizeof(matrizTabla[0][0])


    namespace Interpolacion{

        inline float Red(float x, float x1, float x2, float y1, float y2);
        inline float Suministro(float j, float j1, float j2, float p1, float p2);

    };

    //FUNCIONES PARA ESTABLECER BIT POR BIT LA SALIDA DEL SHIFT REGISTER AL MUX
    void adcRed_R(void);
    void adcRed_S(void);
    void adcRed_T(void);
    void adcSum_R(void);
    void adcSum_S(void);
    void adcSum_T(void);
    void Vbat(void);
    void modManAuto(void);
    void modRedSum(void);
    void RedSumOff(void);
    void RedOn(void);
    void SumOn(void);
    void SumStart(void);


    void beginSetup(void);

    void balanceoDeFasesRed(void);
    void balanceoDeFasesSum(void);

    void CambioModos(void);

    void sendSMS(String number, String message);

    void printCambioModo(int nuevoModo); //AVISO DE CAMBIO DE MODO

    bool Cronometro(int tiempo);

    void muestreo (void);


    void FunctionsSMS(bool estadoRed, bool estadoGrupo, bool estadoSum); //FUNCIONES SMS


    void RTC (void);
    #endif //cierra el condicional del FUNCTION_MATH_H