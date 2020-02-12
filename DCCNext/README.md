![Nederlandse vlag](../images/nl.gif) Nederlands

[Navigate to English version](#English)

De DCCNext heeft 16 uitgangen, die op verschillende pinnen van de Arduino zijn aangesloten.

De Arduino bevat een Atmel ATMega386 met pinnen van de chip, die verbonden zijn met pinnen op het Arduino board.

![Pinnen](./images/ATmega328-Pinout.png) Bron: https://github.com/MCUdude/MiniCore

De tekening van Arcomora is niet compleet:

![Schema](./images/DCCNextSchematic.jpg) Bron: https://www.arcomora.com/arsigdec/

Hierbij de aansluitingen van de DCCNext en pinnummers zoals je die op de Arduino en op de Atmelchip ziet:

|DCCNext|Arduino pin|Atmel    |
|-------|-----------|---------|
|       | 0 RX      |PD0/RXD  |
|       | 1 TX      |PD1/TXD  |
|       | 2 DCC in  |PD2      |
|1      | 3         |PB3      |
|2      | 4         |PD4      |
|3      | 5         |PD5      |
|4      | 6         |PD6      |
|5      | 7         |PD7      |
|6      | 8         |PB0      |
|7      | 9         |PB1      |
|8      | 10        |PB2      |
|9      | 11        |PB3      |
|10     | 12        |PB4      |
|       | 13        |PB5/LED  |
|11     | 14/A0     |PC0/ADC0 |
|12     | 15/A1     |PC1/ADC1 |
|13     | 16/A2     |PC2/ADC2 |
|14     | 17/A3     |PC3/ADC3 |
|15     | 18/A4     |PC4/ADC4 |
|16     | 19/A5     |PC5/ADC5 |
|       | 20        |PB6/XTAL |
|       | 21        |PB7/XTAL |
|       | 22        |PC6/RESET|

Om de DCCNext te kunnen testen zijn op alle uitgangen 4 rode, 4 gele, 4 groene en 4 witte LED's middels een testprint met bij de LED-kleur behorende draad- en adereindhuls-kleur aangesloten. Oranje = 5V.

![Tester](./images/DCCNextTester.jpg)

![English flag](../images/gb.gif) English
