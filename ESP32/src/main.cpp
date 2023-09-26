#include<Arduino.h>

#define us_to_s_factor 1000000
#define time_to_sleep 10 
#define ledPin 2

RTC_DATA_ATTR int bootCount = 0;

void print_wake_up_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup by ESP_SLEEP_WAKEUP_EXT0");
    break;

    case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup by ESP_SLEEP_WAKEUP_EXT1");
    break;

    case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup by ESP_SLEEP_WAKEUP_TIMER");
    break;

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup by ESP_SLEEP_WAKEUP_TOUCHPAD");
    break;

    case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup by ESP_SLEEP_WAKEUP_ULP");
    break;

    default:
    Serial.println("Wakeup was not caused by deep sleep:");
    break;
  }

}


void setup()
{
  Serial.begin(115200);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  pinMode(ledPin, OUTPUT);

  print_wake_up_reason();
  esp_sleep_enable_timer_wakeup(time_to_sleep * us_to_s_factor);
  Serial.println("Setup ESP32 sleep every " + String(time_to_sleep) + " Senconds");
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  Serial.println("Sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}