# Loconet

## Loconet via USB

Via https://download.cnet.com/Ultra-Serial-Port-Monitor/3000-2094_4-10969502.html een gratis sniffer gevonden om het Loconet-verkeer tussen laptop en DCC station te bestuderen. Vervolgens de GUI van het DCC station gebruikt om verkeer te genereren door loc's, seinen, wissels te bedienen en loc's over melders te laten rijden.

#### Loc-bediening

De besturing van loc's staat niet duidelijk in de  [Personal Edition van Loconet](https://www.digitrax.com/static/apps/cms/media/documents/loconet/loconetpersonaledition.pdf) van Digitrax. Zodra in de interface van het DCC station een loc-adres wordt gekozen, zien we een soort aanmelding. E0 06 62 is de aanmeldboodschap; de twee daarop volgende bytes het loc-adres waarbij van het tweede adresbyte het msb niet wordt meegenomen.

|Loc |Actie       | Bericht         |
|----|------------|-----------------|
|5   |Aanmelden   |E0 06 62 00 05 7E|
|6   |Aanmelden   |E0 06 62 00 06 7D|
|7   |Aanmelden   |E0 06 62 00 07 7C|
...
|127 |Aanmelden   |E0 06 62 00 7F 04|
|128 |Aanmelden   |E0 06 62 01 00 7A|
...
|4096|Aanmelden   |E0 06 62 20 00 5B|

Volgens de Personal Edition van Loconet van Digitrax is het laatste byte de checksum zijnde de EXOR van alle bits in het bericht behalve de checksum zelf (pag. 6): **The CHECKSUM is the 1's COMPLEMENT of the byte wise Exclusive Or of all the
bytes in the message, except the CHECKSUM itself.**

Na het aanmelden krijgen loc's een soort volgnummer in de volgorde waarin ze een snelheid krijgen toegewezen (3 was de eerste loc op de baan). Onduidelijk is hoe het volgnummer gekoppeld is aan de aanmelding.

|Loc|Actie       | Bericht    |
|---|------------|------------|
|1  |Speed 2     |A0 05 02 58 |
|2  |Speed 2     |A0 04 02 59 |
|3  |Speed 2     |A0 01 02 5C |
|4  |Speed 2     |A0 03 02 5E |
...
|3  |Speed 0     |A0 01 00 5E |
|3  |Speed 2     |A0 01 02 5C |
|3  |Speed 3     |A0 01 03 5D |
|3  |Speed 127   |A0 01 7F 21 |
|3  |Vooruit     |A1 01 10 4F |
|3  |Achteruit   |A1 01 30 6F |
|3  |Licht aan   |A1 01 31 6E |
|3  |Licht uit   |A1 01 21 7E |
|4  |Speed 0     |A0 03 00 5C |
|4  |Speed 127   |A0 03 7F 23 |

De snelheden hierboven genoemd zijn afgeleid uit de logging van het DCC station.
Bij snelheden is het 3e byte snelheid. Ook apart is dat de richting eenmalig wordt verzonden.

#### Wisselbediening

 Met het DCC station worden wissels bediend:

|Actie        | Bericht                  |
|-------------|--------------------------|
|Wissel 1 R   | B0 00 10 5F / B0 00 00 4F|
|Wissel 1 G   | B0 00 30 7F / B0 00 20 6F|
|Wissel 2 R   | B0 01 10 5E / B0 01 00 4E|
|Wissel 2 G   | B0 01 30 7E / B0 01 20 6E|
..
|Wissel 512 R | B0 7F 13 23 / B0 7F 03 33|
|Wissel 512 G | B0 7F 33 03 / B0 7F 23 13|
|Wissel 513 R | B0 00 14 5B / B0 00 04 4B|
..
|Wissel 2048 R| B0 7F 1F 2F / B0 7F 0F 3F|
|Wissel 2048 G| B0 7F 3F 0F / B0 7F 2F 1F|

Als we kijken naar 'Wissel 1 R' is volgens pag. 10 0xB0 een wisselopdracht; dat klopt. In het 3e byte <SW2> met de waarde 0x10 is DIR = 0 voor Thrown/RED en ON=1. Kort daarna gaat ON weer naar 0. Het adres van de wissel is 0; hier zien we weer dat onder water adressen één lager zijn dan in de interface wordt aangegeven/aangeklikt.

