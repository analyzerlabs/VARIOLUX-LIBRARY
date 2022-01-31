#include "Variolux_lib.h"
#include "colores.h"
String modelo = "EC-VL-001";
variolux EC(modelo);              // MD-VL-001 -> mando para EC-VL-001 : CONTROL DE 6 CANALES ON/OFF VARIOPLUS
                                  // MD-VL-002 -> mando para EC-VL-002 : CONTROL DE 1 CANAL DIMEABLE DE 10 PASOS VARIOPLUS
                                  // EC-VL-001 -> CONTROL DE 6 CANALES ON/OFF VARIOPLUS
                                  // EC-VL-002 -> CONTROL DE 1 CANAL DIMEABLE DE 10 PASOS VARIOPLUS
                                  // EC-VL-003 -> CONTROL DE 1 CANAL ON/OFF , CONTROLADO POR BOTONES EN PANEL
                                  // EC-VL-004 -> CONTROL DE 1 CANAL ON/OFF , CONTROLADO POR BLUETOOTH
                                  // EC-FR-002 -> CONTROL DE 2 CANALES FRACTAL , VIA BOTONES EN PANEL
                                  // EC-FR-003 -> CONTROL DE 2 CANALES FRACTAL , VIA BLUETOOTH 

void setup() {
  
  //ECU_VL_002.shutDownVarioPlus();
  //EC_VL_001.eepromInit();
  EC.setVariablesColors(tablaRGB); // FUNCION GENERAL , VALIDA PARA TODO EQUIPO Y MANDO
  
  if(modelo == "MD-VL-001" || modelo == "MD-VL-002"){
      EC.EncoderSetup();             
      EC.OledSetup();
      EC.updateOled();
  }
  else if (modelo == "EC-VL-004" || modelo == "EC-FR-003"){
      EC.bleInit(modelo);    
      EC.OledSetup();
      EC.updateOledBT();
      EC.oledFractaclBT();
  }
  else if(modelo == "EC-VL-003" || modelo == "EC-FR-002"){
      EC.OledSetup();
      EC.updateOledBT();
      EC.oledFractaclBT();
  }

}

void loop() {
  EC.run();
}
