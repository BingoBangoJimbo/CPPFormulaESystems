#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 4 on the Arduino
// LED wire is plugged into port 3 of the Arduino
#define ONE_WIRE_BUS 4
#define ledPin 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

void setup(void) {
  // start serial port
  Serial.begin(9600);
  
  // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++) 
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)) 
    {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } 
    else 
    {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
  Serial.println();
}
const int tempFLimit = 80;
void loop(void) { 
  sensors.requestTemperatures(); // Send the command to get temperatures
  int tempFHighest = -256;
  // Loop through each device, print out temperature data
  for(int i=0; i < numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)) 
    {
        // Output the device ID
        Serial.print("Temperature for device: ");
        Serial.println(i,DEC);
		
        float tempF = sensors.getTempF(tempDeviceAddress);

        // Print temp data;
        Serial.print("Temp F: ");
        Serial.println(tempF);

    if (tempF > tempFLimit)    
      {
        tempFHighest = tempF;
      } 

    if (tempFHighest > tempFLimit)
      {
        digitalWrite(ledPin, HIGH);
        Serial.println("Temp is over limit");      
      } 
    else
      {
        digitalWrite(ledPin, LOW);                  
      } 
    } 
  }
  Serial.println();
  delay(5000);
}


// function to print a device address
void printAddress(DeviceAddress deviceAddress) 
  {
  for (uint8_t i = 0; i < 8; i++) 
  {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}




