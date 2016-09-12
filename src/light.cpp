#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "send_progmem.h"
#include "html_index.h"


#define HOSTNAME      "derhut" // mDNS-adress (http://HOSTNAME.local/)
#define SSID          "Der Hut"
#define PASSWD        "12341234"
#define REGISTER_PIN  4

ESP8266WebServer server(80);     // handles networking and provides http requests
const uint16_t led[] = {D1,D2,D3,D4,D6};

// Functions
void serveIndex();
void handleOther();

void setup(void){
  // Set up the debug connection
  Serial.begin(115200);

  uint8_t numled = sizeof(led)/sizeof(uint16_t); //number of leds
  for(int i=0; i<numled; i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }

  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  WiFi.softAP(SSID,PASSWD);
  // Set up HTTP-Server
  server.on("/",serveIndex);
  server.onNotFound(handleOther);
  server.begin();

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Set MDNS address ("hostname.local")
  if (!MDNS.begin(HOSTNAME,myIP)) {
    Serial.println("Fehler: MDNS fail");
  }

  Serial.println("Setup finished!");
  Serial.println("");
}

void loop(void){
  server.handleClient();
  delay(10);
  //Serial.println("free heap:" + String(ESP.getFreeHeap()));
}

void serveIndex(){
  server.send(200, "text/html", FPSTR(html_index));
  sendProgmem(&server,html_index);
}

void handleOther(){
  server.send(200, "text/html", "unknown");
}
