#include <SPI.h>
#include <RFID.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "amireyzah@unifi";
const char* password = "Am_ir0212";

#define SS_PIN 15
#define RST_PIN 0
const int pingPin = 4;
const int echoPin = 3;

RFID CARD(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int serNum[5];
String payload;
String idcard;
String binlevels;
String Status;
bool states = false;
long duration, cm;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  CARD.init();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Garbage Monitor");
  lcd.setCursor(0, 5);
  lcd.print("System");
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  binlevels = ultrsonic();
  Serial.println(binlevels);
  if (CARD.isCard()) {

    if (CARD.readCardSerial()) {
      for (int i = 0; i < sizeof(CARD.serNum); i++ ) {
        idcard += (String)CARD.serNum[i];
      }
    }
    if ((states == false) && (cm < 50)) {
      Status = "checkin";
      Serial.println(binlevels);
      payload = updatedata(idcard, binlevels, Status);
      Serial.println(payload);
      states = true;
    }
    if ((states == true) && (cm > 50)) {
      Status = "checkout";
      Serial.println(binlevels);
      payload = updatedata(idcard, binlevels, Status);
      Serial.println(payload);
      states = false;
    }

    if (payload == "200") {
      Serial.println("Success");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Success");

    } else if (payload == "error insert") {
      Serial.println("Error");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System Error");

    } else if (payload == "no matching card") {
      Serial.println("No card register");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not Register");
    }
    
    idcard = "";
    payload = "";
  }

  CARD.halt();

}

String updatedata(String idcard, String binlevel, String Statuss) {
  const char* serverName = "http://dustbinmonitoring.000webhostapp.com/collect.php";
  String payload;

  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "idcard=" + idcard + "&" + "binlevel=" + binlevel + "&" + "status=" + Statuss;
  int httpResponseCode = http.POST(httpRequestData);
  payload = http.getString();
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  http.end();

  return payload;
}

String ultrsonic() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  delay(100);
  return (String)cm + "cm";
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
