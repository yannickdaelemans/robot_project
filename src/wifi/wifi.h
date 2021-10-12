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

#include "http_post.h"

#define EXAMPLE_ESP_MAXIMUM_RETRY  5
 
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

void wifi_init_sta(void);
void wifi_init(void);