unsigned long wifi_last_reconnect = 0, wifi_last_status=0;

void wifi_init() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host_name);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
}

void wifi_loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (millis() - wifi_last_status > 5000) {
      wifi_status();
      wifi_last_status = millis();
    }
  } else { 
    if (WiFi.status() != WL_CONNECTED && millis() - wifi_last_reconnect > WIFI_RECONNECT_INTERVAL) {
      Serial.println("Reconnecting to WiFi...");
      WiFi.reconnect();
      wifi_last_reconnect = millis();
    }
  }
}

void wifi_status() {
  DynamicJsonDocument doc(1024);

  doc["RSSI"] = WiFi.RSSI();
  doc["ESSID"] =  WiFi.SSID();
  doc["MAC"] = WiFi.macAddress();
  doc["IP"] = WiFi.localIP();
  serializeJson(doc, buffer);
  client.publish(topic_status_wifi, buffer, true);
}