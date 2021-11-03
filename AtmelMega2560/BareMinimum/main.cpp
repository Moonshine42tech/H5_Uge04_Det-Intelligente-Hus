#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#pragma region DHT

#define DHTPIN 2			// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11		// DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

String DhtSencorTemp = "";
String DhtSencorHum = "";

#pragma endregion DHT

void setup()
{
	Serial.begin(9600);
	
#pragma region  DHT

	// Initialize device.
	dht.begin();
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	dht.humidity().getSensor(&sensor);
	delayMS = sensor.min_delay / 1000;		// Set delay between sensor readings based on sensor details.
	
#pragma endregion DHT

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


}
