#ifndef GPIO_H_
#define GPIO_H_

#include "Config.h" 



/************************************************************************************************
 *           Function Name : SetPortDirection									 				*
 *			 Function Returns : Void										  					*
 *           Function Arguments : PortName, Direction			   	    						*
 *           Function Description : Set the direction of given pin 		       					*
 *									Direction may be INPUT or OUTPUT           					*
 ************************************************************************************************/
	
void SetPortDirection (pName PortName, Direction Dir); 

/************************************************************************************************
 *           Function Name : SetPinDirection									 				*
 *			 Function Returns : Void										  					*
 *           Function Arguments : PortName, PinNumber, Direction			   					*
 *           Function Description : Set the direction of given pin 		       					*
 *									Direction may be INPUT or OUTPUT           					*
 ************************************************************************************************/
 
void SetPinDirection (pName PortName, uint8 PinNumber, Direction Dir); 

/************************************************************************************************
 *           Function Name : WriteOnPort									                    *
 *			 Function Returns : Void										                    *
 *           Function Arguments : PortName, Value 						                        *
 *           Function Description : Set the value of given Port 		           					*
 *									Value may be (0->255)                   					*
 ************************************************************************************************/
 
void WriteOnPort (pName PortName, uint8 value); 

/************************************************************************************************
 *           Function Name : WriteOnpin										                    *
 *			 Function Returns : Void										                    *
 *           Function Arguments : PortName, PinNumber, Value			                        *
 *           Function Description : Set the value of given pin 		           					*
 *									Value may be LOW = 0 or HIGH = 1                   			*
 ************************************************************************************************/
 
void WriteOnpin (pName PortName, uint8 PinNumber, Value val);

/************************************************************************************************
 *           Function Name : ReadPort										                    *
 *			 Function Returns : uint8										                    *
 *           Function Arguments : PortName				          	           	                *
 *           Function Description : Reverse the value of the given port  					    *
 *									Value may be 0 -> 255	 					                *                                            *
 ************************************************************************************************/
 
uint8 ReadPort (pName PortName); 

/************************************************************************************************
 *           Function Name : ReadPin									                    *
 *			 Function Returns : uint8										                    *
 *           Function Arguments : PortName, PinNumber            	           	                *
 *           Function Description : Reverse the value of the given pin in the given port        *
 *									Value may be LOW or HIGH 					                *                                            *
 ************************************************************************************************/
 
uint8 ReadPin (pName PortName, uint8 PinNumber); 
#endif