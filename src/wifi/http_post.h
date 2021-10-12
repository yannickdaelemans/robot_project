#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <sys/param.h>
#include "tcpip_adapter.h"
#include <esp_http_server.h>
 
#include "lwip/err.h"
#include "lwip/sys.h"

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);
int put_in_buffer(float *pointer_float_buf, char* buf, size_t len);