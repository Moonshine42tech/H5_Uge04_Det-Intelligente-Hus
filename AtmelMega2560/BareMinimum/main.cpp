#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>


byte x = 0;
#pragma region DHT

#define DHTPIN 2			// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11		// DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Output holders
int DhtSencorTemp;
int DhtSencorHum;

#pragma endregion DHT

void setup()
{
	Serial.begin(9600);
	Wire.begin(); // join i2c bus (address optional for master)

#pragma region DHT

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
		DhtSencorTemp = 420;
	}
	else
	{
		DhtSencorTemp = (long)event.temperature;
	}

#pragma endregion DHT Temperature

#pragma region DHT Humidity

	// Get temperature from event
	dht.humidity().getEvent(&event);
	
	// set Humidity value
	if (isnan(event.relative_humidity))
	{
		DhtSencorHum = 360;
	}
	else
	{
		DhtSencorHum = (long)event.relative_humidity;
	}
	
#pragma endregion DHT Humidity

#pragma endregion DHT

	// Send values to MKR WIFI 110 board
#pragma region Master Writer/Slave Receiver

	//// testing DHT11 sensor output in Terminal
	//Serial.print("Temp: ");
	//Serial.println(DhtSencorTemp);
	//Serial.print("Hum: ");
	//Serial.println(DhtSencorHum);
  
  Wire.beginTransmission(4);		// transmit to device #4
  
  Wire.write("Temp: ");				// sends some bytes
  Wire.write(DhtSencorTemp);		// sends some bytes
  
  Wire.endTransmission();			// stop transmitting
  
  Wire.beginTransmission(4);		// transmit to device #4
  
  Wire.write("Hum: ");			// sends some bytes
  Wire.write(DhtSencorHum);		    // sends some bytes
  
  Wire.endTransmission();			// stop transmitting


	
#pragma endregion Master Writer/Slave Receiver

#pragma region RFID lås (Hoveddør)

	//...

#pragma endregion RFID lås (Hoveddør)

  delay(1000);		// run loop every 1 sec
}
