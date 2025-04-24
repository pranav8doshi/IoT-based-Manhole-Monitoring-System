#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);
#define MA1 D0
#define MA2 D1
#define MB1 D2
#define MB2 D3
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    WiFi.begin("Tenda", "12345678");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("NodeMCU is Connected");
    Serial.println(WiFi.localIP());
    server.begin();
    pinMode(MA1, OUTPUT);
    pinMode(MA2, OUTPUT);
    pinMode(MB1, OUTPUT);
    pinMode(MB2, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    client = server.available();
    if (client == 1)
    {
        String request = client.readStringUntil('\n');
        Serial.println(request);
        request.trim();
    
    while (request == "GET /front HTTP/1.1")
    {
        digitalWrite(MA1, LOW);
        digitalWrite(MA2, HIGH);
        digitalWrite(MB1, LOW);
        digitalWrite(MB2, HIGH);
        client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /back HTTP/1.1" || request == "GET /left HTTP/1.1" || request == "GET /right HTTP/1.1"|| request == "GET /stop HTTP/1.1")
                break;
        }
    }
  while (request == "GET /back HTTP/1.1")
    {
        digitalWrite(MA2, LOW);
        digitalWrite(MA1, HIGH);
        digitalWrite(MB1, HIGH);
        digitalWrite(MB2, LOW);
        client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /front HTTP/1.1" || request == "GET /left HTTP/1.1" || request == "GET /right HTTP/1.1"|| request == "GET /stop HTTP/1.1")
                break;
        }
    }
    while (request == "GET /right HTTP/1.1")
    {
        digitalWrite(MA1, HIGH);
        digitalWrite(MA2, LOW);
        digitalWrite(MB2, LOW);
        digitalWrite(MB1, LOW);client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /back HTTP/1.1" || request == "GET /left HTTP/1.1" || request == "GET /front HTTP/1.1"|| request == "GET /stop HTTP/1.1")
                break;
        }
    }
    while (request == "GET /left HTTP/1.1")
    {
        digitalWrite(MB1, HIGH);
        digitalWrite(MB2, LOW);
        digitalWrite(MA2, LOW);
        digitalWrite(MA1, LOW);client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /back HTTP/1.1" || request == "GET /front HTTP/1.1" || request == "GET /right HTTP/1.1"|| request == "GET /stop HTTP/1.1")
                break;
        }
    }
    while (request == "GET /stop HTTP/1.1")
    {
        digitalWrite(MA1, LOW);
        digitalWrite(MA2, LOW);
        digitalWrite(MB1, LOW);
        digitalWrite(MB2, LOW);
        client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /back HTTP/1.1" || request == "GET /left HTTP/1.1" || request == "GET /right HTTP/1.1"|| request == "GET /front HTTP/1.1")
                break;
        }
    }
}}
