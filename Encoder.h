/* Encoder Library, for measuring quadrature encoded signals
 * https://github.com/joruiz/Encoder
 * Copyright (c) 2016 Jonathan Ruiz de Garibay
 *
 * Version 0.9 - initial release (no checked)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"
#include "./interrupt_pins.h"

typedef struct {
	uint8_t pin1;
	uint8_t pin2;
	uint32_t position;
	uint8_t state;
} Encoder_internal_state_t;

class Encoder
{
	public:
		Encoder(uint8_t pin1, uint8_t pin2);
		uint32_t read();
		void write(uint32_t newPosition);
	
		static Encoder_internal_state_t * interruptArgs[CORE_NUM_INTERRUPT];	
	private:
		Encoder_internal_state_t encoder;
		uint8_t interrupt_in_use;
		
		static void update(Encoder_internal_state_t *arg){
			
			uint8_t s = arg->state & 3;
			if (digitalRead(arg->pin1)) s |= 4;
			if (digitalRead(arg->pin2)) s |= 8;
			switch (s) {
				case 0: case 5: case 10: case 15:
					break;
				case 1: case 7: case 8: case 14:
					arg->position++; 
					break;
				case 2: case 4: case 11: case 13:
					arg->position--; 
					break;
				case 3: case 12:
					arg->position += 2;
					break;
				default:
					arg->position -= 2; 
					break;
			}
			arg->state = (s >> 2);
		}		

		static uint8_t attach_interrupt(uint8_t pin, Encoder_internal_state_t *encoder) {

			switch (pin) {
		#ifdef CORE_INT0_PIN
				case CORE_INT0_PIN:
					interruptArgs[0] = encoder;
					attachInterrupt(0, isr0, RISING);
					break;
		#endif
		#ifdef CORE_INT1_PIN
				case CORE_INT1_PIN:
					interruptArgs[1] = encoder;
					attachInterrupt(1, isr1, RISING);
					break;
		#endif
		#ifdef CORE_INT2_PIN
				case CORE_INT2_PIN:
					interruptArgs[2] = encoder;
					attachInterrupt(2, isr2, RISING);
					break;
		#endif
		#ifdef CORE_INT3_PIN
				case CORE_INT3_PIN:
					interruptArgs[3] = encoder;
					attachInterrupt(3, isr3, RISING);
					break;
		#endif
		#ifdef CORE_INT4_PIN
				case CORE_INT4_PIN:
					interruptArgs[4] = encoder;
					attachInterrupt(4, isr4, RISING);
					break;
		#endif
		#ifdef CORE_INT5_PIN
				case CORE_INT5_PIN:
					interruptArgs[5] = encoder;
					attachInterrupt(5, isr5, RISING);
					break;
		#endif
		#ifdef CORE_INT6_PIN
				case CORE_INT6_PIN:
					interruptArgs[6] = encoder;
					attachInterrupt(6, isr6, RISING);
					break;
		#endif
				default:
					return 0;
			}
			return 1;
		}
		
		#ifdef CORE_INT0_PIN
		static void isr0() { update(interruptArgs[0]); }
		#endif

		#ifdef CORE_INT1_PIN
		static void isr1() { update(interruptArgs[1]); }
		#endif

		#ifdef CORE_INT2_PIN
		static void isr2() { update(interruptArgs[2]); }
		#endif

		#ifdef CORE_INT3_PIN
		static void isr3() { update(interruptArgs[3]); }
		#endif

		#ifdef CORE_INT4_PIN
		static void isr4() { update(interruptArgs[4]); }
		#endif

		#ifdef CORE_INT5_PIN
		static void isr5() { update(interruptArgs[5]); }
		#endif
};

#endif