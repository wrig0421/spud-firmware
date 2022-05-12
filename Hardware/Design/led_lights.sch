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
L power:GND #PWR0101
U 1 1 5F5D23E5
P 3950 7200
F 0 "#PWR0101" H 3950 6950 50  0001 C CNN
F 1 "GND" H 3955 7027 50  0000 C CNN
F 2 "" H 3950 7200 50  0001 C CNN
F 3 "" H 3950 7200 50  0001 C CNN
	1    3950 7200
	1    0    0    -1  
$EndComp
NoConn ~ 4800 6850
Connection ~ 3950 6850
Wire Wire Line
	3950 6750 3950 6850
Wire Wire Line
	4000 6750 3950 6750
Wire Wire Line
	3900 6650 3900 6400
Wire Wire Line
	4000 6650 3900 6650
Wire Wire Line
	3950 6850 4000 6850
Wire Wire Line
	4400 6450 4400 6400
$Comp
L Memory_EEPROM:CAT24C256 U4
U 1 1 5F5D23FD
P 4400 6750
F 0 "U4" H 4400 7231 50  0000 C CNN
F 1 "CAT24C256" H 4400 7140 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4400 6750 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/on-semiconductor/CAT24C256WI-GT3/CAT24C256WI-GT3OSCT-ND/2704982" H 4400 6750 50  0001 C CNN
	1    4400 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F5D2403
P 7050 1150
F 0 "R1" H 7120 1196 50  0000 L CNN
F 1 "10k" H 7120 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6980 1150 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 7050 1150 50  0001 C CNN
	1    7050 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1000 7050 900 
Wire Wire Line
	7050 1300 7050 1500
Text Label 6950 1500 2    50   ~ 0
NRST
$Comp
L Device:CP1_Small C2
U 1 1 5F5D2415
P 4250 3500
F 0 "C2" V 4386 3500 50  0000 C CNN
F 1 "CP1_Small" H 4341 3455 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4250 3500 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/avx-corporation/06032U4R3BAT2A/478-10269-1-ND/6797265" H 4250 3500 50  0001 C CNN
	1    4250 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4150 3500 4100 3500
Wire Wire Line
	4100 3500 4100 3450
Wire Wire Line
	4150 3100 4100 3100
Wire Wire Line
	4100 3100 4100 3150
$Comp
L power:GND #PWR0103
U 1 1 5F5D241F
P 4550 3550
F 0 "#PWR0103" H 4550 3300 50  0001 C CNN
F 1 "GND" H 4555 3377 50  0000 C CNN
F 2 "" H 4550 3550 50  0001 C CNN
F 3 "" H 4550 3550 50  0001 C CNN
	1    4550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3100 4550 3100
Wire Wire Line
	4550 3100 4550 3500
Wire Wire Line
	4550 3500 4350 3500
Wire Wire Line
	4550 3550 4550 3500
Connection ~ 4550 3500
Text Label 4050 3100 2    50   ~ 0
XTAL1
Text Label 4050 3500 2    50   ~ 0
XTAL2
Wire Wire Line
	4050 3500 4100 3500
Connection ~ 4100 3500
Wire Wire Line
	4100 3100 4050 3100
Connection ~ 4100 3100
Wire Wire Line
	7000 2850 7000 2650
Wire Wire Line
	7350 2300 7700 2300
Connection ~ 7350 2300
Wire Wire Line
	7350 2350 7350 2300
Connection ~ 7700 2300
Wire Wire Line
	7000 2300 7350 2300
Wire Wire Line
	7000 2350 7000 2300
$Comp
L Device:C C7
U 1 1 5F5D243B
P 7000 2500
F 0 "C7" H 7115 2546 50  0000 L CNN
F 1 "1u" H 7115 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7038 2350 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 7000 2500 50  0001 C CNN
	1    7000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2900 7700 2850
$Comp
L power:GND #PWR0104
U 1 1 5F5D2442
P 7700 2900
F 0 "#PWR0104" H 7700 2650 50  0001 C CNN
F 1 "GND" H 7705 2727 50  0000 C CNN
F 2 "" H 7700 2900 50  0001 C CNN
F 3 "" H 7700 2900 50  0001 C CNN
	1    7700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2300 7950 2300
Wire Wire Line
	7700 2350 7700 2300
Wire Wire Line
	7700 2850 7700 2650
$Comp
L Device:C C10
U 1 1 5F5D2586
P 3650 6400
F 0 "C10" H 3765 6446 50  0000 L CNN
F 1 "1u" H 3765 6355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3688 6250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 3650 6400 50  0001 C CNN
	1    3650 6400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5F5D258C
P 3400 6400
F 0 "#PWR0110" H 3400 6150 50  0001 C CNN
F 1 "GND" H 3405 6227 50  0000 C CNN
F 2 "" H 3400 6400 50  0001 C CNN
F 3 "" H 3400 6400 50  0001 C CNN
	1    3400 6400
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 6400 3400 6400
Wire Wire Line
	3800 6400 3900 6400
Connection ~ 3900 6400
$Comp
L Device:R R8
U 1 1 5F5D25B2
P 1500 6650
F 0 "R8" H 1570 6696 50  0000 L CNN
F 1 "100" H 1570 6605 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1430 6650 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ101/RHM100DCT-ND/1983776" H 1500 6650 50  0001 C CNN
	1    1500 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 6500 1500 6350
Wire Wire Line
	2800 6400 2800 6500
Wire Wire Line
	2800 6800 2800 6850
Wire Wire Line
	1500 6800 1500 6850
$Comp
L Device:R R16
U 1 1 5F5D25C2
P 2800 6650
F 0 "R16" H 2870 6696 50  0000 L CNN
F 1 "100" H 2870 6605 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2730 6650 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ101/RHM100DCT-ND/1983776" H 2800 6650 50  0001 C CNN
	1    2800 6650
	1    0    0    -1  
$EndComp
Connection ~ 2350 7050
Wire Wire Line
	2350 7050 2500 7050
Wire Wire Line
	2350 7100 2350 7050
Wire Wire Line
	2800 7450 2800 7500
Connection ~ 2800 7450
Wire Wire Line
	2350 7450 2800 7450
Wire Wire Line
	2800 7250 2800 7450
$Comp
L Device:R R14
U 1 1 5F5D25CF
P 2350 7250
F 0 "R14" H 2420 7296 50  0000 L CNN
F 1 "1M" H 2420 7205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2280 7250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 2350 7250 50  0001 C CNN
	1    2350 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 7450 2350 7400
$Comp
L power:GND #PWR0112
U 1 1 5F5D25D6
P 2800 7500
F 0 "#PWR0112" H 2800 7250 50  0001 C CNN
F 1 "GND" H 2805 7327 50  0000 C CNN
F 2 "" H 2800 7500 50  0001 C CNN
F 3 "" H 2800 7500 50  0001 C CNN
	1    2800 7500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q2
U 1 1 5F5D25DC
P 2700 7050
F 0 "Q2" H 2906 7096 50  0000 L CNN
F 1 "BSS138" H 2906 7005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2900 6975 50  0001 L CIN
F 3 "https://www.digikey.com/product-detail/en/nexperia-usa-inc/BSS138P-215/1727-1142-2-ND/2779827" H 2700 7050 50  0001 L CNN
	1    2700 7050
	1    0    0    -1  
$EndComp
Text Label 2250 7050 2    50   ~ 0
RED_LED
Wire Wire Line
	2250 7050 2350 7050
Connection ~ 1050 7050
Wire Wire Line
	1050 7050 1200 7050
Wire Wire Line
	1050 7100 1050 7050
Wire Wire Line
	1500 7450 1500 7500
