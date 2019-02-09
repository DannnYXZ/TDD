#ifndef D_LedDriver_H
#define D_LedDriver_H
#endif
#include <stdint.h>
#define TRUE 1
#define FALSE 0
typedef int BOOL;

void LedDriver_Create(uint16_t * ledsAddress);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);