Als we kijken naar 'Wissel 1 G' is het 3e byte 0x30 dus DIR is 1 voor Closed/GREEN en ON = 1. Korte tijd later is ON weer 0.

Wissel 2 R klopt ook weer met een DIR = RED op adres 1 (in interface dus 2) met ON kort 1 dan 0.

**;<0xB0>,<SW1>,<SW2>,<CHK> REQ SWITCH function
<SW1> =<0,A6,A5,A4- A3,A2,A1,A0>, 7 ls adr bits. A1,A0 select 1 of 4 input pairs in a DS54
<SW2> =<0,0,DIR,ON- A10,A9,A8,A7> Control bits and 4 MS adr bits.
,DIR=1 for Closed,/GREEN, =0 for Thrown/RED
,ON=1 for Output ON, =0 FOR output OFF
 Note-,Immediate response of <0xB4><30><00> if command failed, otherwise no response**

#### Melders

We laten loc's rijden over de baan en deze passeren daarbij melders. In de baan zijn 12 melders aanwezig beginnend met adres 17 (in de gebruikersinterface).

|Melder  | Bericht    |
|--------|------------|
|17 IN   |B2 08 50 15 |
|17 UIT  |B2 08 40 05 |
|18 IN   |B2 08 70 35 |
|18 UIT  |B2 08 60 25 |
|19 IN   |B2 09 50 14 |
|19 UIT  |B2 09 40 04 |
|20 IN   |B2 09 70 34 |
|20 UIT  |B2 09 60 24 |
..
|23 IN   |B2 0B 50 16 |
|23 UIT  |B2 0B 40 06 |
|24 IN   |B2 0B 70 36 |
|24 UIT  |B2 0B 60 26 |

L als bit5 van <IN2> geeft IN- of UITrijden aan. Melder 17 bij het inrijden (ws. intern adres 16) heeft een Loconet-adres met A6 = 1 -> 64. Zou de tekst kunnen zijn dat bij gebruik van de DR4088 als bezetmelder A1 en A0 altijd 0 zijn en dus het adres gedeeld moet worden door 4? Melder 18 (intern 17) heeft adres A6 = 1 dus 64 wat weer 16 zou kunnen betekenen, maar I=1 betekent waarschijnlijk het lsb van het adres hoewel dit niet zo duidelijk in de specificaties staat.

**; <0xB2>, <IN1>, <IN2>, <CHK>
<IN1> =<0,A6,A5,A4- A3,A2,A1,A0>, 7 ls adr bits. A1,A0 select 1 of 4 inputs pairs in a DS54
<IN2> =<0,X,I,L- A10,A9,A8,A7> Report/status bits and 4 MS adr bits.
"I"=0 for DS54 "aux" inputs and 1 for "switch" inputs mapped to 4K SENSOR space.
(This is effectively a least significant adr bit when using DS54 input configuration)
"L"=0 for input SENSOR now 0V (LO) , 1 for Input sensor >=+6V (HI)
"X"=1, control bit , 0 is RESERVED for future!**

😃Als de power wordt uit- en weer ingeschakeld zal de bezetmelder van alle 32 melders de toestand in één boodschap weergeven:

B2 08 40 05 B2 08 60 25 B2 09 40 04 B2 09 60 24 B2 0A 40 07 B2 0A 60 27 B2 0B 40 06
B2 0B 60 26 B2 0C 40 01 B2 0C 60 21 B2 0D 40 00 B2 0D 60 20 B2 0E 40 03 B2 0E 60 23
B2 0F 40 02 B2 0F 60 22 B2 00 40 0D B2 00 60 2D B2 01 40 0C B2 01 60 2C
B2 02 40 0F B2 02 60 2F B2 03 40 0E B2 03 60 2E B2 04 40 09 B2 04 60 29
B2 05 40 08 B2 05 60 28 B2 06 40 0B B2 06 60 2B B2 07 40 0A B2 07 60 2A

##### Power

|Actie    | Bericht    |
|---------|------------|
|Power on |83 7C       |
|Power off|82 7D       |

Conform specs.

##### Multimaus

Ook opdrachten gegeven op de Multimaus verschijnen op Loconet. Bij wisselcommando's zijn ze identiek.