Connection ~ 1500 7450
Wire Wire Line
	1050 7450 1500 7450
Wire Wire Line
	1500 7250 1500 7450
$Comp
L Device:R R5
U 1 1 5F5D25EB
P 1050 7250
F 0 "R5" H 1120 7296 50  0000 L CNN
F 1 "1M" H 1120 7205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 980 7250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 1050 7250 50  0001 C CNN
	1    1050 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 7450 1050 7400
$Comp
L power:GND #PWR0113
U 1 1 5F5D25F2
P 1500 7500
F 0 "#PWR0113" H 1500 7250 50  0001 C CNN
F 1 "GND" H 1505 7327 50  0000 C CNN
F 2 "" H 1500 7500 50  0001 C CNN
F 3 "" H 1500 7500 50  0001 C CNN
	1    1500 7500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q1
U 1 1 5F5D25F8
P 1400 7050
F 0 "Q1" H 1606 7096 50  0000 L CNN
F 1 "BSS138" H 1606 7005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1600 6975 50  0001 L CIN
F 3 "https://www.digikey.com/product-detail/en/nexperia-usa-inc/BSS138P-215/1727-1142-2-ND/2779827" H 1400 7050 50  0001 L CNN
	1    1400 7050
	1    0    0    -1  
$EndComp
Text Label 950  7050 2    50   ~ 0
GRN_LED
Wire Wire Line
	950  7050 1050 7050
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5F5D2600
P 1700 6350
F 0 "J5" V 1808 6162 50  0000 R CNN
F 1 "Conn_01x02_Male" V 1763 6162 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1700 6350 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 1700 6350 50  0001 C CNN
	1    1700 6350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5F5D2606
P 3000 6400
F 0 "J6" V 3108 6212 50  0000 R CNN
F 1 "Conn_01x02_Male" V 3063 6212 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3000 6400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 3000 6400 50  0001 C CNN
	1    3000 6400
	-1   0    0    1   
$EndComp
$Comp
L Device:CP1_Small C1
U 1 1 5F5D260C
P 4250 3100
F 0 "C1" V 4386 3100 50  0000 C CNN
F 1 "CP1_Small" H 4341 3055 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4250 3100 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/avx-corporation/06032U4R3BAT2A/478-10269-1-ND/6797265" H 4250 3100 50  0001 C CNN
	1    4250 3100
	0    -1   -1   0   
$EndComp
Connection ~ 7700 2850
Text Label 3300 5000 0    50   ~ 0
ST_SWDIO
Wire Wire Line
	3050 5000 3300 5000
Wire Wire Line
	3050 4900 3500 4900
Text Label 3300 5100 0    50   ~ 0
ST_SWCLK
Wire Wire Line
	3300 5100 3050 5100
Text Label 3300 5200 0    50   ~ 0
NRST
Wire Wire Line
	3050 5200 3300 5200
$Comp
L power:GND #PWR0120
U 1 1 5F5D26E8
P 3250 5450
F 0 "#PWR0120" H 3250 5200 50  0001 C CNN
F 1 "GND" H 3255 5277 50  0000 C CNN
F 2 "" H 3250 5450 50  0001 C CNN
F 3 "" H 3250 5450 50  0001 C CNN
	1    3250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5450 3250 5300
Wire Wire Line
	3250 5300 3050 5300
$Comp
L Device:CP1_Small C4
U 1 1 5F5D273A
P 4300 2600
F 0 "C4" V 4436 2600 50  0000 C CNN
F 1 "CP1_Small" H 4391 2555 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4300 2600 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM1885C1H200JA01D/490-1410-1-ND/587632" H 4300 2600 50  0001 C CNN
	1    4300 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 2600 4150 2600
Wire Wire Line
	4150 2600 4150 2550
Wire Wire Line
	4200 2200 4150 2200
Wire Wire Line
	4150 2200 4150 2250
Wire Wire Line
	4600 2600 4400 2600
Text Label 4100 2200 2    50   ~ 0
XTAL1_HI
Text Label 4100 2600 2    50   ~ 0
XTAL2_HI
Wire Wire Line
	4100 2600 4150 2600
Connection ~ 4150 2600
Wire Wire Line
	4150 2200 4100 2200
Connection ~ 4150 2200
$Comp
L Device:Crystal Y2
U 1 1 5F5D2755
P 4150 2400
F 0 "Y2" V 4150 2531 50  0000 L CNN
F 1 "8M" V 4195 2531 50  0001 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 4150 2400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/txc-corporation/9B-16-000MEEJ-B/887-1244-ND/2207664" H 4150 2400 50  0001 C CNN
	1    4150 2400
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C3
U 1 1 5F5D275B
P 4300 2200
F 0 "C3" V 4436 2200 50  0000 C CNN
F 1 "CP1_Small" H 4391 2155 50  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4300 2200 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM1885C1H200JA01D/490-1410-1-ND/587632" H 4300 2200 50  0001 C CNN
	1    4300 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5F5D2780
P 4100 3300
F 0 "Y1" V 4146 3169 50  0000 R CNN
F 1 "32.768k Crystal" V 4055 3169 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 4100 3300 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1901081604_Seiko-Epson-Q13FC1350000400_C32346.pdf" H 4100 3300 50  0001 C CNN
	1    4100 3300
	0    -1   -1   0   
$EndComp
NoConn ~ 10350 900 
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5F5D23D6
P 10350 800
F 0 "H2" H 10450 849 50  0000 L CNN
F 1 "MountingHole_Pad" H 10450 758 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 10350 800 50  0001 C CNN
F 3 "~" H 10350 800 50  0001 C CNN
	1    10350 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2850 7350 2850
$Comp
L Device:C C9
U 1 1 600ED63A
P 7700 2500
F 0 "C9" H 7815 2546 50  0000 L CNN
F 1 "1u" H 7815 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7738 2350 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 7700 2500 50  0001 C CNN
	1    7700 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 600F9E37
P 7350 2500
F 0 "C8" H 7465 2546 50  0000 L CNN
F 1 "1u" H 7465 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7388 2350 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 7350 2500 50  0001 C CNN
	1    7350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2850 7350 2650
Connection ~ 7350 2850
Wire Wire Line
	7350 2850 7700 2850
Text Label 8800 5100 2    50   ~ 0
LVL_SHIFTER_EN
Wire Wire Line
	9550 5200 9550 5150
Text Label 2800 6000 0    50   ~ 0
SYS_5V
Wire Wire Line
	2800 6000 2800 6300
Text Label 1500 5950 0    50   ~ 0
SYS_5V
Text Notes 4950 800  0    50   ~ 0
TLV1117 input can be VBAT or VBUS
$Comp
L Device:C C5
U 1 1 5F5D277A
P 5000 1400
F 0 "C5" H 5115 1446 50  0000 L CNN
F 1 "10u" H 5115 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5038 1250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM188R61A106KE69J/490-14372-1-ND/6606833" H 5000 1400 50  0001 C CNN
	1    5000 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 5F5D2774
P 5950 1400
F 0 "C6" H 6065 1446 50  0000 L CNN
F 1 "10u" H 6065 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5988 1250 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/murata-electronics/GRM188R61A106KE69J/490-14372-1-ND/6606833" H 5950 1400 50  0001 C CNN
	1    5950 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6200 1200 5950 1200
Wire Wire Line
	6200 1250 6200 1200
Wire Wire Line
	6200 1550 6200 1600
Connection ~ 5450 1600
Wire Wire Line
	5000 1600 5000 1550
Wire Wire Line
	5450 1600 5000 1600
