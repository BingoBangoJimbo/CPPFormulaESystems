#include <FlexCAN_T4.h>

// Define CAN object
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;

// Define CAN message object
CAN_message_t msg;

void setup() {
    // Initialize serial monitor for debugging
    Serial.begin(115200);
    while (!Serial);

    // Begin CAN1 at 500 kbps (adjust speed if needed)
    can1.begin();
    can1.setBaudRate(250000);

    Serial.println("CAN Receiver Setup Complete");
}

void loop() {
    // Check if a new CAN message is available
    if (can1.read(msg)) {
        // Print the message ID
        Serial.print("Received message with ID: 0x");
        Serial.println(msg.id, HEX);

        // Print the data length
        Serial.print("Data Length: ");
        Serial.println(msg.len);

        // Print the data bytes
        Serial.print("Data: ");
        for (uint8_t i = 0; i < msg.len; i++) {
            Serial.print("0x");
            Serial.print(msg.buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

    delay(10); // Delay to avoid reading the same message multiple times
}
