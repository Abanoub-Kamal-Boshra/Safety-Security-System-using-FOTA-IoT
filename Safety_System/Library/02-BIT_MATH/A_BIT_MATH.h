/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** BIT_MATH								****************/
/*** Date    : 4/12/2020                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#ifndef A_BIT_MATH_H
#define A_BIT_MATH_H

#define SET_BIT(VAR,BIT)    VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)	VAR &= ~(1 << (BIT))
#define GET_BIT(VAR,BIT)	((VAR >> BIT) & 1)
#define TOG_BIT(VAR,BIT)	VAR ^=  (1 << (BIT))



#endif