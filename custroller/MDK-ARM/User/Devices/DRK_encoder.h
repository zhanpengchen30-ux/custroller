#ifndef __DRK_ENCODER_H
#define __DRK_ENCODER_H
#include "can.h"
#include "cmsis_os.h"
#include <stdint.h>
#include <stdbool.h>
#include "can_receive.h"



#define DEVICE_STD_ID						(0x140)
#define DEVICE_STD_BOARDCAST_ID	(0x280)
#define DRK_encoder_ID_1 0x01
#define DRK_encoder_ID_2 0x02
#define DRK_encoder_ID_3 0x03
#define DRK_encoder_ID_4 0x04
#define DRK_encoder_ID_5 0x05
#define DRK_encoder_ID_6 0x06

typedef struct{
	uint8_t DataLength; //读回来的数据长度
	uint8_t EncoderAddress;  //读回来的编码器地址
  uint8_t ScriptCode; //读回来的指令码
	uint32_t EncoderValue;  //读回来的编码器值
	uint32_t EncoderAngle;  //计算真实角度

	uint8_t  InfoUpdateFlag;		  //信息读取更新标志
	uint16_t InfoUpdateFrame;	  //帧率
	uint8_t  OffLineFlag;		    //设备离线标志
}DRK_encoder_t;


extern DRK_encoder_t DRK_encoder[6];

void read_DRK_encoder_value(int DRK_encoder_ID);
void DRK_encoder_getInfo(Can_Export_Data_t RxMessage);
void Send_EncoderAngle(DRK_encoder_t *encoder , int DRK_encoder_ID);
void Receive_EncoderAngle(DRK_encoder_t *encoder);
#endif
