#include <Arduino.h>
#include <Wire.h>
#include <WiFiNINA.h>               // Enables Wi-Fi
#include <WiFi_secrets.h>           // Wi-Fi credentials
#include <thingspeak._secrets.h>    // thingspeak API and MQTT credentials
#include "ThingSpeak.h"             // Bruger dette til ThingSpeak API
//#include <MQTT.h>                   // Jeg bruger dette til at hente data ned for ThingSpeak


// function declarations
void receiveDataEvent(int howMany);
void sendDataEvent();
void sendDataToThingspeak();


WiFiClient client;

#pragma region thingspeak

// API related variables
unsigned long myChannelNumber = Channel_ID;
const char * myWriteAPIKey = Write_API_Key;
const char * myReadAPIKey = Read_API_Key;
int counter = 0;

#pragma endregion thingspeak

#pragma region DHT11 over I2C

int DHT11_Temperature;
int DHT11_Humidity;

#pragma endregion DHT11 over I2C


void setup() 
{
  Wire.begin(4);                      // join I2C bus with address #4
  Wire.onReceive(receiveDataEvent);   // register Receive from marster event
  Wire.onRequest(sendDataEvent);      // register Send to marster event

  Serial.begin(9600);                 // start serial for output (matching the speed of the slowest module ine the house)

#pragma region Wi-Fi

    // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

#pragma endregion Wi-Fi

  ThingSpeak.begin(client);           // Initialize ThingSpeak
}

void loop() 
{

#pragma region Connect/reconnect to Wi-Fi

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to WiFi: ");
    Serial.println(SECRET_SSID);

    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(SECRET_SSID, SECRET_PASS); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

#pragma endregion Connect/reconnect to Wi-Fi

#pragma region write to the ThingSpeak channel

  if (counter == 300000) // 300.000 = 5 min.
  { 

    // Set ThingSpeak Fields
    ThingSpeak.setField(1, DHT11_Temperature);
    ThingSpeak.setField(2, DHT11_Humidity);

    delay(500);

    // write to the ThingSpeak channel
    sendDataToThingspeak();

    counter = 0;        // reset counter
  }
  else 
  {
    counter += 1000;    // 1000 = 1 sec.
    //Serial.println(counter);
  }
  
#pragma endregion write to the ThingSpeak channel

  delay(1000); // loop every 1 sec.
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveDataEvent(int howMany)
{
  String keyword =  "";

  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read();     // receive byte as a character
    keyword += c;             // Append char to string
  }
  int x = Wire.read();        // receive byte as an integer


  // Verify incoming data
  if (keyword == "Temp: ") 
  {
    // Checking the values that got through
    Serial.print("Temperature is: ");
    Serial.println(x);

    // send x to thingspeak
    DHT11_Temperature = x;
  }
  
  if (keyword == "Hum: ") 
  {
    // Checking the values that got through
    Serial.print("Humidity is: ");
    Serial.println(x);

    // send x to thingspeak
    DHT11_Humidity = x;
  }
}


// A function that writes to filds in a ThingSpeak channel
void sendDataToThingspeak() 
{
  delay(100);
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}


// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void sendDataEvent() 
{
  Serial.println("Getting data from ThingSpeak...");

  // Get data from a Thingspeak field 3
  int keyNumber = ThingSpeak.readIntField(Channel_ID, 3, myReadAPIKey);

  Serial.println("Sending data to marster.");

  Wire.write(keyNumber);
}
