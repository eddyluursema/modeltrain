# ![Nederlandse vlag](../../images/nl.gif) Nederlands

In dit hoofdstuk wordt uitgelegd hoe je via de ICSP (In Circuit Serial Programmer) een Arduino-achtige kunt programmeren. De tekst is verder uitsluitend in het Engels.

# ![English flag](../../images/gb.gif)English

In this chapter is explained how to program an Arduino like chip through ICSP (In Circuit Serial Programmer).

* First buy(can be found for less than &euro; 1) and connect the USB ASP. Pay attention to the connection of the header with the ICSP connector on the PCB. Some USB ASP do not have a notch to indicate pin 1. Most of the time the flat cable has a red wire on pin 1. On the Arduino Uno there is a very very small white dot at pin 1.

![Arduino_USBASP](./images/Arduino_USBASP.png)

In an Arduino Nano there is a small '1' at the rear of the board:

![Arduino_USBASP](./images/ArduinoNano_USBASP.jpg)

Source: my own pictures

![6pinAVRprogcable](./images/6pinAVRprogcable.jpg)

![6pinAVRproghead](./images/6pinAVRproghead.jpg)

Source https://tutorial.cytron.io/2015/02/05/using-avr-usbasp-program-arduino/

* Now install the correct driver using the Zadig tool. [See](https://rayshobby.net/dead-simple-driver-installation-for-usbasp-and-usbtiny-on-windows/).

![ZadigInstallDriver](./images/ZadigInstallDriver.PNG)

* Open the Arduino IDE and load an example program e.g. Blink.

* Select the correct target board e.g. Arduino Uno:

![ArduinoIDESelectTarget](./images/ArduinoIDESelectTarget.PNG)

* Select the correct programmer:

![ArduinoIDEProgrammer](./images/ArduinoIDEProgrammer.PNG)

* Now upload your program through the special USB ASP with the menu 'Upload with programmer':

![ArduinoIDEUploadUsingProgrammer](./images/ArduinoIDEUploadUsingProgrammer.PNG)

[TOP](#English)
