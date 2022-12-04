
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
    uint32_t count = 0;
    uint16_t offset = 0;
    while (1)
    {
        xTaskNotifyWait(0, dma_transfer_state, &dma_transfer_state, portMAX_DELAY);
        if (WS2812B_PING == ws2812b_ping_or_pong())
        {
            gp_pwm_data_fill = gp_pwm_data_ping;
        }
        else
        {
            gp_pwm_data_fill = gp_pwm_data_pong;
        }
        dma_transfer_state = (task_dma_transfer_state_e)dma_transfer_state;
        if (TASK_DMA_TRANSFER_CMPLT == dma_transfer_state)
        {
            count++;
            if (NUM_STRIPS == count)
            {
                xSemaphoreGive(g_dma_transfer_semaphore);
            }
        }
        if (TASK_DMA_TRANSFER_STATE_RESET == dma_transfer_state)
        {
#if defined(STRIP_1_LENGTH)
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_1);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)g_pwm_reset, 50);
#endif
#if defined(STRIP_2_LENGTH)
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_2);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)g_pwm_reset, 50);
#endif
#if defined(STRIP_3_LENGTH)
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_3);
            HAL_TIM_PWM_Start_DMA(&g_tim15_handle, TIM_CHANNEL_2, (uint32_t *)g_pwm_reset, 50);
#endif
#if defined(STRIP_4_LENGTH)
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_4);
            HAL_TIM_PWM_Start_DMA(&g_tim16_handle, TIM_CHANNEL_1, (uint32_t *)g_pwm_reset, 50);
#endif
#if defined(STRIP_5_LENGTH)
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_5);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)g_pwm_reset, 50);
#endif
        }
#if defined(STRIP_1_LENGTH)
        if (dma_transfer_state & TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_1)
        {
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_1);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)(gp_pwm_data_fill + (offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (STRIP_NUM_1 * (uint32_t)WS2812B_BIT_RESET_CYCLES)), (STRIP_1_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        }
#endif
#if defined(STRIP_2_LENGTH)
        if (dma_transfer_state & TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_2)
        {
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_2);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)(gp_pwm_data_fill + (offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (STRIP_NUM_2 * (uint32_t)WS2812B_BIT_RESET_CYCLES)), (STRIP_2_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        }
#endif
#if defined(STRIP_3_LENGTH)
        if (dma_transfer_state & TASK_DMA_TRANSFER_STATE_TIM1_CHANNEL_3)
        {
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_3);
            HAL_TIM_PWM_Start_DMA(&g_tim15_handle, TIM_CHANNEL_2, (uint32_t *)(gp_pwm_data_fill + (offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (STRIP_NUM_3 * (uint32_t)WS2812B_BIT_RESET_CYCLES)), (STRIP_3_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        }
#endif
#if defined(STRIP_4_LENGTH)
        if (dma_transfer_state & TASK_DMA_TRANSFER_STATE_TIM15_CHANNEL_1)
        {
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_4);
            HAL_TIM_PWM_Start_DMA(&g_tim16_handle, TIM_CHANNEL_1, (uint32_t *)(gp_pwm_data_fill + (offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (STRIP_NUM_4 * (uint32_t)WS2812B_BIT_RESET_CYCLES)), (STRIP_4_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        }
#endif
#if defined(STRIP_5_LENGTH)
        if (dma_transfer_state & TASK_DMA_TRANSFER_STATE_TIM16_CHANNEL_1)
        {
            offset = ws2812_get_pwm_strip_offset(STRIP_BIT_5);
            HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)(gp_pwm_data_fill + (offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (STRIP_NUM_5 * (uint32_t)WS2812B_BIT_RESET_CYCLES)), (STRIP_5_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
        }
#endif
        while (!g_tim_pwm_transfer_cmplt)
        {
            osDelay(1);
        }
        if (WS2812B_PING == ws2812b_ping_or_pong())
        {
            xSemaphoreGive(g_dma_fill_semaphore);
        }
        g_tim_pwm_transfer_cmplt = false;
        xSemaphoreGive(g_dma_transfer_semaphore);

    }
}