$Comp
L Device:R R4
U 1 1 5F5D270A
P 6200 1400
F 0 "R4" H 6270 1446 50  0000 L CNN
F 1 "1M" H 6270 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6130 1400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/te-connectivity-passive-product/CRGCQ0603J1M0/A130109CT-ND/8577941" H 6200 1400 50  0001 C CNN
	1    6200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1200 6200 1100
Wire Wire Line
	5450 1600 5450 1500
$Comp
L Regulator_Linear:TLV1117-33 U1
U 1 1 5F5D26FB
P 5450 1200
F 0 "U1" H 5450 1442 50  0000 C CNN
F 1 "TLV1117-33" H 5450 1351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 5450 1200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlv1117.pdf" H 5450 1200 50  0001 C CNN
	1    5450 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5F5D261F
P 5450 1600
F 0 "#PWR0115" H 5450 1350 50  0001 C CNN
F 1 "GND" H 5455 1427 50  0000 C CNN
F 2 "" H 5450 1600 50  0001 C CNN
F 3 "" H 5450 1600 50  0001 C CNN
	1    5450 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6850 3950 7200
$Comp
L power:GND #PWR0111
U 1 1 61672B6E
P 4400 7200
F 0 "#PWR0111" H 4400 6950 50  0001 C CNN
F 1 "GND" H 4405 7027 50  0000 C CNN
F 2 "" H 4400 7200 50  0001 C CNN
F 3 "" H 4400 7200 50  0001 C CNN
	1    4400 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 7200 4400 7050
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 611D6812
P 650 1650
F 0 "J1" H 758 1931 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 1840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 1650 50  0001 C CNN
F 3 "~" H 650 1650 50  0001 C CNN
	1    650  1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 611D6818
P 1000 1800
F 0 "#PWR04" H 1000 1550 50  0001 C CNN
F 1 "GND" H 1005 1627 50  0000 C CNN
F 2 "" H 1000 1800 50  0001 C CNN
F 3 "" H 1000 1800 50  0001 C CNN
	1    1000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1800 1000 1750
Wire Wire Line
	1000 1750 850  1750
Wire Wire Line
	850  1550 1150 1550
Wire Wire Line
	1150 1550 1150 1400
Text Label 1150 1400 0    50   ~ 0
SYS_5V
NoConn ~ 9300 1300
NoConn ~ 9300 950 
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 61317BD2
P 9300 1200
F 0 "H4" H 9400 1249 50  0000 L CNN
F 1 "MountingHole_Pad" H 9400 1158 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 9300 1200 50  0001 C CNN
F 3 "~" H 9300 1200 50  0001 C CNN
	1    9300 1200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 61317BD8
P 9300 850
F 0 "H3" H 9400 899 50  0000 L CNN
F 1 "MountingHole_Pad" H 9400 808 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 9300 850 50  0001 C CNN
F 3 "~" H 9300 850 50  0001 C CNN
	1    9300 850 
	1    0    0    -1  
$EndComp
NoConn ~ -5850 -1500
NoConn ~ 2000 -1400
Text Label 5600 6750 0    50   ~ 0
ST_SCL
Text Label 5600 6650 0    50   ~ 0
ST_SDA
Wire Wire Line
	6550 2400 6550 2300
Wire Wire Line
	6550 2300 6450 2300
Wire Wire Line
	6250 2300 6250 2400
Wire Wire Line
	6450 2400 6450 2300
Connection ~ 6450 2300
Wire Wire Line
	6450 2300 6350 2300
Wire Wire Line
	6350 2400 6350 2300
Connection ~ 6350 2300
Wire Wire Line
	6350 2300 6250 2300
Wire Wire Line
	6250 5600 6250 5650
Wire Wire Line
	6250 5650 6350 5650
Wire Wire Line
	6450 5650 6450 5600
Wire Wire Line
	6350 5600 6350 5650
Connection ~ 6350 5650
Wire Wire Line
	6350 5650 6450 5650
$Comp
L power:GND #PWR0102
U 1 1 614E8E9D
P 6750 5750
F 0 "#PWR0102" H 6750 5500 50  0001 C CNN
F 1 "GND" H 6755 5577 50  0000 C CNN
F 2 "" H 6750 5750 50  0001 C CNN
F 3 "" H 6750 5750 50  0001 C CNN
	1    6750 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5650 6750 5650
Wire Wire Line
	6750 5650 6750 5750
Connection ~ 6450 5650
Wire Wire Line
	7050 1500 6950 1500
$Comp
L power:GND #PWR0105
U 1 1 6157F72D
P 7050 1700
F 0 "#PWR0105" H 7050 1450 50  0001 C CNN
F 1 "GND" H 7055 1527 50  0000 C CNN
F 2 "" H 7050 1700 50  0001 C CNN
F 3 "" H 7050 1700 50  0001 C CNN
	1    7050 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J23
U 1 1 6157F733
P 7300 1600
F 0 "J23" V 7408 1412 50  0000 R CNN
F 1 "Conn_01x02_Male" V 7363 1412 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7300 1600 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 7300 1600 50  0001 C CNN
	1    7300 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 1600 7050 1600
Wire Wire Line
	7050 1600 7050 1700
Wire Wire Line
	7100 1500 7050 1500
Connection ~ 7050 1500
Text Label 5650 2600 2    50   ~ 0
NRST
Wire Wire Line
	5750 2600 5650 2600
Wire Wire Line
	6550 2300 7000 2300
Connection ~ 6550 2300
Connection ~ 7000 2300
Wire Wire Line
	9450 4600 9450 4800
Text Label 9450 4600 0    50   ~ 0
SYS_5V
Text Label 9850 5300 0    50   ~ 0
LED_STRIP_OUT_2
Wire Wire Line
	9750 5300 9850 5300
Wire Wire Line
	9250 4800 9250 4700
$Comp
L Device:R R15
U 1 1 6167758F
P 4950 2550
F 0 "R15" H 5020 2596 50  0000 L CNN
F 1 "10k" H 5020 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4880 2550 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 4950 2550 50  0001 C CNN
	1    4950 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3300 4950 3400
$Comp
L Device:R R17
U 1 1 61677598
P 4950 3150
F 0 "R17" H 5020 3196 50  0000 L CNN
F 1 "DNI" H 5020 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4880 3150 50  0001 C CNN
F 3 "~" H 4950 3150 50  0001 C CNN
	1    4950 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 616E975B
P 4950 3400
F 0 "#PWR0106" H 4950 3150 50  0001 C CNN
F 1 "GND" H 4955 3227 50  0000 C CNN
F 2 "" H 4950 3400 50  0001 C CNN
F 3 "" H 4950 3400 50  0001 C CNN
	1    4950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2300 4950 2400
$Comp
L power:VCC #PWR0107
U 1 1 61703F14
P 4950 2300
F 0 "#PWR0107" H 4950 2150 50  0001 C CNN
F 1 "VCC" H 4965 2473 50  0000 C CNN
F 2 "" H 4950 2300 50  0001 C CNN
F 3 "" H 4950 2300 50  0001 C CNN
	1    4950 2300
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0109
U 1 1 6172A215
P 7050 900
F 0 "#PWR0109" H 7050 750 50  0001 C CNN
F 1 "VCC" H 7065 1073 50  0000 C CNN
F 2 "" H 7050 900 50  0001 C CNN
F 3 "" H 7050 900 50  0001 C CNN
	1    7050 900 
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0114
U 1 1 617369F3
P 7950 2200
F 0 "#PWR0114" H 7950 2050 50  0001 C CNN
F 1 "VCC" H 7965 2373 50  0000 C CNN
F 2 "" H 7950 2200 50  0001 C CNN
F 3 "" H 7950 2200 50  0001 C CNN
	1    7950 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2300 7950 2200
