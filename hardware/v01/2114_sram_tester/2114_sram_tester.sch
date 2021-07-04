EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "2114 SRAM tester"
Date "2021-07-02"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 60DF5BD0
P 2450 3500
F 0 "A?" H 2450 2411 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 2450 2320 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 2450 2229 50  0000 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 2450 3500 50  0001 C CNN
	1    2450 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x09_Counter_Clockwise J?
U 1 1 60DF7143
P 5350 3500
F 0 "J?" H 5400 4117 50  0000 C CNN
F 1 "Conn_02x09_Counter_Clockwise" H 5400 4026 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm_Socket" H 5350 3500 50  0001 C CNN
F 3 "~" H 5350 3500 50  0001 C CNN
	1    5350 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 60DFB23B
P 3250 1300
F 0 "D?" H 3243 1517 50  0000 C CNN
F 1 "GREEN LED" H 3243 1426 50  0000 C CNN
F 2 "LED_THT:LED_D4.0mm" H 3250 1300 50  0001 C CNN
F 3 "~" H 3250 1300 50  0001 C CNN
	1    3250 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 60DFBD33
P 1950 1250
F 0 "D?" H 1943 1467 50  0000 C CNN
F 1 "RED LED" H 1943 1376 50  0000 C CNN
F 2 "LED_THT:LED_D4.0mm" H 1950 1250 50  0001 C CNN
F 3 "~" H 1950 1250 50  0001 C CNN
	1    1950 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60DFC4FB
P 4200 4650
F 0 "#PWR?" H 4200 4400 50  0001 C CNN
F 1 "GND" H 4205 4477 50  0000 C CNN
F 2 "" H 4200 4650 50  0001 C CNN
F 3 "" H 4200 4650 50  0001 C CNN
	1    4200 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 4500 2550 4500
Connection ~ 2550 4500
$Comp
L power:+5V #PWR?
U 1 1 60DFCCB0
P 4150 2550
F 0 "#PWR?" H 4150 2400 50  0001 C CNN
F 1 "+5V" H 4165 2723 50  0000 C CNN
F 2 "" H 4150 2550 50  0001 C CNN
F 3 "" H 4150 2550 50  0001 C CNN
	1    4150 2550
	1    0    0    -1  
$EndComp
Text GLabel 4150 2750 3    50   Input ~ 0
5vPower
Wire Wire Line
	4150 2550 4150 2750
Text GLabel 2650 2300 1    50   Input ~ 0
5vPower
Wire Wire Line
	2650 2500 2650 2300
Text GLabel 6500 3100 2    50   Input ~ 0
5vPower
Wire Wire Line
	5650 3100 6500 3100
Wire Wire Line
	5150 3900 4200 3900
Wire Wire Line
	4200 3900 4200 4500
Wire Wire Line
	2550 4500 4200 4500
Wire Wire Line
	4200 4500 4200 4650
Connection ~ 4200 4500
$EndSCHEMATC
