/*
 * RFID_Functions.cpp
 *
 * Created: 04/11/2021 09.00.47
 *  Author: kasjac
 */ 
#include <MFRC522.h>
#include <RFID_Scanner.h>
//#include "RfidKeys.h"

#pragma region RFID

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

MFRC522::MIFARE_Key key;

// Normally this would be in a separate .h file.
String Valid_RFID_Code = "30 45 66 A7";		// card =  30 45 66 A7 | chip = F7 DD 5A D3

#pragma endregion RFID


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
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
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
		//Serial.println("Authorized access");
		//Serial.println();
		return 1;
	}
	else
	{
		//Serial.println(" Access denied");
		return 2;
	}
	
#pragma endregion Validate card reading

}