Text Label 7100 4700 0    50   ~ 0
ST_TIM1_CH1
Wire Wire Line
	6950 4700 7100 4700
Text Label 5600 4300 2    50   ~ 0
ST_TIM3_CH1
Wire Wire Line
	5750 4300 5600 4300
Text Label 5600 4500 2    50   ~ 0
ST_SCL
Text Label 5600 4600 2    50   ~ 0
ST_SDA
Wire Wire Line
	5750 4500 5600 4500
Wire Wire Line
	5600 4600 5750 4600
Text Label 5600 4700 2    50   ~ 0
ST_TIM16_CH1
Wire Wire Line
	5600 4700 5750 4700
Text Label 5600 4800 2    50   ~ 0
ST_TIM17_CH1
Wire Wire Line
	5600 4800 5750 4800
Text Label 7100 5200 0    50   ~ 0
ST_SWDIO
Text Label 7100 5300 0    50   ~ 0
ST_SWCLK
Text Label 7100 4800 0    50   ~ 0
ST_TIM1_CH2
Wire Wire Line
	6950 4800 7100 4800
Text Label 7100 4900 0    50   ~ 0
ST_TIM1_CH3
Wire Wire Line
	6950 4900 7100 4900
Text Label 7100 5000 0    50   ~ 0
ST_TIM1_CH4
Wire Wire Line
	6950 5000 7100 5000
$Comp
L Device:R R18
U 1 1 61B19F2E
P 5000 6400
F 0 "R18" H 5070 6446 50  0000 L CNN
F 1 "10k" H 5070 6355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4930 6400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 5000 6400 50  0001 C CNN
	1    5000 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6150 5000 6250
$Comp
L power:VCC #PWR0116
U 1 1 61B19F35
P 5000 6150
F 0 "#PWR0116" H 5000 6000 50  0001 C CNN
F 1 "VCC" H 5015 6323 50  0000 C CNN
F 2 "" H 5000 6150 50  0001 C CNN
F 3 "" H 5000 6150 50  0001 C CNN
	1    5000 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 6750 5250 6750
Wire Wire Line
	5000 6650 5000 6550
$Comp
L Device:R R19
U 1 1 61B67666
P 5250 6400
F 0 "R19" H 5320 6446 50  0000 L CNN
F 1 "10k" H 5320 6355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5180 6400 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 5250 6400 50  0001 C CNN
	1    5250 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 6150 5250 6250
$Comp
L power:VCC #PWR0117
U 1 1 61B6766D
P 5250 6150
F 0 "#PWR0117" H 5250 6000 50  0001 C CNN
F 1 "VCC" H 5265 6323 50  0000 C CNN
F 2 "" H 5250 6150 50  0001 C CNN
F 3 "" H 5250 6150 50  0001 C CNN
	1    5250 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 6750 5250 6550
Connection ~ 5250 6750
Wire Wire Line
	5250 6750 5600 6750
Connection ~ 5000 6650
Wire Wire Line
	5000 6650 5600 6650
Wire Wire Line
	4800 6650 5000 6650
$Comp
L power:GND #PWR0118
U 1 1 61C1E38B
P 7800 4300
F 0 "#PWR0118" H 7800 4050 50  0001 C CNN
F 1 "GND" H 7805 4127 50  0000 C CNN
F 2 "" H 7800 4300 50  0001 C CNN
F 3 "" H 7800 4300 50  0001 C CNN
	1    7800 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J24
U 1 1 61C1E391
P 8100 3900
F 0 "J24" V 8208 3712 50  0000 R CNN
F 1 "Conn_01x02_Male" V 8163 3712 50  0001 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8100 3900 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/wurth-electronics-inc/61300211121/732-5315-ND/4846823" H 8100 3900 50  0001 C CNN
	1    8100 3900
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0121
U 1 1 61C1E39B
P 7800 3750
F 0 "#PWR0121" H 7800 3600 50  0001 C CNN
F 1 "VCC" H 7815 3923 50  0000 C CNN
F 2 "" H 7800 3750 50  0001 C CNN
F 3 "" H 7800 3750 50  0001 C CNN
	1    7800 3750
	1    0    0    -1  
$EndComp
Text Label 9050 2050 2    50   ~ 0
ST_TIM1_CH2
$Comp
L Device:R R24
U 1 1 61DE48E0
P 9250 2050
F 0 "R24" H 9320 2096 50  0000 L CNN
F 1 "DNI" H 9320 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 2050 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 2050 50  0001 C CNN
	1    9250 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 2050 9050 2050
Wire Wire Line
	9400 2050 9500 2050
Wire Wire Line
	1500 5950 1500 6250
Wire Wire Line
	6950 5200 7100 5200
Wire Wire Line
	7100 5300 6950 5300
Text Label 6400 7550 0    50   ~ 0
ST_SWDIO
Text Label 6400 7650 0    50   ~ 0
ST_SWCLK
Wire Wire Line
	6050 7200 6050 7150
$Comp
L Device:R R21
U 1 1 6202E264
P 6050 7350
F 0 "R21" H 6120 7396 50  0000 L CNN
F 1 "10k" H 6120 7305 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5980 7350 50  0001 C CNN
F 3 "~" H 6050 7350 50  0001 C CNN
	1    6050 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 7550 6050 7500
Wire Wire Line
	6050 7550 6400 7550
Wire Wire Line
	5750 7200 5750 7150
$Comp
L Device:R R20
U 1 1 6205D9FA
P 5750 7350
F 0 "R20" H 5820 7396 50  0000 L CNN
F 1 "10k" H 5820 7305 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5680 7350 50  0001 C CNN
F 3 "~" H 5750 7350 50  0001 C CNN
	1    5750 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 7650 5750 7500
Wire Wire Line
	5750 7650 6400 7650
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 62165863
P 600 2300
F 0 "J3" H 708 2581 50  0000 C CNN
F 1 "Conn_01x03_Male" H 708 2490 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 600 2300 50  0001 C CNN
F 3 "~" H 600 2300 50  0001 C CNN
	1    600  2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 62165869
P 950 2450
F 0 "#PWR0124" H 950 2200 50  0001 C CNN
F 1 "GND" H 955 2277 50  0000 C CNN
F 2 "" H 950 2450 50  0001 C CNN
F 3 "" H 950 2450 50  0001 C CNN
	1    950  2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2450 950  2400
Wire Wire Line
	950  2400 800  2400
Wire Wire Line
	800  2200 1100 2200
Wire Wire Line
	1100 2200 1100 2050
Text Label 1400 2300 0    50   ~ 0
LED_STRIP_OUT_2
Text Label 1100 2050 0    50   ~ 0
SYS_5V
$Comp
L Device:R R2
U 1 1 6218E480
P 1200 2300
F 0 "R2" H 1270 2346 50  0000 L CNN
F 1 "DNI" H 1270 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1130 2300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1200 2300 50  0001 C CNN
	1    1200 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	800  2300 850  2300
Wire Wire Line
	1350 2300 1400 2300
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 622047D5
P 650 2950
F 0 "J4" H 758 3231 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 3140 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 2950 50  0001 C CNN
F 3 "~" H 650 2950 50  0001 C CNN
	1    650  2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 622047DB
P 1000 3100
F 0 "#PWR0125" H 1000 2850 50  0001 C CNN
F 1 "GND" H 1005 2927 50  0000 C CNN
F 2 "" H 1000 3100 50  0001 C CNN
F 3 "" H 1000 3100 50  0001 C CNN
	1    1000 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3100 1000 3050
Wire Wire Line
	1000 3050 850  3050
