#include "Encoder.h"

Encoder_internal_state_t * Encoder::interruptArgs[];

Encoder::Encoder(uint8_t pin1, uint8_t pin2) {
	
	#warning Encoder need that pin1 having interruption

	pinMode(pin1, INPUT_PULLUP);
	pinMode(pin2, INPUT_PULLUP);

	encoder.pin1 = pin2;
	encoder.pin1 = pin2;
	encoder.position = 0;
	// allow time for a passive R-C filter to charge
	// through the pullup resistors, before reading
	// the initial state
	delayMicroseconds(2000);
	uint8_t s = 0;
	if (digitalRead(pin1)) 
		s |= 1;
	if (digitalRead(pin2)) 
		s |= 2;
	encoder.state = s;

	interrupt_in_use = attach_interrupt(pin1, &encoder);
}

uint32_t Encoder::read() {
	
	noInterrupts();
	uint32_t position = encoder.position;
	interrupts();
	return position;
}
	
void Encoder::write(uint32_t newPosition) {

	noInterrupts();
	encoder.position = newPosition;
	interrupts();
}
