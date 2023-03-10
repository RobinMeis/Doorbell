unsigned long lock_unlock_start=0;

void lock_init() {
  pinMode(PIN_OPENER, OUTPUT);
  digitalWrite(PIN_OPENER, true == PIN_OPENER_ACTIVE_LOW);
}

void lock_unlock() {
  digitalWrite(PIN_OPENER, true != PIN_OPENER_ACTIVE_LOW);
  lock_unlock_start = millis();
  lock_status();
}

void lock_lock() {
  digitalWrite(PIN_OPENER, true == PIN_OPENER_ACTIVE_LOW);
  lock_status();
}

void lock_loop() {
  if (!lock_is_locked() && millis() - lock_unlock_start > 1000*lock_get_max_unlock_duration())
    lock_lock();
}

bool lock_is_locked() {
  return digitalRead(PIN_OPENER) == PIN_OPENER_ACTIVE_LOW;
}

void lock_status() {
  DynamicJsonDocument doc(2048);

  if (lock_is_locked())
    doc["status"] = "locked";
  else
    doc["status"] = "unlocked";
  
  doc["max_unlock_duration"] = lock_get_max_unlock_duration();

  serializeJson(doc, buffer);
  client.publish(topic_status_lock, buffer, true);
}

void lock_set_max_unlock_duration(int duration) {
  preferences.putUInt("unlockduration", duration);
  lock_status();
}

int lock_get_max_unlock_duration() {
  return preferences.getUInt("unlockduration", 5);
}