#include <WiFi.h>
#include <PubSubClient.h>

// Configuración de WiFi
const char* ssid = "YOURWIFI";           // Cambia por el nombre de tu red WiFi
const char* password = "YOURPASS"; // Cambia por la contraseña de tu WiFi

// Configuración del broker MQTT
const char* mqttServer = "IP"; // Cambia por la dirección IP de tu broker MQTT
const int mqttPort = 1883;               // Cambia si tu broker utiliza un puerto diferente

WiFiClient espClient;
PubSubClient client(espClient);

// Tópico MQTT
const char* topic = "esp32/SOILHUM";

void setup() {
  // Inicializar el puerto serie
  Serial.begin(115200);

  // Conectar al WiFi
  conectarWiFi();

  // Configurar el cliente MQTT
  client.setServer(mqttServer, mqttPort);

  // Intentar conectar al broker MQTT
  conectarMQTT();
}

void loop() {
  // Asegurar que la conexión MQTT sigue activa
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Generar un valor aleatorio de humedad
  int humedad = random(0, 101);

  // Convertir el valor a un string para enviar por MQTT
  char mensaje[8];
  snprintf(mensaje, sizeof(mensaje), "%d", humedad);

  // Publicar el mensaje en el tópico
  client.publish(topic, mensaje);
  Serial.print("Publicado: ");
  Serial.println(mensaje);

  // Esperar 1 segundo antes de enviar el siguiente mensaje
  delay(1000);
}

void conectarWiFi() {
  Serial.print("Conectando a WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.println("Conectando al broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado al broker MQTT");
    } else {
      Serial.print("Fallo en la conexión. Estado: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void reconnect() {
  // Intentar reconectar si la conexión MQTT se pierde
  while (!client.connected()) {
    Serial.println("Intentando reconectar al broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Reconexión exitosa");
    } else {
      Serial.print("Fallo en la reconexión. Estado: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}
