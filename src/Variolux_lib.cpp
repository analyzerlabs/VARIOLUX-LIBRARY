#include "string.h"
#include <Arduino.h>

#include "variables.cpp"
#include "EEPROM.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "FastLED.h" 
#include <ESP32Encoder.h>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
#define POWEROFF 0
#define POWERON 1
#define _DEBUG_ 1
#define PIN_DATA     6


     
class variolux{
    private:
        int relayState =0;
        BluetoothSerial SerialBT;    
        int colorAsked=0;
        int a;
        int NUM_colors=130;
        int tablaRGB[130][3];
        int RGB_NUM=0;
        String Nombre;
        int R_ADD = 0;
        int G_ADD = 100;
        int B_ADD = 200;
        bool demo = false;
        unsigned long int runtime = 0;
        CRGB leds1[NUM_LEDS];
        CRGB leds2[NUM_LEDS];
        int DATA_PIN1 , DATA_PIN2;
        char modulo[];
        String chipRGB; 
        int fractalChannels;
        int VarioplusDimeableChannels;
        int VarioplusStaticChannels;
        int VarioplusDimeableSteps;
        int* fractalPins;
        int* varioplusStaticPins;
        int* varioplusDimeablePins;
        int encoderPins[2][3];
        int lastVarioPlusDimeablePin = 0; 
        int lastValue = 0;
        String datos;
        Adafruit_SSD1306 display;
        int FR_LastState,VP_LastState,FR_State,VP_State,FR_counter,VP_counter;
        int FR_ENCODER[3] = {0,0,0};
        int VP_ENCODER[3] = {0,0,0};
        ESP32Encoder encoder_FR;
        ESP32Encoder encoder_VP;
        bool encoder_FR_Paused;
        bool encoder_VP_Paused;
        unsigned long int oledTimer = 0;
        unsigned long int enconderTimer = 0;
        int FR_ENCODER_SCREEN=0 , VP_ENCODER_SCREEN=0;
        int lastpos;
        int R_aux,G_aux,B_aux;
        int VARIOPLUSLEVEL;
        int FR_LIMIT = 255;
        int LAST_ENCODER_SCREEN = 0;
        bool flag_change_color=false;
        int encoder2Timer = 0;
        int LAST_VP_ENCODER_SCREEN = 0;
        int button_Demo = 34;
        String Modos[11]={"All on",
                        "All off",
                        "Front",
                        "Rear",
                        "Center",
                        "Blind 1",
                        "Blind 2",
                        "Blind 3",
                        "Blind 4",
                        "Blind 5","Blind 6"};
        bool VP_ENCODER_FLAG = false;
    public:  
        variolux(String tipo){      
            Nombre = tipo;
            if(Nombre == "EC-VL-002"){
                EEPROM.begin(500);
                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                //firmmwareUpdaterSetup();
                //eepromInit();
                fractalChannels = 2;
                VarioplusDimeableChannels = 1;
                VarioplusDimeableSteps = 11;
                chipRGB = "SK6812"; //SK6812 en otros casos
                DATA_PIN1 = 22;
                const int P_DAT1 = 22;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 23;
                // CRGB LEDS2[NUM_LEDS2];
                //this-> leds2  =  LEDS2;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                varioplusDimeablePins = new int[VarioplusDimeableSteps];
                fractalPins =  new int[fractalChannels]; //{14,32,33,25,26,27,13,4,18,19,21};
                varioplusDimeablePins[0] = 14;
                varioplusDimeablePins[1] = 32;
                varioplusDimeablePins[2] = 33;
                varioplusDimeablePins[3] = 25;
                varioplusDimeablePins[4] = 26;
                varioplusDimeablePins[5] = 27;
                varioplusDimeablePins[6] = 13;
                varioplusDimeablePins[7] = 4; 
                varioplusDimeablePins[8] = 18;
                varioplusDimeablePins[9] = 19;
                varioplusDimeablePins[10] = 21;
                runtime = millis();
                setPins();
            }
            else if(Nombre == "EC-VL-001"){            /// 6 blinds
                EEPROM.begin(500);
                Serial2.begin(9600);    
                   
                //bleInit(Nombre);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif

                fractalChannels = 2;
                VarioplusStaticChannels = 6;
                chipRGB = "SK6812"; //SK6812 en otros casos
                const int P_DAT1 = 22;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 23;
                // CRGB LEDS2[NUM_LEDS2];
                //this-> leds2  =  LEDS2;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                varioplusStaticPins = new int[VarioplusStaticChannels];     //define la cantidad de pasos de 1 varioplus
                fractalPins =  new int[fractalChannels]; //{14,32,33,25,26,27,13,4,18,19,21};
                varioplusStaticPins[0] = 32;
                varioplusStaticPins[1] = 33;
                varioplusStaticPins[2] = 25;
                varioplusStaticPins[3] = 26;
                varioplusStaticPins[4] = 27;
                varioplusStaticPins[5] = 13;
                runtime = millis();
                setPins();
            }
            else if(Nombre == "EC-VL-004"){
                EEPROM.begin(500);
                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                chipRGB = "SK6812"; //SK6812 en otros casos
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                // CRGB LEDS2[NUM_LEDS2];
                //this-> leds2  =  LEDS2;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                pinMode(26,INPUT);
                pinMode(25,INPUT);
                pinMode(33,INPUT);
                pinMode(32,OUTPUT);
                relayState = 0;
            }

            else if(Nombre == "EC-VL-003"){
                EEPROM.begin(500);
                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                VarioplusDimeableChannels = 1;
                VarioplusDimeableSteps = 11;
                chipRGB = "SK6812"; //SK6812 en otros casos
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                // CRGB LEDS2[NUM_LEDS2];
                //this-> leds2  =  LEDS2;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                pinMode(26,INPUT);
                pinMode(25,INPUT);
                pinMode(33,INPUT);
                pinMode(32,OUTPUT);
            }
            else if(Nombre == "EC-FR-003"){            /// 6 blinds
                EEPROM.begin(500);
                //Serial2.begin(9600);     
                //SerialBT.begin("ESP32test");           
                
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                chipRGB = "SK6812"; //SK6812 en otros casos
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                OledSetup();
                Serial.println("Oled ready");
                //bleInit(Nombre);
                Serial.println("Setup ready");
            }

            else if(Nombre == "EC-FR-002"){            /// 6 blinds
                EEPROM.begin(500);
                //Serial2.begin(9600);     
                //SerialBT.begin("ESP32test");           
                
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                chipRGB = "SK6812"; //SK6812 en otros casos
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                OledSetup();
                Serial.println("Oled ready");
                //bleInit(Nombre);
                Serial.println("Setup ready");
                pinMode(32,INPUT);
                pinMode(33,INPUT);
            }
            else if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                Serial2.begin(9600);
                runtime=millis();
                VP_ENCODER[0]=35;
                VP_ENCODER[1]=23;
                VP_ENCODER[2]=32;
                FR_ENCODER[0]=18;
                FR_ENCODER[1]=19;
                FR_ENCODER[2]=4;
                if(Nombre == "MD-VL-002" ){
                    pinMode(button_Demo,INPUT);
                }
            }
        }


        void setPins(){
            if(Nombre == "EC-VL-002" || Nombre == "EC-VL-004" || Nombre == "EC-VL-003" ){
                for(int i=0;i<VarioplusDimeableSteps;i++){
                    #if _DEBUG_
                        Serial.println("Setting Relay :" + String(varioplusDimeablePins[i]));
                    #endif
                    pinMode(varioplusDimeablePins[i],OUTPUT);
                    digitalWrite(varioplusDimeablePins[i],POWEROFF);
                }
                digitalWrite(14,POWERON); // AYUDA A SETEAR LA OPACIDAD DEL SPD
                delay(2000);
                #if _DEBUG_
                    Serial.println("Equipo Encendido");
                #endif 
                digitalWrite(14,POWEROFF);
                delay(2000);// esto es frio
                for(int i=0;i<11;i++)digitalWrite(varioplusDimeablePins[i],POWEROFF);
                digitalWrite(14,POWERON);
            }

            else if(Nombre == "EC-VL-001"){
                for(int i=0;i<VarioplusStaticChannels;i++){
                    #if _DEBUG_
                        Serial.println("Setting Relay :" + String(varioplusStaticPins[i]));
                    #endif
                    pinMode(varioplusStaticPins[i],OUTPUT);
                    digitalWrite(varioplusStaticPins[i],POWEROFF);
                }
                #if _DEBUG_
                    Serial.println("Equipo Encendido");
                #endif 
                delay(2000);// esto es frio
            }
        }

        
        
        
