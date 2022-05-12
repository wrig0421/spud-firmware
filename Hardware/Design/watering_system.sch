EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR?
U 1 1 61149EB4
P 5000 7550
F 0 "#PWR?" H 5000 7300 50  0001 C CNN
F 1 "GND" H 5005 7377 50  0000 C CNN
F 2 "" H 5000 7550 50  0001 C CNN
F 3 "" H 5000 7550 50  0001 C CNN
	1    5000 7550
	1    0    0    -1  
$EndComp
NoConn ~ 5850 7200
Connection ~ 5000 7200
Wire Wire Line
	5000 7100 5000 7200
Wire Wire Line
	5050 7100 5000 7100
Connection ~ 5150 6750
Wire Wire Line
	4950 6750 5150 6750
Wire Wire Line
	4950 7000 4950 6750
Wire Wire Line
	5050 7000 4950 7000
Wire Wire Line
	5000 7200 5050 7200
Wire Wire Line
	5450 6750 5150 6750
Wire Wire Line
	5450 6800 5450 6750
$Comp
L Memory_EEPROM:CAT24C256 U?
U 1 1 61149EC5
P 5450 7100
F 0 "U?" H 5450 7581 50  0000 C CNN
F 1 "CAT24C256" H 5450 7490 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5450 7100 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/on-semiconductor/CAT24C256WI-GT3/CAT24C256WI-GT3OSCT-ND/2704982" H 5450 7100 50  0001 C CNN
	1    5450 7100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 61149ECB
P 7350 1200
F 0 "R?" H 7420 1246 50  0000 L CNN
F 1 "10k" H 7420 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7280 1200 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 7350 1200 50  0001 C CNN
	1    7350 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1050 7350 950 
$Comp
L power:GND #PWR?
U 1 1 61149ED2
P 7350 1900
F 0 "#PWR?" H 7350 1650 50  0001 C CNN
F 1 "GND" H 7355 1727 50  0000 C CNN
F 2 "" H 7350 1900 50  0001 C CNN
F 3 "" H 7350 1900 50  0001 C CNN
	1    7350 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1350 7350 1550
Text Label 7250 1550 2    50   ~ 0
RST
Wire Wire Line
	7250 1550 7350 1550
Connection ~ 7350 1550
Wire Wire Line
	7350 1550 7350 1700
$Comp
L Device:CP1_Small C?
U 1 1 61149EDD
P 4750 5150
F 0 "C?" V 4886 5150 50  0000 C CNN
F 1 "CP1_Small" H 4841 5105 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4750 5150 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/avx-corporation/06032U4R3BAT2A/478-10269-1-ND/6797265" H 4750 5150 50  0001 C CNN
	1    4750 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 5150 4600 5150
Wire Wire Line
	4600 5150 4600 5100
Wire Wire Line
	4650 4750 4600 4750
Wire Wire Line
	4600 4750 4600 4800
$Comp
L power:GND #PWR?
U 1 1 61149EE7
P 5050 5200
F 0 "#PWR?" H 5050 4950 50  0001 C CNN
F 1 "GND" H 5055 5027 50  0000 C CNN
F 2 "" H 5050 5200 50  0001 C CNN
F 3 "" H 5050 5200 50  0001 C CNN
	1    5050 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4750 5050 4750
Wire Wire Line
	5050 4750 5050 5150
Wire Wire Line
	5050 5150 4850 5150
Wire Wire Line
	5050 5200 5050 5150
Connection ~ 5050 5150
Text Label 4550 4750 2    50   ~ 0
XTAL1
Text Label 4550 5150 2    50   ~ 0
XTAL2
Wire Wire Line
	4550 5150 4600 5150
Connection ~ 4600 5150
Wire Wire Line
	4600 4750 4550 4750
Connection ~ 4600 4750
Text Label 5850 3350 2    50   ~ 0
RED_LED
Text Label 5850 3450 2    50   ~ 0
GRN_LED
Wire Wire Line
	4650 3550 4650 3450
Wire Wire Line
	4900 3550 4900 3450
Wire Wire Line
	5150 1900 5150 1700
Wire Wire Line
	5500 1350 5850 1350
Connection ~ 5500 1350
Wire Wire Line
	5500 1400 5500 1350
Connection ~ 5850 1350
Wire Wire Line
	5150 1350 5500 1350
Wire Wire Line
	5150 1400 5150 1350
$Comp
L Device:C C?
U 1 1 61149F03
P 5150 1550
F 0 "C?" H 5265 1596 50  0000 L CNN
F 1 "1u" H 5265 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5188 1400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 5150 1550 50  0001 C CNN
	1    5150 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1950 5850 1900
$Comp
L power:GND #PWR?
U 1 1 61149F0A
P 5850 1950
F 0 "#PWR?" H 5850 1700 50  0001 C CNN
F 1 "GND" H 5855 1777 50  0000 C CNN
F 2 "" H 5850 1950 50  0001 C CNN
F 3 "" H 5850 1950 50  0001 C CNN
	1    5850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1350 6100 1350
Wire Wire Line
	5850 1400 5850 1350
Wire Wire Line
	6100 1350 6100 1300
$Comp
L power:+3.3V #PWR?
U 1 1 61149F13
P 6100 1300
F 0 "#PWR?" H 6100 1150 50  0001 C CNN
F 1 "+3.3V" H 6115 1473 50  0000 C CNN
F 2 "" H 6100 1300 50  0001 C CNN
F 3 "" H 6100 1300 50  0001 C CNN
	1    6100 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61149F19
P 7350 950
F 0 "#PWR?" H 7350 800 50  0001 C CNN
F 1 "+3.3V" H 7365 1123 50  0000 C CNN
F 2 "" H 7350 950 50  0001 C CNN
F 3 "" H 7350 950 50  0001 C CNN
	1    7350 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 6750 5150 6650
