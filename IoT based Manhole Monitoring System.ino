#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <ESP8266HTTPClient.h>

#define LM35PIN D0 // Analog pin for LM35
#define MQ2PIN A0  // Analog pin for MQ2
#define LED D2
#define TILT_SENSOR_PIN D6 
#define TRIGGER_PIN D4
#define ECHO_PIN D5

#define WIFI_SSID "VIVO" // Your WiFi SSID
#define WIFI_PASSWORD "11111111" // Your WiFi password
#define THINGSPEAK_API_KEY "1SVO3JHGPOYZRK38" // ThingSpeak API key
#define THINGSPEAK_CHANNEL_ID 2297207 // ThingSpeak Channel ID

WiFiClient Client;

bool tiltDetected = false;
float sensorValue;
void gas_trigger() {
  WiFiClient client;
  if (!client.connect("maker.ifttt.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(String("GET /trigger/gas_leak/json/with/key/cPvqQ-19Y_6uoEMnHpvxnSnbQyr83yhpuj6eqQkdePT") + " HTTP/1.1\r\n" +
               "Host: maker.ifttt.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  Serial.println("Gas Leak Alert Triggered");
}

void tilt_trigger() {
  WiFiClient client;
  if (!client.connect("maker.ifttt.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(String("GET /trigger/lid_tilted/json/with/key/cPvqQ-19Y_6uoEMnHpvxnSnbQyr83yhpuj6eqQkdePT") + " HTTP/1.1\r\n" +
               "Host: maker.ifttt.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  Serial.println("Lid Tilt Alert Triggered");
}

void temp_trigger() {
  WiFiClient client;
  if (!client.connect("maker.ifttt.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(String("GET /trigger/temperature_threshold/json/with/key/cPvqQ-19Y_6uoEMnHpvxnSnbQyr83yhpuj6eqQkdePT") + " HTTP/1.1\r\n" +
               "Host: maker.ifttt.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  Serial.println("Temperature Threshold Alert Triggered");
}

void overflow_trigger() {
  WiFiClient client;
  if (!client.connect("maker.ifttt.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(String("GET /trigger/waterlevel_overflow/json/with/key/cPvqQ-19Y_6uoEMnHpvxnSnbQyr83yhpuj6eqQkdePT") + " HTTP/1.1\r\n" +
               "Host: maker.ifttt.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  Serial.println("Water Level Overflow Alert Triggered");
}
void sms_alert() {
  WiFiClient client;
  if (!client.connect("maker.ifttt.com", 80)) {
    Serial.println("Connection failed");
    return;
  }

  // Correctly URL-encoded version of "!!!!Manhole Crisis"
  String encodedEvent = "!!!!Manhole%20Crisis";

  client.print(String("GET /trigger/") + encodedEvent + String("/json/with/key/cPvqQ-19Y_6uoEMnHpvxnSnbQyr83yhpuj6eqQkdePT") + " HTTP/1.1\r\n" +
               "Host: maker.ifttt.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(10); // Allow time for the request to process
  Serial.println("Manhole Crisis Alert Triggered");
}


void setup() {
  Serial.begin(9600);
  
  // Initialize pin modes
  pinMode(TILT_SENSOR_PIN, INPUT_PULLUP); 
  pinMode(LED, OUTPUT); 
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

float readLM35Temperature() {
  int analogValue = analogRead(LM35PIN); // Read from LM35
  float millivolts = (analogValue/10240.0) * 3300; //3300 is the voltage provided by NodeMCU
float celsius = millivolts/10;
 return celsius+4;
}

float getUltrasonicDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the response pulse
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  float distance = (duration * 0.034) / 2; 
  return distance;
}
void loop() {
  delay(2000); // Delay for pacing the loop

  float temperature = readLM35Temperature(); // Get temperature from LM35
  sensorValue = analogRead(MQ2PIN); // Read gas concentration
  int tiltValue = digitalRead(TILT_SENSOR_PIN); // Check tilt sensor
  float distance = getUltrasonicDistance(); // Get distance from ultrasonic sensor
  bool flag=0;
  // Log data to Serial for debugging
  Serial.print("Temperature (C): ");
  Serial.println(temperature);
  Serial.print("Tilt Value: ");
  Serial.println(tiltValue);
  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);
  Serial.print("Water Level (cm): ");
  Serial.println(distance);

  // Check conditions and send HTTP alerts
  if (sensorValue > 800) 
  {
    gas_trigger();
    flag=1;
  }
  if(tiltValue==1)
  {
    tilt_trigger();
    flag=1;
    digitalWrite(LED,1);
  }
  if(distance<10)
  {
    overflow_trigger();
    flag=1;
  }
  if(temperature>60)
  {
    temp_trigger();
    flag=1;
  }
  if(flag==1)
  {
    sms_alert();
  }
  // Send data to ThingSpeak
  ThingSpeak.begin(Client);
  ThingSpeak.setField(1, temperature); // Field for temperature
  ThingSpeak.setField(2, tiltDetected ? 1 : 0); // Field for tilt status
  ThingSpeak.setField(3, distance); // Field for distance
  ThingSpeak.setField(4, sensorValue); // Field for gas concentration

  int status = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_API_KEY); // Send to ThingSpeak

  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.println("Failed to send data to ThingSpeak.");
  }
  
  delay(2000); // Delay before the next loop iteration
}