#pragma once

#include <stdint.h>
#include "driver/ledc.h"

class PWM {
public:
  // Constructor
  PWM(gpio_num_t pin_out, ledc_channel_t ledc_channel_num);

  // Functions
  void drive(uint16_t speed);

private:
  // Variables
  gpio_num_t pin;
  ledc_channel_t channel;

  // Functions
  void init_gpio();
  void init_pwm_timer();
  void init_pwm_channel();
};