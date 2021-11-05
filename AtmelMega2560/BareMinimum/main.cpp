#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>	// LCD Display

// Define functions
int RfidValidater(); 
void moveServo();
void makeBipSound(int soundMode);
void SetRfidLeds(bool status); 

byte x = 0;
int BIP_PIN = 10;					// For ALARM and feed back sound effects

#pragma region LCD Display

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#pragma endregion LCD Display

#pragma region DHT

#define DHTPIN 2			// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11		// DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Output holders
int DhtSencorTemp;
int DhtSencorHum;

#pragma endregion DHT

#pragma region RFID

// definitions
#define RST_PIN   5							// Configurable, see typical pin layout above
#define SS_PIN    53						// Configurable, see typical pin layout above
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}	// Set your new UID here!

int isCardValid = 0;	// set - reset state

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance



MFRC522::MIFARE_Key key;

// Normally this would be in a separate .h file.
String Valid_RFID_Code = "30 45 66 A7";		// card =  30 45 66 A7 | chip = F7 DD 5A D3

#pragma endregion RFID

#pragma region Servo Motor

Servo servo;			// defines a servo motor
int Servo_pin = 12;		// Servo signal pin

#pragma endregion Servo Motor

#pragma region LEDs

int RFID_GREEN_LED  = 8;	// Green led pin
int RFID_RED_LED  = 9;		// Red led pin;

#pragma endregion LEDs

void setup()
{
	Serial.begin(9600);
	Wire.begin(); // join i2c bus (address optional for master)
	
	pinMode(BIP_PIN, OUTPUT);	// alarm biber
	digitalWrite(BIP_PIN, LOW);  // silence the alarm biber
	
#pragma region LEDs

	// Front door led status indicator for door lock
	pinMode(RFID_GREEN_LED, OUTPUT);	// Green led
	pinMode(RFID_RED_LED, OUTPUT);		// Red led

	// set door led state to closed 
	SetRfidLeds(true);

#pragma endregion LEDs

#pragma region DHT

	// Initialize device.
	dht.begin();
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	dht.humidity().getSensor(&sensor);
	delayMS = sensor.min_delay / 1000;		// Set delay between sensor readings based on sensor details.
	
#pragma endregion DHT

#pragma region RFID Scanner

  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  
// Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++)
  {
	  key.keyByte[i] = 0xFF;
  }
  
#pragma endregion RFID Scanner

#pragma region Servo Motor

	servo.attach(Servo_pin);	// servo
	servo.write(0);				// set servo position to 0

#pragma endregion Servo Motor
 
 
#pragma region LCD Display

  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

#pragma endregion LCD Display
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
		DhtSencorTemp = 0;
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
		DhtSencorHum = 0;
	}
	else
	{
		DhtSencorHum = (long)event.relative_humidity;
	}
	
#pragma endregion DHT Humidity

	// Alarm the user if conditions are critical
	if (DhtSencorTemp > 27 || DhtSencorHum > 70)
	{
		if (DhtSencorTemp > 27)
		{
			Serial.println("ALARM: The temperature is to high");
		}
		if (DhtSencorHum > 70)
		{
			Serial.println("ALARM: Humidity levels is to high");
		}
		makeBipSound(3); // ALARM sound
	}

#pragma endregion DHT

#pragma region LCD Display

	// Print a message to the LCD.

	lcd.setCursor(1,0);
	lcd.print("Temp: ");
	lcd.print(DhtSencorTemp);

	lcd.setCursor(1,1);
	lcd.print("Hum: ");
	lcd.print(DhtSencorHum);

#pragma endregion LCD Display

	// Send values to MKR WIFI 110 board
#pragma region Master Writer/Slave Receiver
  
  Wire.beginTransmission(4);		// transmit to device #4
  
  Wire.write("Temp: ");				// sends some bytes
  Wire.write(DhtSencorTemp);		// sends some bytes
  
  Wire.endTransmission();			// stop transmitting
  
  Wire.beginTransmission(4);		// transmit to device #4
  
  Wire.write("Hum: ");				// sends some bytes
  Wire.write(DhtSencorHum);		    // sends some bytes
  
  Wire.endTransmission();			// stop transmitting
	
#pragma endregion Master Writer/Slave Receiver

	// Ask slave (MKR WIFI 110 board) for data
