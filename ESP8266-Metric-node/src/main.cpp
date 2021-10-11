#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SimpleTimer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <DHT.h>

SimpleTimer timer;

void postData();
void configSetup();
void readSensor();

long Temperature;
long Humidity;

char serverName[60] = "http://192.168.1.100:8000";
char token[8] = "dpq4Q7G";
char bearer_token[41] = "bec0cc857ff19b122433efbedd8c8772b8e3f8c6";
String url;

#define DHTPIN 4
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

bool shouldSaveConfig = false;

void saveConfigCallback()
{
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void setup()
{
    Serial.begin(115200);
    configSetup();
    url = String(serverName) + "/dashboard/api/device/" + String(token) + "/data";
    Serial.println("Timer set to 10 seconds");
    dht.begin();
    timer.setInterval(10000, postData);
    timer.setInterval(5000, readSensor);
}

void loop()
{
    timer.run();
}

void readSensor()
{
    Temperature = dht.readHumidity();    
    Humidity = dht.readTemperature();


    // Check if any reads failed and exit early (to try again).
    if (isnan(Temperature) || isnan(Humidity))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    Serial.print(F("Humidity: "));
    Serial.print(Humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(Temperature);
    Serial.print(F("°C "));
}

void postData()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(client, url);

        // Specify content-type header
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Token " + String(bearer_token));

        int httpResponseCode = http.POST("{\"temperature\":" + String(Temperature) + ",\"humidity\":" + String(Humidity) + "}");

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        // Free resources
        http.end();
    }
}

void configSetup()
{
    Serial.println();
    Serial.println("mounting FS...");

    if (SPIFFS.begin())
    {
        Serial.println("mounted file system");
        if (SPIFFS.exists("/config.json"))
        {
            //file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile)
            {
                Serial.println("opened config file");
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);

                DynamicJsonDocument json(1024);
                auto deserializeError = deserializeJson(json, buf.get());
                serializeJson(json, Serial);
                if (!deserializeError)
                {

                    Serial.println("\nparsed json");
                    strcpy(serverName, json["serverName"]);
                    strcpy(token, json["token"]);
                    strcpy(bearer_token, json["bearer_token"]);
                }
                else
                {
                    Serial.println("failed to load json config");
                }
                configFile.close();
            }
        }
        else
        {
            SPIFFS.format();
        }
    }
    else
    {
        Serial.println("failed to mount FS");
    }

    WiFiManagerParameter custom_serverName("serverName", "serverName", serverName, 60);
    WiFiManagerParameter custom_token("token", "token", token, 8);
    WiFiManagerParameter custom_bearer_token("bearer_token", "bearer_token", bearer_token, 41);

    WiFiManager wifiManager;

    wifiManager.setSaveConfigCallback(saveConfigCallback);

    wifiManager.addParameter(&custom_serverName);
    wifiManager.addParameter(&custom_token);
    wifiManager.addParameter(&custom_bearer_token);

    if (!wifiManager.autoConnect("Metric Node", "12345678"))
    {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.restart();
        delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    //read updated parameters
    strcpy(serverName, custom_serverName.getValue());
    strcpy(token, custom_token.getValue());
    strcpy(bearer_token, custom_bearer_token.getValue());
    Serial.println("The values in the file are: ");
    Serial.println("\tserver : " + String(serverName));
    Serial.println("\ttoken : " + String(token));
    Serial.println("\tbearer_token : " + String(bearer_token));

    //save the custom parameters to FS
    if (shouldSaveConfig)
    {
        Serial.println("saving config");
        DynamicJsonDocument json(1024);
        json["serverName"] = serverName;
        json["token"] = token;
        json["bearer_token"] = bearer_token;

        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile)
        {
            Serial.println("failed to open config file for writing");
        }

        serializeJson(json, Serial);
        serializeJson(json, configFile);

        configFile.close();
    }
    Serial.println();
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
}
