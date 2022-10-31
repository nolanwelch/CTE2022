#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>
#include "LightStripController.h"

#define ENCODER_TIMEOUT_MS 1000

class RotaryEncoder {
	public:
		RotaryEncoder(int dt, int clk, int pulsesPerRotation, LightStripController controller);
		void updateEncoder();
		int getRPM();
		void enable();
		void disable();
		bool isEnabled();
	private:
		int _dt;
		int _clk;
		int _pulsesPerRotation;
		LightStripController _controller;
		int _counter;
		unsigned long _lastMs;
		int _rpm;
		bool _clockwise;
		bool _currentClkState;
		bool _lastClkState;
		bool _enabled;
};

#endif