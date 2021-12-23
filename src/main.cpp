#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"

variolux ECU_VL_002("MD-VL-002");

void setup() {
  //ECU_VL_002.shutDownVarioPlus();
  ECU_VL_002.setVariablesColors(tablaRGB);
  ECU_VL_002.EncoderSetup();
  ECU_VL_002.OledSetup();
}

void loop() {
  ECU_VL_002.run();
}

