#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <BH1750FVI.h>
#define WIFI_SSID "Telstra1AA87A"
#define WIFI_PASSWORD "rqp2vsnk44b7unk4"
#define MQTT_SERVER "12e2770e12f3437bacae95f715b07c81.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_TOPIC "Arduino"
#define MQTT_USER "hivemq.webclient.1748318755220"
#define MQTT_PASSWORD "Y.n?j3S2shV04xGO%o,U"
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
WiFiSSLClient wifiSSLClient;
PubSubClient mqttClient(wifiSSLClient);

void connectMQTT() {
   while (!mqttClient.connected()) {
       Serial.println("Connecting to MQTT");
       if (mqttClient.connect("ArduinoNanoIoT", MQTT_USER, MQTT_PASSWORD)) {
           Serial.println("Connected to MQTT Broker!");
       } else {
           Serial.print("Failed, rc=");
           Serial.print(mqttClient.state());
           Serial.println(" Retrying in 5 seconds...");
           delay(5000);
       }
   }
}
void setup() {
   Serial.begin(115200);
   LightSensor.begin();
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
       delay(1000);
       Serial.println("Connecting to WiFi...");
   }
   Serial.println("Connected to WiFi");
   mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
   connectMQTT();
}
void loop() {
   if (!mqttClient.connected()) {
       connectMQTT();
   }
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.println(lux);
  delay(250);
   if(lux >= 1000) {
       Serial.println("Sunlight detected!");
       mqttClient.publish(MQTT_TOPIC, "Sunlight detected");
       while(lux >= 1000){
      lux = LightSensor.GetLightIntensity();
      delay(10000);
       }
   } else {
       Serial.println("No sunlight detected");
       mqttClient.publish(MQTT_TOPIC, "sunlight=0");
       while(lux < 1000){
      lux = LightSensor.GetLightIntensity();
       delay(10000);
       }
   }
   delay(5000);
}