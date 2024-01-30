#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "motor/motor.h"

uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};


extern "C" {
  void app_main(void);
};


const moto_conf_t moto_conf = {
  .forward_conf = {
    .pin_high         = GPIO_NUM_19,
    .pin_low          = GPIO_NUM_18,
    .ledc_channel_num = LEDC_CHANNEL_0,
  },
  .reverse_conf = {
    .pin_high         = GPIO_NUM_17,
    .pin_low          = GPIO_NUM_16,
    .ledc_channel_num = LEDC_CHANNEL_1,
  },
};


void app_main() {
  
  Motor motor(moto_conf);

  while (1) {

    printf("Forward\n");
    /*for (uint16_t i = 0; i < 100; i += 10) {
      motor.forward(i);
      printf(" - Speed: %d\n", i);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }*/
    motor.forward(100);
    vTaskDelay(pdMS_TO_TICKS(3000));

    printf("Reverse\n");
    /*for (uint16_t i = 0; i < 100; i += 10) {
      motor.reverse(i);
      printf(" - Speed: %d\n", i);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }*/
    motor.reverse(100);
    vTaskDelay(pdMS_TO_TICKS(3000));

    printf("Stop\n");
    motor.forward(0);
    motor.reverse(0);
    //vTaskDelay(pdMS_TO_TICKS(3000));
    vTaskDelay(pdMS_TO_TICKS(3000));

  }
};