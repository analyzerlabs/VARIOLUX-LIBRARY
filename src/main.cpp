#include <Arduino.h>
#include "Variolux_lib.cpp"
#include "colores.h"



variolux ECU_VL_002("Equipo003");

void setup() {

  //ECU_VL_002.shutDownVarioPlus();
  ECU_VL_002.setVariablesColors(tablaRGB);
  
}

void loop() {
  
  ECU_VL_002.run();

}

