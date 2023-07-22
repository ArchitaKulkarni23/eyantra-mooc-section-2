#include "firebird_simulation.h"
#include <util/delay.h>

void buzzer_pin_config(void) {
	// Make 'buzzer_pin' as output
	buzzer_ddr_reg |= (1 << buzzer_pin);

	// Set 'buzzer_pin' to low initially
	buzzer_port_reg &= ~(1 << buzzer_pin);
}

void buzzer_on(void) {
	// Set 'buzzer_pin' to high
	buzzer_port_reg |= (1 << buzzer_pin);
}

void buzzer_off(void) {
	// Set 'buzzer_pin' to low
	buzzer_port_reg &= ~(1 << buzzer_pin);
}

int main(void) {
	buzzer_pin_config();

	while (1) {
		buzzer_on();
		_delay_ms(1000);

		buzzer_off();
		_delay_ms(1000);
	}
}
