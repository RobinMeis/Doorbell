unsigned long mqtt_last_reconnect=0, last_heartbeat=0;

void mqtt_init() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqtt_callback);
}

void mqtt_reconnect() {
  if (!client.connected()) {
    if (WiFi.status() == WL_CONNECTED && millis() - mqtt_last_reconnect > MQTT_RECONNECT_INTERVAL) {
      Serial.println("Reconnecting MQTT");

      if (client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD, topic_availability, 1, true, "offline")) {
        client.setBufferSize(2048);
        Serial.println("MQTT connected");

        client.subscribe(topic_control_lock);
        client.subscribe(topic_control_lock_max_unlock_duration);
        client.subscribe(topic_control_doorbell_debounce_duration);
        client.subscribe(topic_control_reset_button);

        mqtt_heartbeat();
        homeassistant_autodiscovery();
        doorbell_status();
        lock_status();
      }

      mqtt_last_reconnect = millis();
    }
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  if (strcmp(topic, topic_control_lock) == 0) { //Lock control
    if (strcmp((char*)payload, "lock") == 0)
      lock_lock();
    else if (strcmp((char*)payload, "unlock") == 0)
      lock_unlock();
  } else if (strcmp(topic, topic_control_doorbell_debounce_duration) == 0) { //Doorbell debounce duration
    doorbell_set_debounce_duration(atoi((char*)payload));
  } else if (strcmp(topic, topic_control_lock_max_unlock_duration) == 0) { //Lock max unlock duration
    lock_set_max_unlock_duration(atoi((char*)payload));
  } else if (strcmp(topic, topic_control_reset_button) == 0) { //Reset button
    reset();
  }
}

void mqtt_loop() {
  mqtt_reconnect();
  client.loop();

  if (millis() - last_heartbeat > 1000) {
    mqtt_heartbeat();
    last_heartbeat = millis();
  }
}

void mqtt_generate_topic(char *topic_variable, const String topic) {
  sprintf(topic_variable, "%s/%s", host_name.c_str(), topic.c_str());
}

void mqtt_heartbeat() {
  client.publish(topic_availability, "online");
}