#pragma region Master Receiver/Slave Writer
	
	Wire.requestFrom(4, 7);		// request 6 bytes from slave device #4

	int keyNumber = 0;
	//String keyword =  "";
	// slave may send less than requested
	//while (Wire.available()) 
	//{ 
		//char request_c = Wire.read();		// receive a byte as character
		//keyword += request_c;
	//}
	keyNumber = Wire.read();        // receive byte as an integer
	
	// Removes the last char in the received string
	//keyword = keyword.substring(0, keyword.length() - 1);
	 
	 Serial.println(keyNumber);
	 
	// Verify incoming data
	if (keyNumber == 42)
	{
		// toggle servo position
		moveServo();
	}


#pragma endregion Master Receiver/Slave Writer


#pragma region RFID lås (Hoveddør)

	isCardValid = 0;	   // set - reset state

	// Look for new cards, and select one if present
	if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() )
	{
		delay(50);
		isCardValid = 0;
	}
	else 
	{
		isCardValid = RfidValidater();

		// if card/chip is valid
		if (isCardValid == 1)
		{			
			// makes 1 small bib sound
			makeBipSound(1);
				
			// Move servo
			moveServo();
		}
		// if card/chip is not valid
		else if (isCardValid == 2)
		{	
			// makes 3 small bib sounds
			makeBipSound(2);
		}
	}
	
#pragma endregion RFID lås (Hoveddør)

  delay(1000);		// run loop every 1 sec
}


// This function adds RFID functionality to the program.
// - It can see if a card is present or not. 
// - it can return 3 states: 0 = null, 1 = true, -1 = false.
int RfidValidater() 
{

#pragma region reading card and format output

	// reading card
	String content= "";
	byte letter;
	for (byte i = 0; i < mfrc522.uid.size; i++)
	{
		//Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		//Serial.print(mfrc522.uid.uidByte[i], HEX);
		content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		content.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	
	// formating output
	content.toUpperCase();
	
#pragma endregion reading card and format output
	
#pragma region Validate card reading 

	// validation
	//if (content.substring(1) == Valid_RFID_Code) //change here the UID of the card/cards that you want to give access
	if (content.substring(1) == Valid_RFID_Code) //change here the UID of the card/cards that you want to give access
	{
		Serial.println();
		Serial.println("Authorized access");
		Serial.println();
		return 1;
	}
	else
	{
		Serial.println();
		Serial.println("Access denied");
		Serial.println();
		return 2;
	}
	
#pragma endregion Validate card reading 

}

// This function switches between high and low values each time it is called.
void SetRfidLeds(bool status)
{
	// sets the Front door status led's state
	if (status == false)
	{
		digitalWrite(RFID_GREEN_LED, LOW);	// Turn OFF GREEN LED
		digitalWrite(RFID_RED_LED, HIGH);	// Light up RED LED
	}
	if (status == true)
	{
		digitalWrite(RFID_GREEN_LED, HIGH);	// Light up GREEN LED
		digitalWrite(RFID_RED_LED, LOW);	// Turn OFF RED LED
	}
	delay(100);
}

// This function will simulate a lock opening or closing.
void moveServo()
{
	// oppen dør
	if ( servo.read() == 180 )
	{
		digitalWrite(Servo_pin, HIGH);
		servo.write(0);
		
		SetRfidLeds(true);		// red light off | green light onn
	}
	// Lås døren
	else if ( servo.read() == 0 )
	{
		digitalWrite(Servo_pin, LOW);
		servo.write(180);
		
		SetRfidLeds(false);		// red light on | green light off
	}
	// Correct servo error. (Set state to closed)
	else 
	{
		digitalWrite(Servo_pin, LOW);
		servo.write(180);
	}
	delay(100);
}

// This function is used for making sound feedback to the user
// - it takes an int between 1-3.
// - 1 = 1 short bib, 2 = 3 short bibs, 3 = NON STOP ALARM
void makeBipSound(int soundMode) 
{
	// 1 Short bib sound
	if (soundMode == 1)
	{
		digitalWrite(BIP_PIN, HIGH); // start alarm
		delay(100);
		digitalWrite(BIP_PIN, LOW); // silence the alarm 
	}
	// 3 short bib sound 
	else if (soundMode == 2)
	{
		// bibs 3 times
		for (int i = 0; i < 3;  i++)
		{
			digitalWrite(BIP_PIN, HIGH);	// start alarm
			delay(100);						// tone length
			digitalWrite(BIP_PIN, LOW);		// silence the alarm
			delay(50);						// Interval between tones
		}
	}
	// No stop bib sound (ALARM mode)
	else if (soundMode == 3)
	{
		digitalWrite(BIP_PIN, HIGH); // start alarm
	}
	delay(100);
}