Wire Wire Line
	850  2850 1150 2850
Wire Wire Line
	1150 2850 1150 2700
Text Label 1150 2700 0    50   ~ 0
SYS_5V
Text Label 1500 2950 0    50   ~ 0
LED_STRIP_OUT_3
$Comp
L Device:R R9
U 1 1 62213319
P 1300 2950
F 0 "R9" H 1370 2996 50  0000 L CNN
F 1 "DNI" H 1370 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1230 2950 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1300 2950 50  0001 C CNN
	1    1300 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 2950 1500 2950
Wire Wire Line
	850  2950 1100 2950
Text Label 1450 1650 0    50   ~ 0
LED_STRIP_OUT_1
$Comp
L Device:R R3
U 1 1 6223DFA9
P 1250 1650
F 0 "R3" H 1320 1696 50  0000 L CNN
F 1 "DNI" H 1320 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1180 1650 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1250 1650 50  0001 C CNN
	1    1250 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 1650 1450 1650
Wire Wire Line
	850  1650 950  1650
$Comp
L Connector:Conn_01x01_Male J14
U 1 1 623A153D
P 1350 2500
F 0 "J14" H 1322 2432 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1322 2523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1350 2500 50  0001 C CNN
F 3 "~" H 1350 2500 50  0001 C CNN
	1    1350 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 2500 1050 2500
Wire Wire Line
	1050 2500 1050 2350
Wire Wire Line
	1050 2350 850  2350
Wire Wire Line
	850  2350 850  2300
Connection ~ 850  2300
Wire Wire Line
	850  2300 1050 2300
$Comp
L Connector:Conn_01x01_Male J13
U 1 1 623B2D9F
P 1300 1850
F 0 "J13" H 1272 1782 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1272 1873 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1300 1850 50  0001 C CNN
F 3 "~" H 1300 1850 50  0001 C CNN
	1    1300 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1100 1850 1100 1700
Wire Wire Line
	1100 1700 950  1700
Wire Wire Line
	950  1700 950  1650
Connection ~ 950  1650
Wire Wire Line
	950  1650 1100 1650
$Comp
L Connector:Conn_01x01_Male J15
U 1 1 623D0BFD
P 1350 3150
F 0 "J15" H 1322 3082 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1322 3173 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1350 3150 50  0001 C CNN
F 3 "~" H 1350 3150 50  0001 C CNN
	1    1350 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 3150 1100 3150
Wire Wire Line
	1100 3150 1100 2950
Connection ~ 1100 2950
Wire Wire Line
	1100 2950 1150 2950
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 624193A8
P 650 3600
F 0 "J7" H 758 3881 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 3790 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 3600 50  0001 C CNN
F 3 "~" H 650 3600 50  0001 C CNN
	1    650  3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 624193AE
P 1000 3750
F 0 "#PWR0127" H 1000 3500 50  0001 C CNN
F 1 "GND" H 1005 3577 50  0000 C CNN
F 2 "" H 1000 3750 50  0001 C CNN
F 3 "" H 1000 3750 50  0001 C CNN
	1    1000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3750 1000 3700
Wire Wire Line
	1000 3700 850  3700
Wire Wire Line
	850  3500 1150 3500
Wire Wire Line
	1150 3500 1150 3350
Text Label 1450 3600 0    50   ~ 0
LED_STRIP_OUT_4
Text Label 1150 3350 0    50   ~ 0
SYS_5V
$Comp
L Device:R R6
U 1 1 624193BA
P 1250 3600
F 0 "R6" H 1320 3646 50  0000 L CNN
F 1 "DNI" H 1320 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1180 3600 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1250 3600 50  0001 C CNN
	1    1250 3600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	850  3600 900  3600
Wire Wire Line
	1400 3600 1450 3600
$Comp
L Connector:Conn_01x01_Male J18
U 1 1 624193C2
P 1400 3800
F 0 "J18" H 1372 3732 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1372 3823 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1400 3800 50  0001 C CNN
F 3 "~" H 1400 3800 50  0001 C CNN
	1    1400 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 3800 1100 3800
Wire Wire Line
	1100 3800 1100 3650
Wire Wire Line
	1100 3650 900  3650
Wire Wire Line
	900  3650 900  3600
Connection ~ 900  3600
Wire Wire Line
	900  3600 1100 3600
$Comp
L Connector:Conn_01x03_Male J10
U 1 1 6242C6EA
P 650 4200
F 0 "J10" H 758 4481 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 4390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 4200 50  0001 C CNN
F 3 "~" H 650 4200 50  0001 C CNN
	1    650  4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 6242C6F0
P 1000 4350
F 0 "#PWR0128" H 1000 4100 50  0001 C CNN
F 1 "GND" H 1005 4177 50  0000 C CNN
F 2 "" H 1000 4350 50  0001 C CNN
F 3 "" H 1000 4350 50  0001 C CNN
	1    1000 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4350 1000 4300
Wire Wire Line
	1000 4300 850  4300
Wire Wire Line
	850  4100 1150 4100
Wire Wire Line
	1150 4100 1150 3950
Text Label 1150 3950 0    50   ~ 0
SYS_5V
Text Label 1500 4200 0    50   ~ 0
LED_STRIP_OUT_5
$Comp
L Device:R R10
U 1 1 6242C6FC
P 1300 4200
F 0 "R10" H 1370 4246 50  0000 L CNN
F 1 "DNI" H 1370 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1230 4200 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1300 4200 50  0001 C CNN
	1    1300 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 4200 1500 4200
Wire Wire Line
	850  4200 1100 4200
$Comp
L Connector:Conn_01x01_Male J16
U 1 1 6242C704
P 1350 4400
F 0 "J16" H 1322 4332 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1322 4423 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1350 4400 50  0001 C CNN
F 3 "~" H 1350 4400 50  0001 C CNN
	1    1350 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 4400 1100 4400
Wire Wire Line
	1100 4400 1100 4200
Connection ~ 1100 4200
Wire Wire Line
	1100 4200 1150 4200
$Comp
L Connector:Conn_01x03_Male J11
U 1 1 62485946
P 650 4850
F 0 "J11" H 758 5131 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 5040 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 4850 50  0001 C CNN
F 3 "~" H 650 4850 50  0001 C CNN
	1    650  4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 6248594C
P 1000 5000
F 0 "#PWR0129" H 1000 4750 50  0001 C CNN
F 1 "GND" H 1005 4827 50  0000 C CNN
F 2 "" H 1000 5000 50  0001 C CNN
F 3 "" H 1000 5000 50  0001 C CNN
	1    1000 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 5000 1000 4950
Wire Wire Line
	1000 4950 850  4950
Wire Wire Line
	850  4750 1150 4750
Wire Wire Line
	1150 4750 1150 4600
Text Label 1450 4850 0    50   ~ 0
LED_STRIP_OUT_6
Text Label 1150 4600 0    50   ~ 0
SYS_5V
$Comp
L Device:R R7
U 1 1 62485958
P 1250 4850
F 0 "R7" H 1320 4896 50  0000 L CNN
F 1 "DNI" H 1320 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1180 4850 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1250 4850 50  0001 C CNN
	1    1250 4850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	850  4850 900  4850
Wire Wire Line
	1400 4850 1450 4850
$Comp
L Connector:Conn_01x01_Male J19
U 1 1 62485960
P 1400 5050
F 0 "J19" H 1372 4982 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1372 5073 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1400 5050 50  0001 C CNN
F 3 "~" H 1400 5050 50  0001 C CNN
	1    1400 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 5050 1100 5050
Wire Wire Line
	1100 5050 1100 4900
