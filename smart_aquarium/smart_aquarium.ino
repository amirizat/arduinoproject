#include <SoftwareSerial.h>
#include "RTClib.h"
#include <OneWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RIG_STATUS 6
#define RIG_PWRKEY 7
#define motorPin 12
#define ONE_WIRE_BUS 8
#define relay 10
#define led 13

bool gsmblock = false;
String masa;
float temp;

SoftwareSerial gsm(4, 2);
RTC_DS1307 rtc;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(RIG_PWRKEY, OUTPUT);
  pinMode(RIG_STATUS, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(motorPin, LOW);
  digitalWrite(relay, HIGH);
  digitalWrite(led, LOW);
  resetmodem();

  gsm.begin(115200);
  sensors.begin();
  Serial.begin(115200);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  gsm.println("AT"); //Once the handshake test is successful, it will back to OK
  gsm.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  gsm.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  gsm.println("AT+CREG?"); //Check whether it has registered in the network


  Serial.println("Smart Aquarium");
}

void loop() {
  DateTime now = rtc.now();
  sensors.requestTemperatures();

  masa = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  temp = sensors.getTempCByIndex(0);

  Serial.println("masa sekarang=" + masa);
  Serial.print("temperature sekarang=");
  Serial.println(temp);

  if (masa == "8:0:0" || masa == "12:0:0" || masa == "20:0:0") {
    feedFish();
  }

  if ((temp > 50) && (gsmblock == false)) {
    sendMessage("Water Temperature Not Stable. Heater is off");
    delay(1000);
    //DialCall();
    digitalWrite(relay, LOW);
    digitalWrite(led, HIGH);
    gsmblock = true;
    Serial.println("mesej sent.Heater is off");
  } else if ((temp < 50) && (gsmblock == true)) {
    sendMessage("Water Temperature Now Stable. Heater is on");
    delay(1000);
    //DialCall();
    digitalWrite(relay, HIGH);
    digitalWrite(led, LOW);
    gsmblock = false;
    Serial.println("mesej sent.Heater is on");
  }
}

void sendMessage(String message) {
  Serial.println("msj");
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  gsm.println("AT+CMGS=\"+601133217034\"\r"); // Replace x with mobile number

  delay(1000);

  gsm.println(message);// The SMS text you want to send

  delay(100);

  gsm.println((char)26);// ASCII code of CTRL+Z

  delay(1000);
}

void DialCall() {
  Serial.println("call");
  gsm.print("ATD");
  gsm.println("+601133217034;");
  //delay(10000);
  //mySerial.println("ATH");

}

void resetmodem() {
  digitalWrite(RIG_PWRKEY, LOW);
  if (!digitalRead(RIG_STATUS))
  {
    digitalWrite(RIG_PWRKEY, HIGH);
    while (1)
    {
      if (digitalRead(RIG_STATUS))
      {
        digitalWrite(RIG_PWRKEY, LOW);
        break;
      }
    }
  }
}

void feedFish() {
  digitalWrite(motorPin, HIGH);
}
