#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"

variolux EC_VL_001("MD-VL-002");

void setup() {//ECU_VL_002.shutDownVarioPlus();
  EC_VL_001.eepromInit();
  EC_VL_001.setVariablesColors(tablaRGB);
  EC_VL_001.EncoderSetup();
  EC_VL_001.OledSetup();
  EC_VL_001.updateOled();
  
  //EC_VL_001.updateOledBT();
  //EC_VL_001.oledFractaclBT();
  //EC_VL_001.bleInit("EC-FR-003");
}

void loop() {
  EC_VL_001.run();
}