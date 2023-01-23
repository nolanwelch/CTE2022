#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int dt, int clk, int pulsesPerRotation) {
	pinMode(dt, INPUT);
	pinMode(clk, INPUT);
	_dt = dt;
	_clk = clk;
	_pulsesPerRotation = pulsesPerRotation;
	attachInterrupt(0, updateEncoder, CHANGE);
	attachInterrupt(1, updateEncoder, CHANGE);
	_lastMs = millis();
	_enabled = true;
	_pulses = 0;
}

int RotaryEncoder::getPulses() {
	if (!_enabled || millis() - _lastMs > ENCODER_TIMEOUT_MS) {
		_pulses = 0;
	}
	return _pulses;
}

void RotaryEncoder::updateEncoder() {
	if (!_enabled) {
		return;
	}
	_lastMs = millis();
	if(_currentClkState != _lastClkState && _currentClkState == 1) {
		_pulses++;
		_lastClkState = _currentClkState;
	}
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