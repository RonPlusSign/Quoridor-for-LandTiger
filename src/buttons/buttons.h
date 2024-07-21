#ifndef __BUTTON_H
#define __BUTTON_H

#include "../utils/CAN_utils.h"
#include "../utils/game_utils.h"
#include "../utils/structs.h"
#include "lpc17xx.h"


void BUTTON_init(void);

// Methods that handle interrupts
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

void INT0_Callback(void);
void KEY1_Callback(void);
void KEY2_Callback(void);
void EINT3_Callback(void);


#endif /* __BUTTON_H */