$Comp
L power:+3.3V #PWR?
U 1 1 61149F20
P 5150 6650
F 0 "#PWR?" H 5150 6500 50  0001 C CNN
F 1 "+3.3V" H 5165 6823 50  0000 C CNN
F 2 "" H 5150 6650 50  0001 C CNN
F 3 "" H 5150 6650 50  0001 C CNN
	1    5150 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3450 4800 3450
$Comp
L power:+3.3V #PWR?
U 1 1 61149F27
P 4800 3400
F 0 "#PWR?" H 4800 3250 50  0001 C CNN
F 1 "+3.3V" H 4815 3573 50  0000 C CNN
F 2 "" H 4800 3400 50  0001 C CNN
F 3 "" H 4800 3400 50  0001 C CNN
	1    4800 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3450 4800 3400
Connection ~ 4800 3450
Wire Wire Line
	4800 3450 4900 3450
Wire Wire Line
	5850 1900 5850 1700
$Comp
L Device:C C?
U 1 1 61149F31
P 4700 6750
F 0 "C?" H 4815 6796 50  0000 L CNN
F 1 "1u" H 4815 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4738 6600 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 4700 6750 50  0001 C CNN
	1    4700 6750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61149F37
P 4450 6750
F 0 "#PWR?" H 4450 6500 50  0001 C CNN
F 1 "GND" H 4455 6577 50  0000 C CNN
F 2 "" H 4450 6750 50  0001 C CNN
F 3 "" H 4450 6750 50  0001 C CNN
	1    4450 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 6750 4450 6750
Wire Wire Line
	4850 6750 4950 6750
Connection ~ 4950 6750
$Comp
L Device:R R?
U 1 1 61149F40
P 4650 3700
F 0 "R?" H 4720 3746 50  0000 L CNN
F 1 "10k" H 4720 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4580 3700 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 4650 3700 50  0001 C CNN
	1    4650 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 61149F46
P 4900 3700
F 0 "R?" H 4970 3746 50  0000 L CNN
F 1 "10k" H 4970 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4830 3700 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 4900 3700 50  0001 C CNN
	1    4900 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 61149F4C
P 2150 6250
F 0 "R?" H 2220 6296 50  0000 L CNN
F 1 "100" H 2220 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2080 6250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ101/RHM100DCT-ND/1983776" H 2150 6250 50  0001 C CNN
	1    2150 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 6100 2150 5950
Wire Wire Line
	3450 6000 3450 6100
Wire Wire Line
	3450 6400 3450 6450
Wire Wire Line
	2150 6400 2150 6450
$Comp
L Device:R R?
U 1 1 61149F56
P 3450 6250
F 0 "R?" H 3520 6296 50  0000 L CNN
F 1 "100" H 3520 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3380 6250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ101/RHM100DCT-ND/1983776" H 3450 6250 50  0001 C CNN
	1    3450 6250
	1    0    0    -1  
$EndComp
Connection ~ 3000 6650
Wire Wire Line
	3000 6650 3150 6650
Wire Wire Line
	3000 6700 3000 6650
Wire Wire Line
	3450 7050 3450 7100
Connection ~ 3450 7050
Wire Wire Line
	3000 7050 3450 7050
Wire Wire Line
	3450 6850 3450 7050
$Comp
L Device:R R?
U 1 1 61149F63
P 3000 6850
F 0 "R?" H 3070 6896 50  0000 L CNN
F 1 "1M" H 3070 6805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2930 6850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 3000 6850 50  0001 C CNN
	1    3000 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 7050 3000 7000
$Comp
L power:GND #PWR?
U 1 1 61149F6A
P 3450 7100
F 0 "#PWR?" H 3450 6850 50  0001 C CNN
F 1 "GND" H 3455 6927 50  0000 C CNN
F 2 "" H 3450 7100 50  0001 C CNN
F 3 "" H 3450 7100 50  0001 C CNN
	1    3450 7100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 61149F70
P 3350 6650
F 0 "Q?" H 3556 6696 50  0000 L CNN
F 1 "BSS138" H 3556 6605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3550 6575 50  0001 L CIN
F 3 "https://www.digikey.com/product-detail/en/nexperia-usa-inc/BSS138P-215/1727-1142-2-ND/2779827" H 3350 6650 50  0001 L CNN
	1    3350 6650
	1    0    0    -1  
$EndComp
Text Label 2900 6650 2    50   ~ 0
RED_LED
Wire Wire Line
	2900 6650 3000 6650
Connection ~ 1700 6650
Wire Wire Line
	1700 6650 1850 6650
Wire Wire Line
	1700 6700 1700 6650
Wire Wire Line
	2150 7050 2150 7100
Connection ~ 2150 7050
Wire Wire Line
	1700 7050 2150 7050
Wire Wire Line
	2150 6850 2150 7050
$Comp
L Device:R R?
U 1 1 61149F7F
P 1700 6850
F 0 "R?" H 1770 6896 50  0000 L CNN
F 1 "1M" H 1770 6805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1630 6850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 1700 6850 50  0001 C CNN
	1    1700 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 7050 1700 7000
$Comp
L power:GND #PWR?
U 1 1 61149F86
P 2150 7100
F 0 "#PWR?" H 2150 6850 50  0001 C CNN
F 1 "GND" H 2155 6927 50  0000 C CNN
F 2 "" H 2150 7100 50  0001 C CNN
F 3 "" H 2150 7100 50  0001 C CNN
	1    2150 7100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 61149F8C
