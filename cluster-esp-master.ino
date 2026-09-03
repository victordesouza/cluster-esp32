#include <WiFi.h>
const char* ssid = "ESP32_CLUSTER"; 
const char* password = "12345678";
IPAddress local_IP(192, 168, 50, 1);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("=== ESP32 CLUSTER MASTER ===");
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Erro ao configurar IP do AP");
    return;
  }
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Erro ao criar Access Point");
    return;
  }
  Serial.println("Rede criada!");
  Serial.print("SSID: ");
  Serial.println(ssid); 
  Serial.print("IP do Master: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  delay(1000);
}

