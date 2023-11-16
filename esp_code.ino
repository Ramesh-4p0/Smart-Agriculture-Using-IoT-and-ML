#include <ESP8266WiFi.h>
#include <Servo.h>
int so = 0;
Servo sow;
int pos = 0;

WiFiClient client;
WiFiServer server(80);

void setup() {
  sow.attach(D6);

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("mphvrk", "vrk822003");
  Serial.println("connecting to wifi! ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(' ');
  Serial.print("IP Address = ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address = ");
  Serial.print(WiFi.macAddress());
  server.begin();

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() {
  client = server.available();
  if (client == 1) {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request == "GET /front HTTP/1.1") {
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
    }
    if (request == "GET /left HTTP/1.1") {
      digitalWrite(D1, HIGH);
      digitalWrite(D0, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      delay(1000);
      request = "GET /stop HTTP/1.1";
    }
    if (request == "GET /right HTTP/1.1") {
      digitalWrite(D2, HIGH);
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      delay(1000);
      request = "GET /stop HTTP/1.1";
    }
    if (request == "GET /back HTTP/1.1") {
      digitalWrite(D3, HIGH);
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D4, LOW);
    }
    if (request == "GET /stop HTTP/1.1") {
      digitalWrite(D4, HIGH);
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
    }

    if (request == "GET /plowingon HTTP/1.1") {
      digitalWrite(D6, HIGH);
      for (pos = 0; pos <= 90; pos += 1) {
        sow.write(pos);
        delay(15);
      }
    }
    if (request == "GET /plowingoff HTTP/1.1") {
      digitalWrite(D6, HIGH);
      for (pos = 90; pos >= 0; pos -= 1) {
        sow.write(pos);
        delay(15);
      }
    }
    if (request == "GET /sowingon HTTP/1.1") {
      digitalWrite(D5, HIGH);
    }
    if (request == "GET /sowingoff HTTP/1.1") {
      digitalWrite(D5, LOW);
    }
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type:L text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Remote Controller</title>");
  client.println("</head>");
  client.println("<body>");

  client.println("<h1>Remote Controller</h1>");
  client.println("<h3>Control</h3>");
  client.println("<br>");
  client.println("<a href=\"/front\"\"><button><b>FRONT</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/left\"\"><button><b>LEFT</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/right\"\"><button><b>RIGHT</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/back\"\"><button><b>BACK</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/stop\"\"><button><b>STOP</b></button></a>");
  client.println("<br>");
  client.println("<br>");
  client.println("<h3>Work</h3>");

  client.println("<br>");
  client.println("<a href=\"/plowingon\"\"><button><b>PLOWING ON</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/plowingoff\"\"><button><b>PLOWING OFF</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

  client.println("<br>");
  client.println("<a href=\"/sowingon\"\"><button><b>SOWING ON</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("<a href=\"/sowingoff\"\"><button><b>SOWING OFF</b></button></a>");
  client.println("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  client.println("</body>");
  client.println("</html>");
}
