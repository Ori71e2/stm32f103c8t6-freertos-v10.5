#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

static TaskHandle_t led_task_handle0 = NULL;
static TaskHandle_t led_task_handle1 = NULL;
static TaskHandle_t led_task_handle2 = NULL;

void led_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void led_task0(void *arg)
{
	while(1)                            
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		vTaskDelay(500/portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}
void led_task1(void *arg)
{
	while(1)                            
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(1000/portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}
void led_task2(void *arg)
{
	while(1)                            
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		vTaskDelay(2000/portTICK_PERIOD_MS);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
}
int main(void) 
{
	led_init();
	xTaskCreate(led_task0, "led_task0", 1024, NULL, 20, &led_task_handle0);
	xTaskCreate(led_task1, "led_task1", 1024, NULL, 20, &led_task_handle1);
	xTaskCreate(led_task2, "led_task2", 1024, NULL, 20, &led_task_handle2);
	vTaskStartScheduler();
	while(1);
}