//***************************** MENU SCREENS ************************************//
        
        void askLimits(){
            if(encoder_FR.getCount()>FR_LIMIT)encoder_FR.setCount(0);
            else if(encoder_FR.getCount()<0)encoder_FR.setCount(FR_LIMIT);
        }
        void oledFractaclBT(){
                    display.setTextSize(1);
                    display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.setCursor(80,0);  //POSICION DEL CONTADOR DE COLORES EN OLE
                    
                    display.print(RGB_NUM);
                    display.setTextSize(2);
                    display.setCursor(0,16);
                    display.print(tablaRGB[RGB_NUM][0]);
                    display.setCursor(45,16);
                    display.print(tablaRGB[RGB_NUM][1]);
                    display.setCursor(90,16);
                    display.print(tablaRGB[RGB_NUM][2]);
                    display.display();
        }

        void oledMenuPrincipal(){
                //menu principal para Fractal
                if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                    display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.setCursor(75,0);  //POSICION DEL CONTADOR DE COLORES EN OLED
                    if(FR_ENCODER_SCREEN == 1){
                        display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
                        RGB_NUM = encoder_FR.getCount();
                        if(RGB_NUM>NUM_colors-1)encoder_FR.setCount(0);
                        else if(RGB_NUM<0)encoder_FR.setCount(NUM_colors-1);
                        RGB_NUM = encoder_FR.getCount();
                    }
                    else display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);

                    display.print(RGB_NUM);
                    display.setCursor(10,8);
                    if(FR_ENCODER_SCREEN == 2){
                        display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
                        tablaRGB[RGB_NUM][0] = encoder_FR.getCount();
                        if(tablaRGB[RGB_NUM][0]>255)encoder_FR.setCount(0);
                        else if(tablaRGB[RGB_NUM][0]<0)encoder_FR.setCount(255);
                        tablaRGB[RGB_NUM][0] = encoder_FR.getCount();
                    }
                    else display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.print(tablaRGB[RGB_NUM][0]);
                    display.setCursor(50,8);
                    if(FR_ENCODER_SCREEN == 3){
                        display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
                        tablaRGB[RGB_NUM][1] = encoder_FR.getCount();
                        if(tablaRGB[RGB_NUM][1]>255)encoder_FR.setCount(0);
                        else if(tablaRGB[RGB_NUM][1]<0)encoder_FR.setCount(255);
                        tablaRGB[RGB_NUM][1] = encoder_FR.getCount();
                    }
                    else display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.print(tablaRGB[RGB_NUM][1]);
                    display.setCursor(90,8);
                    if(FR_ENCODER_SCREEN == 4){
                        display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
                        tablaRGB[RGB_NUM][2] = encoder_FR.getCount();
                        if(tablaRGB[RGB_NUM][2]>255)encoder_FR.setCount(0);
                        else if(tablaRGB[RGB_NUM][2]<0)encoder_FR.setCount(255);
                        tablaRGB[RGB_NUM][2] = encoder_FR.getCount();
                    }
                    else display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.print(tablaRGB[RGB_NUM][2]);
                    display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    // menu principal para varioplus
                    if (Nombre == "MD-VL-002"){
                        display.setCursor(45,16);
                        if(VP_ENCODER_SCREEN<0)VP_ENCODER_SCREEN=0;
                        if(VP_ENCODER_SCREEN>10)VP_ENCODER_SCREEN=10;
                        display.print(VP_ENCODER_SCREEN*10);
                        display.display();
                    }
                    else if(Nombre == "MD-VL-001"){
                        display.setCursor(40,16);
                        if(VP_ENCODER_SCREEN<0)VP_ENCODER_SCREEN=0;
                        if(VP_ENCODER_SCREEN>10)VP_ENCODER_SCREEN=10;
                        display.print(Modos[VP_ENCODER_SCREEN]);
                        display.display();
                    }
                }
        }
        void updateOledBT(){
            if(Nombre == "EC-FR-002"  || Nombre == "EC-FR-003" ||Nombre == "EC-VL-004"  ||Nombre == "EC-VL-003"){
                display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                display.setCursor(20,0);
                display.print("FR Color#");
                //display.print(Nombre);
                display.display();
                display.setTextSize(2);
            }
        }

        void updateOled(){
            if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                display.setCursor(10,0);
                display.print("FR Color#");
                //display.print(Nombre);
                display.setCursor(10,16);
                if(Nombre == "MD-VL-002")display.print("VP:        VAC");
                else if(Nombre == "MD-VL-001")display.print("VP:   ");
                if(VP_ENCODER_FLAG){
                    display.setCursor(100,16);
                    display.println("<");
                }
                display.setCursor(0,16);
                oledMenuPrincipal();        
            }   
        }

