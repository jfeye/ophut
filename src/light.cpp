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

uint8_t numled;

// Functions
void serveIndex();
void handleSet();
void handleOther();

void setup(void){
  // Set up the debug connection
  Serial.begin(115200);

  numled = sizeof(led)/sizeof(uint16_t); //number of leds
  for(int i=0; i<numled; i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }

  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  WiFi.softAP(SSID,PASSWD);
  // Set up HTTP-Server
  server.on("/",serveIndex);
  server.on("/set",handleSet);
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
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send ( 200, "text/plain", message );
}

void handleSet(){
  uint8_t l = 255; //led index
  uint8_t b = 255; //led brightness

  for (uint8_t i=0; i < server.args(); i++) {
    if(server.argName(i) == "led") l = atoi(server.arg(i).c_str()); //set next led index
    else if(server.argName(i) == "b"){
      b = atoi(server.arg(i).c_str());
      if(l < numled) analogWrite(led[l], b);
      l = 255;
    }
  }

  server.send ( 200, "text/plain", "OK" );
}
