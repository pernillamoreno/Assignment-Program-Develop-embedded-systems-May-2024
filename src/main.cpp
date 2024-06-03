#include <Arduino.h>
#include "button.h"
#include "bsp.h"

// Constants
const uint8_t buttonPin = 34;
const unsigned long updateInterval = 2; 

// Timer handle
hw_timer_t *timer = NULL;

// ISR for the timer
void IRAM_ATTR onTimer() {
    button_update_state();
}

void setup() {
  
    Serial.begin(9600);
    delay(1000); // Small delay to ensure Serial is ready

    
    button_init(buttonPin);
    

    // Initialize the timer
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, updateInterval * 1000, true);
    timerAlarmEnable(timer);                             // Enable the timer alarm

    Serial.println("Setup complete. press when ever you like...");
}

void loop() {
    // Check for falling edge
    if (button_get_state() == BUTTON_FALLING_EDGE) {
        Serial.println("Falling edge");
    }
}

