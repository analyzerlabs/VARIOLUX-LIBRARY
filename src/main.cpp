#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"

variolux EC("MD-VL-001");

void setup() {//ECU_VL_002.shutDownVarioPlus();
  //EC_VL_001.eepromInit();
  EC.setVariablesColors(tablaRGB);
  //EC_VL_001.EncoderSetup();
  EC.OledSetup();
  //EC_VL_001.updateOled();
  
  EC.updateOledBT();
  EC.oledFractaclBT();
  //EC_VL_001.bleInit("EC-VL-003");
}

void loop() {
  EC.run();
}