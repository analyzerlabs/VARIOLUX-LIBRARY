#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"



variolux ECU_VL_002("Equipo002");

void setup() {

  //ECU_VL_002.shutDownVarioPlus();
  ECU_VL_002.setVariablesColors(tablaRGB);
  //ECU_VL_002.OledSetup();
  //ECU_VL_002.EncoderSetup();
  //ECU_VL_002.showOled();
}

void loop() {
  // put your main code here, to run repeatedly
    //Serial.println(EEPROM.read(1));
  ECU_VL_002.run();

}

//problemas entre btserial y serial 2 por harwadres