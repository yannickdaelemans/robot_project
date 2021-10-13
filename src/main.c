#include "motor_driver/drive.h"
#include "wifi/wifi.h"

httpd_handle_t server;
QueueHandle_t xQueue = NULL;
static const char *TAG = "MAIN TASK";

//const struct direction go_forward = {1,0};
//const struct direction go_back = {0,1};

void init_all(QueueHandle_t queue){
    motor_init();
    //init_queues();
    move_motor_floats(0.1,0.1);
    wifi_init();
    server = start_webserver(queue);
}

void destruct_all(void){
    stop_webserver(server);
}

void app_main() {
    ESP_LOGI(TAG, "start main");
    /* create queus */
    xQueue = xQueueCreate( 2, sizeof( float ) );
    ESP_LOGI(TAG, "start main 11");
    // initialize all peripherals
    init_all(xQueue);
    ESP_LOGI(TAG, "start main 22");
    
    BaseType_t xReturned;
    TaskHandle_t xHandle_driving = NULL;

    /* Create the task for driving, storing the handle. */
    xReturned = xTaskCreate(
                    vTask_drive_motor,      /* Function that implements the task. */
                    "task_drive_motor",     /* Text name for the task. */
                    50000 ,                    /* Stack size in words, not bytes. */
                    ( void * ) &xQueue,      /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,       /* Priority at which the task is created. */
                    &xHandle_driving );     /* Used to pass out the created task's handle. */

    if (xReturned != pdPASS){
        ESP_LOGI(TAG, "Task could not be created");
        // if task cannot be made, restart the esp
        esp_restart();
    } else{
        ESP_LOGI(TAG, "Start scheduler");
        // task are created succesfully, so start the scheduler
        //vTaskStartScheduler();
    }
    
    
}



