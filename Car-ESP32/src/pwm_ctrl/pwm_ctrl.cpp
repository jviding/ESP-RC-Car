#include "pwm_ctrl.h"
#include "driver/ledc.h"


void PWM_Ctrl::conf_pin_low() {
  gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << pin_low),
    .mode         = GPIO_MODE_OUTPUT,
    .pull_up_en   = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
  };
  gpio_config(&io_conf);
};

PWM_Ctrl::PWM_Ctrl(gpio_num_t pin_high, gpio_num_t pin_low, ledc_channel_t ledc_channel_num)
  : pwm(pin_high, ledc_channel_num), 
    pin_low(pin_low), 
    can_run(false) 
{
  conf_pin_low();
  // Default stop
  stop();
};

void PWM_Ctrl::start() {
  gpio_set_level(pin_low, 0);
  can_run = true;
};

esp_err_t PWM_Ctrl::drive(uint16_t speed) {
  if (can_run) {
    pwm.drive(speed);
    return ESP_OK;
  } else {
    return ESP_ERR_INVALID_STATE;
  }
};

void PWM_Ctrl::stop() {
  can_run = false;
  pwm.drive(0);
  gpio_set_level(pin_low, 1);
};