#include <TcbTile.h>
#include <fontScroll.h>
#include <ZigduinoRadio.h>

void setup() {
     TcbTileSetup();
 ZigduinoRadio.begin(20);
 //Serial.begin(9600);
 randomSeed(analogRead(33));
 show_screen(w88, 100);
}

void loop(){
  uint16_t i = random(9);

      ZigduinoRadio.beginTransmission();
     // Serial.print("Sending area: ");
     // Serial.println(i);
      show_screen(font5x8['1'+i-0x21], 100);
      ZigduinoRadio.write((char)i);
      ZigduinoRadio.endTransmission();
      delay(6000);

}

