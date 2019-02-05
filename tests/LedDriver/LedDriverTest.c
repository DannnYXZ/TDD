#include "unity_fixture.h"
#include "LedDriver.h"

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

