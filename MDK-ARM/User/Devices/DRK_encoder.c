#include "can_receive.h"
#include "cmsis_os.h"
#include <stdint.h>
#include "DRK_encoder.h"
#include "usart.h"

DRK_encoder_t DRK_encoder[6];

void read_DRK_encoder_value(int DRK_encoder_ID) // 读取DRK编码器的值
{
	CAN_TxHeaderTypeDef tx_header;//用来存储发送的CAN帧的头部信息，包括帧ID、帧类型、帧长度等
  uint8_t             tx_data[8];//用来存储接发送的CAN帧的数据部分
	
	tx_header.StdId = DRK_encoder_ID;
  tx_header.IDE   = CAN_ID_STD;
  tx_header.RTR   = CAN_RTR_DATA;                                                                                               
  tx_header.DLC   = 8;//定义发送格式

  tx_data[0] = 0x04;
  tx_data[1] = DRK_encoder_ID;//设备 ID
  tx_data[2] = 0x01;
  tx_data[3] = 0x00;
	
  HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,(uint32_t*)CAN_TX_MAILBOX0); //函数会根据指定的邮箱号将CAN帧发送到对应的邮箱
												//CAN, 信息格式，      信息内容，  指向邮箱号的指针
}


void DRK_encoder_getInfo(Can_Export_Data_t RxMessage)  // 从接收到的CAN消息中解析DRK编码器信息
	{
    uint32_t DRK_ID;
    DRK_ID = (int32_t)(RxMessage.CAN_RxHeader.StdId - 0x01);// 假设 CAN_ID 对应编码器的 DRK_encoder_ID
    
    DRK_encoder[DRK_ID].DataLength     = (uint8_t)(RxMessage.CAN_RxMessage[0]);
		DRK_encoder[DRK_ID].EncoderAddress = (uint8_t)(RxMessage.CAN_RxMessage[1]);
		DRK_encoder[DRK_ID].ScriptCode     = (uint8_t)(RxMessage.CAN_RxMessage[2]);
    DRK_encoder[DRK_ID].EncoderValue   = (uint32_t)(RxMessage.CAN_RxMessage[6] << 24 | 
		                                                RxMessage.CAN_RxMessage[5] << 16 | 
		                                                RxMessage.CAN_RxMessage[4] <<  8 | 
		                                                RxMessage.CAN_RxMessage[3]);
		DRK_encoder[DRK_ID].EncoderAngle   = (uint32_t)(DRK_encoder[DRK_ID].EncoderValue * 360 / 1024);


    // 帧率统计，数据更新标志位
    DRK_encoder[DRK_ID].InfoUpdateFrame++;
    DRK_encoder[DRK_ID].InfoUpdateFlag = 1;
		
}
	
void Send_EncoderAngle(DRK_encoder_t *encoder , int DRK_encoder_ID)  // 通过串口发送编码器角度数据
	{
    uint8_t data[4];
    uint32_t angle = encoder->EncoderAngle;

    // 添加编码器ID作为第一个字节
    data[0] = DRK_encoder_ID;  // 1,2,3 分别代表三个不同的编码器
    
    // 角度数据（与原函数相同）
    data[1] = (angle >> 0) & 0xFF;
    data[2] = (angle >> 8) & 0xFF;
    data[3] = 0xFF;  // 结束标志
    // 发送数据
    HAL_UART_Transmit(&huart7, data, 4, 100);

}

void Receive_EncoderAngle(DRK_encoder_t *encoder) // 通过串口接收编码器角度数据
	{
    uint8_t data[4];
    uint32_t angle;

    // 接收数据
    HAL_UART_Receive(&huart6, data, 4, 100);

    // 将字节数组转换回EncoderAngle（小端模式）
    angle = (uint32_t)data[0] | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 24);

    encoder->EncoderAngle = angle;
}
