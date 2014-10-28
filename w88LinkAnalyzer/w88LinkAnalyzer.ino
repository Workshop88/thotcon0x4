/*

Test sketch for radio signal characteristics.


*/

#include <ZigduinoRadio.h>

void setup()
{
  ZigduinoRadio.begin(20);
  Serial.begin(9600);
  
  ZigduinoRadio.attachError(errHandle);
  //ZigduinoRadio.attachReceiveFrame(processFrame);
  ZigduinoRadio.setChannel(20);
  randomSeed(ZigduinoRadio.getLastEd());
  Serial.println(); // signal the start with a new line
  Serial.print("Init Complete: ");
  Serial.println(random(768));
}

void loop()
{
 
 //   Serial.flush();
    int len = 0;
    int i = 20;
   delay(500);
      if (len = ZigduinoRadio.available()) { 
       Serial.print(len);
       Serial.print(" Data Rx: (");
       while(ZigduinoRadio.available())
         Serial.print(ZigduinoRadio.read());
       Serial.print(") ");
       Serial.print(i, DEC);
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
      
      

       Serial.println();
       Serial.println();
       Serial.println();  
     }
     delay(500);
  }


void errHandle(radio_error_t err)
{
  Serial.println();
  Serial.print("Error: ");
  Serial.print((uint8_t)err, 10);
  Serial.println();
}

uint8_t* processFrame(uint8_t len, uint8_t* frm, uint8_t lqi, uint8_t crc_fail)
{
  int i,n = 0;
  char frameId[4];
  Serial.flush();
  Serial.print ("Recieved frame: "); 
  Serial.println (len); 
  for (i = 0; i < (int) len; i++)
  {
    Serial.print("[");
    Serial.print(frm[i],HEX);
    Serial.print("]");
    if (i >= 3 && i < 7) frameId[i-3] = (char)frm[i];
  }
  frameId[4] = '\0';
  Serial.print(frameId);
  //Serial.println(frameId); /*(!strcmp(frameId,"THOT")) ? "Our Frame" : "Not Our Frame"*/ 
     
   for (int i = 0; i < (int) len; i++)
   {
       uint16_t j = ((uint16_t)((uint16_t)ZigduinoRadio.rxRingBufferHead + 1)) % ZR_FIFO_SIZE;
       if (j != ZigduinoRadio.rxRingBufferTail)
       {
                                        // push into FIFO
          ZigduinoRadio.rxRingBuffer[ZigduinoRadio.rxRingBufferHead] = frm[i];
          ZigduinoRadio.rxRingBufferHead = j;
       }
      else
      {
                                        // FIFO full
           break;
      }
   }                
  Serial.println();
  return ZigduinoRadio.rxRingBuffer;
}

