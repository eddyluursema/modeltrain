# ![Nederlandse vlag](../images/nl.gif) Nederlands

[Navigate to English version](#English)

## UNDER CONSTRUCTION
In deze pagina's wordt beschreven hoe je zelf een signaal- en/of wisseldecoder kan bouwen, maar er worden ook een aantal commerciële produkten opgesomd.


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


### DIY Signaaldecoders

* [NMRA](https://github.com/mrrwa/NmraDcc)

* [MynaBay](https://github.com/MynaBay/DCC_Decoder)

* [OpenDCC](https://www.opendcc.de/elektronik/opendecoder/opendecoder_e.html) veel meer dan alleen decoder. Geschikt voor zelfbouw, maar ook te koop. Complete ondersteuning van het digitaliseren van de modelspoorbaan. Bijna alles is beschikbaar. Nieuwere ontwerpen bevatten wel veel SMD-componenten.

* [Werk van Frans Stevens](http://members.home.nl/fjstevens/) veel meer dan alleen decoder. Complete ondersteuning van het digitaliseren van de modelspoorbaan. Geeft helaas code als hex-bestand.

* [Werk van Arjan Mooldijk](https://arjanmooldijk.wordpress.com/2018/10/15/signal-decoder-sketch-voor-duitse-seinen/) en zijn [code](https://github.com/ArjanMooldijk/Signal-Decoder) voor seinen

* [Werk van Paco](http://usuaris.tinet.cat/fmco/main_en.html) bevat niet alleen decoders voor seinen en wissels, maar nog veel meer zoals boosters, RailCom. Het nadeel is dat hij niet altijd broncode beschikbaar stelt, maar alleen hex-bestanden.

* [Lydo](https://www.lydo.nl/hobby/diy-dcc-accessory-decoder/) geeft helaas geen code.

* [Bicknell](https://github.com/bicknell/rpi-dcc-decoder) op basis van een Pi.

### Oplossingsrichtingen processor

* Atmel familie
* Arduino Mega Pro PCB
* Arduino Nano PCB
* Arduino Uno PCB
* Arduino Mega PCB
* PIC familie

### Oplossingsrichtingen aansturing

* Rechtstreeks uit controller
 * met serieweerstand
 * pas op maximale stroom door controller
* Buffer b.v. UNL2003
  * hogere spanning en stroom b.v. voor wissels
  * maar 7 i.p.v. 8 buffers in één chip
* MCP 23017 multiplexer met serieweerstand
  * 16 uitgangen/chip
* TLC5940 LED driver
  * geen serieweerstand
  * PWM ingebouwd per uitgang
  * 16 uitgangen/chip


# ![English flag](../images/gb.gif)English
