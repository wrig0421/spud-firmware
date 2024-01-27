
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "main.h"
#include "semaphore_create.h"
#include "ws2812b.h"
#include "numbers.h"
#include "task_dma_transfer.h"


typedef enum
{
    TASK_DMA_TRANSFER_STATE_RESET = 0,
    TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_1 = (1 << 0),
    TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_2 = (1 << 1),
    TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_3 = (1 << 2),
    TASK_DMA_TRANSFER_STATE_TIM15_CHANNEL_1 = (1 << 3),
    TASK_DMA_TRANSFER_STATE_TIM16_CHANNEL_1 = (1 << 4),
    TASK_DMA_TRANSFER_CMPLT = 0xFF
} task_dma_transfer_state_e;

extern bool g_tim_pwm_transfer_cmplt;
extern TIM_HandleTypeDef g_tim1_handle;
extern TIM_HandleTypeDef g_tim15_handle;
extern TIM_HandleTypeDef g_tim16_handle;
extern SemaphoreHandle_t g_dma_transfer_semaphore;
extern SemaphoreHandle_t g_dma_fill_semaphore;
extern p_pwm_data_t gp_pwm_data_fill;

uint16_t g_pwm_reset[50] = {0};
extern p_pwm_data_t gp_pwm_data_ping;
extern p_pwm_data_t gp_pwm_data_pong;
extern p_pwm_data_t gp_pwm_data_fill;

void task_dma_transfer(void *argument)
{
    uint32_t dma_transfer_state = 0;
    //uint32_t count = 0;
    uint16_t offset = 0;
    uint16_t strip_size = 0;
    while (1)
    {
        xTaskNotifyWait(0, dma_transfer_state, &dma_transfer_state, portMAX_DELAY);
        dma_transfer_state = (task_dma_transfer_state_e)dma_transfer_state;
        offset = ws2812_get_pwm_strip_offset(STRIP_NUM_1);
        strip_size = ws2812_get_strip_size(STRIP_NUM_1);
        HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        g_tim_pwm_transfer_cmplt = false;
        while (!g_tim_pwm_transfer_cmplt)
        {
            osDelay(1);
            portYIELD();
        }
    }
}
