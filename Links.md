### Links for Thotcon badges
#### Protocols
* 802.15.4 - MAC (Media Access Layer) and PHY (Physical layer) used by all RF devices (may be some others)
* ZigBee - proprietary (consortium owned) protocol set over 802.15.4 RF. Requires 256k memory for protocol stack. 
* 6LowPan - [IPv6 over Low Power access network](http://www.ecnmag.com/articles/2009/02/6lowpan-goes-where-zigbee-cant) - Routing, Addressing, IP protocols over 802.15.4 RF. Applications similar to Zigbee, multiple implementations. Each node gets an IP address.
* [Contiki](http://www.contiki-os.org/) - network OS built atop 6LowPan, open source. Runs on current generation chipsets. Full IDE, Cooja network simulator free. 
* [SimpliciTI](http://www.ti.com/tool/simpliciti) - simple protocol for small star networks, uses hubs for store and forward, minimal memory footprint, software available for Texas Instruments chipsets, price?
* SNAP - network operating system over 802.15.4. Proprietary to [Synapse Networks](http://www.synapse-wireless.com/snap-components/rf-engine), programmed by Python over the air. Modules $40 each.

#### Chipsets
TI has a variety of [chipsets](http://focus.ti.com/wireless/docs/wirelessproduct.tsp?familyId=2003&sectionId=646&tabId=2736) with integrated radios that could fit the budget:

*  [CC1110F32](http://www.ti.com/product/cc1110f32) 8 bit processor (antique 8051 instruction set) + CC1101 900MHz RF. $2.75 1K quantity. This probably needs an additional host processor to do much. There’s a version with 6LowPan protocol preloaded [CC1180](http://www.ti.com/product/cc1180) $3.85@1K.
*  [CC430F6137](http://www.ti.com/docs/prod/folders/print/cc430f6137.html) -  TI CC430 processor + CC1101 900MHz RF. $3 in 1K quantity. Used for variety of radio protocols. The processor is TI's 16 bit ultra low power series. <1Ghz radio, use same band as wireless phone handset (900 mhz)
* [CC2530](http://www.ti.com/product/cc2530) 8-bit 8051 + 2.4 GHz radio $3.65@1K. ZigBee stack available on 256K flash memory version
* [CC2544](http://www.ti.com/product/cc2544) - 8-bit + 2.4GHz radio. “Value line” $1.80@1k. 32K flash memory, targeted to proprietary 2.4 GHz systems, USB dongles

Freescale

* MC13211:2.4 GHz 802.15.4 RF and 8-bit HCS08 MCU with 16KB Flash, 1KB RAM
*  MC13224V: 2.4 GHz 802.15.4 RF and 32-bit ARM7™ MCU with 128KB Flash, 96K ram <$5.
* MPXY8300: Microcontroller, Pressure Sensor, X-Z Accelerometer and RF Transmitter- 900 MHz intended for tire pressure monitoring
* MC12311: Sub-1 GHz RF and 8-bit HCS08 MCU with 32KB Flash, 2KB RAM
* MC33696: PLL Tuned UHF Transceiver - 900Mhz, needs microprocessor to do anything

Atmel

* [ATMEGA256RFR2](http://www.atmel.com/devices/ATMEGA256RFR2.aspx) brand new, AVR 8 bit processor + 2.4 GHz $6.20 DigiKey
* AT86RF212 - 900 MHz transceiver chip, < $3

#### RF modules
Modules include radio chip, antenna, and support chips, sometimes with MCU. Price is the issue - they seem to range from $20 to $75.

[Anaren](http://www.anaren.com/air-wiki-zigbee/index.php/Main_Page) - makes [RF Boosterpacks](https://estore.ti.com/430BOOST-CC110L-CC110L-RF-Module-BoosterPack-P2734.aspx) for TI Launchpad dev units. $19 single unit

[Anaren A110LR09A](http://www.anaren.com/sites/default/files/Part-Datasheets/A110LR09A.pdf) - 900 MHz $15

[MICROCHIP - MRF89XAM9A-I/RM](http://www.newark.com/microchip/mrf89xam9a-i-rm/915mhz-radio-transceiver-module/dp/76R6669?in_merch=Popular%20RF%20Modules&in_merch=Popular%20Products&MER=PPSO_N_C_RFModules_None) - 915MHZ RADIO TRANSCEIVER MODULE W/ FCC CERTIFICATION, PCB ANTENNA AND MIWI SUPPORT $7+, SPI interface to host board






#### RF issues
Design decision needed: what radio spectrum? Common choices for US are 900 MHz and 2.4 GHz. Radios available for each, most (all?) protocols work on both.

[Collection of real antenna designs](http://www.qsl.net/va3iul/Antenna/Printed_and_Microstrip_Antennas/Design_Ideas_for_Printed_and_Microstrip_Antennas.htm)


