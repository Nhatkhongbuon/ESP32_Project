#include<Arduino.h>
#include<WiFi.h>
#include<ESPAsyncWebServer.h>
#include<AsyncTCP.h>
#include "SPIFFS.h"
const char* ssid = "Nguyen Phu Cau"; 
const char* password = "0904868337";

AsyncWebServer server(80);

void initSPIFFS() {
    if(!SPIFFS.begin(true)) {
        Serial.println("An error has occurred while mounting SPIFFS");
    } else {
        Serial.println("SPIFFS mounted successfully");
    }
}
void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    initWiFi();
    initSPIFFS();
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.serveStatic("/", SPIFFS, "/");
    server.begin();
}

void loop() {

}