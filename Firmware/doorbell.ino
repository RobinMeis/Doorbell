unsigned long doorbell_last_pressed=0;
bool doorbell_pressed=false;

void doorbell_init() {
  pinMode(PIN_DOORBELL, INPUT_PULLUP);
  doorbell_status();
}

void doorbell_loop() { //Debouncing loop for doorbell. Implemented in a strange way to filter out AC signals
  if (digitalRead(PIN_DOORBELL) == PIN_DOORBELL_ACTIVE_LOW) { //Button released
    if (millis() - doorbell_last_pressed < doorbell_get_debounce_duration()) //Wait for released signal for the whole debounce perioud
      return;

    if (doorbell_pressed) { //Changed from pressed to released
      doorbell_pressed = false;
      doorbell_status();
    }
  } else { //Button pressed
    doorbell_last_pressed = millis(); //Restart debounce period as soon as button pressed is detected
    if (!doorbell_pressed) { //Changed from released to pressed
      doorbell_pressed = true;
      doorbell_status();
    }
  }
}

void doorbell_status() {
  DynamicJsonDocument doc(2048);

  if (doorbell_pressed)
    doc["status"] = "pressed";
  else
    doc["status"] = "released";
  
  doc["debounce_duration"] = doorbell_get_debounce_duration();

  serializeJson(doc, buffer);
  client.publish(topic_status_doorbell, buffer, true);
}

void doorbell_set_debounce_duration(int duration) {
  preferences.putUInt("debounce", duration);
  doorbell_status();
}

int doorbell_get_debounce_duration() {
  return preferences.getUInt("debounce", 100);
}