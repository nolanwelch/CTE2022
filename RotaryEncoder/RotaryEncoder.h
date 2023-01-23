#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

#define ENCODER_TIMEOUT_MS 1000

class RotaryEncoder {
	public:
		RotaryEncoder(int dt, int clk, int pulsesPerRotation);
		void updateEncoder();
		int getPulses();
		void enable();
		void disable();
		bool isEnabled();
	private:
		int _dt;
		int _clk;
		int _lastMs;
		int _pulsesPerRotation;
		bool _currentClkState;
		bool _lastClkState;
		bool _enabled;
		int _pulses;
};

#endif