Wire Wire Line
	1100 4900 900  4900
Wire Wire Line
	900  4900 900  4850
Connection ~ 900  4850
Wire Wire Line
	900  4850 1100 4850
$Comp
L Connector:Conn_01x03_Male J12
U 1 1 6248596C
P 650 5500
F 0 "J12" H 758 5781 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 5690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 5500 50  0001 C CNN
F 3 "~" H 650 5500 50  0001 C CNN
	1    650  5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 62485972
P 1000 5650
F 0 "#PWR0130" H 1000 5400 50  0001 C CNN
F 1 "GND" H 1005 5477 50  0000 C CNN
F 2 "" H 1000 5650 50  0001 C CNN
F 3 "" H 1000 5650 50  0001 C CNN
	1    1000 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 5650 1000 5600
Wire Wire Line
	1000 5600 850  5600
Wire Wire Line
	850  5400 1150 5400
Wire Wire Line
	1150 5400 1150 5250
Text Label 1150 5250 0    50   ~ 0
SYS_5V
Text Label 1500 5500 0    50   ~ 0
LED_STRIP_OUT_7
$Comp
L Device:R R11
U 1 1 6248597E
P 1300 5500
F 0 "R11" H 1370 5546 50  0000 L CNN
F 1 "DNI" H 1370 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1230 5500 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 1300 5500 50  0001 C CNN
	1    1300 5500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 5500 1500 5500
Wire Wire Line
	850  5500 1100 5500
$Comp
L Connector:Conn_01x01_Male J17
U 1 1 62485986
P 1350 5700
F 0 "J17" H 1322 5632 50  0000 R CNN
F 1 "Conn_01x01_Male" H 1322 5723 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1350 5700 50  0001 C CNN
F 3 "~" H 1350 5700 50  0001 C CNN
	1    1350 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 5700 1100 5700
Wire Wire Line
	1100 5700 1100 5500
Connection ~ 1100 5500
Wire Wire Line
	1100 5500 1150 5500
$Comp
L Logic_LevelTranslator:TXS0108EPW U3
U 1 1 624CCBC9
P 9350 5500
F 0 "U3" H 9350 4711 50  0000 C CNN
F 1 "TXS0108EPW" H 9350 4620 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 9350 4750 50  0001 C CNN
F 3 "www.ti.com/lit/ds/symlink/txs0108e.pdf" H 9350 5400 50  0001 C CNN
	1    9350 5500
	1    0    0    -1  
$EndComp
Text Label 9050 2300 2    50   ~ 0
ST_TIM3_CH1
Wire Wire Line
	9100 2300 9050 2300
Wire Wire Line
	9500 2050 9500 2200
Text Label 9600 2200 0    50   ~ 0
ST_LED_OUT_1
Wire Wire Line
	9600 2200 9500 2200
Connection ~ 9500 2200
Wire Wire Line
	9500 2200 9500 2300
Text Label 9050 2550 2    50   ~ 0
ST_TIM1_CH3
$Comp
L Device:R R26
U 1 1 6261F7D5
P 9250 2550
F 0 "R26" H 9320 2596 50  0000 L CNN
F 1 "DNI" H 9320 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 2550 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 2550 50  0001 C CNN
	1    9250 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 2550 9050 2550
Wire Wire Line
	9400 2550 9500 2550
Text Label 9050 2800 2    50   ~ 0
ST_TIM16_CH1
$Comp
L Device:R R27
U 1 1 6261F7DE
P 9250 2800
F 0 "R27" H 9320 2846 50  0000 L CNN
F 1 "0" H 9320 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 2800 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 2800 50  0001 C CNN
	1    9250 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 2800 9050 2800
Wire Wire Line
	9400 2800 9500 2800
Wire Wire Line
	9500 2550 9500 2700
Text Label 9600 2700 0    50   ~ 0
ST_LED_OUT_2
Wire Wire Line
	9600 2700 9500 2700
Connection ~ 9500 2700
Wire Wire Line
	9500 2700 9500 2800
Text Label 9050 3050 2    50   ~ 0
ST_TIM1_CH4
$Comp
L Device:R R28
U 1 1 62741400
P 9250 3050
F 0 "R28" H 9320 3096 50  0000 L CNN
F 1 "DNI" H 9320 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 3050 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 3050 50  0001 C CNN
	1    9250 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 3050 9050 3050
Wire Wire Line
	9400 3050 9500 3050
Text Label 9050 3300 2    50   ~ 0
ST_TIM17_CH1
$Comp
L Device:R R29
U 1 1 62741409
P 9250 3300
F 0 "R29" H 9320 3346 50  0000 L CNN
F 1 "0" H 9320 3255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 3300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 3300 50  0001 C CNN
	1    9250 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 3300 9050 3300
Wire Wire Line
	9400 3300 9500 3300
Wire Wire Line
	9500 3050 9500 3200
Text Label 9600 3200 0    50   ~ 0
ST_LED_OUT_3
Wire Wire Line
	9600 3200 9500 3200
Connection ~ 9500 3200
Wire Wire Line
	9500 3200 9500 3300
Text Label 7100 4100 0    50   ~ 0
ST_TIM15_CH1
Wire Wire Line
	6950 4100 7100 4100
Text Label 9050 3550 2    50   ~ 0
ST_TIM15_CH1
$Comp
L Device:R R30
U 1 1 6277232B
P 9250 3550
F 0 "R30" H 9320 3596 50  0000 L CNN
F 1 "0" H 9320 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 3550 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 3550 50  0001 C CNN
	1    9250 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 3550 9050 3550
Text Label 9600 3550 0    50   ~ 0
ST_LED_OUT_4
Wire Wire Line
	8950 5100 8800 5100
Text Label 9050 1800 2    50   ~ 0
ST_TIM1_CH1
Wire Wire Line
	8950 5200 8800 5200
Text Label 9850 5200 0    50   ~ 0
LED_STRIP_OUT_3
Wire Wire Line
	9750 5200 9850 5200
Wire Wire Line
	9750 5400 9850 5400
Text Label 9850 5400 0    50   ~ 0
LED_STRIP_OUT_1
Wire Wire Line
	9750 5500 9850 5500
Text Label 9850 5500 0    50   ~ 0
LED_STRIP_OUT_0
Text Label 8800 5300 2    50   ~ 0
ST_LED_OUT_2
Text Label 8800 5400 2    50   ~ 0
ST_LED_OUT_1
Text Label 8800 5500 2    50   ~ 0
ST_LED_OUT_0
Text Label 8800 5600 2    50   ~ 0
ST_LED_OUT_5
Wire Wire Line
	8800 5300 8950 5300
Wire Wire Line
	8950 5400 8800 5400
Wire Wire Line
	8800 5500 8950 5500
Wire Wire Line
	8950 5600 8800 5600
$Comp
L power:GND #PWR0131
U 1 1 62AAA6D9
P 8950 6300
F 0 "#PWR0131" H 8950 6050 50  0001 C CNN
F 1 "GND" H 8955 6127 50  0000 C CNN
F 2 "" H 8950 6300 50  0001 C CNN
F 3 "" H 8950 6300 50  0001 C CNN
	1    8950 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 6300 8950 6250
Wire Wire Line
	8950 6250 9350 6250
Wire Wire Line
	9350 6250 9350 6200
Text Label 9050 3800 2    50   ~ 0
ST_TIM15_CH2
$Comp
L Device:R R31
U 1 1 62B0A445
P 9250 3800
F 0 "R31" H 9320 3846 50  0000 L CNN
F 1 "0" H 9320 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 3800 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 3800 50  0001 C CNN
	1    9250 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 3800 9050 3800
