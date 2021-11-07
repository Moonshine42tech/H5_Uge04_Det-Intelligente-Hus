<!-- PROJECT LOGO -->
<div align="center">
  <h1>Det Intelligente Hus</h1>
  <p>EMBEDDED CONTROLLER III</p><br />

  <img src="Billeder/Floor plan.png" alt="Floor plan" width="720" height="480">
</div><br/>

<p>
<br/>
</p>

# Indholdsfortegnelse

* [Introduktion](#Introduktion)
    * [Projectets formål](#Projectets-formål)
    * [Godt at vide](#Godt-at-videl)
* [Functionelle og non-functionelle krav](#Functionelle-og-non-functionelle-krav)
    * [Fremtidige kvav](#Fremtidige-kvav)
* [Brugsvejledning](#Brugsvejledning)
    * [Setup](#Setup)
        * [Thingspeak](#Thingspeak)
        * [Computer Client](#Computer-Client---MQTTX)
        * [Android Mobil Client](#Android-Mobil-Client---MQTT-Test)
* [Hardware](#Hardware)
    * [Hardware Componenter](#Hardware-Componenter)
    * [Pinout Diagram](#Pinout-Diagram)
* [Video Præsentation](#Video-Præsentation)
* [Anerkendelse](#Anerkendelse)

<p>
<br/>
</p>

# Introduktion

Det intelligente hus er en simplificeret repræsentation af hvad der er muligt at lave med embeded programmering og IoT. Dette project er en skole opgave, som i teorien godt ville kunne inplementeres i et rigtigt hjem. 

<p>
<br/>
</p>

## Projectets formål

Det intiligente hus er et skoleproject der har til formål at vise underviseren ’Egon C. Rasmusen’. Hvad eleven ’Kasper Jacobsen’, har lært i løbet at det to ugers undervisning i ’EMBEDDED CONTROLLER III - IOT - S21DMH5B11’.

<p>
<br/>
</p>

## Godt at vide

* Der vil ikke blive inplimenteret en fysisk menu function i dette project, da der er sat fokus på at dette intelligente hus, kun skal kunne styres via en app. <br/>(appen kommer på et senere fag).

* Dette project har taget udgangspunkt i at bruge følgene teknologier, til komunikation. 
    * MQTT 
    * SPI (Serial Peripheral Interface)
    * I2C (Inter-Integrated Circuit) / TWI (Two Wire Interface)
    * Seriel datakommunikation 
    * Wi-Fi

* Intil faget 'App Programmering 3' starter. vil alle fjernstyret User-Interfaces/componenter blive styret via en eller flere MQTT/API clienter. 

    Disse clienter vil senere blive erstattet med en app, for bedre brugervenlighed og kontrol.

<p>
<br/>
</p>

# Functionelle og non-functionelle krav

Der skal laves et "proof of concept" der kan demonstrere følgene krav. 

* Fjernstyring af forskellige funktioner.

    * Huset skal have midst en alarm og alle alarmer skal kunne deaktiveres både trådløst (over MQTT) og ved fysist at scanne et kort/chip.

    * Termustat: 
        * Temperature og Luftfugtighed skal sendes fra et 'board' til et andet 'board'. 
        * Temperature og Luftfugtigheds målinger skal sendes op til 'thingspeak'

    * Hoveddøren: <br/>
        * En RFID kort/chip skal fungere som en nøjle til huset. 
        * En servo motor skal vise om døren er åben/lukket.
        * Dørens lås skal kunne styres både trådløst (via MQTT) og via RFID kort/chip

* Et 'stort display' der skal vise nogle live ændring det sker i huset. f.eks "Temperatur og Luftfugtighed". 

<p>
<br/>
</p>

## Fremtidige kvav 

* App
    * Opsamlet data (Fra Thingspeak) skal kunne hentes og præseteres.
    * Der skal være en menu i appen, så huset kan styres via appen.

<p>
<br/>
</p>

# Brugsvejledning

Denne del af dokumentet viser dig hvordan du kommer igang med at bruge dette project. Der er linket til guides til hver af de individuelle eksterne programmer. 

<p>
<br/>
</p>

## Setup
Når du cloner dette project skal du først sette Thingspeak op, samt en eller flere clienter. 

Denne del af dokumentet viser dig de forskellige "guides", til hvordan du setter de forskelloge ting op.

<p>
<br/>
</p>

### Thingspeak
Thingspeak er systemets 'Broker' og står for alt pub/sub routing i systemet. 
For at sette thingspeak ordenligt op så bør du først læse denne guide, der forteller dig hvad du behøver og hvordan der gøres. <br/> 

>Dokumenter/Setup-thingspeak.rtf

[Find hjemmesiden her!](https://thingspeak.com/)

<p>
<br/>
</p>
 
### Computer Client - MQTTX
An Elegant Cross-platform MQTT 5.0 Desktop Client<br/>

[Find programmet her!](https://mqttx.app/)<br/>
[Setup Guide](https://mqttx.app/docs)

<p>
<br/>
</p>


### Android Mobil Client - MQTT Test
'MQTT Test' bruger MQTT Client protokol til at forbinde MQTT server. Du kan blant andet oprette 3 forbindelser for at forbinde 3 forskellige servere på samme tid, og grænsefladen er intuitiv.<br/>

[Find appen her!](https://play.google.com/store/apps/details?id=org.thinhlt.mqtttesttool&hl=da&gl=US)<br/>
[Setup Guide](https://play.google.com/store/apps/details?id=org.thinhlt.mqtttesttool&hl=da&gl=US)


<p>
<br/><br/>
</p>

# Hardware
Hardware er en vigtig del af et hvert embeded system. Så her uder vises alt fra vilket dele der er brugt i systemet, til hvordan det hele er sat sammen. 

<p>
<br/>
</p>

## Hardware Componenter
Til dette project bruges der følgene hardware Componenter. <br/>

* Udviklings boards
    * Atmel Mega 2560
    * MKR WIFI 1010
* Programmer 
    * Atmel-ICE
* Modules
    * DHT11 (temperatur og luftfugtighed)
    * RC522 RFID Module
    * Logic Level Bidirectional module
    * LCD Backpack Modul
    * Buzzer
* Displays 
    * LCD Display 1602, I2C
* Motors 
    * SG90 Mikro Servo
* Other components
    * 2x LEDs
    * 2x 220 ohm resistor


<p>
<br/>
</p>

## Pinout Diagram
<br/>
<div align="center">
  <img src="Billeder/Det Intiligente Hus - Pinout Diagram.png" alt="Floor plan">
</div><br/>

<p>
<br/><br/>
</p>

# Video Præsentation

https://youtu.be/xV4eB2DHPKI

<p>
<br/>
</p>

# Anerkendelse

* [Kasper Jacobsen](https://github.com/Moonshine42tech)


