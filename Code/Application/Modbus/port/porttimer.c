/*
 * FreeModbus Libary: LPC214X Port
 * Copyright (C) 2007 Tiago Prado Lone <tiago@maxwellbohr.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2007/04/24 23:15:18 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_DeInit(TIM2);

    /*
    3.5个字符时间区分不同的帧，即接收到的两个字符之间时间间隔小于3.5个字符
    时间时认为是同一个帧的，如果间隔大于3.5个字符时间则认为是不同帧的
    在一般的串口通信中，发送1个字符需要：1位起始位，8位数据位，1位校验位(可无),
    1位停止位,总共 1+8+1+1 = 11位，3.5个字符时间就是 3.5 * 11 = 38.5位，
    假如波特率是9600,那么传输1位的时间是1000/9600 = 0.10416667(ms) ,
    这样，3.5个字符时间就大约是 4 ms ,即定时器需要的中断时间
    */
#if 0
    TIM_TimeBaseStructure.TIM_Period = 0x7E54;		  //CLK==24MHz ((1000000000/9600)*11*3.5)/(1000/24) == 0x7e54
    TIM_TimeBaseStructure.TIM_Prescaler = 0x3;
#endif
    // 这个就是预分频系数，7200/72M = 0.0001,即每100us计数值加1
    //10us x 50 = 5ms,即5ms中断一次
    TIM_TimeBaseStructure.TIM_Period = 50;
    TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	return TRUE;
}


void
vMBPortTimersEnable(  )
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void vMBPortTimersDisable(  )
{
	TIM_SetCounter(TIM2, 0);
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
}

void TIMERExpiredISR( void )
{
    (void)pxMBPortCBTimerExpired();
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  	TIMERExpiredISR();
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}