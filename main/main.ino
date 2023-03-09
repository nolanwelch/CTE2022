#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelBusLg.h>
#include <NeoPixelSegmentBus.h>

#define LED_PIN 3 // forced by NeoPixelBus library
// DMA methods use GPIO3
// UART1 methods use GPIO2
// UART0 methods use GPIO1
#define LIGHT_TIMEOUT_MS 120000
const uint16_t LED_COUNT = 41;
#define COLOR_R 223
#define COLOR_G 20
#define COLOR_B 250
RgbColor black(0);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(LED_COUNT);
bool lightOn = false;

const uint8_t CLK_PIN = D6;
const uint8_t DT_PIN = D7;
#define ENCODER_TIMEOUT_MS 5000
#define PULSES_PER_ROTATION 20
#define ROTATIONS_TO_LIGHT 5
#define MAX_BRIGHTNESS 255
const float BRIGHTNESS_COEFF = MAX_BRIGHTNESS/(float)(PULSES_PER_ROTATION*ROTATIONS_TO_LIGHT);

bool lastClkState;
bool currClkState;
volatile bool encoderUpdated = false;
unsigned int pulses = 0;
int lastPulses = 0;
unsigned long lastEncoderMs = 0;

void ICACHE_RAM_ATTR updateEncoder() {
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

void setup() {
  Serial.begin(9600); // MUST leave this in or LED strip will not work!
  while(!Serial); // remove when done testing
  Serial.println("Beginning setup...");
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  lastClkState = digitalRead(CLK_PIN);
  Serial.println("Set up pins!");
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT_PIN), updateEncoder, CHANGE);
  Serial.println("Attached interrupts!");
  strip.Begin();
  Serial.println("Started light strip!");
  for (int i = 0; i < LED_COUNT; i++) {
    strip.SetPixelColor(i, black);
  }
  Serial.println("Assigned color to light strip!");
  strip.Show();
  Serial.println("Showing light strip!");
  delay(1500);
  Serial.println("Setup complete!");
  Serial.println(PULSES_PER_ROTATION*ROTATIONS_TO_LIGHT); // temp
}

void loop() {
  //  encoder logic
  if (encoderUpdated) {
    encoderUpdated = false;
    readEncoderUpdate();
    if (!lightOn) {
      int brightness = min(pulses*BRIGHTNESS_COEFF, (float)MAX_BRIGHTNESS);
      RgbColor color(brightness*COLOR_R, brightness*COLOR_G, brightness*COLOR_B);
      for (int i = 0; i < LED_COUNT; i++) {
        strip.SetPixelColor(i, color);
      }
      strip.Show();
      Serial.println(pulses);
    }
  } else if (pulses > 0 && millis() - lastEncoderMs >= ENCODER_TIMEOUT_MS) {
      pulses = 0;
      for (int i = 0; i < LED_COUNT; i++) {
        strip.SetPixelColor(i, black);
      }
      strip.Show();
      Serial.println("Pulses and light reset");
  }

  //  light logic
  if (!lightOn && pulses >= PULSES_PER_ROTATION*ROTATIONS_TO_LIGHT) {
    lightOn = true;
    Serial.println("Light on");
  } else if (lightOn && millis() - lastEncoderMs >= LIGHT_TIMEOUT_MS) {
    for (int i = 0; i < LED_COUNT; i++) {
      strip.SetPixelColor(i, black);
    }
    strip.Show();
    lightOn = false;
    Serial.println("Light reset");
  }
}
