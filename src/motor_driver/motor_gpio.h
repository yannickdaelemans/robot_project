#include "pwm.h"
#include "driver/gpio.h"

/*
 * Motor is driven using an L298N chip. 
 * This needs a pwm signal and a foward (1 and 0) or backward (0 and 1) signal.
 * pwm comes out of p21 (left motor) and p19 (right motor)
 * p22 and p23 (1 - 0 forward) controls left motor
 * p17 and p18 (1 - 0 forward) controls right motor
*/

#define LEFT_FORWARD_PIN    GPIO_NUM_22
#define LEFT_BACK_PIN       GPIO_NUM_23
#define RIGHT_FORWARD_PIN   GPIO_NUM_17
#define RIGHT_BACK_PIN      GPIO_NUM_18

#define LEFT    1
#define RIGHT   0


typedef struct direction{
    int pin1;
    int pin2;
} dir;

void motor_GPIO_init(void);
void change_direction (int left_right, struct direction dir);