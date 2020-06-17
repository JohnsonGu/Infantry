#include "AutoGimbal.h"

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

uint8_t sbus_rx_buffer[BUFLENGTH];
BUF RresPi;
void  AUTO_control_init(void)
{
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);								//使能串口空闲中断（两次消息的间隙会触发）
		HAL_UART_Receive_DMA(&huart1,sbus_rx_buffer,BUFLENGTH);
}

	
void Usart1Receive_IDLE(void)
{
	HAL_UART_DMAStop(&huart1);
	uint8_t data_length  = BUFLENGTH - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);  //36-剩余空间 得到已经接收的数量
	if( data_length == DATELENGTH )
	{
		memcpy(RresPi.buf,sbus_rx_buffer,data_length);
		//	Latest_Remote_Control_Pack_Time = HAL_GetTick();//用于掉线检测
	}
	memset(sbus_rx_buffer,0,BUFLENGTH);
	HAL_UART_Receive_DMA(&huart1,sbus_rx_buffer,BUFLENGTH);
}

void USART1_IRQHandler(void)
{
	if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   
	{
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);                    
			Usart1Receive_IDLE();                          
	}
  HAL_UART_IRQHandler(&huart1);
}

CTRL *get_AUTO_control_point(void)
{
	return &RresPi.Rec;
}
