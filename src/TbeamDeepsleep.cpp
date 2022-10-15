#include <esp_sleep.h>
#include "TbeamDeepsleep.h"

RTC_DATA_ATTR int rtc = 0;

TbeamDeepsleep::TbeamDeepsleep() {}

TbeamDeepsleep::~TbeamDeepsleep() {
}

void TbeamDeepsleep::sleepInterrupt(uint8_t gpio, uint8_t mode) {
    esp_sleep_enable_ext0_wakeup((gpio_num_t) gpio, mode);
}

void TbeamDeepsleep::sleepInterruptMask(uint64_t mask, uint8_t mode) {
    esp_sleep_enable_ext1_wakeup(mask, (esp_sleep_ext1_wakeup_mode_t) mode);
}

void TbeamDeepsleep::sleepMillis(uint64_t ms) {
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_deep_sleep_start();
}

void TbeamDeepsleep::sleepSeconds(uint32_t seconds) {
    esp_sleep_enable_timer_wakeup(seconds * 1000000);
    esp_deep_sleep_start();
}

void TbeamDeepsleep::sleepForever() {
    esp_deep_sleep_start();
}

int TbeamDeepsleep::getRtc() {
    return rtc;
}

void TbeamDeepsleep::setRtc(int data) {
    rtc = data;
}

// see https://m1cr0lab-esp32.github.io/sleep-modes/hibernation-mode/
void TbeamDeepsleep::hibernate(uint32_t seconds) {
    // In hibernation mode, the only way to save data is to host it in the EEPROM.
    // The ledIndex value is saved at address 0x0000.
    // #include <EEPROM.h>
    // setup()
    // EEPROM.begin(1)
      // if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
      //   // in hibernation mode, the only way to save data is to host it in the EEPROM
      //   ledIndex = EEPROM.read(0); // <-- the value stored at address 0x0000 is assigned to ledIndex
      // }
    // 
    // here in hibernate()
    // EEPROM.write(0, ledIndex);
    // EEPROM.commit();

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,   ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL,         ESP_PD_OPTION_OFF);
    
    TbeamDeepsleep::sleepSeconds(seconds);
}