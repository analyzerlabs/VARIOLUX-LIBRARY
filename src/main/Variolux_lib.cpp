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
#define _DEBUG_ 0
     
class variolux{
    private:
        int encoderSpeed =50;
        int a=0;
        int relayState =0;
        BluetoothSerial SerialBT;    
        short NUM_colors=131;
        short tablaRGB[131][3];
        int RGB_NUM=0;
        String Nombre;
        short R_ADD = 0;
        short G_ADD = 100;
        short B_ADD = 200;
        bool demo = false;
        unsigned long int runtime = 0;
        CRGB leds1[NUM_LEDS];
        CRGB leds2[NUM_LEDS];
        int DATA_PIN1 , DATA_PIN2;
        int fractalChannels;
        short VarioplusDimeableChannels;
        short VarioplusStaticChannels;
        short VarioplusDimeableSteps;
        int* fractalPins;
        int* varioplusStaticPins;
        int* varioplusDimeablePins;
        short encoderPins[2][3];
        int lastValue = 0;
        String datos;
        Adafruit_SSD1306 display;
        short FR_LastState,VP_LastState,FR_State,VP_State,FR_counter,VP_counter;
        short FR_ENCODER[3] = {0,0,0};
        short VP_ENCODER[3] = {0,0,0};
        ESP32Encoder encoder_FR;
        ESP32Encoder encoder_VP;
        bool encoder_FR_Paused;
        bool encoder_VP_Paused;
        unsigned long int oledTimer = 0;
        unsigned long int enconderTimer = 0;
        short FR_ENCODER_SCREEN=0 , VP_ENCODER_SCREEN=0;
        short lastpos;
        short FR_LIMIT = 255;
        short LAST_ENCODER_SCREEN = 0;
        bool flag_change_color=false;
        int encoder2Timer = 0;
        short LAST_VP_ENCODER_SCREEN = 0;
        short button_Demo = 34;
        String Modos[11]={"All on",
                        "All off",
                        "Front",
                        "Rear",
                        "Center",
                        "Blind 1",
                        "Blind 2",
                        "Blind 3",
                        "Blind 4",
                        "Blind 5",
                        "Blind 6"};
        bool VP_ENCODER_FLAG = false;
    public:  
        variolux(String tipo){      
            Nombre = tipo;
            if(Nombre == "EC-VL-002"){
                
                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                VarioplusDimeableChannels = 1;
                VarioplusDimeableSteps = 11;
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
                
                Serial2.begin(9600);    
                   
                //bleInit(Nombre);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif

                fractalChannels = 2;
                VarioplusStaticChannels = 6;
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
                
                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
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

                Serial2.begin(9600);
                #if _DEBUG_
                    Serial.begin(9600);
                    Serial.println("__DEBUG__ INICIADO");
                #endif
                fractalChannels = 2;
                VarioplusDimeableChannels = 1;
                VarioplusDimeableSteps = 11;
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
                //Serial2.begin(9600);     
                //SerialBT.begin("ESP32test");           
                Serial.begin(9600);
                #if _DEBUG_
                    Serial.println("__DEBUG__ INICIADO");
                    Serial.println("Setup ready");
                #endif
                fractalChannels = 2;
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                OledSetup();
                
            }

            else if(Nombre == "EC-FR-002"){            // fractal panel
                Serial2.begin(9600);     
                //SerialBT.begin("ESP32test");   comunicacion bt se inicia en el setup del main        
                Serial.begin(9600);
                #if _DEBUG_
                    Serial.println("__DEBUG__ INICIADO");
                    Serial.println("Oled ready");
                    Serial.println("Setup ready");
                #endif
                fractalChannels = 2;
                const int P_DAT1 = 18;     //CAMBIAR LOS PIENS DE CONTROL DE TIRA LED
                const int P_DAT2 = 19;
                FastLED.addLeds<LED_TYPE , P_DAT2, GRB>(leds2, NUM_LEDS);
                FastLED.addLeds<LED_TYPE , P_DAT1, GRB>(leds1, NUM_LEDS);
                runtime = millis();
                OledSetup();
                pinMode(32,INPUT);
                pinMode(33,INPUT);
            }
            else if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                Serial.begin(9600);
                #if _DEBUG_ 
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
            if(Nombre == "EC-VL-002" ){
                for(int i=0;i<VarioplusDimeableSteps;i++){
                    #if _DEBUG_
                        Serial.println("Setting Relay :" + String(varioplusDimeablePins[i]));
                    #endif
                    pinMode(varioplusDimeablePins[i],OUTPUT);
                    digitalWrite(varioplusDimeablePins[i],POWEROFF);
                }
                digitalWrite(14,POWERON);                                           // AYUDA A SETEAR LA OPACIDAD DEL SPD
                delay(1000);
                #if _DEBUG_
                    Serial.println("Equipo Encendido");
                #endif 
                digitalWrite(14,POWEROFF);                                         // PIN A RELAY COMUN
                delay(2000);                                                       //
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
                delay(1000);
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
                    
                    
                    int rojo,azul,verde;
                    rojo = tablaRGB[RGB_NUM][0];
                    verde = tablaRGB[RGB_NUM][1];
                    azul = tablaRGB[RGB_NUM][2];
                    display.setCursor(80,0);  //POSICION DEL CONTADOR DE COLORES EN OLED
                    display.print(RGB_NUM);
                    display.setTextSize(2);
                    if(rojo>=0 && rojo <10) display.setCursor(15,16);
                    else if(rojo>=10 && rojo <100)display.setCursor(7,16);
                    else if(rojo>=100 && rojo <1000)display.setCursor(0,16);
                    display.print(rojo);
                    if(verde>=0 && verde <10) display.setCursor(60,16);
                    else if(verde>=10 && verde <100)display.setCursor(52,16);
                    else if(verde>=100 && verde <1000)display.setCursor(45,16);
                    display.print(verde);
                    if(azul>=0 && azul <10) display.setCursor(105,16);
                    else if(azul>=10 && azul <100)display.setCursor(97,16);
                    else if(azul>=100 && azul <1000)display.setCursor(90,16);
                    display.print(azul);
                    display.display();
        }

        void oledMenuPrincipal(){
                //menu principal para Fractal MANDO
                if(Nombre == "MD-VL-002" || Nombre == "MD-VL-001"){
                    encoder_FR.resumeCount();
                    display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                    display.setCursor(75,0);  //POSICION DEL CONTADOR DE COLORES EN OLED
                    
                        display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
                        RGB_NUM = encoder_FR.getCount();
                        if(RGB_NUM>NUM_colors-1)encoder_FR.setCount(0);
                        else if(RGB_NUM<0)encoder_FR.setCount(NUM_colors-1);
                        RGB_NUM = encoder_FR.getCount();
                    

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
                    display.print(tablaRGB[RGB_NUM][1]);
                    display.setCursor(90,8);
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
                display.print("FR Color #");
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
                display.print("FR Color #");
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
                        #if _DEBUG_
                            Serial.println("button demo presionado");
                        #endif
                        delay(150);
                }
                
                /*if(digitalRead(FR_ENCODER[2]) == 0 && digitalRead(VP_ENCODER[2])==0){
                    unsigned long timer_f = millis();
                    while(digitalRead(FR_ENCODER[2]) == 0 && digitalRead(VP_ENCODER[2])==0){
                        if(millis() - timer_f >3000){
                            Serial.println("Modo de Consulta de datos");
                            askColorsRGB();
                            for(int i = 0; i< RGB_NUM; i++){
                                askColor(i);
                                decode(1);
                            }
                        }
                    }
                }*/

                
                else if(digitalRead(FR_ENCODER[2]) == 0){ 
                    enconderTimer = millis();
                    #if _DEBUG_
                        Serial.println("button encoder FR presionado");
                    #endif
                    
                        RGB_NUM = encoder_FR.getCount();
                        if(RGB_NUM>NUM_colors-1)encoder_FR.setCount(0);
                        else if(RGB_NUM<0)encoder_FR.setCount(NUM_colors-1);

                        if(RGB_NUM>=100)sendUART("FR,"+String(RGB_NUM));
                        else if(RGB_NUM>=10 && RGB_NUM<100) sendUART("FR,0"+ String(RGB_NUM));
                        else if(RGB_NUM>= 0 && RGB_NUM<10 ) sendUART("FR,00"+String(RGB_NUM));
                    while(digitalRead(FR_ENCODER[2]) == 0){}
                }

                else if(digitalRead(VP_ENCODER[2]) == 0){
                        if(Nombre == "MD-VL-002"){
                                setVarioPlus(VP_ENCODER_SCREEN);
                                while(digitalRead(VP_ENCODER[2]) == 0){}
                        }
                        else if(Nombre =="MD-VL-001"){
                                setVarioPlusChannel(VP_ENCODER_SCREEN);
                                while(digitalRead(VP_ENCODER[2]) == 0){}
                            }
                        }         
                

                VP_ENCODER_SCREEN = encoder_VP.getCount()/(encoderSpeed/10);
                if(encoder_VP.getCount()>encoderSpeed)encoder_VP.setCount(0);
                else if(encoder_VP.getCount()<0)encoder_VP.setCount(encoderSpeed);
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

        void setVarioPlusChannel(int mode_ch){
            String msg = "";
            Serial.println("Comando enviado");
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
            Serial.println("Comando enviado");
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
        void getColors(int input){
            String NumColor = "";
            String __RED = "",__GREEN ="" , __BLUE="";
            if(input > 0 && input<100){
                if(input<10){
                    NumColor = "00" + String(input);
                }
                else{
                    NumColor = "0" + String(input);
                }
            }
            else if(input >= 100 && input < 1000){

            }
            for(int i=0;i<input;i++){
                String  c = getStringRGB(input);
                sendUART("RGB,"+ c);
                delay(10);
            }
        }
        String getStringRGB( int n_color){
            String msg = "";
            int RGB___ = getColor(n_color ,0);
            if(RGB___ < 100)msg  += String();
            msg +=",";
            msg  += String(getColor(n_color ,1));
            msg +=",";
            msg  += String(getColor(n_color ,2));
            return msg;
        }
        int getColor(int _addr_, int rgb){
            tablaRGB[_addr_][rgb] = EEPROM.read(_addr_*3+rgb); 
            delay(1);
            return tablaRGB[_addr_][rgb];
        }

        void getDataColors(){
            for(int i=0 ;i<NUM_colors;i++){
                sendUART("OK+"+getStringRGB(i));
                delay(10);
            }
        }
        void askColor(int index){
            if(index <10)sendUART("RGB?00"+String(index));
            else if(index>=10 && index <100)sendUART("RGB?0"+String(index));
            else if(index>=150 && index <1000)sendUART("RGB?"+String(index));
        }
        void eepromInit(){
            EEPROM.begin(512);
            if (!EEPROM.begin(512)) {
                //Serial.println("Failed to initialise EEPROM");
                //Serial.println("Restarting...");
                EEPROM.begin(512);
                delay(1000);
               // ESP.restart();
            }
        }

        void shutDownVarioPlus(){
            for(int i=0;i<VarioplusDimeableSteps;i++){
                #if _DEBUG_
                    Serial.println("Shutdown Relay # :" + String(varioplusDimeablePins[i]));
                #endif
                digitalWrite(varioplusDimeablePins[i],POWEROFF);
            }
        }

        void askNumberofLeds(){
            sendUART("ASKLEDS");
        }
        void askColorsRGB(){
            sendUART("RGB?n");
            unsigned long waiting = millis();
            while(!Serial2.available()){
                if(millis() - waiting >1000){
                    Serial.println("Waiting data in Serial 2");
                    waiting = millis();
                }
            }
            decode(1);
        }
        
        void replyColor(int index){
            String r_str = "";
            String g_str = "";
            String b_str = "";
            if(index <10){
                if(tablaRGB[index][0]<10)r_str = "00"+String(tablaRGB[index][0]);
                else if(tablaRGB[index][0]<100)r_str = "0"+String(tablaRGB[index][0]);
                else if(tablaRGB[index][0]<1000)r_str = String(tablaRGB[index][0]);

                if(tablaRGB[index][0]<10)g_str = "00"+String(tablaRGB[index][1]);
                else if(tablaRGB[index][0]<100)g_str = "0"+String(tablaRGB[index][1]);
                else if(tablaRGB[index][0]<1000)g_str = String(tablaRGB[index][1]);

                if(tablaRGB[index][0]<10)b_str = "00"+String(tablaRGB[index][2]);
                else if(tablaRGB[index][0]<100)b_str = "0"+String(tablaRGB[index][2]);
                else if(tablaRGB[index][0]<1000)b_str = String(tablaRGB[index][2]);

                sendUART("FR,RGB,00"+String(index)+","+ r_str+","+g_str+","+b_str);
            }
            else if(index>=10 && index <100)sendUART("RGB?0"+String(index));
            else if(index>=150 && index <1000)sendUART("RGB?"+String(index));
        }
        void sendNumberofLeds(){
            if(NUM_LEDS<10)sendUART("LEDS,00"+String(NUM_LEDS));
            else if(NUM_LEDS<100)sendUART("LEDS,0"+String(NUM_LEDS));
            else if(NUM_LEDS>=100)sendUART("LEDS,"+String(NUM_LEDS)); 
        }
        // ************************* datos recibidos *********************************************************
        void run(){
            if(Nombre == "EC-VL-003"  || Nombre =="EC-VL-004"  ){
                if(digitalRead(26)==0){
                    relayState = 1 - relayState;
                    digitalWrite(32,relayState);
                    #if _DEBUG_
                        Serial.println("Button Pressed");
                    #endif
                    delay(150);
                    while(digitalRead(26)==0){

                    }
                }
                if(digitalRead(33)==0){
                    RGB_NUM++;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    #if _DEBUG_
                        Serial.println("Button Pressed");
                    #endif
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    delay(150);
                }
                if(digitalRead(25)==0){
                    RGB_NUM--;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    #if _DEBUG_
                        Serial.println("Button Pressed");
                    #endif
                    delay(150);
                }
            }
            if(Nombre=="MD-VL-002" ){
                readEncoder();
                updateOled();
                runtime = millis();
            }
            else if(Nombre=="MD-VL-001" ){
                readEncoder();
                updateOled();
                runtime = millis();
            }
            else if(Nombre =="EC-FR-002"){
                if(digitalRead(33)==0){
                    RGB_NUM++;
                    if(RGB_NUM > NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    #if _DEBUG_
                        Serial.println("Button Pressed");
                    #endif
                    delay(200);
                }
                if(digitalRead(32)==0){
                    RGB_NUM--;
                    if(RGB_NUM >= NUM_colors -1)RGB_NUM = 0;
                    else if(RGB_NUM < 0)RGB_NUM = NUM_colors -1;
                    changeColor(tablaRGB[RGB_NUM][0],tablaRGB[RGB_NUM][1],tablaRGB[RGB_NUM][2]);
                    updateOledBT();
                    oledFractaclBT();
                    #if _DEBUG_
                        Serial.println("Button Pressed");
                    #endif
                    delay(200);
                }
            }
            else if (Nombre=="EC-VL-002" || Nombre=="EC-VL-001" || Nombre == "EC-FR-002" || Nombre =="EC-FR-003" || Nombre == "EC-VL-003" || Nombre == "EC-VL-004" ){
                
                if(Serial.available()) {     
                    
                    datos = Serial.readStringUntil('\n');
                    datos.trim();
                    decode(0);
                    #if _DEBUG_
                        Serial.println(datos);
                    #endif
                }
                if(SerialBT.available()) {
                    datos = "";  //elimina datos de buffer
                    datos = SerialBT.readStringUntil('\n');
                    datos.trim();
                    decode(2);
                    #if _DEBUG_
                        Serial.println(datos);
                    #endif
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
                        datos.trim();              
                        decode(1);
                        #if _DEBUG_
                            Serial.println(datos);
                        #endif
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
        
        void setVarioplusChannel(int channel, bool state){
            digitalWrite(varioplusStaticPins[channel],state);
        }
        void setVarioplusStep(int value){
            
            if(value>=0 && value <= VarioplusDimeableSteps){
                
                for(int i=0;i<11;i++)digitalWrite(varioplusDimeablePins[i],POWEROFF);
                //digitalWrite(varioplusDimeablePins[0],POWERON); //PRENDE RELAY 0
                //delay(50);
                digitalWrite(varioplusDimeablePins[0],POWEROFF); //APAGA RELAY 0
                delay(50);
                digitalWrite(varioplusDimeablePins[value],POWERON);
                lastValue = value;          
                #if _DEBUG_
                    Serial.print("Last Value = ");
                    Serial.println(lastValue);
                    Serial.print("new Value = ");
                    Serial.println(value);
                    Serial.println("cambiando Relay :" + String(varioplusDimeablePins[value]));
                #endif
            }
        }
        void bleInit(String name){
            
            SerialBT.begin(name);
        }

        void sendUART(String command){
            Serial.println("Comando enviado");
            Serial2.println(command);
            #if _DEBUG_
                Serial.print("ok sent: ");
                Serial.println(command);
            #endif
        }
        void ok(int ch){
            switch (ch)
            {
            case 0:
                Serial.println("OK");
                break;
            case 1:
                Serial2.println("OK");
                break;
            case 2:
                SerialBT.println("OK");
                break;
            default:
                break;
            }
        }
        /*String *split(String input[]){
            int index[5];
            int j=0;
            for(int i=0 ;i < input.length() ;i++){
                if(input[i] == ","){
                    index[j]=i;
                    j++;
                }
            }
            return output;
        }*/

        void  decode(int canal){
            //String command =  (datos,",");
            #if _DEBUG_
                Serial.print("decode:  ");
            #endif

            if(datos == "FR,DEMO"){
                    demo = ! demo;
                    ok(canal);
                }  

            else if(datos == "GET"){
                ok(canal);
                getDataColors();
            }
            else if(datos == "VP,ON" &&  (Nombre == "EC-VL-004" || Nombre == "EC-VL-003")){               
                relayState = 1;
                digitalWrite(32,relayState);
                ok(canal);
            }
            else if(datos == "VP,OFF" && (Nombre == "EC-VL-004" || Nombre == "EC-VL-003")){
                relayState = 0;
                digitalWrite(32,relayState);
                ok(canal);
            }

            else if(datos == "VP,A" || datos == "VP,B" || datos == "VP,C"
                    || datos == "VP,D" || datos == "VP,E" || datos == "VP,F"
                    || datos == "VP,G" || datos == "VP,H" || datos == "VP,I"
                    || datos == "VP,J" || datos == "VP,K" && Nombre == "EC-VL-002"){
                    
                    int voltaje = datos[3] - 65;
                    #if _DEBUG_
                        Serial.print("Setting VP: ");
                        Serial.println(datos[3] - 65); 
                    #endif
                    setVarioplusStep(voltaje);
                    ok(canal);
            }
            else if(datos == "VP,ALLON" ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,1);
                    ok(canal);
            }
            else if(datos == "VP,ALLOFF" ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    ok(canal);
                }
            else if(datos == "VP,FRONT"){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(0,POWERON);
                    setVarioplusChannel(1,POWERON);
                    setVarioplusChannel(2,POWERON);
                    ok(canal);
                }
            else if(datos == "VP,REAR"){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(3,POWERON);
                    setVarioplusChannel(4,POWERON);
                    setVarioplusChannel(5,POWERON);
                    ok(canal);
                }
            else if(datos == "VP,CENTER"){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(2,POWERON);
                    setVarioplusChannel(3,POWERON);
                    ok(canal);
            }
            else if(datos == "VP,BLIND1" || datos == "VP,BLIND2" || datos == "VP,BLIND3" ||
                    datos == "VP,BLIND4" || datos == "VP,BLIND5" || datos == "VP,BLIND6" ){
                    #if _DEBUG_
                        Serial.print("Setting VP CH: ");
                    #endif
                    for(int i=0;i<6;i++)setVarioplusChannel(i,0);
                    setVarioplusChannel(int(datos[8])-1,POWERON);
                    ok(canal);
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
                        Serial.print("Canal # " + String(canal));
                    #endif
                    ok(canal);
                    
                    
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
                    ok(canal);
                }

                else if(datos[3]>='0' && datos[3]<='9' && datos[4]>='0' && datos[4]<='9' && datos[5]>='0' && datos[5]<='9'){
                    int index = datos[5]-48 + 10*(datos[4]-48)+ 100* (datos[3]-48);
                    RGB_NUM = index;
                    int R_,G_,B_;
                    R_= tablaRGB[index][0];
                    G_= tablaRGB[index][1];
                    B_= tablaRGB[index][2];
                    changeColor(R_,G_,B_);
                    ok(canal);
                }
            }  
        }
};