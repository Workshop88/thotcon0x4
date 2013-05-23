/*

Test sketch for radio signal characteristics.


*/

#include <ZigduinoRadio.h>

void setup()
{
  ZigduinoRadio.begin(11);
  Serial.begin(9600);
  
  ZigduinoRadio.attachError(errHandle);
  
  Serial.println(); // signal the start with a new line
  Serial.print("Init Complete:");
}

void loop()
{
 // if (Serial.available()) {
    Serial.flush();
    
    char i;
   // for (i = 25; i >= 11; i--) {
      ZigduinoRadio.setChannel(11);
      while(ZigduinoRadio.available()) { 
      Serial.print(i, 10);
      Serial.print(": Freq:");
      Serial.print(((int16_t)(i*5))+2350, 10);
      Serial.print("Hz, LQI: ");
      Serial.print(ZigduinoRadio.getLqi(), 10);
      Serial.print(", ED: ");
      Serial.print(ZigduinoRadio.getEdNow(), 10);
      Serial.print("dBm, RSSI: ");
      Serial.print(ZigduinoRadio.getRssiNow(), 10);
      Serial.print("dBm, Clear: ");  
      Serial.print(ZigduinoRadio.doCca(), 10);
      Serial.print("; Data Rx: (");
      Serial.print(ZigduinoRadio.read());
      Serial.print(")");

      Serial.println();
      Serial.println();
      Serial.println();
   }
  delay(500); //}
}

void errHandle(radio_error_t err)
{
  Serial.println();
  Serial.print("Error: ");
  Serial.print((uint8_t)err, 10);
  Serial.println();
}

