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
        * [Computer Client](#MQTTX---Computer-Client)
        * [Android Mobil Client](#MQTT-Test---Android-Mobil-Client)
* [Anerkendelse](#Anerkendelse)

<p>
<br/>
</p>

# Introduktion

Det intelligente hus er en simplificeret repræsentation af hvad der er muligt at lave med embeded programmering og IoT. Dette project er en skole opgave, som i teorien godt ville kunne inplementeres i et rigtigt home. 

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

* Dette project har taget udgangspunkt i at bruge følgene teknologier til komunikation. 
    * MQTT 
    * SPI (Serial Peripheral Interface)
    * I2C (Inter-Integrated Circuit) / TWI (Two Wire Interface)
    * Seriel datakommunikation 
    * Wi-Fi

<p>
<br/>
</p>

# Functionelle og non-functionelle krav

lav et "proof of concept" der kan demonstrere følgene krav. 

* Fjernstyring af forskellige funktioner.

    * Huset skal have midst en alarm og alle alarmer skal kunne deaktiveres både trådløst over MQTT og ved fysist at trykke på en knap.

    * Termustat: 
        * Temperature og Humidity skal sendes fra et 'board' til et andet 'board'. 
        * Temperature og Humidity målinger skal sendes op til 'thingspeak'

    * Hoveddøren: <br/>
        * En RFID kort/chip skal fungere som en nøjle til huset. 
        * En servo motor skal vise døren der åbner/lukker.
        * Døren skal kunne styres både trådløst (via MQTT) og via RFID kort/chip

* Et 'stort display' der skal vise den sidste ændring det er sket i huset. f.eks "Stue lyd: OFF"

<p>
<br/>
</p>

## Fremtidige kvav 

* Lys i de forkællige rum skal kunne styres via en app.

* Opsamlet data skal, i 'App Programmering 3' faget, kunne præseteres i en mobil app.

<p>
<br/>
</p>

# Brugsvejledning

Intil 'App Programmering 3' faget starter. vil alle fjernstyret User-Interfaces/componenter blive styret via en eller flere MQTT clienter. 

Disse kontrol functioer vil senere blive inplementeret ind i en app for lettere brug og kontrol.

<p>
<br/>
</p>

## Setup
..................<br/>
.............<br/>

<p>
<br/>
</p>

### Thingspeak
Thingspeak er systemets 'Broker' og står for alt routing i systemet. 
For at sette thingspeak ordenligt op så bør du først læse denne guide, der forteller dig hvad du behøver og hvordan der gøres. <br/> 
```
Dokumenter/Setup thingspeak.rtf
```
<p>
<br/>
</p>

### MQTTX - Computer Client
An Elegant Cross-platform MQTT 5.0 Desktop Client<br/>

[Find programmet her!](https://mqttx.app/)

<p>
<br/><br/>
</p>


### MQTT Test - Android Mobil Client
'MQTT Test' bruger MQTT Client protokol til at forbinde MQTT server. Du kan blant andet oprette 3 forbindelser for at forbinde 3 forskellige servere på samme tid, og grænsefladen er intuitiv.<br/>

[Find appen her!](https://play.google.com/store/apps/details?id=org.thinhlt.mqtttesttool&hl=da&gl=US)

<p>
<br/>
</p>

# Hardware
...............<br/>
......................<br/>

<p>
<br/>
</p>

## Hardware Componenter
Til dette project bruges der følgene hardware <br/>

* Udviklings board
    * Atmel Mega 2560
    * MKR WIFI 1010
* Sensore
    * DHT11 (temperatur og luftfugtighed)

<p>
<br/>
</p>

## Tilkobling Pinout
...............<br/>
......................<br/>

<p>
<br/><br/>
</p>


# Anerkendelse

Dette project eksistere grundet disse menesker:

* [Kasper Jacobsen](https://github.com/Moonshine42tech)
* [Egon Rasmussen](https://github.com/EgonRasmussen)

