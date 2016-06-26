/* Encoder Library - Basic Example
 * https://github.com/joruiz/Encoder
 *
 * This example code is in the public domain.
 */
 
#include <Encoder.h>

Encoder myEncoder(2, 3);

void setup() {

  Serial.begin(9600);
  Serial.println("Basic Counter Test:");
}

long oldValue  = -999;

void loop() {

  long newValue = myEncoder.read();
  if (newValue != oldValue) {
    oldValue = newValue;
    Serial.println(newValue);
  }
}
