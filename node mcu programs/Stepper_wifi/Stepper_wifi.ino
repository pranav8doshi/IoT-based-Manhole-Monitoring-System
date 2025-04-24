#include <Stepper.h>
#include <ESP8266WiFi.h>

Stepper my_Stepper(200, D1, D2, D3, D4);

WiFiClient client;
WiFiServer server(80);
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  /// WiFi.begin("Airtel-MyWiFi-AMF-311WW-CCFB", "1b0b4bd4");
  WiFi.begin("OnePlus", "j4ixpx46");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("NodeMCU is Connected");
  Serial.println(WiFi.localIP());
  server.begin();
  my_Stepper.setSpeed(200); // Speed for stepper motor
}

void Stepper1(int Direction, int Rotation)
{                                              // Function for stepper motor control with 2 parameters
  my_Stepper.step(Direction * Rotation * 200); // 200 steps is 360 degrees, multiply by Rotation for full rotations
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
  }
  while (true)
  {
    client = server.available();
    if (client == 1)
    {
      String request = client.readStringUntil('\n');
      Serial.println(request);
      request.trim();
      if (request == "GET /R HTTP/1.1")
      {
        // Rotate stepper motor 360 degrees to the left
        Stepper1(1, 1); // Stepper motor rotates 1 time (360 degrees) right
        Serial.println("Right turn");
        delay(1000); // Wait for 5 seconds
      }
      if (request == "GET /L HTTP/1.1")
      {
        // Rotate stepper motor 360 degrees to the left
        Stepper1(-1, 1); // Stepper motor rotates 1 time (360 degrees) right
        Serial.println("Left turn");
        delay(1000); // Wait for 5 seconds
      }
      if (request == "GET /S HTTP/1.1")
      {
        // Rotate stepper motor 360 degrees to the left
        Stepper1(1, 0); // Stepper motor rotates 1 time (360 degrees) right
        Serial.println("Stop");
        delay(1000); // Wait for 5 seconds
      }
    }
  }
}