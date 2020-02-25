# ![Nederlandse vlag](../../images/nl.gif)Nederlands

[Navigate to English version](#English)

#### Inleiding

In mijn baan gebruik ik 4 schakeldecoders DR4018 op de vier hoeken van de tafel. Om bedrading te besparen worden zowel max. 2 wissels als 3 4-aspect NS-seinen op één decoder aangesloten. Hiertoe is documentatie geraadpleegd afkomstig van Digikeijs "DR4018 toepassing handleiding_beneluxforum.pdf":

#### Aansluitschema

![2 wissels als 3 NS-seinen op één decoder](./images/DR4018_mixedswitchesandsignals.png)

#### Configuratie

De volgende CV-adres-value-combinaties moeten in de DR4018 worden geprogrammeerd:

CV|Waarde|Betekenis
--|------|---------
47|7|Preset
113|143|Pulse tijd+max.intensiteit uitgangspoort 1
114|143|Pulse tijd+max.intensiteit uitgangspoort 2
115|143|Pulse tijd+max.intensiteit uitgangspoort 3
116|143|Pulse tijd+max.intensiteit uitgangspoort 4
131|0|Geen sein
141|1|Uitgangspoort 1 aan bij activeren 1e adres
143|0|Sein 1 uit
144|2|Uitgangspoort 2 aan bij deactiveren 1e adres
147|4|Uitgangspoort 3 aan bij activeren 2e adres
150|8|Uitgangspoort 4 aan bij deactiveren 2e adres

**⚠️CV 47 moet altijd als eerste worden geschreven, omdat de andere CV's wijzigingen zijn op preset 7**

#### Test

Op adres 501 GROEN wordt output 1 van de DR4018 geactiveerd gedurende 0.5 s; bij ROOD output 2.

Op adres 502 GROEN wordt output 3 van de DR4018 geactiveerd gedurende 0.5 s; bij ROOD output 4.

Adres 503 en 504 geven geen reactie.

Vanaf adres 505 t/m 508 zal een GROEN en ROOD een seinbeeld op het 1e sein geven, adres 509 t/m 512 op het 2e en adres 513 t/m 516 het 3e sein.


#### RocRail

Om een DR4018 zoals hierboven geconfigureerd samen te laten werken met RocRail moet je de [handleiding](../Preset7/README.md) lezen van preset 7 voor de seinen en [handleiding](../Preset0/README.md) lezen van preset 0 voor de wissels.

# ![English flag](../../images/gb.gif)English

#### Introduction

In my modeltrain track I use 4 accessory decoders DR4018 in the four corners of the table. To save wiring both 2 switches and 3 Dutch signals are connected to the same decoder. The documentation comes from the site of Digikeijs and is a Dutch document "DR4018 toepassing handleiding_beneluxforum.pdf":

#### Wiring

![2 switches and 3 Dutch signals](./images/DR4018_mixedswitchesandsignals.png)

#### Configuration

The next CV-adres-value-combinations must be written to the DR4018:

CV|Value|Meaning
--|------|------
47|7|Preset
113|143|Pulse time+max.intensity output port 1
114|143|Pulse time+max.intensity output port 2
115|143|Pulse time+max.intensity output port 3
116|143|Pulse time+max.intensity output port 4
131|0|No signal
141|1|Activate adres 1 output port 1 on
143|0|Signal 1 off
144|2|Deactivate adres 1 output port 2 on
147|4|Activate adres 2 output port 3 on
150|8|Deactivate adres 2 output port 4 on

**⚠️CV 47 must always be the first CV to set. The other CV values are changes on preset 7**

#### Test

A GREEN on adress 501 will activate output 1 of the DR4018 during 0.5 s; at RED output 2.

A GREEN on adress 502 will activate output 3 of the DR4018 during 0.5 s; at RED output 4.

Adress 503 and 504 have no response.

From adress 505 until adress 508 a combination of RED and GREEN will show an aspect on the 1st signal, adress 509-512 the 2nd and 513-516 the 3rd.


#### RocRail

To configure a DR4018 with signals as described above in RocRail read the [manual](../Preset7/README.md) of preset 7 for the signals and [manual](../Preset0/README.md) of preset 0 for the switches.
