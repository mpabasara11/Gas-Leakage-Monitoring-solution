#include <Buzzer.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

//SSID and Password of WiFi router
const char* ssid = "SLT-ADSL-15958";
const char* password = "mngPassword147";

//buzzer pins config
int buz1 = D0;
int buz2 = D1;

//sensor digital pins
int sen1 = D2;
int sen2 = D3;

//rgb pins sensor 1
int redOne = D6;
int greenOne = D5;
int blueOne = D4;

//rgb pins sensor 2
int redTwo = D7;
int greenTwo = D8;
int blueTwo = 10;

String sensorTwoValue = "";
String sensorOneValue = "";
String sensorOnePower = "";
String sensorTwoPower = "";

ESP8266WebServer server(80);

//handle web page
void handleRoot()
{
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

//gas sensor 1 values pass to server
void handleMeter1() {
  String adcValue1 = String(sensorOneValue);
  server.send(200, "text/plane", adcValue1);
}

//gas sensor 2 values pass to server
void handleMeter2()
{
  String adcValue2 = String(sensorTwoValue);
  server.send(200, "text/plane", adcValue2);
}

//sensor 1 power
void meterOneP() {
  String ledState = "OFF";
  String t_state = server.arg("MeterOneState");
  Serial.println(t_state);
  if (t_state == "1")
  {
    ledState = "ON";
  }
  else
  {
    ledState = "OFF";
  }
  server.send(200, "text/plane", ledState);
  sensorOnePower = ledState;
}

//sensor 2 power
void meterTwoP() {
  String ledState = "OFF";
  String t_state = server.arg("MeterTwoState");
  Serial.println(t_state);
  if (t_state == "1")
  {
    ledState = "ON";
  }
  else
  {
    ledState = "OFF";
  }
  server.send(200, "text/plane", ledState);
  sensorTwoPower = ledState;
}

//read sensors according to sensor power states
void sensorRead() {
  int sn1 = digitalRead(sen1);
  int sn2 = digitalRead(sen2);

  //sensor 1
  if (sensorOnePower == "ON")
  {
    if (sn1 == 0)
    {
      sensorOneValue = "Gas Detected !!";
    }
    else
    {
      sensorOneValue = "Normal";
    }
  }
  else if (sensorOnePower == "OFF")
  {
    sensorOneValue = "";
  }

  //sensor 2
  if (sensorTwoPower == "ON")
  {
    if (sn2 == 0)
    {
      sensorTwoValue = "Gas Detected !!";
    }
    else
    {
      sensorTwoValue = "Normal";
    }
  }

  else if (sensorTwoPower == "OFF")
  {
    sensorTwoValue = "";
  }
}

void bNotify()
{
  if (sensorOneValue == "Gas Detected !!" && sensorTwoValue == "Gas Detected !!")
  {
    digitalWrite(buz1, HIGH);
    digitalWrite(buz2, HIGH);
  }
  else if (sensorOneValue == "Gas Detected !!")
  {
    digitalWrite(buz1, HIGH);
    delay(300);
    digitalWrite(buz1, LOW);
    delay(100);
  }
  else if (sensorTwoValue == "Gas Detected !!")
  {
    digitalWrite(buz2, HIGH);
    delay(300);
    digitalWrite(buz2, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(buz1, LOW);
    digitalWrite(buz2, LOW);
  }
}

void lNotify()
{
  //sensor 1 rgb
  if (sensorOnePower == "") {
    digitalWrite(redOne, LOW);
    digitalWrite(greenOne, LOW);
    digitalWrite(blueOne, HIGH);
  }
  else if (sensorOnePower == "OFF")
  {
    digitalWrite(redOne, LOW);
    digitalWrite(greenOne, LOW);
    digitalWrite(blueOne, HIGH);
  }
  else if (sensorOnePower == "ON" && sensorOneValue == "Normal")
  {
    digitalWrite(redOne, LOW);
    digitalWrite(blueOne, LOW);
    digitalWrite(greenOne, HIGH);
  }
  else if (sensorOnePower == "ON" && sensorOneValue == "Gas Detected !!")
  {
    digitalWrite(blueOne, LOW);
    digitalWrite(greenOne, LOW);
    digitalWrite(redOne, HIGH);
  }


  //sensor 2 rgb
  if (sensorTwoPower == "")
  {
    digitalWrite(redTwo, LOW);
    digitalWrite(greenTwo, LOW);
    digitalWrite(blueTwo, HIGH);
  }
  else if (sensorTwoPower == "OFF")
  {
    digitalWrite(redTwo, LOW);
    digitalWrite(greenTwo, LOW);
    digitalWrite(blueTwo, HIGH);
  }
  else if (sensorTwoPower == "ON" && sensorTwoValue == "Normal")
  {
    digitalWrite(redTwo, LOW);
    digitalWrite(blueTwo, LOW);
    digitalWrite(greenTwo, HIGH);
  }
  else if (sensorTwoPower == "ON" && sensorTwoValue == "Gas Detected !!")
  {
    digitalWrite(blueTwo, LOW);
    digitalWrite(greenTwo, LOW);
    digitalWrite(redTwo, HIGH);
  }
}

void setup(void)
{
  //pin mode configuration
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(10, OUTPUT);   //sk pin

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setLED1", meterOneP);
  server.on("/meter1", handleMeter1);
  server.on("/setLED2", meterTwoP);
  server.on("/meter2", handleMeter2);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  sensorRead();
  lNotify();
  bNotify();
}
