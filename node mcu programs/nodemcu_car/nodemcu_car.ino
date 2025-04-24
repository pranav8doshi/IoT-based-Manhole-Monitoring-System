//
//#include <ESP8266WiFi.h>

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
    WiFi.begin("Vivo", "11111111");
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
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
    digitalWrite(MA2, LOW);
    digitalWrite(MA1, LOW);
    Serial.println("Stop");
}

void loop()
{
    //  put your main code here, to run repeatedly:
    //  client = server.available();
    //  if (client == 1)
    //  {
    //    String request = client.readStringUntil('\n');
    //    Serial.println(request);
    //    request.trim();
    //  }
    while (true)
    {
        client = server.available();
        if (client == 1)
        {
            String request = client.readStringUntil('\n');
            Serial.println(request);
            request.trim();
            if (request == "GET /F HTTP/1.1")
            {
                digitalWrite(MA1, LOW);
                digitalWrite(MA2, HIGH);
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, HIGH);
                Serial.println("Front");
                delay(1000); // Wait for 5 seconds
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
            }
            if (request == "GET /B HTTP/1.1")
            {
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, HIGH);
                digitalWrite(MB1, HIGH);
                digitalWrite(MB2, LOW);
                Serial.println("Back");
                delay(1000); // Wait for 5 seconds
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
            }
            if (request == "GET /R HTTP/1.1")
            {
                digitalWrite(MA1, HIGH);
                digitalWrite(MA2, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MB1, LOW);
                delay(900); // Wait for 5 seconds
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
            }
            if (request == "GET /L HTTP/1.1")
            {
                digitalWrite(MB1, HIGH);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
                Serial.println("Left");
                delay(900); // Wait for 5 seconds
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
            }
            if (request == "GET /S HTTP/1.1")
            {
                digitalWrite(MB1, LOW);
                digitalWrite(MB2, LOW);
                digitalWrite(MA2, LOW);
                digitalWrite(MA1, LOW);
                Serial.println("Stop");
                delay(1000); // Wait for 5 seconds
            }
        }
    }
}
