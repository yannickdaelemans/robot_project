#include "drive.h"

static const char *TAG = "drive TASK";

const struct direction go_forward = {1,0};
const struct direction go_back = {0,1};
const struct direction stand_still = {0,0};

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

void move_motor_floats(float up, float side){
    // if up is possitive, you can go forward, otherwise go backwards
    dir dir_left = go_forward;
    dir dir_right = go_forward;

    float right = (fabsf(up) - side);
    float left =  (fabsf(up) + side);

    if (left < 0){
        dir_left = go_back;
    } 
    if (right < 0){
        dir_right = go_back;
    }
    if (left < 0 || left > 0){
        left = 1;
    }
    if (right < 0 || right > 0){
        right = 1;
    }
    if(up == 0 && side == 0){
        dir_left = stand_still;
        dir_right = stand_still;
    }

    move_motor(dir_left, fabsf(left), dir_right, fabsf(right));
}

void move_motor(dir dir_left, float pwm_left,
                dir dir_right, float pwm_right){
    motor_pwm_set(pwm_left, pwm_right);
    change_direction (RIGHT, dir_right);
    change_direction (LEFT, dir_left);
}

// Task to be created.
void vTask_drive_motor( void * pvParameters ){
    ESP_LOGI(TAG, "start task");
    QueueHandle_t task_queue = *(QueueHandle_t*) pvParameters;
    static float buffer [2];
    ESP_LOGI(TAG, "queue created here");
    
    while(1){
        // Task code goes here.
        ESP_LOGI(TAG, "inside while loop");
        int number_waiting = uxQueueMessagesWaiting(task_queue);
        ESP_LOGI(TAG, "inside queue %d", number_waiting);
        if (number_waiting < 2 ){
            ESP_LOGI(TAG, "waiting for queue, in queue %d", number_waiting);
        } else{
            int read_buf_one = xQueueReceive(task_queue, &buffer[0], 0);
            int read_buf_two = xQueueReceive(task_queue, &buffer[1], 0);
            if(read_buf_one && read_buf_two){
                ESP_LOGI(TAG, "received data from queue");
                ESP_LOGI(TAG, "floats in buffer %f and %f", buffer[0], buffer[1]);
                move_motor_floats(buffer[0], buffer[1]);
            } else {
                ESP_LOGI(TAG, "error getting data from queue");
                ESP_LOGI(TAG, "return values queue: %d %d", read_buf_one, read_buf_two);
            }
        }

    }

}