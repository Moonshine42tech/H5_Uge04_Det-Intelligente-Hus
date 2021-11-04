/*
 * RFID_Scanner.cpp
 *
 * Created: 04/11/2021 09.09.07
 *  Author: kasjac
 */ 
// definitions
#define RST_PIN   5     // Configurable, see typical pin layout above
#define SS_PIN    53    // Configurable, see typical pin layout above

/* Set your new UID here! */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
	
int RfidValidater(void); 