P 2050 6650
F 0 "Q?" H 2256 6696 50  0000 L CNN
F 1 "BSS138" H 2256 6605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2250 6575 50  0001 L CIN
F 3 "https://www.digikey.com/product-detail/en/nexperia-usa-inc/BSS138P-215/1727-1142-2-ND/2779827" H 2050 6650 50  0001 L CNN
	1    2050 6650
	1    0    0    -1  
$EndComp
Text Label 1600 6650 2    50   ~ 0
GRN_LED
Wire Wire Line
	1600 6650 1700 6650
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 61149F94
P 2350 5950
F 0 "J?" V 2458 5762 50  0000 R CNN
F 1 "Conn_01x02_Male" V 2413 5762 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2350 5950 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 2350 5950 50  0001 C CNN
	1    2350 5950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 61149F9A
P 3650 6000
F 0 "J?" V 3758 5812 50  0000 R CNN
F 1 "Conn_01x02_Male" V 3713 5812 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3650 6000 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 3650 6000 50  0001 C CNN
	1    3650 6000
	-1   0    0    1   
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 61149FA0
P 4750 4750
F 0 "C?" V 4886 4750 50  0000 C CNN
F 1 "CP1_Small" H 4841 4705 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4750 4750 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/avx-corporation/06032U4R3BAT2A/478-10269-1-ND/6797265" H 4750 4750 50  0001 C CNN
	1    4750 4750
	0    -1   -1   0   
$EndComp
Text Label 4450 4050 2    50   ~ 0
I2C1_SDA
Text Label 4450 3950 2    50   ~ 0
I2C1_SCL
Text Label 7400 4650 0    50   ~ 0
SWDIO
Wire Wire Line
	7200 4650 7400 4650
Text Label 7400 4750 0    50   ~ 0
SWCLK
Wire Wire Line
	7200 4750 7400 4750
Text Label 7400 4850 0    50   ~ 0
TDI
Wire Wire Line
	7200 4850 7400 4850
Wire Wire Line
	6000 3650 5850 3650
Wire Wire Line
	6000 3750 5850 3750
$Comp
L power:GND #PWR?
U 1 1 61149FB0
P 6250 5400
F 0 "#PWR?" H 6250 5150 50  0001 C CNN
F 1 "GND" H 6255 5227 50  0000 C CNN
F 2 "" H 6250 5400 50  0001 C CNN
F 3 "" H 6250 5400 50  0001 C CNN
	1    6250 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5400 6250 5150
Wire Wire Line
	6250 5150 6400 5150
Wire Wire Line
	6400 5150 6400 5050
Wire Wire Line
	6400 5150 6500 5150
Wire Wire Line
	6500 5150 6500 5050
Connection ~ 6400 5150
Wire Wire Line
	6500 5150 6600 5150
Wire Wire Line
	6600 5150 6600 5050
Connection ~ 6500 5150
Text Label 5850 3050 2    50   ~ 0
XTAL1
Text Label 5850 3150 2    50   ~ 0
XTAL2
Wire Wire Line
	5850 3150 6000 3150
Wire Wire Line
	6000 3050 5850 3050
Text Label 5800 2550 2    50   ~ 0
XTAL1_HI
Text Label 5850 2650 2    50   ~ 0
XTAL2_HI
Wire Wire Line
	5850 2650 6000 2650
Connection ~ 5850 1900
Wire Wire Line
	6500 1900 6500 2150
Wire Wire Line
	6600 2150 6600 1900
Wire Wire Line
	6600 1900 6500 1900
Connection ~ 6500 1900
Wire Wire Line
	6700 2150 6700 1900
Wire Wire Line
	6700 1900 6600 1900
Connection ~ 6600 1900
Wire Wire Line
	6800 2150 6800 1900
Wire Wire Line
	6800 1900 6700 1900
Connection ~ 6700 1900
Wire Wire Line
	6400 2150 6400 1900
Wire Wire Line
	6400 1900 6500 1900
Text Label 5850 2350 2    50   ~ 0
RST
Wire Wire Line
	5850 2350 6000 2350
Wire Wire Line
	5850 3350 6000 3350
Wire Wire Line
	6000 3450 5850 3450
Wire Wire Line
	4650 3950 4650 3850
Wire Wire Line
	6400 1900 6400 1350
Wire Wire Line
	6400 1350 6100 1350
Connection ~ 6400 1900
Connection ~ 6100 1350
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 61149FDC
P 900 1850
F 0 "J?" H 1008 2331 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1008 2240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 900 1850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/sullins-connector-solutions/GRPB042VWVN-RC/S9015E-04-ND/1786454" H 900 1850 50  0001 C CNN
	1    900  1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61149FE2
P 1550 1400
F 0 "#PWR?" H 1550 1250 50  0001 C CNN
F 1 "+3.3V" H 1565 1573 50  0000 C CNN
F 2 "" H 1550 1400 50  0001 C CNN
F 3 "" H 1550 1400 50  0001 C CNN
	1    1550 1400
	1    0    0    -1  
$EndComp
Text Label 1350 1650 0    50   ~ 0
SWDIO
Wire Wire Line
	1100 1650 1350 1650
Wire Wire Line
	1100 1550 1550 1550
Wire Wire Line
	1550 1550 1550 1400
Text Label 1350 1750 0    50   ~ 0
SWCLK
Wire Wire Line
	1350 1750 1100 1750
Text Label 1350 1850 0    50   ~ 0
SWO
Wire Wire Line
	1100 1850 1350 1850
Text Label 1350 1950 0    50   ~ 0
NJTRST
Wire Wire Line
	1100 1950 1350 1950
$Comp
L power:GND #PWR?
U 1 1 61149FF2
P 1300 2400
F 0 "#PWR?" H 1300 2150 50  0001 C CNN
F 1 "GND" H 1305 2227 50  0000 C CNN
F 2 "" H 1300 2400 50  0001 C CNN
F 3 "" H 1300 2400 50  0001 C CNN
	1    1300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2400 1300 2250
