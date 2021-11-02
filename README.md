<!-- PROJECT LOGO -->
<div align="center">
  <h1>Det Intelligente Hus</h1>
  <p>EMBEDDED CONTROLLER III</p><br />

  <img src="Billeder/Floor plan.png" alt="Floor plan" width="720" height="480">
</div>

<p>
<br/>
</p>

___

## Indholdsfortegnelse

* [Introduktion](#Introduktion)
    * [Projectets formål](#Projectets-formål)
* [Functionelle og non-functionelle krav](#Functionelle-og-non-functionelle-krav)
* [Brugsvejledning](#Brugsvejledning)
    * [Setup](#Setup)
        * [Thingspeak](#Thingspeak)
        * [Computer Client](#MQTTX-\(Computer-Client\))
        * [Android Mobil Client](#MQTT-Test-\(Android-Mobil-Client\))
* [Anerkendelse](#Anerkendelse)

<p>
<br/>
</p>

___

## Introduktion

Det intelligente hus er en simplificeret repræsentation af hvad der er muligt at lave med embeded programmering og IoT. Dette project er en skole opgave, som i teorien godt ville kunne inplementeres i et rigtigt smart home. 

<p>
<br/>
</p>

### Projectets formål

Det intiligente hus er et skoleproject der har til formål at vise underviseren ’Egon C. Rasmusen’. Hvad eleven ’Kasper Jacobsen’, har lært i løbet at det to ugers undervisning i ’EMBEDDED CONTROLLER III - IOT - S21DMH5B11’.

<p>
<br/>
</p>

## Functionelle og non-functionelle krav

lav et "proof of concept" der kan demonstrere følgene krav. 

* Sikkerhed skal være indtænkt overalt.

* Fjernstyring af forskellige funktioner.

    * Lys i de forkællige rum skal kunne styres via en app.

    * Alle alarmer skal aktivere en "alarm lyd". men skal kunne deaktiveres både trådløst og ved fysist at trykke på en knap.

    * Hoveddøren: <br/>
    En RFID kort/chip skal fungere som en nøjle til huset. 
        * Rød led for låst dør .
        * Grøn led for u-låst dør.
        * En servo motor skal vise døren der åbner/lukker.
        * Døren skal kunne styres både vi app og via RFID kort/chip
        <br/>

* Et 'stort display' der skal vise den sidste ændring det er sket i huset. f.eks "Stue lyd: OFF"

* Relevante opsamlede data skal logges og gemmes, således at systemet fremover kan drage nytte af dem og foretage intelligente beslutninger.

* De opsamlede data skal, i 'App Programmering 3' faget, kunne præseteres i en mobil app.

<p>
<br/>
</p>

## Brugsvejledning

Intil 'App Programmering 3' faget starter. vil alle fjernstyret User-Interfaces/componenter blive styret via en eller flere MQTT clienter. 

Disse kontrol functioer vil senere blive inplementeret ind i en app for lettere brug og kontrol.

### Setup
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

### MQTTX (Computer Client)
An Elegant Cross-platform MQTT 5.0 Desktop Client<br/>

[Find programmet her!](https://mqttx.app/)

<p>
<br/><br/>
</p>


### MQTT Test (Android Mobil Client)
'MQTT Test' bruger MQTT Client protokol til at forbinde MQTT server. Du kan blant andet oprette 3 forbindelser for at forbinde 3 forskellige servere på samme tid, og grænsefladen er intuitiv.<br/>

[Find appen her!](https://play.google.com/store/apps/details?id=org.thinhlt.mqtttesttool&hl=da&gl=US)

<p>
<br/><br/>
</p>

___

## Anerkendelse

Dette project eksistere grundet disse menesker:

* [Kasper Jacobsen](https://github.com/Moonshine42tech)
* [Egon Rasmussen](https://github.com/EgonRasmussen)