Text Label 9600 3800 0    50   ~ 0
ST_LED_OUT_5
Wire Wire Line
	9400 3800 9600 3800
Text Label 8800 5700 2    50   ~ 0
ST_LED_OUT_4
Wire Wire Line
	8950 5700 8800 5700
Text Label 9050 4050 2    50   ~ 0
ST_TIM3_CH2
$Comp
L Device:R R32
U 1 1 62BF98F8
P 9250 4050
F 0 "R32" H 9320 4096 50  0000 L CNN
F 1 "0" H 9320 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 4050 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 4050 50  0001 C CNN
	1    9250 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 4050 9050 4050
Text Label 9600 4050 0    50   ~ 0
ST_LED_OUT_6
Wire Wire Line
	9400 4050 9600 4050
Text Label 9050 4300 2    50   ~ 0
ST_TIM3_CH3
$Comp
L Device:R R33
U 1 1 62C29999
P 9250 4300
F 0 "R33" H 9320 4346 50  0000 L CNN
F 1 "0" H 9320 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 4300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 4300 50  0001 C CNN
	1    9250 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 4300 9050 4300
Text Label 9600 4300 0    50   ~ 0
ST_LED_OUT_7
Wire Wire Line
	9400 4300 9600 4300
Text Label 8800 5800 2    50   ~ 0
ST_LED_OUT_6
Wire Wire Line
	8950 5800 8800 5800
Text Label 8800 5900 2    50   ~ 0
ST_LED_OUT_7
Wire Wire Line
	8950 5900 8800 5900
Text Label 9850 5700 0    50   ~ 0
LED_STRIP_OUT_4
Wire Wire Line
	9750 5700 9850 5700
Text Label 9850 5600 0    50   ~ 0
LED_STRIP_OUT_5
Wire Wire Line
	9750 5600 9850 5600
Text Label 9850 5900 0    50   ~ 0
LED_STRIP_OUT_7
Wire Wire Line
	9750 5900 9850 5900
Text Label 9850 5800 0    50   ~ 0
LED_STRIP_OUT_6
Wire Wire Line
	9750 5800 9850 5800
Wire Wire Line
	9400 2300 9500 2300
$Comp
L Device:R R25
U 1 1 625ACB5A
P 9250 2300
F 0 "R25" H 9320 2346 50  0000 L CNN
F 1 "0" H 9320 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 2300 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 2300 50  0001 C CNN
	1    9250 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R23
U 1 1 62D854A5
P 9250 1800
F 0 "R23" H 9320 1846 50  0000 L CNN
F 1 "0" H 9320 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9180 1800 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 9250 1800 50  0001 C CNN
	1    9250 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 1800 9050 1800
Text Label 9550 1800 0    50   ~ 0
ST_LED_OUT_0
Wire Wire Line
	9400 1800 9550 1800
Text Label 1150 650  0    50   ~ 0
SYS_5V
Wire Wire Line
	900  900  850  900 
Text Label 900  900  0    50   ~ 0
LED_STRIP_OUT_0
Wire Wire Line
	1150 800  1150 650 
Wire Wire Line
	850  800  1150 800 
Wire Wire Line
	1000 1000 850  1000
Wire Wire Line
	1000 1050 1000 1000
$Comp
L power:GND #PWR0137
U 1 1 601EBEC4
P 1000 1050
F 0 "#PWR0137" H 1000 800 50  0001 C CNN
F 1 "GND" H 1005 877 50  0000 C CNN
F 2 "" H 1000 1050 50  0001 C CNN
F 3 "" H 1000 1050 50  0001 C CNN
	1    1000 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 601EA58A
P 650 900
F 0 "J8" H 758 1181 50  0000 C CNN
F 1 "Conn_01x03_Male" H 758 1090 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 650 900 50  0001 C CNN
F 3 "~" H 650 900 50  0001 C CNN
	1    650  900 
	1    0    0    -1  
$EndComp
Text Label 5600 4400 2    50   ~ 0
ST_TIM3_CH2
Wire Wire Line
	5750 4400 5600 4400
Wire Wire Line
	9400 3550 9600 3550
Wire Wire Line
	4950 2700 4950 2800
Connection ~ 4950 2800
Wire Wire Line
	4950 2800 4950 3000
NoConn ~ 6950 4000
NoConn ~ 6950 4200
NoConn ~ 6950 4300
NoConn ~ 6950 4400
NoConn ~ 6950 4500
NoConn ~ 6950 4600
NoConn ~ 6950 5100
NoConn ~ 6950 5400
NoConn ~ 5750 5300
NoConn ~ 5750 5200
NoConn ~ 5750 5100
NoConn ~ 5750 4200
NoConn ~ 5750 4100
NoConn ~ 5750 3500
NoConn ~ 5750 3300
$Comp
L MCU_ST_STM32F0:STM32F030C8Tx U2
U 1 1 614ABAAF
P 6350 4000
F 0 "U2" H 6350 2311 50  0000 C CNN
F 1 "STM32F030C8Tx" H 6350 2220 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 5850 2500 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 6350 4000 50  0001 C CNN
	1    6350 4000
	1    0    0    -1  
$EndComp
NoConn ~ 5750 3200
$Comp
L Device:C C11
U 1 1 61FEC410
P 8100 4750
F 0 "C11" H 8215 4796 50  0000 L CNN
F 1 "1u" H 8215 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8138 4600 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 8100 4750 50  0001 C CNN
	1    8100 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 6205B0BD
P 8100 4950
F 0 "#PWR0133" H 8100 4700 50  0001 C CNN
F 1 "GND" H 8105 4777 50  0000 C CNN
F 2 "" H 8100 4950 50  0001 C CNN
F 3 "" H 8100 4950 50  0001 C CNN
	1    8100 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4950 8100 4900
Text Label 10800 4550 0    50   ~ 0
SYS_5V
$Comp
L Device:C C12
U 1 1 620EFDB0
P 10800 4800
F 0 "C12" H 10915 4846 50  0000 L CNN
F 1 "1u" H 10915 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10838 4650 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/kemet/C0603C105K8PACTU/399-3118-1-ND/551623" H 10800 4800 50  0001 C CNN
	1    10800 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0134
U 1 1 620EFDB6
P 10800 5000
F 0 "#PWR0134" H 10800 4750 50  0001 C CNN
F 1 "GND" H 10805 4827 50  0000 C CNN
F 2 "" H 10800 5000 50  0001 C CNN
F 3 "" H 10800 5000 50  0001 C CNN
	1    10800 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 5000 10800 4950
Wire Wire Line
	10800 4650 10800 4550
Text Label 3250 3700 0    50   ~ 0
VIN
$Comp
L power:GND #PWR010
U 1 1 615E87EB
P 3150 4300
F 0 "#PWR010" H 3150 4050 50  0001 C CNN
F 1 "GND" H 3155 4127 50  0000 C CNN
F 2 "" H 3150 4300 50  0001 C CNN
F 3 "" H 3150 4300 50  0001 C CNN
	1    3150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4250 3150 4300
Wire Wire Line
	2950 4250 3150 4250
Wire Wire Line
	2950 4000 3250 4000
Wire Wire Line
	3250 4000 3250 3700
$Comp
L Connector:Conn_01x01_Male J9
U 1 1 61624FE5
P 2750 4250
F 0 "J9" H 2858 4431 50  0000 C CNN
F 1 "Conn_01x01_Male" H 2858 4340 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 2750 4250 50  0001 C CNN
F 3 "~" H 2750 4250 50  0001 C CNN
	1    2750 4250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J2
