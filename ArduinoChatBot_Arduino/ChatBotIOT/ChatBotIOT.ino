#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>

const char ssid1[] = "foxx-house";
const char pass1[] = "nuevo1234567891234";
//const char ssid2[] = "ALSW2";
//const char pass2[] = "7210-3607";
//const char ssid3[] = "ssid";
//const char pass3[] = "pass";

WiFiClient net;
MQTTClient client;

int Foco2 = 3;
int Foco = 2;
unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    //digitalWrite(Led, 0);
   // delay(100);
   // digitalWrite(Led, 1);
    delay(100);
    Serial.print(".");
  }
{
  Serial.print("\nConectando con MQTT...");
  while (!client.connect("dell_house", "laptdell", "123andress")) {
    //digitalWrite(Led, 0);
   // delay(1000);
    //digitalWrite(Led, 1);
    delay(1000);
    Serial.print("*");
  }
  Serial.println("\nConectado :D/ !");
  client.subscribe("/fh/Foco/casa");
  }
  {
Serial.print("\nConectando con MQTT...");
  while (!client.connect("dell_house", "housefox", "123andres")) {
    //digitalWrite(Led, 0);
   // delay(1000);
    //digitalWrite(Led, 1);
    delay(1000);
    Serial.print("*");
  }
  Serial.println("\nConectado :D !");
  client.subscribe("/dll/Foco/casa");
  
}}

void RecibirMensaje(String &topic, String &payload ){
  Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(Foco, 1);
    Serial.println(" Activada");
  }
  else {
    digitalWrite(Foco, 0);
    Serial.println(" Desactivada");
  }

}

void RecibirMensaje2(String &topic, String &payload ){
  Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(Foco2, 1);
    Serial.println(" Activada");
  }
  else {
    digitalWrite(Foco2, 0);
    Serial.println(" Desactivada");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Foco2, OUTPUT);
  pinMode(Foco, OUTPUT);
  digitalWrite(Foco2, 0);
  digitalWrite(Foco, 0);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
//  wifiMulti.addAP(ssid2, pass2);
//  wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMensaje);
  client.onMessage(RecibirMensaje2);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
}