Wire Wire Line
	1300 2250 1100 2250
Text Label 1350 2050 0    50   ~ 0
TDI
Wire Wire Line
	1350 2050 1100 2050
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 61149FFC
P 7550 1800
F 0 "J?" V 7658 1612 50  0000 R CNN
F 1 "Conn_01x02_Male" V 7613 1612 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7550 1800 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 7550 1800 50  0001 C CNN
	1    7550 1800
	-1   0    0    1   
$EndComp
NoConn ~ 6000 3550
$Comp
L MCU_ST_STM32L4:STM32L433CCTx U?
U 1 1 6114A003
P 6600 3550
F 0 "U?" H 6600 1961 50  0000 C CNN
F 1 "STM32L433CCTx" H 6600 1870 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 6100 2150 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00257192.pdf" H 6600 3550 50  0001 C CNN
	1    6600 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2550 5800 2550
$Comp
L power:GND #PWR?
U 1 1 6114A00A
P 7000 5100
F 0 "#PWR?" H 7000 4850 50  0001 C CNN
F 1 "GND" H 7005 4927 50  0000 C CNN
F 2 "" H 7000 5100 50  0001 C CNN
F 3 "" H 7000 5100 50  0001 C CNN
	1    7000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5100 7000 5050
Wire Wire Line
	7000 5050 6700 5050
$Comp
L Device:CP1_Small C?
U 1 1 6114A012
P 4950 6050
F 0 "C?" V 5086 6050 50  0000 C CNN
F 1 "CP1_Small" H 5041 6005 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4950 6050 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM1885C1H200JA01D/490-1410-1-ND/587632" H 4950 6050 50  0001 C CNN
	1    4950 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 6050 4800 6050
Wire Wire Line
	4800 6050 4800 6000
Wire Wire Line
	4850 5650 4800 5650
Wire Wire Line
	4800 5650 4800 5700
$Comp
L power:GND #PWR?
U 1 1 6114A01C
P 5250 6100
F 0 "#PWR?" H 5250 5850 50  0001 C CNN
F 1 "GND" H 5255 5927 50  0000 C CNN
F 2 "" H 5250 6100 50  0001 C CNN
F 3 "" H 5250 6100 50  0001 C CNN
	1    5250 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 5650 5250 5650
Wire Wire Line
	5250 5650 5250 6050
Wire Wire Line
	5250 6050 5050 6050
Wire Wire Line
	5250 6100 5250 6050
Connection ~ 5250 6050
Text Label 4750 5650 2    50   ~ 0
XTAL1_HI
Text Label 4750 6050 2    50   ~ 0
XTAL2_HI
Wire Wire Line
	4750 6050 4800 6050
Connection ~ 4800 6050
Wire Wire Line
	4800 5650 4750 5650
Connection ~ 4800 5650
$Comp
L Device:Crystal Y?
U 1 1 6114A02D
P 4800 5850
F 0 "Y?" V 4800 5981 50  0000 L CNN
F 1 "8M" V 4845 5981 50  0001 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 4800 5850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/txc-corporation/9B-16-000MEEJ-B/887-1244-ND/2207664" H 4800 5850 50  0001 C CNN
	1    4800 5850
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 6114A033
P 4950 5650
F 0 "C?" V 5086 5650 50  0000 C CNN
F 1 "CP1_Small" H 5041 5605 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4950 5650 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM1885C1H200JA01D/490-1410-1-ND/587632" H 4950 5650 50  0001 C CNN
	1    4950 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7350 1800 7350 1900
$Comp
L Device:Crystal Y?
U 1 1 6114A03A
P 4600 4950
F 0 "Y?" V 4646 4819 50  0000 R CNN
F 1 "32.768k Crystal" V 4555 4819 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 4600 4950 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1901081604_Seiko-Epson-Q13FC1350000400_C32346.pdf" H 4600 4950 50  0001 C CNN
	1    4600 4950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 6114A040
P 4700 2850
F 0 "R?" H 4770 2896 50  0000 L CNN
F 1 "10k" H 4770 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4630 2850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 4700 2850 50  0001 C CNN
	1    4700 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A046
P 4700 2450
F 0 "R?" H 4770 2496 50  0000 L CNN
F 1 "DNI" H 4770 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4630 2450 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 4700 2450 50  0001 C CNN
	1    4700 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2700 4700 2650
$Comp
L power:+3.3V #PWR?
U 1 1 6114A04D
P 4700 2250
F 0 "#PWR?" H 4700 2100 50  0001 C CNN
F 1 "+3.3V" H 4715 2423 50  0000 C CNN
F 2 "" H 4700 2250 50  0001 C CNN
F 3 "" H 4700 2250 50  0001 C CNN
	1    4700 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2300 4700 2250
Wire Wire Line
	6000 2750 4800 2750
Wire Wire Line
	4800 2750 4800 2650
Wire Wire Line
	4800 2650 4700 2650
Connection ~ 4700 2650
Wire Wire Line
	4700 2650 4700 2600
Wire Wire Line
	7200 3850 7400 3850
Text Label 5800 4350 2    50   ~ 0
STM32_LED_STRIP_OUT_BACKUP
Wire Wire Line
	6000 4350 5800 4350
Wire Wire Line
	7200 3750 7400 3750
Text Label 7400 3750 0    50   ~ 0
LVL_SHIFTER_EN
Text Label 7400 3850 0    50   ~ 0
STM32_LED_STRIP_OUT_1
NoConn ~ 10350 1550
NoConn ~ 10350 1200
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6114A080
P 10350 1450
F 0 "H?" H 10450 1499 50  0000 L CNN
F 1 "MountingHole_Pad" H 10450 1408 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 10350 1450 50  0001 C CNN
F 3 "~" H 10350 1450 50  0001 C CNN
	1    10350 1450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6114A086
