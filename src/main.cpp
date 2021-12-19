#include <Arduino.h>
#include "Variolux_lib.cpp"

variolux ECU_VL_002("Mando002");

void setup() {

  //ECU_VL_002.shutDownVarioPlus();
  ECU_VL_002.OledSetup();
  ECU_VL_002.EncoderSetup();
  ECU_VL_002.showOled();
}

void loop() {
  // put your main code here, to run repeatedly
    //Serial.println(EEPROM.read(1));
    ECU_VL_002.run();

}

//problemas entre btserial y serial 2 por harwadres