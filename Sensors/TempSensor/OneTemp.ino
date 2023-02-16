#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the serial monitor
  Serial.begin(9600);
  // Start up the temperature sensor library
  sensors.begin();

}

void loop() {
  // Request a temperature reading from each sensor
  sensors.requestTemperatures();

  // Iterate through the list of sensors and print the temperature for each one
  
  float temperature = sensors.getTempFByIndex(0);
  Serial.print("Temp: ");

  Serial.print(temperature);
  Serial.println("°F");


  // Wait for a brief moment before taking the next measurement
  delay(1000);
}