#if HTTP_UPDATE_ENABLED==true

  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPUpdateServer.h>

  ESP8266WebServer httpServer(80);
  ESP8266HTTPUpdateServer httpUpdater;

  void updater_init() {
    httpUpdater.setup(&httpServer, "/update", HTTP_UPDATE_USERNAME, HTTP_UPDATE_PASSWORD);
    httpServer.begin();
  }

  void updater_loop() {
    httpServer.handleClient();
  }

#endif