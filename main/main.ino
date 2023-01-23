#define CLK_PIN 2
#define DT_PIN 3

#define MOTOR_TIMEOUT_MS 60000
#define ENCODER_TIMEOUT_MS 5000
#define PULSES_PER_ROTATION (float) 20
#define ROTATIONS_TO_DROP (float) 10
#define MAX_BRIGHTNESS (float) 255
const float BRIGHTNESS_COEFF = MAX_BRIGHTNESS/(PULSES_PER_ROTATION*ROTATIONS_TO_DROP);

bool lastClkState;
bool currClkState;
volatile bool encoderUpdated = false;
unsigned int pulses = 0;
int lastPulses = 0;
unsigned long lastEncoderMs = 0;
unsigned long lastMotorMs = 0;

void setup() {
  Serial.begin(9600);
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  lastClkState = digitalRead(CLK_PIN);
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT_PIN), updateEncoder, CHANGE);
  delay(1500);
  Serial.println("Setup complete!");
}

void loop() {
  //  encoder logic
  if (encoderUpdated) {
    encoderUpdated = false;
    readEncoderUpdate();
    int brightness = min(pulses*BRIGHTNESS_COEFF, MAX_BRIGHTNESS);
    Serial.println(pulses);
    Serial.print(brightness);
    Serial.print("/255\n");
  } else if (millis() - lastEncoderMs >= ENCODER_TIMEOUT_MS) {
      pulses = 0;
  }

  //  mouth logic
  if (pulses >= PULSES_PER_ROTATION*ROTATIONS_TO_DROP) {
    openMouth();
  } else if (millis() - lastMotorMs >= MOTOR_TIMEOUT_MS) {
    closeMouth();
  }
}

void updateEncoder() {
  encoderUpdated = true;
}

void readEncoderUpdate() {
  currClkState = digitalRead(CLK_PIN);
  if (currClkState != lastClkState && currClkState == 1) {
    pulses++;
    lastEncoderMs = millis();
  }
  lastClkState = currClkState;
}

void openMouth() {
  
}

void closeMouth() {
  
}
