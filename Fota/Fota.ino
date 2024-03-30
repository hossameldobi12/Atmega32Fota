
/**
 * @author  Hossam Eldobi (hossameldobi12@gmail.com)
 * @version 1.0
 * @date    2022-10-28
 *
 */

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#elif __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#elif __has_include(<WiFiS3.h>)
#include <WiFiS3.h>
#endif

#include <Firebase_ESP_Client.h>
#include <PubSubClient.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>
// #include <filesystem/LittleFS>
//  Provide the SD card interfaces setting and mounting
#include <addons/SDHelper.h>

#define RXp2     4
#define TXp2     2

#define Start  (0x01)
#define Exit   (0x00)
#define OK     (0x01)
#define NOT_OK (0x00)

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Hossam"
#define WIFI_PASSWORD "11111111"

/* 2. Define the API Key */
#define API_KEY "AIzaSyDh8jgz-87CKKcoj5odn3pVBOAZHFvtVyI"

/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "hossameldobi12@gmail.com"
#define USER_PASSWORD "11111111"

/* 4. Define the Firebase storage bucket ID e.g bucket-name.appspot.com */
#define STORAGE_BUCKET_ID "atmega32fota.appspot.com"

const char *mqtt_server = "broker.hivemq.com";
char buff[2] = {0};
unsigned char packet[128] = {0};
const char *path = "/update.bin";
unsigned char Data;

void BootloaderSendData();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool taskCompleted = false;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{

    Serial.begin(115200);
    Serial1.begin(9600, SERIAL_8N1, RXp2, TXp2);

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    multi.addAP(WIFI_SSID, WIFI_PASSWORD);
    multi.run();
#else
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

    Serial.print("Connecting to Wi-Fi");
    unsigned long ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
        if (millis() - ms > 10000)
            break;
#endif
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    // The WiFi credentials are required for Pico W
    // due to it does not have reconnect feature.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    config.wifi.clearAP();
    config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
    Firebase.reconnectNetwork(true);

    // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
    // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
    fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

    /* Assign download buffer size in byte */
    // Data to be downloaded will read as multiple chunks with this size, to compromise between speed and memory used for buffering.
    // The memory from external SRAM/PSRAM will not use in the TCP client internal rx buffer.
    config.fcs.download_buffer_size = 2048;

    Firebase.begin(&config, &auth);

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

// The Firebase Storage download callback function
void fcsDownloadCallback(FCS_DownloadStatusInfo info)
{
    if (info.status == firebase_fcs_download_status_init)
    {
        Serial.printf("Downloading file %s (%d) to %s\n", info.remoteFileName.c_str(), info.fileSize, info.localFileName.c_str());
    }
    else if (info.status == firebase_fcs_download_status_download)
    {
        Serial.printf("Downloaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    }
    else if (info.status == firebase_fcs_download_status_complete)
    {
        Serial.println("Download completed\n");
    }
    else if (info.status == firebase_fcs_download_status_error)
    {
        Serial.printf("Download failed, %s\n", info.errorMsg.c_str());
    }
}
void readfile()
{
    Serial.println("Reading file : \n");
    File file = LittleFS.open(path, "r");

    if (!file)
    {
        Serial.println("faild to read file :\n");
        return;
    }
    Serial.println("reading from file\n");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void loop()
{

    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    delay(100);
}

void BootloaderSendData()
{

    File file = LittleFS.open(path, "r");
    while (file.available())
    {
        Serial.printf("\nStart %x", Start);
        Serial1.write(Start);
        while (!Serial1.available())
        {
        }
        Data = Serial1.read();

        if (Data == NOT_OK)
        {
            Serial.printf("\nReceved not ok : %x ", Data);
            break;
        }
        else if (Data == OK)
        {
            Serial.printf("\nReceved ok : %x ", Data);
            unsigned char CounterByte = 0;
            while (CounterByte < 128)
            {
                file.readBytes(buff, 2);
                unsigned char HexData = strtol(buff, NULL, 16);
                packet[CounterByte] = HexData;
                CounterByte++;
            }
            CounterByte = 0;
            while (CounterByte < 128)
            {
                // Serial.printf("\nPacket[%i] = %x ", CounterByte,packet[CounterByte]);
                Serial1.write(packet[CounterByte]);
                CounterByte++;
            }
            Serial.printf("\nData sent");
            while (!Serial1.available())
            {
            }
            Data = Serial1.read();
            if (Data == NOT_OK)
            {
                Serial.printf("\nReceved not ok after sending : %x ", Data);
                break;
            }
            else if (Data == OK)
            {
                Serial.printf("\nReceved ok after sending : %x ", Data);
                continue;
            }
            else
            {
                Serial.printf("\ninvallid number after sending : %x", Data);
                break;
            }
        }
        else
        {
            Serial.printf("\ninvallid number before sending : %x", Data);
            break;
        }
    }
    if (!file.available())
    {

        Serial.printf("\nExit %x \n", Exit);
        Serial1.write(Exit);
        file.close();
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String string;
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        string += ((char)payload[i]);
    }
    Serial.print(string);
    Serial.print("\n");
    if (topic = "Fota") /// esp32 subscribe topic
        if (string == "1")
        {

            if (Firebase.ready() && !taskCompleted)
            {
                taskCompleted = true;

                Serial.println("\nDownload file...\n");

                // The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
                if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, "MainPy.txt" /* path of remote file stored in the bucket */, path /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, fcsDownloadCallback /* callback function */))

                {
                    Serial.println(fbdo.errorReason());
                }
                readfile();
                BootloaderSendData();
                taskCompleted = false;
            }
        }
    delay(15);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESPClient"))
        {
            Serial.println("connected");
            client.subscribe("Fota");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
