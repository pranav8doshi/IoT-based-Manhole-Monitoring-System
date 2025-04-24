#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
WiFiClient client;

long myChannelNumber = 2232587;

//const char myWriteAPIKey[] = "AP62XBI9VY93MP16";
const char myWriteAPIKey[] = "8S2XSMMNXPESH4BN";

//Code to read temperature
const int sensor=A0; // Assigning analog pin A0 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading


//Code to set-up wi-fi
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

WiFi.begin("vivo 1907","11111111");
while(WiFi.status() !=WL_CONNECTED)
{delay(100);
Serial.print(".");
}
Serial.println();
Serial.println("NodeMCU is Connected");
Serial.println(WiFi.localIP());
ThingSpeak.begin(client);
pinMode(sensor,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
vout=analogRead(sensor);
vout=(vout*500)/1024-18;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 
  Serial.println("Temperature in C: " + (String) tempc);
  Serial.println("Temperature in F: " + (String) tempf);
  ThingSpeak.writeField(myChannelNumber, 1, tempc, myWriteAPIKey);
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 2, tempf, myWriteAPIKey);
  delay(100);
}
