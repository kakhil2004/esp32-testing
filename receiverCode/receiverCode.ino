#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

typedef struct struct_message {
    char text[32];
    int number;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Text: ");
    Serial.println(myData.text);
    Serial.print("Number: ");
    Serial.println(myData.number);
    Serial.printf("%4d", WiFi.RSSI());
}

void setup() {
    Serial.begin(9600);
    Serial.println(WiFi.macAddress());
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    //handles all the work
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
