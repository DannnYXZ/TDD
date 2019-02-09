#include "unity_fixture.h"
#include "LedDriver.h"
#include <stdio.h>

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver){
    LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver){
}

TEST(LedDriver, LedsOffAfterCreate){
    uint16_t virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
TEST(LedDriver, TurnOnLedOne){
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(0x1, virtualLeds);
}
TEST(LedDriver, TurnOffLedOne){
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}
TEST(LedDriver, TurnOnMultipleLeds){
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}
TEST(LedDriver, TurnOffAnyLed){
    LedDriver_TurnAllOn();
    LedDriver_TurnOn(8); LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}
TEST(LedDriver, LedMemoryIsNotReadable){
    virtualLeds = 0xffff;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}
TEST(LedDriver, UpperAndLowerBounds){
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}
TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm){
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(33);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}
TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm){
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(33);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
IGNORE_TEST(LedDriver, OutOfBoundsProducesRuntimeError){
    LedDriver_TurnOn(-1);
    const char * msg = RuntimeErrorStub_GetLastError();
    //printf("%s", msg);
    //TEST_ASSERT_EQUAL_STRING("LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}
IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
}