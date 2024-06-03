// Use this for implement the test-program
// clear && make clean check for makefile
#include "bsp.h"
#include "unity.h"
#include "button.h"

#ifndef DEVENV
#include <Arduino.h>
#endif

static const uint8_t pin = 34;

void setUp(void)
{
   
}

void tearDown(void) {}

void test_button_initialization(void)
{
    // Ensure the button state is uninitialized before initialization
    TEST_ASSERT_FALSE(button_get_state() != BUTTON_UNINITITIALIZED);

    // Ensure the state is uninitialized before any update
    TEST_ASSERT_EQUAL_UINT8(BUTTON_UNINITITIALIZED, button_get_state());

    // Call button_update_state without initializing the button
    button_update_state();

    // Ensure the state is still uninitialized after the update attempt
    TEST_ASSERT_EQUAL_UINT8(BUTTON_UNINITITIALIZED, button_get_state());

    // Initialize the button
    button_init(pin);
    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(BSP_INPUT_PULLUP, bsp_get_pin_mode());
}

void test_button_state_transitions(void)
{
    TEST_ASSERT_FALSE(button_get_state() == BUTTON_PRESSED);

    
    button_init(pin);

    // Simulate button press
    for (int i = 0; i < 5; ++i)
    {
        bsp_set_pin_state(BSP_LOW);
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_state());

    // Simulate button  hold
    bsp_set_pin_state(BSP_LOW);
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());

#ifndef DEVENV
    delay(1000);
#endif

    // Simulate release of button
    for (int i = 0; i < 5; ++i)
    {
        bsp_set_pin_state(BSP_HIGH);
        button_update_state();
    }
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, button_get_state());

    // Check final release-state
    bsp_set_pin_state(BSP_HIGH);
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
}

#ifdef DEVENV
int main(void)
#else
void loop() {}
void setup()
#endif

{
    UNITY_BEGIN();

    RUN_TEST(test_button_initialization);
    RUN_TEST(test_button_state_transitions);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif

        
}
