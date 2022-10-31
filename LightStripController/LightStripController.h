#ifndef LightStripController_h
#define LightStripController_h

#include "Arduino.h"
#include <FastLED.h>


class LightStripController {
	public:
		LightStripController(int din);
	private:
		int _din;
};

#endif