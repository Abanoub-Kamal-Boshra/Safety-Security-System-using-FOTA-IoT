/*******************************************************************/
/*******************************************************************/
/***************************     Author: Magdy     *************/
/***************************     Layer:HALL            *************/
/***************************     SWC:KPD               *************/
/***************************     Version:1.00          *************/
/***************************     Data:1-9-2020        *************/
/*******************************************************************/
/*******************************************************************/

#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H


//These are the elements of the Array
// and they represent the 16 keypad buttons
#define KPD_BUTTONS_VAL    {{'*',0,'#','D'},{7,8,9,'C'},{4,5,6,'B'},{1,2,3,'A'}}


// this is the PORT that the 8 pins of the keypad are connected to
#define KPD_PORT     GPIO_PORTB


// the COLUMNS of the keypad and to which PINS are they connected
#define COLLUM_PIN0  GPIO_PIN0
#define COLLUM_PIN1  GPIO_PIN1
#define COLLUM_PIN2  GPIO_PIN5
#define COLLUM_PIN3  GPIO_PIN11



// the ROWs of the keypad and to which PINS are they connected
#define ROW_PIN0  GPIO_PIN12
#define ROW_PIN1  GPIO_PIN13
#define ROW_PIN2  GPIO_PIN14
#define ROW_PIN3  GPIO_PIN10


// this value "0xff" is chosen to be returned to the user to show him that there is no pressed key on the keypad
#define NO_PRESSED_KEY  0xff

#endif       /*KPD_CONFIG_H*/

