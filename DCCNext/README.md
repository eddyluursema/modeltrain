![Nederlandse vlag](../images/nl.gif) Nederlands

[Navigate to English version](#English)

## Schema DCCNext

De DCCNext heeft 16 uitgangen, die op verschillende pinnen van de Arduino zijn aangesloten.

Een normaal Arduino-board bevat een Atmel ATMega386 met pinnen van de chip, die verbonden zijn met pinnen op het board.

![Pinnen](./images/ATmega328-Pinout.png) Bron: https://github.com/MCUdude/MiniCore

De tekening van Arcomora is niet compleet:

![Schema](./images/DCCNextSchematic.jpg) Bron: https://www.arcomora.com/arsigdec/

Hierbij de aansluitingen van de DCCNext en pinnummers zoals je die op de DCCNext, de Arduino en op de Atmelchip ziet:

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

## Tester

Om de DCCNext te kunnen testen zijn op alle uitgangen 4 rode, 4 gele, 4 groene en 4 witte LED's middels een testprint met bij de LED-kleur behorende draad- en adereindhuls-kleur aangesloten. Oranje = 5V.

![Tester](./images/DCCNextTester.jpg)


## Configureren

M.b.v. de handleiding van de [ArSigDec](https://www.globalvisuals.nl/downloads/arsigdecmanualdb.pdf) van Arcomora worden voor Nederland een zogenaamd P-sein met en een P-sein zonder cijferbak geconfigureerd.

Adres 517 P-sein met cijferbak. Adressen 517 en 518 met ieder ROOD- of GROEN-commando's.
Adres 519 P-sein zonder cijferbak. Adressen 519 met ROOD- of GROEN-commando. Adres 520 alleen ROOD-commando. Onderzoeken wat 520-GROEN doet.



## DCC commando's naar aspect

Om de configuratie testen worden eerst via de DCC Command Centre (b.v. DR5000) en/of MultiMaus ROOD- en GROEN-commando's naar de ingestelde adressen gestuurd om te controleren welke commando's nodig zijn voor welk aspect.

## RocRail configuratie

De hierboven bekeken ROOD- en GROEN-commando's moeten nu door een juiste configuratie uit RocRail komen. Op de site van Arcomora wordt verwezen naar een video waarin wordt uitgelegd dat bij de DCCNext de adresseermethode 'Linear' moet worden gekozen.

Maak twee seinen in RocRail met b.v. de namen sgNext1 en sgNext2.


![English flag](../images/gb.gif) English
