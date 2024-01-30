#pragma once

#include <stdint.h>
#include "driver/ledc.h"
#include "../pwm/pwm.h"


class PWM_Ctrl {
public:
  // Constructor
  PWM_Ctrl(gpio_num_t pin_high, gpio_num_t pin_low, ledc_channel_t ledc_channel_num);

  // Functions
  void start();
  esp_err_t drive(uint16_t speed);
  void stop();

private:
  // Variables
  PWM pwm;
  gpio_num_t pin_low;
  bool can_run;

  // Functions
  void conf_pin_low();
};
