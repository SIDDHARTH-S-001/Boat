#include <WiFi.h>

WiFiClient client;
WiFiServer server(80);

const char* ssid = "Micromax HS2";
const char* password = "micromax";
String  data = "";

#define in1 12
#define in2 14
#define in3 27
#define in4 26
#define ena 13
#define enb 25

void setup() {
  // put your setup code here, to run once:

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  Serial.begin(115200);
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(500);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  client = server.available();
  if (!client)
  {
    return;
  }
  data = checkClient ();
  String dataVal = data.substring(1, data.length());
  String rt = data.substring(0, 1);
  Serial.println(data);

  if (rt = "f") {
    forward();
    Serial.println("Moving Forward");
  }

  else if (rt = "b") {
    backward();
    Serial.println("Moving Backwards");
  }

  else if (rt = "l") {
    left();
    Serial.println("Moving Left");
  }

  else if (rt = "r") {
    right();
    Serial.println("Moving Right");
  }

  else if (rt == "s") {
    stop();
    Serial.println("Stop");
  }
  // client.println({'message':'I am Screwed xD'});
  client.print("HTTP/1.1 200 OK\r\n");
  client.print("\r\n\r\n");
  client.print("Hello ");
  Serial.println(data);
  Serial.print("  ");
}

String checkClient (void)
{
  while (!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  //request.body();
  /*Serial.println(request);
    request.remove(0, 5);
    Serial.println(request);
    request.remove(request.length()-9,9);
    Serial.println(request);*/
  return request;
}

void forward() {
  analogWrite(ena, 255);
  analogWrite(enb, 255);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward() {
  analogWrite(ena, 255);
  analogWrite(enb, 255);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left() {
  analogWrite(ena, 255);
  analogWrite(enb, 255);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right() {
  analogWrite(ena, 255);
  analogWrite(enb, 255);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stop() {
  analogWrite(ena, 0);
  analogWrite(enb, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