P 10350 1100
F 0 "H?" H 10450 1149 50  0000 L CNN
F 1 "MountingHole_Pad" H 10450 1058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 10350 1100 50  0001 C CNN
F 3 "~" H 10350 1100 50  0001 C CNN
	1    10350 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3350 7400 3350
Text Label 7400 3350 0    50   ~ 0
INT2
$Comp
L power:+3.3V #PWR?
U 1 1 6114A08E
P 3350 2300
F 0 "#PWR?" H 3350 2150 50  0001 C CNN
F 1 "+3.3V" H 3365 2473 50  0000 C CNN
F 2 "" H 3350 2300 50  0001 C CNN
F 3 "" H 3350 2300 50  0001 C CNN
	1    3350 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2750 3350 2750
Text Label 3400 2750 0    50   ~ 0
INT2
Wire Wire Line
	3350 2350 3350 2300
Wire Wire Line
	3350 2750 3350 2650
$Comp
L Device:R R?
U 1 1 6114A098
P 3350 2500
F 0 "R?" H 3420 2546 50  0000 L CNN
F 1 "10k" H 3420 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3280 2500 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 3350 2500 50  0001 C CNN
	1    3350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3550 7400 3550
Text Label 7400 3550 0    50   ~ 0
INT3
$Comp
L power:+3.3V #PWR?
U 1 1 6114A0A7
P 3000 2300
F 0 "#PWR?" H 3000 2150 50  0001 C CNN
F 1 "+3.3V" H 3015 2473 50  0000 C CNN
F 2 "" H 3000 2300 50  0001 C CNN
F 3 "" H 3000 2300 50  0001 C CNN
	1    3000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2950 3000 2950
Text Label 3050 2950 0    50   ~ 0
INT3
Wire Wire Line
	3000 2350 3000 2300
Wire Wire Line
	3000 2950 3000 2650
$Comp
L Device:R R?
U 1 1 6114A0B1
P 3000 2500
F 0 "R?" H 3070 2546 50  0000 L CNN
F 1 "10k" H 3070 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2930 2500 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
NoConn ~ 7200 3450
NoConn ~ 7200 3650
NoConn ~ 7200 3950
NoConn ~ 7200 4050
NoConn ~ 7200 4150
NoConn ~ 7200 4250
NoConn ~ 7200 4350
NoConn ~ 7200 4450
NoConn ~ 7200 4550
NoConn ~ 6000 4850
NoConn ~ 6000 4750
NoConn ~ 6000 4650
NoConn ~ 6000 4550
NoConn ~ 6000 4250
NoConn ~ 6000 4150
Wire Wire Line
	3000 3000 3000 2950
Connection ~ 3000 2950
Wire Wire Line
	3350 2950 3350 2750
Connection ~ 3350 2750
$Comp
L power:GND #PWR?
U 1 1 6114A0CA
P 3200 3400
F 0 "#PWR?" H 3200 3150 50  0001 C CNN
F 1 "GND" H 3205 3227 50  0000 C CNN
F 2 "" H 3200 3400 50  0001 C CNN
F 3 "" H 3200 3400 50  0001 C CNN
	1    3200 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3400 3200 3350
Wire Wire Line
	3000 3350 3000 3300
Wire Wire Line
	3350 3250 3350 3350
Wire Wire Line
	3350 3350 3200 3350
Wire Wire Line
	1200 3150 1150 3150
Wire Wire Line
	1200 3800 1200 3750
$Comp
L power:GND #PWR?
U 1 1 6114A0D6
P 1200 3800
F 0 "#PWR?" H 1200 3550 50  0001 C CNN
F 1 "GND" H 1205 3627 50  0000 C CNN
F 2 "" H 1200 3800 50  0001 C CNN
F 3 "" H 1200 3800 50  0001 C CNN
	1    1200 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3100 1550 3250
Wire Wire Line
	1150 3250 1550 3250
$Comp
L Connector:Conn_01x07_Male J?
U 1 1 6114A0DE
P 950 3450
F 0 "J?" H 1058 3931 50  0000 C CNN
F 1 "Conn_01x07_Male" H 1058 3840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 950 3450 50  0001 C CNN
F 3 "~" H 950 3450 50  0001 C CNN
	1    950  3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2150 1350 2150
Wire Wire Line
	5150 1900 5500 1900
$Comp
L Device:C C?
U 1 1 6114A0E6
P 5850 1550
F 0 "C?" H 5965 1596 50  0000 L CNN
F 1 "1u" H 5965 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5888 1400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 5850 1550 50  0001 C CNN
	1    5850 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6114A0EC
P 5500 1550
F 0 "C?" H 5615 1596 50  0000 L CNN
F 1 "1u" H 5615 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5538 1400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 5500 1550 50  0001 C CNN
	1    5500 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1900 5500 1700
Connection ~ 5500 1900
Wire Wire Line
	5500 1900 5850 1900
$Comp
L Device:R R?
U 1 1 6114A0F5
P 3350 3100
F 0 "R?" H 3420 3146 50  0000 L CNN
F 1 "DNI" H 3420 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3280 3100 50  0001 C CNN
F 3 "~" H 3350 3100 50  0001 C CNN
	1    3350 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A0FB
P 3000 3150
F 0 "R?" H 3070 3196 50  0000 L CNN
F 1 "DNI" H 3070 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2930 3150 50  0001 C CNN
F 3 "~" H 3000 3150 50  0001 C CNN
	1    3000 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 6114A101
P 1000 4550
F 0 "J?" H 1108 4831 50  0000 C CNN
F 1 "Conn_01x03_Male" H 1108 4740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1000 4550 50  0001 C CNN
F 3 "~" H 1000 4550 50  0001 C CNN
	1    1000 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6114A107
