#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// WiFi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak
const char* server = "http://api.thingspeak.com";
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

// DHT Sensor
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Buzzer
#define BUZZER_PIN 19

void setup() {
  Serial.begin(115200);

  // Start DHT sensor
  dht.begin();

  // Start buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Read DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = String(server) +
                 "/update?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity);

    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {

      String response = http.getString();

      Serial.print("ThingSpeak response: ");
      Serial.println(response);

      if (response != "0") {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);

        Serial.println("BEEP!");
      }

    } 
    else {

      Serial.print("HTTP error: ");
      Serial.println(httpCode);

    }

    http.end();
  }

  delay(15000);
}
