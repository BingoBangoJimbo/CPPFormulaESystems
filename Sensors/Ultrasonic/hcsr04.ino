#define TRIG_PIN 12
#define ECHO_PIN 13

void setup() {
  // Set the TRIG_PIN as an output
  pinMode(TRIG_PIN, OUTPUT);
  // Set the ECHO_PIN as an input
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Set the TRIG_PIN low for 2 microseconds
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Set the TRIG_PIN high for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  // Set the TRIG_PIN low again
  digitalWrite(TRIG_PIN, LOW);

  // Read the ECHO_PIN and measure the time it takes for the
  // sound wave to travel to the object and back
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters using the speed of sound
  // (340 m/s or 29 microseconds per centimeter)
  long distance = duration / 29 / 2;

  // Print the distance to the serial monitor
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a brief moment before taking the next measurement
  delay(250);
}