#include "LedDriver.h"
#include "RuntimeErrorStub.h"
enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
static uint16_t * ledsAddress;
static uint16_t ledsImage;

void LedDriver_Create(uint16_t * address){
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    *address = ledsImage;
}
static uint16_t convertLedNumberToBit(int ledNumber){
    return 1 << (ledNumber - 1);
}
static updateHardware(void){
    *ledsAddress = ledsImage;
}
static BOOL IsLedOutOfBounds(int ledNumber){
    return ledNumber <= 0 || ledNumber > 16;
}
void LedDriver_TurnOn(int ledNumber){
    if(IsLedOutOfBounds(ledNumber))
        return;
    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}
void LedDriver_TurnOff(int ledNumber){
    if(IsLedOutOfBounds(ledNumber))
        return;
    ledsImage &= ~convertLedNumberToBit(ledNumber);
    updateHardware();
}
void LedDriver_TurnAllOn(){
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}
void LedDriver_Destroy(void){
}
BOOL LedDriver_IsOn(int ledNumber){
    if(IsLedOutOfBounds(ledNumber))
        return FALSE;
    return ledsImage & convertLedNumberToBit(ledNumber);
}
BOOL LedDriver_IsOff(int ledNumber){
    return !LedDriver_IsOn(ledNumber);
}
void LedDriver_TurnAllOff(void){
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}