#include <WiFi.h> 
const char* ssid = "ESP32_CLUSTER";
const char* password = "12345678";
IPAddress local_IP(192, 168, 50, 101);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress masterIP(192, 168, 50, 1);
WiFiClient client;

void TaskWorker(void *pvParameters) {
  for (;;) {
    if (!client.connected()) {
      Serial.println("Conectando ao Master...");
      if (client.connect(masterIP, 5000)) {
        Serial.println("Conectado ao Master!");
      }
      else {
        Serial.println("Falha na conexão");
      }
    }
    if (client.connected()) { 
      client.println("WORKER 101 READY");
      if (client.available()) {
        String msg = client.readStringUntil('\n');
        Serial.print("Master: ");
        Serial.println(msg);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.config(
  local_IP,
  gateway,
  subnet
  );
  WiFi.begin(
  ssid,
  password
  );
  Serial.println("=== WORKER 101 ==="); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  xTaskCreate(
  TaskWorker,
  "Worker",
  4096,
  NULL,
  2,
  NULL
  );
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
} 