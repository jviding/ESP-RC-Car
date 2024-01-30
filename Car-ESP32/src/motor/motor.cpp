#include "motor.h"


Motor::Motor(const moto_conf_t& moto_conf)
  : pwm_forward(
      moto_conf.forward_conf.pin_high, 
      moto_conf.forward_conf.pin_low,
      moto_conf.forward_conf.ledc_channel_num
    ),
    pwm_reverse(
      moto_conf.reverse_conf.pin_high,
      moto_conf.reverse_conf.pin_low,
      moto_conf.reverse_conf.ledc_channel_num
    ),
    is_forward_mode(true)
{};

void Motor::forward(uint16_t speed) {
  if (!is_forward_mode) {
    pwm_reverse.stop();
    pwm_forward.start();
    is_forward_mode = true;
  }
  pwm_forward.drive(speed);
};

void Motor::reverse(uint16_t speed) {
  if (is_forward_mode) {
    pwm_forward.stop();
    pwm_reverse.start();
    is_forward_mode = false;
  }
  pwm_reverse.drive(speed);
};
