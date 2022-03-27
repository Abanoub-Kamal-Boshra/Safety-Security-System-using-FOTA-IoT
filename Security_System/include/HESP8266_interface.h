


#ifndef ESP8266_INTERFACE_H_
#define ESP8266_INTERFACE_H_

void HESP8266_voidInit            ( void                                                    ) ;
void HESP8266_voidConnectToWiFi   ( u8 * SSID , u8 * Password                               ) ;
void HESP8266_voidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port                   ) ;
u8 HESP8266_u8ReceiveHttpReq( u8 * Copy_u8FileID , u8 * Copy_u8Length );
void HESP8266_voidSendHttpReq     ( u8 * Copy_u8ChannelID , u8 * Copy_u8Length , u8 * Copy_u8Value );
void HESP8266_voidSendHttpReq2( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ,u8 * Copy_u8Length2, u8 * Copy_u8Value );
void HESP8266_voidSendHttpReq3 ( u8 * Copy_u8ChannelID , u8 * Copy_u8Length , u8*Copy_u8Value) ;
void HESP8266_voidSendHttpReq4(  u8 * Copy_u8Length) ;
void HESP8266_voidSendHttpReq5( u8*Copy_u8temprature,u8*Copy_humidity,u8*Copy_gas);
void CIP_send(void) ;

void HESP8266_voidConnectToSrvTcp2 ( u8 * Copy_u8thingspeak , u8 * Copy_u8Port );
void HESP8266_voidConnectToSrvTcp ( u8 * Copy_u8IP , u8 * Copy_u8Port );

void HESP8266_voidCIPsend(u8 * Copy_u8Length);
void HESP8266_voidStealingSys(u8* Copy_u8Value);
//u8  S(u8 Copy_u8Port , u8 Copy_u8Pin);


#endif /* ESP8266_INTERFACE_H_ */
