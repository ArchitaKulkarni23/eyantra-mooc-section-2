#include "firebird_simulation.h"    // Header file included that contains macro definitions essential for Firebird V robot
#include <stdbool.h>                // Standard C Library for Boolean Type

//---------------------------------- FUNCTIONS ----------------------------------------------------------

/**
 * @brief Makes **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output and initially sets **ONLY** 2nd Bar-graph LED as high (ON)
 */
void bar_graph_led_pins_config(void) {
    // Make **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output
    bar_graph_led_ddr_reg |= (1 << bar_graph_led_2_pin) | (1 << bar_graph_led_6_pin) | (1 << bar_graph_led_8_pin);

    // Set **ONLY** 2nd Bar-graph LED as high (ON)
    bar_graph_led_port_reg |= (1 << bar_graph_led_2_pin);
}

/**
 * @brief Makes **ONLY** Interrupt Switch pin as input and pulls it up internally
 */
void interrupt_sw_pin_config(void) {
    // Makes **ONLY** Interrupt Switch pin as input
    interrupt_sw_ddr_reg &= ~(1 << interrupt_sw_pin);

    // Makes **ONLY** Interrupt Switch pin internally pull-up
    interrupt_sw_port_reg |= (1 << interrupt_sw_pin);
}

/**
 * @brief Checks if Interrupt Switch is pressed or not
 *
 * @return boolean true if Interrupt Switch is pressed, else false.
 */
bool interrupt_switch_pressed(void) {
    if (interrupt_sw_pin_reg & (1 << interrupt_sw_pin)) {
        return false;  // Interrupt Switch is not pressed
    } else {
        return true;   // Interrupt Switch is pressed
    }
}

/**
 * @brief Sets **ONLY** a particular Bar-graph LED pin as high (ON)
 *
 * @param[in] led_pin Pin number of Bar-graph LED
 */
void turn_on_bar_graph_led(unsigned char led_pin) {
    // Set **ONLY** a particular Bar-graph LED pin as high (ON)
    bar_graph_led_port_reg |= (1 << led_pin);
}

/**
 * @brief Sets **ONLY** a particular Bar-graph LED pin as low (OFF)
 *
 * @param[in] led_pin Pin number of Bar-graph LED
 */
void turn_off_bar_graph_led(unsigned char led_pin) {
    // Set **ONLY** a particular Bar-graph LED pin as low (OFF)
    bar_graph_led_port_reg &= ~(1 << led_pin);
}

//---------------------------------- MAIN ----------------------------------------------------------------
int main(void) {
    bar_graph_led_pins_config();      // Initialize the 2nd, 6th and 8th Bar-graph LEDs
    interrupt_sw_pin_config();        // Initialize the Interrupt Switch

    while (1) {
        if (interrupt_switch_pressed()) {
            turn_off_bar_graph_led(bar_graph_led_2_pin);    // Turn OFF 2nd Bar-graph LED
            turn_on_bar_graph_led(bar_graph_led_8_pin);     // Turn ON 8th Bar-graph LED
        } else {
            turn_on_bar_graph_led(bar_graph_led_2_pin);     // Turn ON 2nd Bar-graph LED
            turn_off_bar_graph_led(bar_graph_led_8_pin);    // Turn OFF 8th Bar-graph LED
        }
    }
}
