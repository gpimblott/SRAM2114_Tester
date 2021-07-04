# 2114 SRAM Tester

Tester for 2114 SRAM chips using an Arduino Nano

2114 SRAM chips are used in the ZX81, they are 4096 bit chips arranged in 1024 rows of 4 bits.  This code uses a Arduino Nano to perform various tests on a 2114 chip to check that it is working.

The wiring is outlined in the table below

Port | Arduino  |  2114
-----|----------|--------
PC0  |A0        |IO1
PC1  |A1        |IO2
PC2  |A2        |IO3
PC3  |A3        |IO4
PC4  |A4        |Green LED
PC5  |A5        |Red LED
PD0  |0         |Serial (Debug) - leave empty for USB
PD1  |1         |Serial (Debug) - leave empty for USB
PD2  |2         |/CS (Chip Select)
PD3  |3         |/WE (Write Enabled)
PD4  |4         |A0
PD5  |5         |A1
PD6  |6         |A2
PD7  |7         |A3
PB0  |8         |A4
PB1  |9         |A5
PB2  |10        |A6
PB3  |11        |A7
PB4  |12        |A8
PB5  |13        |A9


I also intend to provide gerber files to create boards for a more professional projects.
