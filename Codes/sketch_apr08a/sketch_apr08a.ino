#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <QMC5883L.h>
#include <ThingSpeak.h>

QMC5883L compass;

// ------------------------------------------- Wifi -------------------------------------
const char* ssid = "Micromax HS2";
const char* password = "Micromax";

// ----------------------------------------- Turbidity ----------------------------------
#define TurbiditySensorPin 33
// -------------------------------------------- pH --------------------------------------
#define pH_pin 35
// --------------------------------------- Dissolved Oxygen -----------------------------
#define DO_pin 32
// -------------------------------------------- TDS -------------------------------------
#define TdsSensorPin 34
// ------------------------------------------ DHT-11 ------------------------------------
#define DHTTYPE DHT11
int dht_pin = 15;
DHT dht(dht_pin, DHTTYPE);
// ------------------------------------------- Sonar-------------------------------------
#define trigPin 4
#define echoPin 2
int distance;
float duration;

WiFiClient  client;

unsigned long myChannelNumber = 2026413;
const char * myWriteAPIKey = "D4YLF7GRZZPJ47R0";


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
      // tds
  pinMode(TdsSensorPin,INPUT);

  // turbidity
  pinMode(TurbiditySensorPin,INPUT);

  // dht-11
  pinMode(dht_pin, INPUT);
  dht.begin();

  // pH
  pinMode(pH_pin, INPUT);
  
  // DO
  pinMode(DO_pin, INPUT);

  // QMC5883L
  compass.init();
  Wire.begin();

  // Sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ThingSpeak.begin(client); 

}

void loop() {
  // put your main code here, to run repeatedly:
  int x,y,z;
  compass.read(&x,&y,&z);

 // Calculate heading when the magnetometer is level, then correct for signs of axis.
  // Atan2() automatically check the correct formula taking care of the quadrant you are in
  float heading = atan2(y, x);

  float declinationAngle = 0.0404;
  heading += declinationAngle;
  // Find yours here: http://www.magnetic-declination.com/

   // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;

  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 


  Serial.print("x: ");
  Serial.print(x);
  Serial.print("    y: ");
  Serial.print(y);
  Serial.print("    z: ");
  Serial.print(z);
  Serial.print("    heading: ");
  Serial.print(heading);
  Serial.print("    Radius: ");
  Serial.print(headingDegrees);
  Serial.println();
  delay(100);

  int turbidity_sensorValue = analogRead(TurbiditySensorPin);
  float turbidity = map(turbidity_sensorValue, 0, 4096, 10, 0);
  Serial.print("Turbidity:");
  Serial.println(turbidity);
  ThingSpeak.writeField(myChannelNumber, 4, turbidity, myWriteAPIKey);

  int pH_voltage = analogRead(pH_pin);
  float pH = map(pH_voltage, 0, 4096, 0, 14)/2;
  Serial.print("pH: ");
  Serial.println(pH);
  ThingSpeak.writeField(myChannelNumber, 3, pH, myWriteAPIKey);

  int temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temp);
  ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);

  int DO_analog = analogRead(DO_pin);
  float DO_sat = map(temp, 0, 47, 14.6, 5.79);
  float DO_value = map(DO_analog, 0, 4096, 0, DO_sat);
  Serial.print("DO: ");
  Serial.println(DO_value);
  ThingSpeak.writeField(myChannelNumber, 2, DO_value, myWriteAPIKey);

  int tds_reading = analogRead(TdsSensorPin);
  int tds = map(tds_reading, 0, 4096, 0, 1000);
  Serial.print("TDS: ");
  Serial.println(tds_reading);  
  ThingSpeak.writeField(myChannelNumber, 5, tds_reading, myWriteAPIKey);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  

}
