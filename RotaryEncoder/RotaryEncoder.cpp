#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int dt, int clk, int pulsesPerRotation) {
	pinMode(dt, INPUT);
	pinMode(clk, INPUT);
	_dt = dt;
	_clk = clk;
	_pulsesPerRotation = pulsesPerRotation;
	attachInterrupt(0, RotaryEncoder::updateEncoder, CHANGE);
	attachInterrupt(1, RotaryEncoder::updateEncoder, CHANGE);
	_enable = true;
	_clockwise = true;
	_counter = 0;
	_lastMs = millis();
}

int RotaryEncoder::getRPM() {
	if (!_enabled || millis() - _lastMs > RE_TIMEOUT_MS) {
		return 0;
	}
	return rpm;
}

void RotaryEncoder::updateEncoder() {
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

	_rpm = 1 / ((millis() - _lastMs) * 6000 * _pulsesPerRotation);
	
	_lastMs = millis()
	_lastClkState = _currentClkState;
}

void RotaryEncoder::enable() {
	_enabled = true;
}

void RotaryEncoder::disable() {
	_enabled = false;
}

bool RotaryEncoder::isEnabled() {
	return _enabled;
}