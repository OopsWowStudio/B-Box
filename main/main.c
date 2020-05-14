/*
    Making Plan <1>  B-Box project.
    Author: IAMLIUBO
    Blog: https://blogs.oopswow.com/
*/
#include "config.h"

static xQueueHandle B_Box_gpio_evt_queue = NULL;

static void IRAM_ATTR B_Box_gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(B_Box_gpio_evt_queue, &gpio_num, NULL);
}

static void B_Box_gpio_task(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(B_Box_gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}


void app_main(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = B_BOX_GPIO_OUTPUT_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    //turn off LED & LCD backlight
    gpio_set_level(RUN_LEN_PIN, 1);
    gpio_set_level(LCD_BL_PIN, 0);

    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.pin_bit_mask = B_BOX_GPIO_INPUT_SEL;  
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    /* after 3s hold the power pin to power on*/
    vTaskDelay(3000 / portTICK_RATE_MS);
    gpio_set_level(POWER_HOLD_PIN, 1);
    /* turn on the LED */
    gpio_set_level(RUN_LEN_PIN, 0);
    vTaskDelay(2000 / portTICK_RATE_MS);

    /* create gpio task for process the buttons */
    B_Box_gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(B_Box_gpio_task, "B_Box_gpio_task", 2048, NULL, 10, NULL);
    /* init the button gpio isr */
    gpio_install_isr_service(0);
    gpio_isr_handler_add(POWER_DETECT_PIN, B_Box_gpio_isr_handler, (void*) POWER_DETECT_PIN);
    gpio_isr_handler_add(BUTTON_1_PIN, B_Box_gpio_isr_handler, (void*) BUTTON_1_PIN);
    gpio_isr_handler_add(BUTTON_2_PIN, B_Box_gpio_isr_handler, (void*) BUTTON_2_PIN);
    gpio_isr_handler_add(BUTTON_3_PIN, B_Box_gpio_isr_handler, (void*) BUTTON_3_PIN);


    while(1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(RUN_LEN_PIN, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(RUN_LEN_PIN, 1);
    }
}
