#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "WIFI_NAME";
const char *password = "WIFI_PASSWORD";
const char *phpScriptUrl = "http://YOUR-DOMAIN.com/save_ip.php";
const char *ipifyUrl = "http://api.ipify.org/?format=json"; //Dont change, This Will Fetch public IP address from ipify
const char *databaseFetchUrl = "http://YOUR-DOMAIN.com/fetch_data.php";

const int ledPin = LED_BUILTIN; // ESP8266 built-in LED pin
WiFiClient client;

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT); // Set the LED pin as output

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to WiFi.");
}

void blinkLED() {
    digitalWrite(ledPin, LOW);
    delay(10);
    digitalWrite(ledPin, HIGH);
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Fetch public IP address from ipify
        if (http.begin(client, ipifyUrl)) {
            int httpCode = http.GET();

            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                StaticJsonDocument<200> jsonDoc;
                deserializeJson(jsonDoc, payload);

                const char* publicIP = jsonDoc["ip"];
                Serial.println("Public IP Address: " + String(publicIP));

                // Send public IP address to server
                if (http.begin(client, phpScriptUrl)) {
                    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                    String postData = "public_ip=" + String(publicIP);
                    Serial.println("Sending public IP to server: " + postData);
                    httpCode = http.POST(postData);

                    if (httpCode == HTTP_CODE_OK) {
                        Serial.println("Public IP sent to server.");
                        blinkLED(); // Blink LED on successful data send
                    } else {
                        Serial.print("Failed to send public IP to server. Error code: ");
                        Serial.println(httpCode);
                    }

                    http.end();
                } else {
                    Serial.println("Failed to connect to server.");
                }
            } else {
                Serial.print("Failed to get IP address from server. Error code: ");
                Serial.println(httpCode);
            }

            http.end();
        } else {
            Serial.println("Failed to connect to IP address fetch server.");
        }

        // Fetch data from the database
        if (http.begin(client, databaseFetchUrl)) {
            int httpCode = http.GET();

            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println("Data received from server:");
                Serial.println(payload);
                blinkLED(); // Blink LED on successful data receive
                // Parse and handle the received data here
            } else {
                Serial.print("Failed to fetch data from server. Error code: ");
                Serial.println(httpCode);
            }

            http.end();
        } else {
            Serial.println("Failed to connect to database fetch server.");
        }
    }

    delay(30000); // Update IP and fetch data every 30 Seconds
}
