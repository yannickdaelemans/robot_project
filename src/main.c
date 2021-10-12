#include "motor_driver/drive.h"
#include "wifi/wifi.h"

httpd_handle_t server;

//const struct direction go_forward = {1,0};
//const struct direction go_back = {0,1};

void init_all(void){
    //motor_init();
    wifi_init();
    server = start_webserver();
}

void destruct_all(void){
    stop_webserver(server);
}

void app_main() {
    init_all();
    //motor_forward();
}
