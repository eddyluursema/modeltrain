![Nederlandse vlag](../../images/nl.gif)

Er zijn diverse manieren om schakeldecoders te adresseren en de diverse fabrikanten verschillen onderling, maar zelf binnen Digikeijs verschilt het binnen één produkt.

In de DR5000 kunnen we met het schakelbord een wissel of sein bedienen. Bij het bedienen van wissel/sein 501 wordt in de [logging](./images/DR5000_adress_one_down.png) het aangeroepen adres echter altijd één lager genoemd!!
In de [Arduino-sniffer](./images/DR4018_sniffer_output.png) worden zowel PADA als MADA getoond; dus zowel 501 als 126:0.

RocRail gebruikt [PADA](./images/DR4018_RocRail_PADA_adressing.JPG) en [MADA](./images/DR4018_RocRail_MADA_adressing.PNG) voor een DR4018. We kunnen dus bij het instellen bij preset 1 de adressen 501, 502 en 503 gebruiken maar ook 126:1, 126:2 en 126:3 (omdat het gebruik van het getal 0 bij RocRail betekent niets mee doen moeten dus de waarden 1 hoger liggen).

![English flag](../../images/gb.gif)

There are several ways of adressing accessory decoders like the DR4018 and manufacturers use differnt ways and even Digikeijs use more than one.

In the DR5000 we can use the switch board to control switches and signals. Switching adress 501 will show in the [logging](./images/DR5000_adress_one_down.png) the adress minus 1!!
In de [Arduino-sniffer](./images/DR4018_sniffer_output.png) worden zowel PADA als MADA getoond; dus zowel 501 als 126:0.

RocRail uses both [PADA](./images/DR4018_RocRail_PADA_adressing.JPG) and [MADA](./images/DR4018_RocRail_MADA_adressing.PNG) for a DR4018. For preset 1 we can use adresses 501, 502 en 503 but also 126:1, 126:2 en 126:3 (because a value 0 in the RocRail interface means 'no meaning' the values are 1 higher).
