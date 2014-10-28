//use beacon_poc to send frames to ctl_poc

#include <ZigduinoRadio.h>

#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

void setup(){
  Serial.begin(9600);
  ZigduinoRadio.begin(20);
  Serial.println("init");
}

void loop(){
  if (ZigduinoRadio.available())
  {
      switch(ZigduinoRadio.read()){
        case CTL_CHECKIN:
          Serial.print("Haz Check-In: ");
          Serial.println(ZigduinoRadio.read());
          break;
        case CTL_MESSAGE:
          Serial.print("Haz Msg:");
          while (ZigduinoRadio.available())
            Serial.print((char)ZigduinoRadio.read());
          Serial.println();
          break;
        case CTL_REPORT:
          Serial.println("Haz Report");
          break;
        case CTL_SQUELCH:
           Serial.println("Squelch");
           break;
        default:
           Serial.println("CTL OB");
           break;
      }
  }
}

