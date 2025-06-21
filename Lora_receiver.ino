#include <LoRa.h>

#define SS    15  // LoRa NSS
#define RST   16  // LoRa Reset
#define DIO0  2   // LoRa DIO0

#define LED_BUILTIN 2   // Built-in LED on ESP8266 (GPIO2 / D4)

unsigned long lastPacketTime = 0;
unsigned long currentTime = 0;
const unsigned long timeout = 5000;  // 5 seconds timeout

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Receiver Host Starting...");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // LED OFF initially

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections!");
    while (1);
  }

  Serial.println("LoRa Receiver Ready.");
  lastPacketTime = millis();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  currentTime = millis();

  if (packetSize) {
    Serial.println("Connected: Packet Received ✅");

    Serial.print("Receiving Data: ");
    while (LoRa.available()) {
      String data = LoRa.readString();
      Serial.println(data);
    }
    Serial.println("------------------------------------");

    digitalWrite(LED_BUILTIN, HIGH);  // Turn ON LED when connected
    lastPacketTime = currentTime;
  }

  // If no packet received within timeout, turn OFF LED and show message
  if (currentTime - lastPacketTime > timeout) {
    Serial.println("Waiting for connection...");
    digitalWrite(LED_BUILTIN, LOW);  // Turn OFF LED
    lastPacketTime = currentTime;    // reset timer to avoid flooding
  }

  delay(10);  // Prevent watchdog reset
}
