#pragma once

#include <stdint.h>
#include "driver/ledc.h"
#include "../pwm_ctrl/pwm_ctrl.h"


struct pwm_conf_t {
  gpio_num_t pin_high;
  gpio_num_t pin_low;
  ledc_channel_t ledc_channel_num;
};

struct moto_conf_t {
  pwm_conf_t forward_conf;
  pwm_conf_t reverse_conf;
};


class Motor {
public:
  // Constructor
  Motor(const moto_conf_t& moto_conf);

  // Functions
  void forward(uint16_t speed);
  void reverse(uint16_t speed);

private:
  // Variables
  PWM_Ctrl pwm_forward;
  PWM_Ctrl pwm_reverse;

  bool is_forward_mode;

};