//****************************** READ ENCODER ************************************//
        void readEncoder(){
            if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                if(digitalRead(button_Demo)==0 && Nombre == "MD-VL-002"){
                        sendUART("FR,DEMO");
                        Serial.println("button demo presionado");
                        delay(250);
                }
                if(digitalRead(FR_ENCODER[2]) == 0){
                    enconderTimer = millis();
                    Serial.println("button encoder FR presionado");
                    while(digitalRead(FR_ENCODER[2]) == 0){
                        delay(100);
                        if(millis()-enconderTimer>10000){
                            flag_change_color = ! flag_change_color;
                            break;
                        }
                    }
                    if(flag_change_color) {
                        FR_ENCODER_SCREEN++;
                        delay(300);
                    }
                    else{
                        if(FR_ENCODER_SCREEN==0)FR_ENCODER_SCREEN=1;
                        else if(FR_ENCODER_SCREEN>=1)FR_ENCODER_SCREEN=0;
                    }

                    if(FR_ENCODER_SCREEN>4)FR_ENCODER_SCREEN = 0;
                    else if(FR_ENCODER_SCREEN<0)FR_ENCODER_SCREEN = 4;
                    if(FR_ENCODER_SCREEN == 0) {
                        if(RGB_NUM>=100)sendUART("FR,"+String(RGB_NUM));
                        else if(RGB_NUM>=10 && RGB_NUM<100) sendUART("FR,0"+ String(RGB_NUM));
                        else if(RGB_NUM>= 0 && RGB_NUM<10 ) sendUART("FR,00"+String(RGB_NUM));
                    }
                    if(FR_ENCODER_SCREEN == 1) {
                        FR_LIMIT=NUM_colors;
                        encoder_FR.setCount(RGB_NUM);
                        encoder_FR.resumeCount();
                        LAST_ENCODER_SCREEN = FR_ENCODER_SCREEN;
                    }
                    else if(FR_ENCODER_SCREEN == 2 && flag_change_color){
                        FR_LIMIT=255;
                        encoder_FR.setCount(tablaRGB[RGB_NUM][0]);
                        Serial.println(tablaRGB[RGB_NUM][0]);
                        encoder_FR.resumeCount();
                        LAST_ENCODER_SCREEN = FR_ENCODER_SCREEN;
                    } 
                    else if(FR_ENCODER_SCREEN == 3 && flag_change_color) {
                        FR_LIMIT=255;
                        encoder_FR.setCount(tablaRGB[RGB_NUM][1]); 
                        encoder_FR.resumeCount();
                        LAST_ENCODER_SCREEN = FR_ENCODER_SCREEN;
                    }
                    else if(FR_ENCODER_SCREEN == 4 ) {
                        FR_LIMIT=255;
                        encoder_FR.setCount(tablaRGB[RGB_NUM][2]);
                        encoder_FR.resumeCount();
                        LAST_ENCODER_SCREEN = FR_ENCODER_SCREEN;
                    }
                    else if(FR_ENCODER_SCREEN == 0 && LAST_ENCODER_SCREEN == 4){
                        encoder_FR.pauseCount();
                        setColor(RGB_NUM,tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                        if(RGB_NUM>=100)sendUART("FR,"+String(RGB_NUM));
                        else if(RGB_NUM>=10 && RGB_NUM<100) sendUART("FR,0"+String(RGB_NUM));
                        else if(RGB_NUM>=0 && RGB_NUM<10) sendUART("FR,00"+String(RGB_NUM));
                        LAST_ENCODER_SCREEN = FR_ENCODER_SCREEN;
                    }
                    else if(FR_ENCODER_SCREEN == 0 && LAST_ENCODER_SCREEN == 1){
                        encoder_FR.pauseCount();
                    }
                    Serial.println("FR_SCREEN : "+ String(FR_ENCODER_SCREEN));
                    Serial.println("lasr FR_SCREEN : "+ String(LAST_ENCODER_SCREEN));
                }

                if(digitalRead(VP_ENCODER[2]) == 0){
                    Serial.println("button VP presionado");
                    if(Nombre == "MD-VL-002"){
                        encoder_VP.pauseCount();
                        if(encoder_VP.getCount()>= 0 && encoder_VP.getCount()< 200 ){
                            encoder_VP.setCount(200);
                            VP_ENCODER_SCREEN = 10;
                        } 
                        else if(encoder_VP.getCount() ==200 ){
                            encoder_VP.setCount(0);
                            VP_ENCODER_SCREEN = 0;
                        } 
                        delay(250);
                        encoder_VP.resumeCount();
                        a= encoder_VP.getCount();
                        Serial.println("VARIO PLUS LEVEL : " + String(VP_ENCODER_SCREEN));
                    }
                    else if(Nombre =="MD-VL-001"){
                        VP_ENCODER_FLAG=!VP_ENCODER_FLAG;
                        delay(150);
                        if(VP_ENCODER_FLAG){
                            encoder_VP.resumeCount();
                        }
                        else{
                            encoder_VP.pauseCount();
                            sendVarioPlusChannel(VP_ENCODER_SCREEN);
                        }
                    }         
                }
                VP_ENCODER_SCREEN = encoder_VP.getCount()/20;
                if(LAST_VP_ENCODER_SCREEN != VP_ENCODER_SCREEN){
                    LAST_VP_ENCODER_SCREEN = VP_ENCODER_SCREEN;
                    setVarioPlus(VP_ENCODER_SCREEN);
                    
                    Serial.println("VARIO PLUS LEVEL : " + String(VP_ENCODER_SCREEN));
                }
                
                if(encoder_VP.getCount()>=200)encoder_VP.setCount(200);
                else if(encoder_VP.getCount()<0)encoder_VP.setCount(0);
                askLimits();
                updateOled();    
            }       
        }
