#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "AndroidHotspot2688";
const char* password = "qwerty00";
ESP8266WebServer server(80);


const int led = 14;
String s,s_head;

void handleRoot() {
  digitalWrite(led, LOW);
  s=s_head+"<h1>켜짐</h1><br>";
  server.send(200, "text/html", s);
  Serial.println("LED 불좀 켜주세요");
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setupWifi() {
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.println("LED 불은 꺼져있다."); 
  Serial.begin(115200);
  setupWifi();
  s_head="<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  s_head=s_head+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";
  server.on("/", handleRoot);
  server.on("/inline", [](){
    digitalWrite(led, HIGH);
    s=s_head+"<h1>꺼짐</h1><br>";
    server.send(200, "text/html", s);
    Serial.println("LED 불좀 꺼주세요");  
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
