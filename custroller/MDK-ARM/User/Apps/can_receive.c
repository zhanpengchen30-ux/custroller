#include "can_receive.h"
#include "bsp_can.h"
#include "cmsis_os.h"
#include "DRK_encoder.h"



Can_Export_Data_t Can1_Export_Data;//用来存储接收到的CAN1数据
Can_Export_Data_t Can2_Export_Data;//用来存储接收到的CAN2数据


/**
  * @brief  处理CAN接收到的数据
  */
void Process_CAN1_Message(Can_Export_Data_t *CanData)
{
    switch (CanData->CAN_RxHeader.StdId)
    {

				case 0x01:
				case 0x02:
				case 0x03:
				case 0x04:
				case 0x05:
				case 0x06:
             DRK_encoder_getInfo(*CanData);
				     break;	
			    
				default:
            // Ignore unhandled IDs
            break;
    }
}

void Process_CAN2_Message(Can_Export_Data_t *CanData)
{

	    switch (CanData->CAN_RxHeader.StdId)
    {



        default:
            // Ignore unhandled IDs
            break;
		}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    Can_Export_Data_t *CanData;

    if (hcan->Instance == CAN1)
    {
        CanData = &Can1_Export_Data; // Use the correct data structure for CAN1
			  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanData->CAN_RxHeader, CanData->CAN_RxMessage);
        Process_CAN1_Message(CanData);

    }
    else if (hcan->Instance == CAN2)
    {
        CanData = &Can2_Export_Data; // Use the correct data structure for CAN2
			  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanData->CAN_RxHeader, CanData->CAN_RxMessage);
        Process_CAN2_Message(CanData); // Pass CanData directly
    }
    else
    {
        return; // Invalid CAN instance
    }

		
		
//    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CanData->CAN_RxHeader, CanData->CAN_RxMessage);
}






/**
 * @brief Task to receive and process CAN messages.
 */
void vTaskCanReceives(void const * argument)
{
    for (;;)
    {
        // 检查CAN1 FIFO是否有消息
        if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) > 0)
        {
            HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &Can1_Export_Data.CAN_RxHeader, Can1_Export_Data.CAN_RxMessage);
            Process_CAN1_Message(&Can1_Export_Data); // 处理CAN1消息
        }

        // 检查CAN2 FIFO是否有消息
        if (HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0) > 0)
        {
            HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &Can2_Export_Data.CAN_RxHeader, Can2_Export_Data.CAN_RxMessage);
            Process_CAN2_Message(&Can2_Export_Data); // 处理CAN2消息
        }

        vTaskDelay(10); // 控制任务执行频率
    }
}