//**********************************Encoder Setup ***********************************//
        void EncoderSetup(){
            ESP32Encoder::useInternalWeakPullResistors=UP;
            encoder_VP.attachSingleEdge(VP_ENCODER[0], VP_ENCODER[1]);
            pinMode(VP_ENCODER[2] ,INPUT);
            encoder_FR.attachSingleEdge(FR_ENCODER[0], FR_ENCODER[1]);
            pinMode(FR_ENCODER[2] ,INPUT);
            encoder_FR.setCount(0);
            encoder_VP.clearCount();
            encoder_FR.pauseCount();
            encoder_VP.pauseCount();
            enconderTimer = millis();
            encoder2Timer = millis();
            encoder_VP.resumeCount();
        }

        void OledSetup(){
            display = Adafruit_SSD1306(128, 32, &Wire);
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            oledTimer = millis();
        }

        void sendVarioPlusChannel(int mode_ch){
            switch(mode_ch){
                case 0:
                    sendUART("VP,ALLON");
                    break;
                case 1:
                    sendUART("VP,ALLOFF");
                    break;
                case 2:
                    sendUART("VP,FRONT");
                    break;
                case 3:
                    sendUART("VP,REAR");
                    break;
                case 4:
                    sendUART("VP,CENTER");
                    break;
                case 5:
                    sendUART("VP,BLIND1");
                    break;
                case 6:
                    sendUART("VP,BLIND2");
                    break;
                case 7:
                    sendUART("VP,BLIND3");
                    break;
                case 8:
                    sendUART("VP,BLIND4");
                    break;
                case 9:
                    sendUART("VP,BLIND5");
                    break;
                case 10:
                    sendUART("VP,BLIND6");
                    break;                
            }
        }
        void setVarioPlus(char c){
            switch(c){
                case 0:
                    sendUART("VP,A");
                    break;
                case 1:
                    sendUART("VP,B");
                    break;
                case 2:
                    sendUART("VP,C");
                    break;
                case 3:
                    sendUART("VP,D");
                    break;
                case 4:
                    sendUART("VP,E");
                    break;
                case 5:
                    sendUART("VP,F");
                    break;
                case 6:
                    sendUART("VP,G");
                    break;
                case 7:
                    sendUART("VP,H");
                    break;
                case 8:
                    sendUART("VP,I");
                    break;
                case 9:
                    sendUART("VP,J");
                    break;
                case 10:
                    sendUART("VP,K");
                    break;
            }
        }
        void getNombre(){

        }
        void saveDataColors(){
            for(int i=0 ;i<NUM_colors;i++){
                setColor(i,tablaRGB[i][0],tablaRGB[i][1],tablaRGB[i][2]);
            }
        }

        void setVariablesColors(int data[][3]){
            for (int i = 0; i< NUM_colors ;i++){
                for (int j = 0; j< 3 ;j++){
                    tablaRGB[i][j] = data[i][j];
                }
            }
            if(Nombre == "MD-VL-002" ||Nombre == "MD-VL-001"){
                OledSetup();
                EncoderSetup();
            }
            saveDataColors();
        }

        void setColor(int _addr_, int _R_, int _G_, int _B_){
            EEPROM.write(_addr_*3,_R_);                 
            EEPROM.write(_addr_*3+1, _G_);     
            EEPROM.write(_addr_*3+2, _B_);    
            EEPROM.commit(); 
            delay(1);
        }

        void getColor(int _addr_){
            tablaRGB[_addr_][0] = EEPROM.read(_addr_*3+0);
            tablaRGB[_addr_][1] = EEPROM.read(_addr_*3+1);
            tablaRGB[_addr_][2] = EEPROM.read(_addr_*3+2); 
            delay(1);
        }

        void getDataColors(){
            for(int i=0 ;i<NUM_colors;i++){
                getColor(i);
            }
        }

        void eepromInit(){
            EEPROM.begin(512);
            if (!EEPROM.begin(512)) {
                Serial.println("Failed to initialise EEPROM");
                Serial.println("Restarting...");
                EEPROM.begin(512);
                delay(1000);
                //saveDataColors();
                //getDataColors();
               // ESP.restart();
            }
        }

        void shutDownVarioPlus(){
            for(int i=0;i<VarioplusDimeableSteps;i++){
                #if _DEBUG_
                    Serial.println("Apago Relay :" + String(varioplusDimeablePins[i]));
                #endif
                digitalWrite(varioplusDimeablePins[i],POWEROFF);
            }
        }

        void askNumberofLeds(){
            sendUART("ASKLEDS");
        }
        void askColorRGB(){
            sendUART("RGB?");
        }
        void recieveFromECU(){
            if(Serial2.available()){
                datos = "";  //elimina datos de buffer
                datos = Serial.readStringUntil('\n');
                if(datos[0]=='L' && datos[1]=='E' && datos[2]=='D' && datos[3]=='S' &&  datos[4]==','){
                    NUM_colors = (datos[4]-48)*100 + (datos[5]-48)*10 + (datos[6]-48);
                }
                else if(datos[0]=='R' && datos[1]=='G' && datos[2]=='B' && datos[3]==',' &&  datos[7]==',' &&  datos[11]==','){
                    tablaRGB[colorAsked][0] = (datos[3]-48)*100  + (datos[4]-48)*10  + (datos[5]-48);
                    tablaRGB[colorAsked][0] = (datos[8]-48)*100  + (datos[9]-48)*10  + (datos[10]-48);
                    tablaRGB[colorAsked][0] = (datos[12]-48)*100 + (datos[13]-48)*10 + (datos[14]-48);
                }
                Serial.println(datos);
            }
        }

        void sendNumberofLeds(){
            if(NUM_LEDS<10)sendUART("LEDS,00"+String(NUM_LEDS));
            else if(NUM_LEDS<100)sendUART("LEDS,0"+String(NUM_LEDS));
            else if(NUM_LEDS>=100)sendUART("LEDS,"+String(NUM_LEDS)); 
        }
        // ************************* datos recibidos *********************************************************
        void run(){
            //Serial.print(Nombre);
            //Serial.println(digitalRead(33));
            if(Nombre == "EC-VL-004" ){
                if(digitalRead(26)==0){
                    relayState = 1 - relayState;
                    digitalWrite(32,relayState);
                    Serial.println("boton presionado");
                    delay(500);
                }
            }

            if(Nombre == "EC-VL-003" ){
                if(digitalRead(26)==0){
                    relayState = 1 - relayState;
                    digitalWrite(32,relayState);
                    Serial.println("boton presionado");
                    delay(400);
                }
                if(digitalRead(25)==0){
                    RGB_NUM++;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    Serial.println("boton presionado");
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    delay(350);
                }
                if(digitalRead(33)==0){
                    RGB_NUM--;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    Serial.println("boton presionado");
                    delay(350);
                }
            }
            if(Nombre=="MD-VL-002" ){
                readEncoder();
                //Serial.println("reading encoder");
                updateOled();
                runtime = millis();
                //Serial.println("MD-VL-002");
                //recieveFromECU();
            }
            else if(Nombre=="MD-VL-001" ){
                readEncoder();
                updateOled();
                runtime = millis();
                //Serial.println("MD-VL-001");
                //recieveFromECU();
            }
            else if(Nombre =="EC-FR-002"){
                if(digitalRead(33)==0){
                    RGB_NUM++;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    Serial.println("boton presionado");
                    delay(350);
                }
                if(digitalRead(32)==0){
                    RGB_NUM--;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    Serial.println("boton presionado");
                    delay(350);
                }
            }
            else if (Nombre=="EC-VL-002" || Nombre=="EC-VL-001" || Nombre =="EC-FR-003" || Nombre == "EC-VL-003" || Nombre == "EC-VL-004" ){
                //Serial.println("EC-VL-002");
                //runtime = millis();
                //Serial.println(Nombre);
                if(Serial.available()) {
                    datos = "";  //elimina datos de buffer
                    datos = Serial.readStringUntil('\n');
                    decode();
                    Serial.println(datos);
                    //SerialBT.println(datos);
                }
                if(SerialBT.available()) {
                    
                    datos = "";  //elimina datos de buffer
                    datos = SerialBT.readStringUntil('\n');
                    decode();
                    Serial.println(datos);
                    if(Nombre == "EC-FR-003"){
                        updateOledBT();
                        oledFractaclBT();
                    }
                    else if(Nombre == "EC-VL-004"){
                        updateOledBT();
                        oledFractaclBT();
                    }
                }
                if(Nombre != "EC-FR-003"){
                    if(Serial2.available()){
                        datos = "";  //elimina datos de buffer
                        datos = Serial2.readStringUntil('\n');                    
                        decode();
                        Serial.println(datos);
                    }
                }
                
                int tr = random(50,150);
                if(demo && millis()- runtime >tr){
                    int ran = random(168);
                    int rcolor = 25;
                    for(int i=0 ; i<NUM_LEDS ; i++){
                        if(i == ran){
                            leds1[i] = CRGB(tablaRGB[rcolor][0],tablaRGB[rcolor][1],tablaRGB[rcolor][2]);
                            leds2[i] = CRGB(tablaRGB[rcolor][0],tablaRGB[rcolor][1],tablaRGB[rcolor][2]);
                            #if _DEBUG_
                                Serial.println("Modo DEMO activado!");
                            #endif
                        }
                        else{
                            leds1[i] = CRGB(0,0,0);
                            leds2[i] = CRGB(0,0,0);
                        }
                    }
                    FastLED.show();
                    runtime = millis();
                }
            }

            
        }

        void changeColor(int R,int G,int B){
            for(int i=0 ; i<NUM_LEDS ; i++){
                        leds1[i] = CRGB(R,G,B);
                        leds2[i] = CRGB(R,G,B);
                    }
            FastLED.show();
        }

        int getNumColors(){
            return NUM_LEDS;
        }

        void  decode(){
            Serial.print("decode:  ");
            if(datos[0]=='V' && datos[1]=='P' && datos[2]==',' ){
                if(datos[3]>='A' && datos[3]<='K' && Nombre == "EC-VL-002"){
                    #if _DEBUG_
                        Serial.print("Setting VP: ");
                    #endif
                    int voltaje = datos[3] - 65;
                    Serial.println(datos[3] - 65); 
                    setVarioplusStep(voltaje);
                }
                else if(datos[3]=='A' && datos[4]=='L' && datos[5]=='L' && datos[6]=='O' && datos[7]=='N' ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,1);
                }
                else if(datos[3]=='A' && datos[4]=='L' && datos[5]=='L' && datos[6]=='O' && datos[7]=='F' && datos[8]=='F' ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                }
                else if(datos[3]=='F' && datos[4]=='R' && datos[5]=='O' && datos[6]=='N' && datos[7]=='T'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(0,POWERON);
                    setVarioplusChannel(1,POWERON);
                    setVarioplusChannel(2,POWERON);
                }
                else if(datos[3]=='R' && datos[4]=='E' && datos[5]=='A' && datos[6]=='R' ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(3,POWERON);
                    setVarioplusChannel(4,POWERON);
                    setVarioplusChannel(5,POWERON);
                }
                else if(datos[3]=='C' && datos[4]=='E' && datos[5]=='N' && datos[6]=='T' && datos[7]=='E' && datos[8]=='R'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(2,POWERON);
                    setVarioplusChannel(3,POWERON);
                }
                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='1'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(0,POWERON);
                }

                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='2'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(1,POWERON);
                }

                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='3'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(2,POWERON);
                }

                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='4'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(3,POWERON);
                }

                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='5'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(4,POWERON);
                }
                else if(datos[3]=='B' && datos[4]=='L' && datos[5]=='I' && datos[6]=='N' && datos[7]=='D' && datos[8]=='6'){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(5,POWERON);
                }
            }
            else if(datos[0]=='A'  && datos[1]=='S'  && datos[2] =='K' && datos[3]=='L'  && datos[4] =='E' && datos[5]=='D'  && datos[6] =='S'){
                sendNumberofLeds();
            }
            else if(datos[0]=='F' && datos[1]=='R'  && datos[2] ==',' ){
                if(datos[3]>='0' &&  datos[3]<='9' &&  datos[4]>='0' &&  datos[4]<='9' &&  datos[5]>='0' &&  datos[5]<='9'
                                                    && datos[6] ==',' &&  datos[7]>='0' &&  datos[7]<='9' &&  datos[8]>='0' &&  datos[8]<='9' &&  datos[9]>='0' &&  datos[9]<='9'
                                                    && datos[10]==',' && datos[11]>='0' && datos[11]<='9' && datos[12]>='0' && datos[12]<='9' && datos[13]>='0' && datos[13]<='9'){
                    
                    int R = 100*(datos[3]-48)  +10*(datos[4]-48)  +datos[5]-48;
                    int G = 100*(datos[7]-48)  +10*(datos[8]-48)  +datos[9]-48;
                    int B = 100*(datos[11]-48) +10*(datos[12]-48) +datos[13]-48; 
                    demo = false;

                    changeColor(R,G,B);
                    #if _DEBUG_
                        Serial.print("RGB : ");Serial.print(R);Serial.print(",");Serial.print(G);Serial.print(",");Serial.println(B);
                    #endif
                }
                else if(datos[3]=='S' &&  datos[4]=='E' &&  datos[5]=='T' 
                                      &&  datos[6]>='0' &&  datos[6]<='9' &&  datos[7]>='0' &&  datos[7]<='9' &&  datos[8]>='0' &&  datos[8]<='9'
                                      &&  datos[9]==',' && datos[10]>='0' && datos[10]<='9' && datos[11]>='0' && datos[11]<='9' && datos[12]>='0' && datos[12]<='9'
                                      && datos[13]==',' && datos[14]>='0' && datos[14]<='9' && datos[15]>='0' && datos[15]<='9' && datos[16]>='0' && datos[16]<='9'
                                      && datos[17]==',' && datos[18]>='0' && datos[18]<='9' && datos[19]>='0' && datos[19]<='9' && datos[20]>='0' && datos[20]<='9'){
                    
                    int index = (datos[8]-48 + 10*(datos[7]-48)+ 100* (datos[6]-48));
                    int R = 100*(datos[10]-48) +10*(datos[11]-48) +datos[12]-48;
                    int G = 100*(datos[14]-48) +10*(datos[15]-48) +datos[16]-48;
                    int B = 100*(datos[18]-48) +10*(datos[19]-48) +datos[20]-48;
                    setColor(index ,R,G,B);
                }

                else if(datos[3]>='0' && datos[3]<='9' && datos[4]>='0' && datos[4]<='9' && datos[5]>='0' && datos[5]<='9'){
                 
                    int index = datos[5]-48 + 10*(datos[4]-48)+ 100* (datos[3]-48);
                    RGB_NUM = index;
                    int R_,G_,B_;
                    R_= tablaRGB[index][0];
                    G_= tablaRGB[index][1];
                    B_= tablaRGB[index][2];
                    changeColor(R_,G_,B_);
                }
                else if(datos[3]=='D' && datos[4]=='E' && datos[5]=='M' && datos[6]=='O'){
                    demo = ! demo;
                } 
            }   
        }

        
        void setVarioplusChannel(int channel, bool state){
            digitalWrite(varioplusStaticPins[channel],state);
        }
        void setVarioplusStep(int value){
            
            if(value>=0 && value <= VarioplusDimeableSteps){
                
                for(int i=0;i<11;i++)digitalWrite(varioplusDimeablePins[i],POWEROFF);
                digitalWrite(varioplusDimeablePins[0],POWERON); //PRENDE RELAY 0
                delay(100);
                digitalWrite(varioplusDimeablePins[0],POWEROFF); //APAGA RELAY 0
                delay(100);
                digitalWrite(varioplusDimeablePins[value],POWERON);
                lastValue = value;
                Serial.print("Last Value = ");
                Serial.println(lastValue);
                Serial.print("new Value = ");
                Serial.println(value);
                #if _DEBUG_
                    Serial.println("cambiando Relay :" + String(varioplusDimeablePins[value]));
                #endif
            }
        }
        void bleInit(String name){
            
            SerialBT.begin(name);
        }

        void sendUART(String command){
            Serial2.println(command);
            Serial.println("enviando");
        }
};