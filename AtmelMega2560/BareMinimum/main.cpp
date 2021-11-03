#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>

#pragma region DHT

#define DHTPIN 2			// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11		// DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

String DhtSencorTemp = "";
String DhtSencorHum = "";

#pragma endregion DHT

String StringBuilder = "";

void setup()
{
	Serial.begin(9600);
	
#pragma region DHT

	// Initialize device.
	dht.begin();
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	dht.humidity().getSensor(&sensor);
	delayMS = sensor.min_delay / 1000;		// Set delay between sensor readings based on sensor details.
	
#pragma endregion DHT

#pragma region SPI Marster

	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	SPI.begin();

#pragma endregion SPI Marster

}

void loop()
{
	// Delay between measurements.
	delay(delayMS);

	// Take Measurements
#pragma region DHT

	// Sensor event
	sensors_event_t event;
	
#pragma region DHT Temperature

	// Get temperature from event
	dht.temperature().getEvent(&event);
	
	// set Temperature value
	if (isnan(event.temperature))
	{
		DhtSencorTemp = "Error temperature!";
	}
	else
	{
		DhtSencorTemp = event.temperature;
	}

#pragma endregion DHT Temperature

#pragma region DHT Humidity

	// Get temperature from event
	dht.humidity().getEvent(&event);
	
	// set Humidity value
	if (isnan(event.relative_humidity))
	{
		DhtSencorHum = "Error humidity!";
	}
	else
	{
		DhtSencorHum = event.relative_humidity;
	}
	
#pragma endregion DHT Humidity

#pragma endregion DHT

	// Send values to MKR WIFI 110 board
#pragma region MKR WIFI 110

	// test output
	Serial.println(DhtSencorHum);
	StringBuilder = "Temperature: " + DhtSencorTemp + " Humidity: " + DhtSencorHum;
	Serial.println(StringBuilder);

#pragma region SPI

  	digitalWrite(SS, LOW);				// enable Slave Select
	SPI.transfer(StringBuilder);		// Transfer a string
  	digitalWrite(SS, HIGH);				// disable Slave Select

#pragma endregion SPI

	
#pragma endregion MKR WIFI 110
}
