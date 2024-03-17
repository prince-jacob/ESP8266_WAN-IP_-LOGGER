#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "WIFI_NAME";
const char *password = "WIFI_PASSWORD";
const char *phpScriptUrl = "http://YOUR-DOMAIN.com/save_ip.php";
const char *ipifyUrl = "http://api.ipify.org/?format=json"; //Dont change, This Will Fetch public IP address from ipify
const char *databaseFetchUrl = "http://YOUR-DOMAIN.com/fetch_data.php";

WiFiClient client;

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to WiFi.");
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

    delay(5000); // Update IP and fetch data every minute
}
