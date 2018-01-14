#include "board.h"
#include "ucos_ii.h"

void RCCConfiguration(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_HCLKConfig(RCC_HCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    FLASH_SetLatency(FLASH_Latency_2);
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);

    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
	NVIC_SetVectorTable(0x8000000 , 0x000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}

void OSStickInit(void)
{

    RCC_ClocksTypeDef  rcc_clocks;
    /*获取系统频率*/
    RCC_GetClocksFreq(&rcc_clocks);
    /*配置HCLK作为SysTick时钟*/
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    /*配置自动加载数值*/
    SysTick_Config((rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC) - 1);
}


void STM32HwLedInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void OSHwLedON(INT8U id)
{
    GPIO_SetBits( GPIOB, GPIO_Pin_0);
}

void OSHwLedOFF(INT8U id)
{
    GPIO_ResetBits( GPIOB, GPIO_Pin_0);
}

void BoardInit(void)
{
    RCCConfiguration();
    OSStickInit();
    STM32HwLedInit();

}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    OS_SysTickHandler();
}

