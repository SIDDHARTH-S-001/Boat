#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ThingsBoard.h>
#include <DHT.h>

#define DHTPIN 4          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);

// Deklarasi Variable dan Konstanta
String wifiSSID = "OnePlus Nord";
String wifiPassword = "capabara";

// Thingsboard Credential
String tbHost = "demo.thingsboard.io";
String tbToken = "6FReIT7HRpmIsAvqsqTw";

WiFiClient client;
ThingsBoard tb(client);

// Deklarasi Fungsi
void connectWifi();
void tbReconnect();

void setup()
{
    Serial.begin(9600);
    dht.begin();
    connectWifi();
}

void loop()
{
    if (!tb.connected())
    {
        tbReconnect();
    }

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.println("Sending data to Thingsboard");
    tb.sendTelemetryFloat("temperature", t);
    tb.sendTelemetryFloat("humidity", h);
    tb.loop();
    delay(1000);
}

void tbReconnect()
{
    while (!tb.connected())
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            connectWifi();
        }

        Serial.println("connecting to thingsboard ... ");
        if (tb.connect(tbHost.c_str(), tbToken.c_str()))
        {
            Serial.println("Thingsboard Connected!");
        }
        else
        {
            Serial.println("Thingsboard connection failed");
            Serial.println("Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void connectWifi()
{
    Serial.println("Connecting To Wifi");
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Wifi Connected");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
}
