#include "esphome.h"
#include <Preferences.h>  // For storing values in flash memory

class DynamicHostname : public Component {
 public:
  void setup() override {
    Preferences preferences;

    // Open preferences for this device
    preferences.begin("hostname", false);

    // Try to read the stored hostname
    String stored_name = preferences.getString("name", "");

    if (stored_name == "") {
      // If no hostname is stored, generate a random one
      String random_name = "bkdevice-" + String(random(1000, 9999));  // Random number between 1000 and 9999
      preferences.putString("name", random_name);  // Store it in flash memory
      stored_name = random_name;
    }

    // Set the device's hostname and ESPHome name dynamically
    WiFi.setHostname(stored_name.c_str());
    App.set_name(stored_name);

    ESP_LOGI("dynamic_hostname", "Device hostname set to: %s", stored_name.c_str());

    preferences.end();  // Close the preferences
  }

  void loop() override {
    // Nothing to do in loop
  }
};