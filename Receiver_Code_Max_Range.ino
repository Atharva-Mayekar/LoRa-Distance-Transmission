#include <LoRa.h>

// LoRa SPI Pins (fixed for ESP8266)
#define SS    15  // D8
#define RST   16  // D0
#define DIO0  2   // D4

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Receiver Host Starting...");

  // LoRa setup
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (1);
  }
  Serial.println("LoRa init succeeded.");

  // LoRa long-range optimized settings (must match TX)
  LoRa.setSpreadingFactor(12);         // Max range (SF12)
  LoRa.setTxPower(20);                 // Max power (20 dBm, for completeness — only TX matters)
  LoRa.setSignalBandwidth(62.5E3);     // 62.5 kHz bandwidth
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Packet Received ✅");

    Serial.print("Receiving Data: ");
    while (LoRa.available()) {
      String data = LoRa.readString();
      Serial.println(data);
    }
    Serial.println("-----------------------------------");
  }
}
