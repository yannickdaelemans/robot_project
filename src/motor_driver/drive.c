#include "drive.h"

const struct direction go_forward = {1,0};
const struct direction go_back = {0,1};

void motor_init(void){
    motor_GPIO_init();
    motor_pwm_init();
}

void motor_forward(void){
    // make motor GPIO go forward
    change_direction (LEFT, go_forward);
    change_direction (RIGHT, go_forward);
    // put PWM at 0,7 for both
    motor_pwm_set(0.5, 0.5);
}

void motor_back(void){
    // make motor GPIO go back
    change_direction (LEFT, go_back);
    change_direction (RIGHT, go_back);
    // put PWM at 0,7 for both
    motor_pwm_set(0.5, 0.5);
}

void motor_turn_left(void){
    // make motor GPIO go left
    change_direction (LEFT, go_back);
    change_direction (RIGHT, go_forward);
    // put PWM at 0,7 for both
    motor_pwm_set(0.5, 0.5);
}

void motor_turn_right(void){
    // make motor GPIO go right
    change_direction (RIGHT, go_back);
    change_direction (LEFT, go_forward);
    // put PWM at 0,7 for both
    motor_pwm_set(0.5, 0.5);
}

void move_motor_floats(float left, float right){
    dir dir_left = go_forward;
    //dir_left = {.pin1 = 1, .pin2 = 0};
    dir dir_right = go_forward;
    if(left < 1){
        left = fabsf(left);
        dir_left = go_back;
    }
    if(right < 1){
        right = fabsf(right);
        dir_right = go_back;
    }
    move_motor(dir_left, left, dir_right, right);
}

void move_motor(dir dir_left, float pwm_left,
                dir dir_right, float pwm_right){
    motor_pwm_set(pwm_left, pwm_right);
    change_direction (RIGHT, dir_right);
    change_direction (LEFT, dir_left);
}