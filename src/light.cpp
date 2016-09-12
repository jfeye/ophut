#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#define HOSTNAME      "derhut" // mDNS-adress (http://HOSTNAME.local/)
#define SSID          "Der Hut"
#define PASSWD        "12341234"
#define REGISTER_PIN  4

ESP8266WebServer server(80);     // handles networking and provides http requests

// Functions
void handleWeb();

void setup(void){
  // Set up the debug connection
  Serial.begin(115200);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);


  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  WiFi.softAP(SSID,PASSWD);
  // Set up HTTP-Server
  server.onNotFound(handleWeb);
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
  delay(100);
  //Serial.println("free heap:" + String(ESP.getFreeHeap()));
}

void handleWeb(){
	server.send(200, "text/html", "<h1>You are connected</h1>");
  Serial.println("request!");
}

/*void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open.
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}*/
