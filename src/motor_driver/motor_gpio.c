#include "motor_gpio.h"

const struct direction forward = {1,0};
const struct direction back = {0,1};

void motor_GPIO_init(void){

    gpio_config_t motor = {0};
    // set which pins to use
    motor.pin_bit_mask = ((1ULL<<LEFT_FORWARD_PIN) | (1ULL<<LEFT_BACK_PIN) 
                            | (1ULL<<RIGHT_FORWARD_PIN) | (1ULL<<RIGHT_BACK_PIN));
    // set pins as in or output
    motor.mode = GPIO_MODE_OUTPUT;
    // set pull-up and pull-down to 0
    motor.pull_down_en = 0;
    motor.pull_up_en = 0;
    // disable interrupts
    motor.intr_type = GPIO_INTR_DISABLE;
    //configure the GPIO
    gpio_config(&motor);
}

void change_direction (int left_right, struct direction dir){
    if(left_right == LEFT){
        gpio_set_level(LEFT_FORWARD_PIN, dir.pin1);
        gpio_set_level(LEFT_BACK_PIN, dir.pin2);
    }
    else{
        gpio_set_level(RIGHT_FORWARD_PIN, dir.pin1);
        gpio_set_level(RIGHT_BACK_PIN, dir.pin2);
    }
}