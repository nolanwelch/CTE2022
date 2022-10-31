#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int dt, int clk) {
	pinMode(dt, INPUT);
	pinMode(clk, INPUT);
	_dt = dt;
	_clk = clk;
	attachInterrupt(0, updateEncoder, CHANGE);
	attachInterrupt(1, updateEncoder, CHANGE);
	_enable = true;
	_clockwise = true;
	_counter = 0;
	_lastMs = millis();
}

int getRPM() {
	if (!_enabled) {
		return -1;
	}
	return rpm;
}

void updateEncoder() {
	if (!_enabled) {
		return;
	}

	_currentClkState = digitalRead(_clk);

	if (_currentClkState != _lastClkState && _currentClkState == 1) {
		if (digitalRead(_dt) != _currentClkState) {
			_counter--;
			_clockwise = false;
		} else {
			_counter++;
			_clockwise = true;
		}
	}

	_lastClkState = _currentClkState;

	// TODO: Calculate and store current RPM
	_rpm = 0;
}

void enable() {
	_enabled = true;
}

void disable() {
	_enabled = false;
}

bool isEnabled() {
	return _enabled;
}