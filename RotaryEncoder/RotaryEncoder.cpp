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
	if (!_enabled || millis() - _lastMs > ENCODER_TIMEOUT_MS) {
		return 0;
	}
	return rpm;
}

void RotaryEncoder::updateEncoder() {
	if (!_enabled) {
		return;
	}
	
	unsigned long currentMs = millis();
	_rpm = 1 / ((currentMs - _lastMs) * 6000 * _pulsesPerRotation);
	_lastMs = currentMs;
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