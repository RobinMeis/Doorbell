#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include "config.h"

#define SW_VERSION "0.0.1"

Preferences preferences;
WiFiClient espClient;
PubSubClient client(espClient);

char buffer[2048];

char topic_availability[35],
     topic_status_doorbell[40],
     topic_control_doorbell_debounce_duration[60],
     topic_status_lock[40],
     topic_control_lock[40],
     topic_control_lock_max_unlock_duration[60],
     topic_control_reset_button[50],
     topic_status_wifi[50];

String host_name;

void setup() {
  Serial.begin(115200);

  byte mac_binary[6];
  char mac[13];
  WiFi.macAddress(mac_binary);
  sprintf(mac, "%x%x%x%x%x%x", mac_binary[0], mac_binary[1], mac_binary[2], mac_binary[3], mac_binary[4], mac_binary[5]);
  host_name = "doorbell-" + (String)mac;

  mqtt_generate_topic(topic_availability, "availability");
  mqtt_generate_topic(topic_status_doorbell, "status/doorbell");
  mqtt_generate_topic(topic_control_doorbell_debounce_duration, "control/doorbell/debounce_duration");
  mqtt_generate_topic(topic_status_lock, "status/lock");
  mqtt_generate_topic(topic_control_lock, "control/lock");
  mqtt_generate_topic(topic_control_lock_max_unlock_duration, "control/lock/max_unlock_duration");
  mqtt_generate_topic(topic_control_reset_button, "control/reset");
  mqtt_generate_topic(topic_status_wifi, "status/wifi");

  preferences.begin("doorbell", false);
  wifi_init();
  mqtt_init();
  doorbell_init();
  lock_init();

  #if HTTP_UPDATE_ENABLED==true
    updater_init();
  #endif
}

void loop() {
  wifi_loop();
  mqtt_loop();
  doorbell_loop();
  lock_loop();

  #if HTTP_UPDATE_ENABLED==true
    updater_loop();
  #endif
}
