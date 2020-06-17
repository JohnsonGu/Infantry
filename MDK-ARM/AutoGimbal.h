#ifndef AUTOGIMBAL_H
#define AUTOGIMBAL_H
#include "string.h"
#include "main.h"

#define BUFLENGTH  		128//最大接收的数据
#define DATELENGTH		8//有效数据

#define YAW_AUTO_SEN    0.005
#define PITCH_AUTO_SEN  0.005 //0.005

typedef struct
{
  float x;
	float y;
} CTRL;

typedef union
{
	CTRL Rec;
	uint8_t buf[DATELENGTH];
}BUF;

extern void  AUTO_control_init(void);
extern CTRL *get_AUTO_control_point(void);

#endif
