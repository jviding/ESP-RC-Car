#include "pwm.h"
#include "driver/ledc.h"


void PWM::init_gpio() {
  gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << pin),
    .mode         = GPIO_MODE_OUTPUT,
    .pull_up_en   = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
  };
  gpio_config(&io_conf);
};

void PWM::init_pwm_timer() {
  ledc_timer_config_t timer_conf = {
    .speed_mode      = LEDC_HIGH_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .timer_num       = LEDC_TIMER_0,
    .freq_hz         = 1000,
    .clk_cfg         = LEDC_AUTO_CLK,
  };
  ledc_timer_config(&timer_conf);
};

void PWM::init_pwm_channel() {
  ledc_channel_config_t chan_conf = {
    .gpio_num   = pin,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .channel    = channel,
    .timer_sel  = LEDC_TIMER_0,
    .duty       = 0,
  };
  ledc_channel_config(&chan_conf);
};

PWM::PWM(gpio_num_t pin_out, ledc_channel_t ledc_channel_num)
  : pin(pin_out), channel(ledc_channel_num) {
  init_gpio();
  init_pwm_timer();
  init_pwm_channel();
};

void PWM::drive(uint16_t speed) {
  // Max speed 100
  speed = (speed > 100 ? 100 : speed);
  // 8-bit resolution = 256
  uint32_t duty_cycle = (speed * 256) / 100;
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty_cycle);
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel);
};