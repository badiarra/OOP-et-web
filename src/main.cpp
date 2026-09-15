#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include "led/Led.h"

//Les broches des deux Dels
const int LED1_PIN = 41;
const int LED2_PIN = 42;

//Creation des objets Led
Led led1(LED1_PIN);
Led led2(LED2_PIN);

//Configuration du réseau Wi-Fi
const char* ssid = "TGE-IOT";
const char* password = "iOTN3t$$";

WebServer server(80);


//Lecture du fichier html

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

//Lecture du fichier CSS
void handleCSS() {
  File file = LittleFS.open("/style.css", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open style.css");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

//Lecture du fichier JS
void handleJS() {
  File file = LittleFS.open("/script.js", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open script.js");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

//Etat des dels

void handleLedState(){
  //
  JsonDocument doc;

  doc["led1"]=led1.getState()?"ON":"OFF";
  doc["led2"]=led2.getState()?"ON":"OFF";
  String response;
  serializeJson(responseDoc, response);
  server.send(200, "application/json", response);
}

//Gestion des requêtes pour allumer/éteindre les Dels
void handleLedControl() {
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"error\":\"No JSON data received\"}");
    return;
  }

  String jsonData = server.arg("plain");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonData);

  if (error) {
    server.send(400, "application/json", "{\"error\":\"Failed to parse JSON\"}");
    return;
  }


  if (!doc["led1"].isNull()) {   // if (doc["led1"].is<JsonVariant>()) {  // if (doc.containsKey("led1")) {
    led1.toggle();
  } 

  if (!doc["led2"].isNull()) {    //if (doc.containsKey("led2")) {
    led2.toggle();
  }

  // Réponse JSON
  JsonDocument responseDoc;
  responseDoc["led1"] = led1.getState() ? "ON" : "OFF";
  responseDoc["led2"] = led2.getState() ? "ON" : "OFF";

  String responseData;
  serializeJson(responseDoc, responseData);
  server.send(200, "application/json", responseData);
}

void setup() {

  Serial.begin(115200);

  delay(3000); // Attendre que le port série soit prêt


  //Initialisation des Dels
  led1.init();
  led2.init();

  if (!LittleFS.begin(true))
  {
    Serial.println("Erreur lors du montage de LittleFS !");
    return;
  }

  Serial.println("LittleFS monté avec succès.");

  
  // ===============================
  // Connexion au WiFi
  // ===============================
  Serial.print("Connexion au WiFi : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
 
//Les routes 
  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/script.js", handleJS);

  server.on("/led-control", HTTP_POST, handleLedControl);
  server.on("/led-state", handleLedState)

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}


