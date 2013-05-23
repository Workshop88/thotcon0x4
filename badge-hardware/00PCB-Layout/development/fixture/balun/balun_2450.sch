EESchema Schematic File Version 2  date Fri 15 Mar 2013 14:03:57 CDT
LIBS:pauls_lib
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:balun_2450-cache
EELAYER 27 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "FIXTURE, ANTENNA TEST"
Date "15 mar 2013"
Rev "T1"
Comp "Wokshop 88"
Comment1 "Engineer: Paul Reich"
Comment2 "Drawn: Paul Reich"
Comment3 "Project Manager: R. Ristich"
Comment4 "CAD File: balun_2450.pro"
$EndDescr
Wire Wire Line
	5100 3200 4900 3200
Wire Wire Line
	4900 3200 4900 2950
Wire Wire Line
	4900 2950 6050 2950
Wire Wire Line
	6050 2950 6050 3200
Wire Wire Line
	6050 3200 5900 3200
$Comp
L STRIPLINE_100 Z2
U 1 1 514370D9
P 5500 3750
F 0 "Z2" H 5450 3850 60  0000 L BNN
F 1 "STRIPLINE_100" H 5150 3575 60  0000 L BNN
	1    5500 3750
	1    0    0    -1  
$EndComp
$Comp
L STRIPLINE_100 Z1
U 1 1 514370E8
P 5500 3250
F 0 "Z1" H 5450 3350 60  0000 L BNN
F 1 "STRIPLINE_100" H 5150 3075 60  0000 L BNN
	1    5500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3700 4900 3700
Wire Wire Line
	4900 3700 4900 4050
Wire Wire Line
	4900 4050 6050 4050
Wire Wire Line
	6050 4050 6050 3700
Wire Wire Line
	6050 3700 5900 3700
$EndSCHEMATC
