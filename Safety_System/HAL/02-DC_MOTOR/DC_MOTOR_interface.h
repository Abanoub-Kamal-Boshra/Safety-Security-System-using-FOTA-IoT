/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** DC-MOTOR - Interface       		    ****************/
/*** Date    : 6/4/2021                     ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#ifndef DC_MOTOR_INTERFACE_H
#define DC_MOTOR_INTERFACE_H

//(1)You should pass to this functions the direction of motion and at which pins you will connect the H_pridge 
void HDC_MOTOR_voidMoveMotor(u8 Copy_u8Direction ,u8 Copy_u8Port, u8 PIN_A , u8 PIN_B);


#define ClockWise_DC_MOTOR           1
#define CounterClockWise_DC_MOTOR    2
#define STOP_DC_MOTOR                0

//(2)

void HDC_MOTOR_voidStopMotor(u8 Copy_u8Port,u8 PIN_A , u8 PIN_B);







#endif