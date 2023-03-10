void homeassistant_autodiscovery_device(JsonDocument &doc) {
  JsonObject device = doc.createNestedObject("device");
  JsonArray identifiers = device.createNestedArray("identifiers");
  identifiers.add(host_name);
  device["manufacturer"] = "Robin Meis";
  device["model"] = "Hells Bells";
  device["name"] = "Doorbell";
  device["sw_version"] = SW_VERSION;
  device["configuration_url"] = "http://" + WiFi.localIP().toString() + "/update";
}

void homeassistant_autodiscovery_doorbell() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "Doorbell";
  doc["unique_id"] = host_name + "_doorbell";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_doorbell;
  doc["value_template"] = "{{ value_json.status }}";
  doc["icon"] = "mdi:bell";
  doc["payload_on"] = "pressed";
  doc["payload_off"] = "released";
  doc["availability_topic"] = topic_availability;

  char topic[60];
  homeassistant_generate_topic(topic, "binary_sensor", "doorbell");

  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_doorbell_debounce_duration() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "Doorbell debounce duration";
  doc["icon"] = "mdi:timer-outline";
  doc["unique_id"] = host_name + "_doorbell_debounce_duration";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_doorbell;
  doc["value_template"] = "{{ value_json.debounce_duration }}";
  doc["command_topic"] = topic_control_doorbell_debounce_duration;
  doc["min"] = 0;
  doc["max"] = 2000;
  doc["step"] = 20;
  doc["unit_of_measurement"] = "ms";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "config";

  char topic[85];
  homeassistant_generate_topic(topic, "number", "doorbell_debounce_duration");

  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_lock() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "Door";
  doc["icon"] = "mdi:lock";
  doc["unique_id"] = host_name + "_door";
  doc["object_id"] = doc["unique_id"];
  doc["payload_lock"] = "lock";
  doc["payload_unlock"] = "unlock";
  doc["state_locked"] = "locked";
  doc["state_unlocked"] = "unlocked";
  doc["state_topic"] = topic_status_lock;
  doc["value_template"] = "{{ value_json.status }}";
  doc["command_topic"] = topic_control_lock;
  doc["availability_topic"] = topic_availability;

  char topic[65];
  homeassistant_generate_topic(topic, "lock", "door");

  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_lock_max_unlock_duration() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "Maximum unlock duration";
  doc["icon"] = "mdi:timer-lock-open-outline";
  doc["unique_id"] = host_name + "_lock_max_unlock_duration";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_lock;
  doc["value_template"] = "{{ value_json.max_unlock_duration }}";
  doc["command_topic"] = topic_control_lock_max_unlock_duration;
  doc["min"] = 1;
  doc["max"] = 60;
  doc["unit_of_measurement"] = "seconds";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "config";

  char topic[85];
  homeassistant_generate_topic(topic, "number", "lock_max_unlock_duration");

  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_reset_button() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "Restart";
  doc["icon"] = "mdi:restart";
  doc["unique_id"] = host_name + "_reset";
  doc["object_id"] = doc["unique_id"];
  doc["command_topic"] = topic_control_reset_button;
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "diagnostic";

  char topic[65];
  homeassistant_generate_topic(topic, "button", "reset");

  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_rssi() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "RSSI";
  doc["icon"] = "mdi:wifi-strength-3";
  doc["unique_id"] = host_name + "_rssi";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_wifi;
  doc["value_template"] = "{{ value_json.RSSI }}";
  doc["unit_of_measurement"] = "dBm";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "diagnostic";

  char topic[85];
  homeassistant_generate_topic(topic, "sensor", "rssi");
  
  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_essid() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "ESSID";
  doc["icon"] = "mdi:wifi";
  doc["unique_id"] = host_name + "_essid";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_wifi;
  doc["value_template"] = "{{ value_json.ESSID }}";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "diagnostic";

  char topic[85];
  homeassistant_generate_topic(topic, "sensor", "essid");
  
  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_mac() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "MAC address";
  doc["icon"] = "mdi:identifier";
  doc["unique_id"] = host_name + "_mac";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_wifi;
  doc["value_template"] = "{{ value_json.MAC }}";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "diagnostic";

  char topic[85];
  homeassistant_generate_topic(topic, "sensor", "mac");
  
  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery_ip() {
  DynamicJsonDocument doc(1024);
  homeassistant_autodiscovery_device(doc);
  doc["name"] = "IP address";
  doc["icon"] = "mdi:ip-network";
  doc["unique_id"] = host_name + "_ip";
  doc["object_id"] = doc["unique_id"];
  doc["state_topic"] = topic_status_wifi;
  doc["value_template"] = "{{ value_json.IP }}";
  doc["availability_topic"] = topic_availability;
  doc["entity_category"] = "diagnostic";

  char topic[85];
  homeassistant_generate_topic(topic, "sensor", "ip");
  
  serializeJson(doc, buffer);
  client.publish(topic, buffer, true);
}

void homeassistant_autodiscovery() {
  homeassistant_autodiscovery_doorbell();
  homeassistant_autodiscovery_doorbell_debounce_duration();
  homeassistant_autodiscovery_lock();
  homeassistant_autodiscovery_lock_max_unlock_duration();
  homeassistant_autodiscovery_reset_button();
  homeassistant_autodiscovery_rssi();
  homeassistant_autodiscovery_essid();
  homeassistant_autodiscovery_mac();
  homeassistant_autodiscovery_ip();
}

void homeassistant_generate_topic(char *topic_variable, String component, String objectid) {
  sprintf(topic_variable, "homeassistant/%s/%s/%s/config", component.c_str(), host_name.c_str(), objectid.c_str());
}