P 1350 4700
F 0 "#PWR?" H 1350 4450 50  0001 C CNN
F 1 "GND" H 1355 4527 50  0000 C CNN
F 2 "" H 1350 4700 50  0001 C CNN
F 3 "" H 1350 4700 50  0001 C CNN
	1    1350 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 4700 1350 4650
Wire Wire Line
	1350 4650 1200 4650
Wire Wire Line
	1200 4450 1500 4450
Wire Wire Line
	1500 4450 1500 4300
Text Label 1250 4550 0    50   ~ 0
LED_STRIP_OUT_1
Wire Wire Line
	1250 4550 1200 4550
NoConn ~ 6000 3850
Text Label 1500 4300 0    50   ~ 0
SYS_5V
Text Label 1550 3100 0    50   ~ 0
SYS_5V
Text Label 3450 5600 0    50   ~ 0
SYS_5V
Wire Wire Line
	3450 5600 3450 5900
Text Label 2150 5350 0    50   ~ 0
SYS_5V
Wire Wire Line
	2150 5350 2150 5850
Text Notes 2250 850  0    50   ~ 0
TLV1117 input can be 5 or 12 V
Wire Wire Line
	2300 1250 2250 1250
Text Label 2250 1250 2    50   ~ 0
VIN
Wire Wire Line
	3150 1650 3500 1650
Connection ~ 3150 1650
Wire Wire Line
	3150 1600 3150 1650
Wire Wire Line
	3150 1300 3150 1250
$Comp
L Device:C C?
U 1 1 6114A144
P 2300 1450
F 0 "C?" H 2415 1496 50  0000 L CNN
F 1 "10u" H 2415 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2338 1300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM188R61A106KE69J/490-14372-1-ND/6606833" H 2300 1450 50  0001 C CNN
	1    2300 1450
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 6114A14A
P 3150 1450
F 0 "C?" H 3265 1496 50  0000 L CNN
F 1 "10u" H 3265 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3188 1300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM188R61A106KE69J/490-14372-1-ND/6606833" H 3150 1450 50  0001 C CNN
	1    3150 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 1650 3150 1650
Wire Wire Line
	2300 1250 2300 1300
Connection ~ 3150 1250
Wire Wire Line
	3500 1250 3150 1250
Wire Wire Line
	3500 1300 3500 1250
Wire Wire Line
	3500 1600 3500 1650
Connection ~ 2750 1650
Wire Wire Line
	2300 1650 2300 1600
Wire Wire Line
	2750 1650 2300 1650
$Comp
L Device:R R?
U 1 1 6114A159
P 3500 1450
F 0 "R?" H 3570 1496 50  0000 L CNN
F 1 "1M" H 3570 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3430 1450 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 3500 1450 50  0001 C CNN
	1    3500 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1250 3150 1150
Wire Wire Line
	3050 1250 3150 1250
$Comp
L power:+3.3V #PWR?
U 1 1 6114A161
P 3150 1150
F 0 "#PWR?" H 3150 1000 50  0001 C CNN
F 1 "+3.3V" H 3165 1323 50  0000 C CNN
F 2 "" H 3150 1150 50  0001 C CNN
F 3 "" H 3150 1150 50  0001 C CNN
	1    3150 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1650 2750 1550
$Comp
L Regulator_Linear:TLV1117-33 U?
U 1 1 6114A168
P 2750 1250
F 0 "U?" H 2750 1492 50  0000 C CNN
F 1 "TLV1117-33" H 2750 1401 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 2750 1250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlv1117.pdf" H 2750 1250 50  0001 C CNN
	1    2750 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6114A16E
P 2750 1650
F 0 "#PWR?" H 2750 1400 50  0001 C CNN
F 1 "GND" H 2755 1477 50  0000 C CNN
F 2 "" H 2750 1650 50  0001 C CNN
F 3 "" H 2750 1650 50  0001 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1050 5400 950 
Wire Wire Line
	5300 1050 5400 1050
Text Label 5400 950  0    50   ~ 0
SYS_5V
Wire Wire Line
	4600 1350 4600 1500
$Comp
L power:GND #PWR?
U 1 1 6114A178
P 4600 1500
F 0 "#PWR?" H 4600 1250 50  0001 C CNN
F 1 "GND" H 4605 1327 50  0000 C CNN
F 2 "" H 4600 1500 50  0001 C CNN
F 3 "" H 4600 1500 50  0001 C CNN
	1    4600 1500
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:TLV1117-33 U?
U 1 1 6114A17E
P 4600 1050
F 0 "U?" H 4600 1292 50  0000 C CNN
F 1 "TLV1117-33" H 4600 1201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 4600 1050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlv1117.pdf" H 4600 1050 50  0001 C CNN
	1    4600 1050
	1    0    0    -1  
$EndComp
Text Label 8800 1200 0    50   ~ 0
VIN
$Comp
L Device:R R?
U 1 1 6114A185
P 8350 1400
F 0 "R?" H 8420 1446 50  0000 L CNN
F 1 "1M" H 8420 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8280 1400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 8350 1400 50  0001 C CNN
	1    8350 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6114A18B
P 8350 1600
F 0 "#PWR?" H 8350 1350 50  0001 C CNN
F 1 "GND" H 8355 1427 50  0000 C CNN
F 2 "" H 8350 1600 50  0001 C CNN
F 3 "" H 8350 1600 50  0001 C CNN
	1    8350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1600 8350 1550
Text Label 4200 1050 2    50   ~ 0
12V_EN
Wire Wire Line
	4200 1050 4300 1050
Text Label 8150 850  2    50   ~ 0
VIN
Text Label 8650 850  0    50   ~ 0
SYS_5V
Wire Wire Line
	8150 850  8250 850 
