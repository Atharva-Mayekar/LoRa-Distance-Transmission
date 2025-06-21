#include <LoRa.h>

// LoRa module pin connections to ESP8266
#define SS    15  // LoRa NSS
#define RST   16  // LoRa Reset
#define DIO0  2   // LoRa DIO0 (interrupt pin)

String data = "Atharva Mayekar";

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial monitor to open

  Serial.println("LoRa Transmitter Starting...");

  // Initialize LoRa module with pin definitions
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections!");
    while (true); // Stop here if failed
  }

  Serial.println("LoRa Transmitter Ready.");
}

void loop() {
  Serial.print("Sending Data: ");
  Serial.println(data);

  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  Serial.println("Status: Data Sent");
  delay(3000);  // Wait 3 seconds before sending next packet
}
