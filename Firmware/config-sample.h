#ifndef CONFIG_H
#define CONFIG_H

// WiFi configuration
#define WIFI_SSID "IoT"
#define WIFI_PSK "12345678"

// MQTT configuration
#define MQTT_SERVER "mqtt.local"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID host_name.c_str()
#define MQTT_USERNAME "user"
#define MQTT_PASSWORD "password"

// HTTP update server
#define HTTP_UPDATE_ENABLED true
#define HTTP_UPDATE_USERNAME "admin"
#define HTTP_UPDATE_PASSWORD "admin"

// Pins
#define PIN_DOORBELL 1
#define PIN_DOORBELL_ACTIVE_LOW true
#define PIN_OPENER 3
#define PIN_OPENER_ACTIVE_LOW false

// Intervals
#define WIFI_RECONNECT_INTERVAL 5000
#define MQTT_RECONNECT_INTERVAL 5000
#define HOMEASSISTANT_AUTODISCOVERY_INTERVAL 60000

#endif