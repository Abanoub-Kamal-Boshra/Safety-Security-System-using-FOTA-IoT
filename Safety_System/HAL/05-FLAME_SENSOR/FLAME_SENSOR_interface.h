/*******************************************************************************/
/******                  Author  :  Solyma                      ****************/
/******                  FLAME_SENSOR_interface					****************/
/******                  Date    : 3/7/2021                    ****************/
/******                  Version :  01                          ****************/
/*******************************************************************************/

#ifndef FLAME_SENSOR_INTERFACE_H
#define FLAME_SENSOR_INTERFACE_H


#define V_REF_mv   3300UL
#define V_CC_mv    3300
#define RL_ohm     10000

                            /******  Values of light intensity in mV if " V_out = V_Rl " *******/
#define FLAME_SENSOR_DARK_mv			 5
#define FLAME_SENSOR_ORDINARY_LIGHT_mv   55
#define FLAME_SENSOR_BRIGHTING_mV        100
#define FLAME_SENSOR_FIRE_mV			 110	

							//(1) /***********  USED  **************/
u32 HFLAME_SENSOR_u32ReadAnalogVolt_mv(u8 Copy_u8Channel ); // Pass the channel which is connected with Flame Sensor

/*
 * EX :
 *  	   HFLAME_SENSOR_u32ReadAnalogVolt_mv 	( ADC_CH0)
 *  											( ADC_CH1)
 *		     										.	
 *	    											.
 *  											( ADC_CH9)
 * */








#endif