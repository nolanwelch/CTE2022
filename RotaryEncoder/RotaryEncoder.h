#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

#define RE_TIMEOUT_MS 1000

class RotaryEncoder {
	public:
		RotaryEncoder(int dt, int clk, int pulsesPerRotation);
		void updateEncoder();
		int getRPM();
		void enable();
		void disable();
		bool isEnabled();
	private:
		int _dt;
		int _clk;
		int _pulsesPerRotation;
		int _counter;
		unsigned long _lastMs;
		int _rpm;
		bool _clockwise;
		bool _currentClkState;
		bool _lastClkState;
		bool _enabled;
};

#endif