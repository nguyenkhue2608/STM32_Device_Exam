#ifndef __PLATFORM_H
#define __PLATFORM_H
//*************************** USE HAL Platform ************************************************/
#define USE_HAL_LIB
#define USE_STM32F1XX


#ifdef USE_HAL_LIB
#ifdef USE_STM32F1XX
#include "stm32f1xx_hal.h"
#endif
#endif
#endif
