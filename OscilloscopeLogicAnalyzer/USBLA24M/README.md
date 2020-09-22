# ![Nederlandse vlag](../../images/nl.gif) Nederlands

[Navigate to English version](#English)


In deze pagina's wordt de USB LA 24M besproken. Deze is in Nederland verkrijgbaar, maar op bij Chinese leveranciers zoals AliExpress.

![USB LA](./images/USBLogicAnalyzer24M.PNG)

## Installatie

Volg de instructies zoals aangegeven bij deze [link](https://learn.sparkfun.com/tutorials/using-the-usb-logic-analyzer-with-sigrok-pulseview). Het installeren van de Windows USB-driver niet vergeten. Ik heb zelf ondervonden dat ik dit een aantal keren heb uitgevoerd. Daarna verscheen bij op opstarten van PulseView meteen een gedetecteerd device (Salea Logic hoewel het een Chinese kloon betreft):. Zie de kleine pijl in het menu.

 ![Device](./images/Menu.PNG)

#### Tips

* Gebruik scroll van de muis om in te zoomen
* Gebruik de 'Show cursors' (twee vlaggetjes) om nauwkeurige metingen te doen
* Het geel/goen-icoontje roept de protocoldecoders op

#### Eerste meting

Maak een klein Arduino programma dat een LED laat knipperen op b.v. 1 Hz en bij het inschakelen de tekst 'On' en bij het uitschakelen de tekst 'Off' toont via de seriële uitgang. Sluit de analyzer aan op de LED-pin en de seriële uitgang. Schakel bij de knop protocolanalyse de UART-analyse in. Je ziet het volgende:

![Device](./images/ToggleSerial.PNG)

Heel goed is het flippen van de pin en de seriële data te zien met start- en stopbit. De protocolanalyse laat de teksten zien inclusief carrige return en linefeed (tenminste als je println() hebt gebruikt)

# ![English flag](../../images/gb.gif)English