U 1 1 61622E73
P 2750 4000
F 0 "J2" H 2858 4181 50  0000 C CNN
F 1 "Conn_01x01_Male" H 2858 4090 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.3mm_L11.0mm" H 2750 4000 50  0001 C CNN
F 3 "~" H 2750 4000 50  0001 C CNN
	1    2750 4000
	1    0    0    -1  
$EndComp
Text Label 4950 1050 2    50   ~ 0
SYS_5V
$Comp
L Device:R R12
U 1 1 6282C4CD
P 3600 950
F 0 "R12" H 3670 996 50  0000 L CNN
F 1 "DNI" H 3670 905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3530 950 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 3600 950 50  0001 C CNN
	1    3600 950 
	0    -1   -1   0   
$EndComp
Text Label 3350 800  0    50   ~ 0
VIN
Wire Wire Line
	3450 950  3350 950 
Wire Wire Line
	3350 950  3350 800 
Wire Wire Line
	3900 950  3750 950 
Text Label 3950 750  0    50   ~ 0
SYS_5V
Wire Wire Line
	3900 950  3900 750 
Wire Wire Line
	5450 1600 5950 1600
Wire Wire Line
	5950 1250 5950 1200
Connection ~ 5950 1200
Wire Wire Line
	5950 1550 5950 1600
Connection ~ 5950 1600
Wire Wire Line
	5950 1600 6200 1600
$Comp
L Device:R R22
U 1 1 611C779E
P 7800 4100
F 0 "R22" H 7870 4146 50  0000 L CNN
F 1 "10k" H 7870 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7730 4100 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERJ-3GEYJ103V/P10KGCT-ND/134717" H 7800 4100 50  0001 C CNN
	1    7800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3900 7800 3900
Wire Wire Line
	7800 4300 7800 4250
Wire Wire Line
	7800 3950 7800 3900
Connection ~ 7800 3900
Wire Wire Line
	7800 3900 7900 3900
Wire Wire Line
	7800 3750 7800 3800
Wire Wire Line
	7800 3800 7900 3800
$Comp
L Connector:Conn_01x06_Male J21
U 1 1 6136942F
P 2850 5000
F 0 "J21" H 2958 5381 50  0000 C CNN
F 1 "Conn_01x06_Male" H 2958 5290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 2850 5000 50  0001 C CNN
F 3 "~" H 2850 5000 50  0001 C CNN
	1    2850 5000
	1    0    0    -1  
$EndComp
Text Label 3300 4350 0    50   ~ 0
SYS_5V
Wire Wire Line
	3050 4800 3300 4800
Wire Wire Line
	3300 4800 3300 4350
Wire Wire Line
	3500 4650 3500 4900
$Comp
L power:GND #PWR0136
U 1 1 6149A448
P 4600 2700
F 0 "#PWR0136" H 4600 2450 50  0001 C CNN
F 1 "GND" H 4605 2527 50  0000 C CNN
F 2 "" H 4600 2700 50  0001 C CNN
F 3 "" H 4600 2700 50  0001 C CNN
	1    4600 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2600 4600 2700
Wire Wire Line
	4400 2200 4600 2200
Wire Wire Line
	4600 2200 4600 2600
Connection ~ 4600 2600
Wire Wire Line
	4950 2800 5750 2800
Wire Wire Line
	5750 3600 5600 3600
Wire Wire Line
	5750 3700 5600 3700
Text Label 5600 3600 2    50   ~ 0
XTAL1
Text Label 5600 3700 2    50   ~ 0
XTAL2
Text Label 5600 3000 2    50   ~ 0
XTAL1_HI
Text Label 5600 3100 2    50   ~ 0
XTAL2_HI
Wire Wire Line
	5600 3000 5750 3000
Wire Wire Line
	5600 3100 5750 3100
$Comp
L power:VCC #PWR0138
U 1 1 616EDD33
P 6200 1100
F 0 "#PWR0138" H 6200 950 50  0001 C CNN
F 1 "VCC" H 6215 1273 50  0000 C CNN
F 2 "" H 6200 1100 50  0001 C CNN
F 3 "" H 6200 1100 50  0001 C CNN
	1    6200 1100
	1    0    0    -1  
$EndComp
Connection ~ 6200 1200
Wire Wire Line
	5750 1200 5950 1200
$Comp
L power:VCC #PWR0126
U 1 1 617573C9
P 8100 4450
F 0 "#PWR0126" H 8100 4300 50  0001 C CNN
F 1 "VCC" H 8115 4623 50  0000 C CNN
F 2 "" H 8100 4450 50  0001 C CNN
F 3 "" H 8100 4450 50  0001 C CNN
	1    8100 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4450 8100 4600
$Comp
L power:VCC #PWR0132
U 1 1 61771A67
P 9250 4700
F 0 "#PWR0132" H 9250 4550 50  0001 C CNN
F 1 "VCC" H 9265 4873 50  0000 C CNN
F 2 "" H 9250 4700 50  0001 C CNN
F 3 "" H 9250 4700 50  0001 C CNN
	1    9250 4700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0108
U 1 1 617DA3F8
P 4100 6300
F 0 "#PWR0108" H 4100 6150 50  0001 C CNN
F 1 "VCC" H 4115 6473 50  0000 C CNN
F 2 "" H 4100 6300 50  0001 C CNN
F 3 "" H 4100 6300 50  0001 C CNN
	1    4100 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 6400 4100 6300
Wire Wire Line
	3900 6400 4100 6400
Connection ~ 4100 6400
Wire Wire Line
	4100 6400 4400 6400
$Comp
L power:VCC #PWR0119
U 1 1 618299A8
P 3500 4650
F 0 "#PWR0119" H 3500 4500 50  0001 C CNN
F 1 "VCC" H 3515 4823 50  0000 C CNN
F 2 "" H 3500 4650 50  0001 C CNN
F 3 "" H 3500 4650 50  0001 C CNN
	1    3500 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1050 4950 1050
Wire Wire Line
	3950 750  3900 750 
Text Label 5600 4000 2    50   ~ 0
LVL_SHIFTER_EN
Wire Wire Line
	5750 4000 5600 4000
$Comp
L power:VCC #PWR0122
U 1 1 6198210D
P 5750 7150
F 0 "#PWR0122" H 5750 7000 50  0001 C CNN
F 1 "VCC" H 5765 7323 50  0000 C CNN
F 2 "" H 5750 7150 50  0001 C CNN
F 3 "" H 5750 7150 50  0001 C CNN
	1    5750 7150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0123
U 1 1 61982113
P 6050 7150
F 0 "#PWR0123" H 6050 7000 50  0001 C CNN
F 1 "VCC" H 6065 7323 50  0000 C CNN
F 2 "" H 6050 7150 50  0001 C CNN
F 3 "" H 6050 7150 50  0001 C CNN
	1    6050 7150
	1    0    0    -1  
$EndComp
Text Label 5600 5400 2    50   ~ 0
ST_TIM15_CH2
Wire Wire Line
	5600 5400 5750 5400
Text Label 5600 3900 2    50   ~ 0
ST_TIM3_CH3
Wire Wire Line
	5750 3900 5600 3900
Wire Wire Line
	5000 1050 5000 1200
Wire Wire Line
	5150 1200 5000 1200
Connection ~ 5000 1200
Wire Wire Line
	5000 1200 5000 1250
Text Label 5600 4900 2    50   ~ 0
GRN_LED
Text Label 5600 5000 2    50   ~ 0
RED_LED
Wire Wire Line
	5750 4900 5600 4900
Wire Wire Line
	5600 5000 5750 5000
Text Label 8800 5200 2    50   ~ 0
ST_LED_OUT_3
$EndSCHEMATC
