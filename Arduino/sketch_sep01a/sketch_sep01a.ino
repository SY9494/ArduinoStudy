#include <ESP8266WiFi.h>

const char* ssid = "AndroidHotspot2688";
const char* password = "qwerty00";

WiFiServer server(80);


void setup() {

  Serial.begin(9600);
  delay(10);
  

  Serial.println();
  Serial.println();
  Serial.print("연결 중 : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("와이파이 연결에 성공하였습니다.");
  server.begin();
  Serial.println("서버를 활성화합니다.");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  String s="<html>";
  s=s+"<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  s=s+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";
  s=s+"<head></head><body>웹 서버가 돌아가고 있습니다.</body></html>";
  client.print(s);
  delay(1);
  Serial.println("클라이언트가 접속을 종료하였습니다.");
}