Wire Wire Line
	8550 850  8650 850 
$Comp
L Device:R R?
U 1 1 6114A198
P 5150 1050
F 0 "R?" H 5220 1096 50  0000 L CNN
F 1 "0" H 5220 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5080 1050 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 5150 1050 50  0001 C CNN
	1    5150 1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 1050 5000 1050
$Comp
L Device:R R?
U 1 1 6114A19F
P 8400 850
F 0 "R?" H 8470 896 50  0000 L CNN
F 1 "0" H 8470 805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8330 850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 8400 850 50  0001 C CNN
	1    8400 850 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 6114A1A5
P 8550 1200
F 0 "R?" H 8620 1246 50  0000 L CNN
F 1 "DNI" H 8620 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8480 1200 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 8550 1200 50  0001 C CNN
	1    8550 1200
	0    -1   -1   0   
$EndComp
Text Label 8300 1200 2    50   ~ 0
12V_EN
Wire Wire Line
	8400 1200 8350 1200
Wire Wire Line
	8700 1200 8800 1200
Wire Wire Line
	8350 1250 8350 1200
Connection ~ 8350 1200
Wire Wire Line
	8350 1200 8300 1200
$Comp
L power:GND #PWR?
U 1 1 6114A1B1
P 4550 3100
F 0 "#PWR?" H 4550 2850 50  0001 C CNN
F 1 "GND" H 4555 2927 50  0000 C CNN
F 2 "" H 4550 3100 50  0001 C CNN
F 3 "" H 4550 3100 50  0001 C CNN
	1    4550 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3100 4700 3000
Wire Wire Line
	5000 7200 5000 7550
$Comp
L power:GND #PWR?
U 1 1 6114A1B9
P 5450 7550
F 0 "#PWR?" H 5450 7300 50  0001 C CNN
F 1 "GND" H 5455 7377 50  0000 C CNN
F 2 "" H 5450 7550 50  0001 C CNN
F 3 "" H 5450 7550 50  0001 C CNN
	1    5450 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 7550 5450 7400
Connection ~ 2300 1250
Wire Wire Line
	2450 1250 2300 1250
Text Label 5800 4450 2    50   ~ 0
STM32_LED_STRIP_OUT_2
Wire Wire Line
	6000 4450 5800 4450
Connection ~ 3200 3350
Wire Wire Line
	3200 3350 3000 3350
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 6114A1CA
P 1000 5350
F 0 "J?" H 1108 5631 50  0000 C CNN
F 1 "Conn_01x03_Male" H 1108 5540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1000 5350 50  0001 C CNN
F 3 "~" H 1000 5350 50  0001 C CNN
	1    1000 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6114A1D0
P 1350 5500
F 0 "#PWR?" H 1350 5250 50  0001 C CNN
F 1 "GND" H 1355 5327 50  0000 C CNN
F 2 "" H 1350 5500 50  0001 C CNN
F 3 "" H 1350 5500 50  0001 C CNN
	1    1350 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 5500 1350 5450
Wire Wire Line
	1350 5450 1200 5450
Wire Wire Line
	1200 5250 1500 5250
Wire Wire Line
	1500 5250 1500 5100
Text Label 1250 5350 0    50   ~ 0
LED_STRIP_OUT_2
Wire Wire Line
	1250 5350 1200 5350
Text Label 1500 5100 0    50   ~ 0
SYS_5V
Wire Wire Line
	1150 3450 1400 3450
Text Label 1400 3450 0    50   ~ 0
INT3_5V
Wire Wire Line
	1150 3350 1400 3350
Text Label 1400 3350 0    50   ~ 0
INT2_5V
Text Label 1400 3550 0    50   ~ 0
STM32_LED_STRIP_OUT_1
Text Label 1400 3650 0    50   ~ 0
STM32_LED_STRIP_OUT_2
Wire Wire Line
	1150 3550 1400 3550
Wire Wire Line
	1400 3650 1150 3650
Wire Wire Line
	1150 3750 1200 3750
Connection ~ 1200 3750
Wire Wire Line
	1200 3750 1200 3150
NoConn ~ 9350 1550
NoConn ~ 9350 1200
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6114A1EA
P 9350 1450
F 0 "H?" H 9450 1499 50  0000 L CNN
F 1 "MountingHole_Pad" H 9450 1408 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 9350 1450 50  0001 C CNN
F 3 "~" H 9350 1450 50  0001 C CNN
	1    9350 1450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H?
U 1 1 6114A1F0
P 9350 1100
F 0 "H?" H 9450 1149 50  0000 L CNN
F 1 "MountingHole_Pad" H 9450 1058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 9350 1100 50  0001 C CNN
F 3 "~" H 9350 1100 50  0001 C CNN
	1    9350 1100
	1    0    0    -1  
$EndComp
NoConn ~ 1350 2150
Wire Wire Line
	4450 3950 4650 3950
Connection ~ 4650 3950
Wire Wire Line
	4700 3100 4550 3100
Text Label 5850 3750 2    50   ~ 0
NJTRST
Text Label 5850 3650 2    50   ~ 0
SWO
Wire Wire Line
	7600 5650 7600 5600
$Comp
L power:+3.3V #PWR?
U 1 1 6114A1FD
P 7600 5600
F 0 "#PWR?" H 7600 5450 50  0001 C CNN
F 1 "+3.3V" H 7615 5773 50  0000 C CNN
F 2 "" H 7600 5600 50  0001 C CNN
F 3 "" H 7600 5600 50  0001 C CNN
	1    7600 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A203
P 7600 5800
F 0 "R?" H 7670 5846 50  0000 L CNN
F 1 "10k" H 7670 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7530 5800 50  0001 C CNN
F 3 "~" H 7600 5800 50  0001 C CNN
	1    7600 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 5650 7850 5600
