#include "http_post.h"

static const char *TAG = "server station";

// Look at website: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_server.html

/* Our URI handler function to be called during GET /uri request */
esp_err_t get_handler(httpd_req_t *req)
{
    /* Send a simple response */
    const char resp[] = "URI GET Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
 
/* To send Post see: https://stackoverflow.com/questions/16229852/post-sending-a-post-request-in-a-url-itself */
// send: curl -v -H "Content-Type: application/json" -X POST -d '255' http://192.168.0.11:80/uri/post
/* Our URI handler function to be called during POST /uri request */
esp_err_t post_handler(httpd_req_t *req)
{
    /* Destination buffer for content of HTTP POST request.
     * httpd_req_recv() accepts char* only, but content could
     * as well be any binary data (needs type casting).
     * In case of string data, null termination will be absent, and
     * content length would give length of string */
    ESP_LOGI(TAG, "handling POST request");
    char content[100];

    /* Truncate if content length larger than the buffer */
    size_t recv_size = MIN(req->content_len, sizeof(content));
    ESP_LOGI(TAG, "received %d size", recv_size);
    // hardcoding it into 100, CHANGE LATER!!
    //recv_size = sizeof(content);
    ESP_LOGI(TAG, "getting post data");
    ESP_LOGI(TAG, "%s", req->uri);
    

    int ret = httpd_req_recv(req, content, recv_size);
    ESP_LOGI(TAG, "getting return");
    ESP_LOGI(TAG, "return value: %d", ret);
    if (ret <= 0) {  /* 0 return value indicates connection closed */
        /* Check if timeout occurred */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            /* In case of timeout one can choose to retry calling
             * httpd_req_recv(), but to keep it simple, here we
             * respond with an HTTP 408 (Request Timeout) error */
            ESP_LOGI(TAG, "Time out occured, 408 send");
            httpd_resp_send_408(req);
        }
        /* In case of error, returning ESP_FAIL will
         * ensure that the underlying socket is closed */
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "POST request in buffer");
    ESP_LOGI(TAG, "POST request is: %s", content);
    float float_buf [2] = {0};

    if (put_in_buffer(float_buf, content, recv_size) == 0){
        ESP_LOGI(TAG, "Buffer could not be converted");
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "floats in buffer %f and %f", float_buf[0], float_buf[1]);

    /* Send a simple response */
    const char resp[] = "URI POST Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    //write method to drive motors from main, use other buffer?
    return ESP_OK;
}

/* URI handler structure for GET /uri */
httpd_uri_t uri_get = {
    .uri      = "/uri/get",
    .method   = HTTP_GET,
    .handler  = get_handler,
    .user_ctx = NULL
};

/* URI handler structure for POST /uri */
httpd_uri_t uri_post = {
    .uri      = "/uri/post",
    .method   = HTTP_POST,
    .handler  = post_handler,
    .user_ctx = NULL
};

/* Function for starting the webserver */
httpd_handle_t start_webserver(void)
{
    /* Generate default configuration */
    // server port 80
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_post);
        ESP_LOGI(TAG, "server has been started");
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

/* Function for stopping the webserver */
void stop_webserver(httpd_handle_t server)
{
    if (server) {
        /* Stop the httpd server */
        ESP_LOGI(TAG, "stopping server");
        httpd_stop(server);
    }
}

int put_in_buffer(float *pointer_float_buf, char* buf, size_t len){
    char intermediate_one [32];
    char intermediate_two [32];
    int i = 0;
    while (*(buf) != '&' && i + 1 < len) {
        intermediate_one [i] = *(buf++);
        i++;
    }
    buf++;
    int j=0;;
    while(*(buf) != '&' && j + i + 1 < len){
        intermediate_two [j] = *(buf++);
        j++;
    }

    *pointer_float_buf = strtof(intermediate_one, NULL);
    *(pointer_float_buf+1) = strtof(intermediate_two, NULL);

    return 1;
}