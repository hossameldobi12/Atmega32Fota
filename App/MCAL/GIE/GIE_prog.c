/**
 * @file GIE_prog.c
 * @author Hossam Eldobi (hossameldobi12@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "STD_MACROS.h"
#include "GIE_private.h"
#include  "GIE_config.h"
#include  "GIE_int.h"



void GIE_enable (void)
{
  SET_BIT(SREG,7);
}
void GIE_disable (void)
{
  CLR_BIT(SREG,7);
}