/*******************************************************************************/
/******                  Author  :  Solyma                      ****************/
/******                  MQ_2_interface							****************/
/******                  Date    : 28/6/2020                    ****************/
/******                  Version :  01                          ****************/
/*******************************************************************************/

#ifndef MQ_2_INTERFACE_H
#define MQ_2_INTERFACE_H

#define V_REF_mv   3300UL
#define V_CC_mv    3300
#define RL_ohm     1000

#define MQ2_Smoking_Value_mv   500 // this is the threshold value of firing
#define MQ2_ON_Fire_Value_mv   650




//(1) /*  USED  */
u32 HMQ_2_u32ReadAnalogVolt_mv(u8 Copy_u8Channel ); // Pass the channel which is connected with MQ2 Sensor

/*
 * EX :
   	   u32 HMQ_2_u32ReadAnalog( ADC_CH0)
   	   	   	   	   	   	   	  ( ADC_CH1)
   	   	   	   	   	   	   	  	  .
   	   	   	   	   	   	   	  	  .
   	   	   	   	   	   	   	  ( ADC_CH9)
 * */


//(2)
f32 HMQ_2_f32_ReadData_ppm(u8 Copy_u8Channel);      /*****  Not Finished *****/




#endif
