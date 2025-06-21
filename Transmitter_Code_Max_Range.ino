#include <LoRa.h>

// LoRa SPI Pins (fixed for ESP8266)
#define SS    15  // D8
#define RST   16  // D0
#define DIO0  2   // D4

// Ultrasonic Pins
#define TRIG_PIN  4   // D2
#define ECHO_PIN  3   // RX (GPIO3)

// Transistor Control Pin
#define CONTROL_PIN 5  // D1

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Sender Host Starting...");

  // LoRa setup
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (1);
  }
  Serial.println("LoRa init succeeded.");

  // LoRa long-range optimized settings
  LoRa.setSpreadingFactor(12);         // Max range (SF12)
  LoRa.setTxPower(20);                 // Max power (20 dBm)
  LoRa.setSignalBandwidth(62.5E3);     // 62.5 kHz bandwidth

  // Ultrasonic pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Control pin for transistor
  pinMode(CONTROL_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN, LOW);  // Keep transistor OFF at boot

  delay(500); // Wait for boot to settle
  digitalWrite(CONTROL_PIN, HIGH); // Turn transistor ON after boot

  Serial.println("Transistor enabled, system ready.");
}

void loop() {
  long duration;
  float distance;

  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read pulse duration from Echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout to avoid lockup

  // Calculate distance in cm
  distance = (duration * 0.0343) / 2;

  Serial.print("Measured Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance via LoRa
  LoRa.beginPacket();
  LoRa.print(distance);
  LoRa.endPacket();

  delay(1000); // 1 second between readings
}
