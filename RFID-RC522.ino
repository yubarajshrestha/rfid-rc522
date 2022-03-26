// Include Libraries
#include "Arduino.h"
#include "RFID.h"


// Pin Definitions
#define RFID_PIN_RST  2
#define RFID_PIN_SDA  10



// Global variables and defines

// object initialization
RFID rfid(RFID_PIN_SDA,RFID_PIN_RST);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //initialize RFID module
    rfid.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    String lastTag = "";
    
    if(menuOption == '1') {
      // RFID Card Reader - RC522 - Test Code
      //Read RFID tag if present
      String rfidtag = rfid.readTag();
      //print the tag to serial monitor if one was discovered
      if(rfidtag != lastTag) {
        lastTag = rfidtag;
        rfid.printTag(rfidtag);
      }
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) RFID Card Reader - RC522"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing RFID Card Reader - RC522"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
