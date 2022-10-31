#include "RotaryEncoder.h"

#define RE_DT_PIN 3
#define RE_CLK_PIN 4
#define RE_PULSES_PER_ROTATION 20

#define LSC_DIN_PIN 7

LightStripController controller = LightStripController(DIN_PIN);
RotaryEncoder encoder = RotaryEncoder(DT_PIN, CLK_PIN, PULSES_PER_ROTATION, controller);

void setup() {
	
}

void loop() {
	
}