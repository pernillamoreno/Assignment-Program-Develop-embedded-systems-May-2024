// make coverage_test_button for cmake 
// clear && make clean check for makefile
#include "bsp.h"

#ifndef DEVENV
#include <Arduino.h>
#endif

#define INVALID_PIN 0xFF


static uint8_t pin_num = INVALID_PIN;
static uint8_t pin_mode = INVALID_PIN;
static uint8_t pin_state = BSP_HIGH;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pin_num = pin;
    pin_mode = mode;
#ifndef DEVENV
    pinMode(pin, mode);

#endif
}

int bsp_digital_read(uint8_t pin)
{
    if (pin == pin_num)
    {
        return pin_state; // Return the simulated pin state
    }
    return INVALID_PIN; // Return an invalid state if pin does not match
}

uint8_t bsp_get_pin_num(void)
{
    return pin_num;
}

uint8_t bsp_get_pin_mode(void)
{
    return pin_mode;
}
void bsp_set_pin_state(uint8_t state)
{
    pin_state = state;
}

