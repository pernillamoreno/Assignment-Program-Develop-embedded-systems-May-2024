#include "bsp.h"
#include "button.h"

#define SAMPLES (5U)                                // Define the number of samples to be used for debouncing.
static uint8_t button_pin = BUTTON_UNINITITIALIZED; // Variable, pin connected to the button.
static uint8_t state = BUTTON_UNINITITIALIZED;      // Variable, current state of the button.
static uint8_t samples[SAMPLES] = {0};              // Array to store the samples for debouncing.
static uint8_t sample_index = 0;                    


void button_init(uint8_t pin)
{
    button_pin = pin;                    // Set the button pin.
    bsp_pin_mode(pin, BSP_INPUT_PULLUP); // Set the pin mode to input with internal pull-up resistor.
    for (uint8_t i = 0; i < SAMPLES; i++)
    {
        samples[i] = bsp_digital_read(pin);
    }
}


void button_update_state(void)
{
    if (button_pin == BUTTON_UNINITITIALIZED)
        return; // Return if the button is not initialized.

    samples[sample_index++] = bsp_digital_read(button_pin); 
    sample_index %= SAMPLES;                               

    uint8_t stable_state = samples[0]; 
    bool stable = true;                // Assume the button state is stable.
    for (uint8_t i = 1; i < SAMPLES; i++)
    {
        if (samples[i] != stable_state)
        {
            stable = false; // If sample is different, the button state is not stable.
            break;
        }
    }

    if (stable)
    {
        if (stable_state == BSP_LOW)
        { // If the stable state is LOW (button pressed).
            if (state != BUTTON_PRESSED)
            {
                state = BUTTON_FALLING_EDGE; // If previous state was not pressed, set it to falling edge.
            }
            else
            {
                state = BUTTON_PRESSED; 
            }
        }
        else
        { // If the stable state is HIGH (button release).
            if (state != BUTTON_RELEASED)
            {
                state = BUTTON_RISING_EDGE; // If previous state was not released, set it to rising edge.
            }
            else
            {
                state = BUTTON_RELEASED; 
            }
        }
    }
}


uint8_t button_get_state(void)
{
    
    uint8_t current_state = state; // Get current state of the button.
    if (state == BUTTON_FALLING_EDGE || state == BUTTON_RISING_EDGE)
    {
        state = (state == BUTTON_FALLING_EDGE) ? BUTTON_PRESSED : BUTTON_RELEASED; 
    }
    return current_state; // Return current state.*/
}
