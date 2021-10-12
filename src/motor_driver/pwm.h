#include <math.h>
#include "driver/ledc.h"
#include "esp_err.h"

#define MOTOR_PWM_CHANNEL_LEFT LEDC_CHANNEL_1
#define MOTOR_PWM_CHANNEL_RIGHT LEDC_CHANNEL_2
#define MOTOR_PWM_TIMER LEDC_TIMER_1
#define MOTOR_PWM_BIT_NUM LEDC_TIMER_10_BIT

#define RIGHT_PWM_PIN GPIO_NUM_19
#define LEFT_PWM_PIN GPIO_NUM_21

void motor_pwm_init(void);
void motor_pwm_set(float left_duty_fraction, float right_duty_fraction);