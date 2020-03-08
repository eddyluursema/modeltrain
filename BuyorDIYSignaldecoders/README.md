# ![Nederlandse vlag](../images/nl.gif) Nederlands

[Navigate to English version](#English)

## UNDER CONSTRUCTION
In deze pagina's worden worden een aantal commerciële produkten opgesomd en beschreven hoe je zelf een signaal- en/of wisseldecoder kan bouwen.


## Commerciële DCC schakeldecoders

* Digikeijs de DR4018. Zie andere pagina's in deze repository.
* ArCoMoRa de ArSigDec en DCCNext. Kit. Code van Arduino alleen hex-bestand.
* OpenDCC diverse uitvoeringen als kit of gebouwd.
* Dinamo OC32NG
* Viessmann o.a. de 5209
* RoSoft de 10836
* Kuehn
* Littfinski
* Roco
* Tams


### DIY Signaal/wissel decoders

* [NMRA](https://github.com/mrrwa/NmraDcc)

* [MynaBay](https://github.com/MynaBay/DCC_Decoder)

* [OpenDCC](https://www.opendcc.de/elektronik/opendecoder/opendecoder_e.html) veel meer dan alleen decoder. Geschikt voor zelfbouw, maar ook te koop. Complete ondersteuning van het digitaliseren van de modelspoorbaan. Bijna alles is beschikbaar. Nieuwere ontwerpen bevatten wel veel SMD-componenten.

* [Werk van Frans Stevens](http://members.home.nl/fjstevens/) veel meer dan alleen decoder. Complete ondersteuning van het digitaliseren van de modelspoorbaan. Geeft helaas code als hex-bestand.

* [Werk van Arjan Mooldijk](https://arjanmooldijk.wordpress.com/2018/10/15/signal-decoder-sketch-voor-duitse-seinen/) en zijn [code](https://github.com/ArjanMooldijk/Signal-Decoder) voor seinen

* [Werk van Paco](http://usuaris.tinet.cat/fmco/main_en.html) bevat niet alleen decoders voor seinen en wissels, maar nog veel meer zoals boosters, RailCom. Het nadeel is dat hij niet altijd broncode beschikbaar stelt, maar alleen hex-bestanden.

* [Lydo](https://www.lydo.nl/hobby/diy-dcc-accessory-decoder/) geeft helaas geen code.

* [Bicknell](https://github.com/bicknell/rpi-dcc-decoder) op basis van een Pi.

## Overzicht schakeldecoders

Na een stuk literatuuronderzoek en onderzoek in een werkende installatie is onderstaand overzicht samengesteld. Zodra meer hardware beschikbaar komt zal de lijst worden aangevuld.

|Decoder |BuyDIY|Configuratie|NLsein|Wisselspoel|Fading|Servo|Open source|Prijs/poort|
|--------|------|------------|------|-----------|------|-----|-----------|-----------|
|DR4018  |Buy   |CV          |❌    |✔️           |      |❌    |❌         |&euro; 2   |
|DCCNext |Kit   |UI ✔️        |✔️    |❌           |✔️     |✔️    |❌         |&euro; 1   |
|OpenDCC1|DIY   |            |      |           |      |     |✔️          |&euro; 0.5 |
|OpenDCC2|Kit   |            |      |           |      |     |✔️          |&euro; 3   |

* BuyDIY: wordt de decoder kant en klaar geleverd (Buy), als zelfbouwkit of moet je alles inclusief printplaat samenstellen (DIY)?
* Configuratie: kan middels CV waarden zijn of met een mooie User Interface
* NLSein betekent dat bij de overgang van groen naar rood kort een geel aspect oplicht
* Wisselspoel: kan een wisselspoel direct zonder extra elektronica worden aangestuurd?
* Fading: kan het oplichten en doven van een licht vertraagd verlopen?
* Servo: kunnen servo's voor b.v. wissels direct worden aangestuurd?
* Open source: is de code van de microcontroller beschikbaar?


### Oplossingsrichtingen processor

* DIY PCM met een processor uit de Atmel familie
* Arduino Mega Pro PCB
* Arduino Nano PCB
* Arduino Uno PCB
* Arduino Mega PCB
* PIC familie

### Oplossingsrichtingen aansturing

* Rechtstreeks uit controller
 * met serieweerstand
 * pas op maximale stroom door controller
* Buffer b.v. UNL2003 (7 drivers) of ULN2803 (8 drivers)
  * hogere spanning en stroom b.v. voor wissels
  * maar 7 i.p.v. 8 buffers in één chip
* MCP23017 [link](https://tronixstuff.com/2011/08/26/arduino-mcp23017-tutorial/)



| IC     | Channels | Bus | PWM |Bits|Resistor|Aliexpress | Library  | Remarks   |Current             |
|--------|----------|-----|-----|----|--------|-----------|----------|-----------|--------------------|
|TLC5940 | 16       |5pin | LED |    |1       |&euro;3 DIP| 2 timers |           | 120 mA/pin         |
|TLC5947 | 24       | SPI | LED | 12 |1       |&euro;3 PCB|No timers |           | 38 mA/pin          |
|TLC59116| 16       | I2C | LED |    |        | not       |          |           |                    |
|TLC59711| 12       | SPI | LED |    |1       |           |          |           |                    |
|MCP23017| 16       | I2C | No  | -  |16      |           |          |Also input |25mA/pin, 150mA chip|
|PCA9685 | 16       | I2C |Servo| 12 |        |&euro;2 PCB|          |           |25mA/pin, 400mA chip|




# ![English flag](../images/gb.gif)English
