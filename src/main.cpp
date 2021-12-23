#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"

variolux EC_VL_001("EC-FR-003");

void setup() {//ECU_VL_002.shutDownVarioPlus();
  EC_VL_001.setVariablesColors(tablaRGB);
  //EC_VL_001.EncoderSetup();
  //EC_VL_001.bleInit("EC-FR-003");
  EC_VL_001.OledSetup();
  //EC_VL_001.oledFractaclBT();
}

void loop() {
  EC_VL_001.run();
}