$Comp
L power:+3.3V #PWR?
U 1 1 6114A20A
P 7850 5600
F 0 "#PWR?" H 7850 5450 50  0001 C CNN
F 1 "+3.3V" H 7865 5773 50  0000 C CNN
F 2 "" H 7850 5600 50  0001 C CNN
F 3 "" H 7850 5600 50  0001 C CNN
	1    7850 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A210
P 7850 5800
F 0 "R?" H 7920 5846 50  0000 L CNN
F 1 "10k" H 7920 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7780 5800 50  0001 C CNN
F 3 "~" H 7850 5800 50  0001 C CNN
	1    7850 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 5650 7350 5600
$Comp
L power:+3.3V #PWR?
U 1 1 6114A217
P 7350 5600
F 0 "#PWR?" H 7350 5450 50  0001 C CNN
F 1 "+3.3V" H 7365 5773 50  0000 C CNN
F 2 "" H 7350 5600 50  0001 C CNN
F 3 "" H 7350 5600 50  0001 C CNN
	1    7350 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A21D
P 7350 5800
F 0 "R?" H 7420 5846 50  0000 L CNN
F 1 "10k" H 7420 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7280 5800 50  0001 C CNN
F 3 "~" H 7350 5800 50  0001 C CNN
	1    7350 5800
	1    0    0    -1  
$EndComp
Text Label 7250 6000 2    50   ~ 0
SWO
Wire Wire Line
	7250 6000 7350 6000
Wire Wire Line
	7350 6000 7350 5950
Text Label 7250 6100 2    50   ~ 0
NJTRST
Wire Wire Line
	7250 6100 7600 6100
Wire Wire Line
	7600 6100 7600 5950
Text Label 7250 6200 2    50   ~ 0
SWDIO
Text Label 7250 6300 2    50   ~ 0
SWCLK
Text Label 7250 6400 2    50   ~ 0
TDI
Wire Wire Line
	7250 6200 7850 6200
Wire Wire Line
	7850 6200 7850 5950
Wire Wire Line
	8100 5650 8100 5600
$Comp
L power:+3.3V #PWR?
U 1 1 6114A22F
P 8100 5600
F 0 "#PWR?" H 8100 5450 50  0001 C CNN
F 1 "+3.3V" H 8115 5773 50  0000 C CNN
F 2 "" H 8100 5600 50  0001 C CNN
F 3 "" H 8100 5600 50  0001 C CNN
	1    8100 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A235
P 8100 5800
F 0 "R?" H 8170 5846 50  0000 L CNN
F 1 "10k" H 8170 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8030 5800 50  0001 C CNN
F 3 "~" H 8100 5800 50  0001 C CNN
	1    8100 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5650 8350 5600
$Comp
L power:+3.3V #PWR?
U 1 1 6114A23C
P 8350 5600
F 0 "#PWR?" H 8350 5450 50  0001 C CNN
F 1 "+3.3V" H 8365 5773 50  0000 C CNN
F 2 "" H 8350 5600 50  0001 C CNN
F 3 "" H 8350 5600 50  0001 C CNN
	1    8350 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6114A242
P 8350 5800
F 0 "R?" H 8420 5846 50  0000 L CNN
F 1 "10k" H 8420 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8280 5800 50  0001 C CNN
F 3 "~" H 8350 5800 50  0001 C CNN
	1    8350 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 6300 8100 6300
Wire Wire Line
	8100 6300 8100 5950
Wire Wire Line
	7250 6400 8350 6400
Wire Wire Line
	8350 6400 8350 5950
Wire Wire Line
	5900 7100 5850 7100
Text Label 5900 7100 0    50   ~ 0
I2C1_SCL
Wire Wire Line
	5900 7000 5850 7000
Text Label 5900 7000 0    50   ~ 0
I2C1_SDA
Wire Wire Line
	4450 4050 4900 4050
Wire Wire Line
	4650 3950 6000 3950
Wire Wire Line
	4900 4050 4900 3850
Connection ~ 4900 4050
Wire Wire Line
	4900 4050 6000 4050
Text Label 2200 2100 0    50   ~ 0
VIN
$Comp
L power:GND #PWR?
U 1 1 6114A256
P 2100 2700
F 0 "#PWR?" H 2100 2450 50  0001 C CNN
F 1 "GND" H 2105 2527 50  0000 C CNN
F 2 "" H 2100 2700 50  0001 C CNN
F 3 "" H 2100 2700 50  0001 C CNN
	1    2100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2650 2100 2700
Wire Wire Line
	1900 2650 2100 2650
Wire Wire Line
	1900 2400 2200 2400
Wire Wire Line
	2200 2400 2200 2100
$Comp
L Connector:Conn_01x01_Male J?
U 1 1 6114A260
P 1700 2650
F 0 "J?" H 1808 2831 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1808 2740 50  0000 C CNN
F 2 "" H 1700 2650 50  0001 C CNN
F 3 "~" H 1700 2650 50  0001 C CNN
	1    1700 2650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J?
U 1 1 6114A266
P 1700 2400
F 0 "J?" H 1808 2581 50  0000 C CNN
F 1 "Conn_01x01_Male" H 1808 2490 50  0000 C CNN
F 2 "" H 1700 2400 50  0001 C CNN
F 3 "~" H 1700 2400 50  0001 C CNN
	1    1700 2400
	1    0    0    -1  
$EndComp
NoConn ~ 6000 2950
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 6116BEEF
P 8850 4000
F 0 "Q?" H 9040 4046 50  0000 L CNN
F 1 "2N3904" H 9040 3955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9050 3925 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8850 4000 50  0001 L CNN
	1    8850 4000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
