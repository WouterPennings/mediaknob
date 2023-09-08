#include "HID-Project.h"  // Link to library: https://github.com/NicoHood/HID
#include "Button2.h"      // Link to library: https://github.com/LennartHennigs/Button2

/* ==========================================================================
=========== BEGIN OF DEVICE CONFIG  =========================================
=============================================================================
Below is a list of all possible actions:
  MEDIA_FAST_FORWARD
  MEDIA_REWIND
  MEDIA_NEXT
  MEDIA_PREVIOUS
  MEDIA_STOP
  MEDIA_PLAY_PAUSE
  MEDIA_VOLUME_MUTE
  MEDIA_VOLUME_UP
  MEDIA_VOLUME_DOWN
  CONSUMER_EMAIL_READER
  CONSUMER_CALCULATOR
  CONSUMER_EXPLORER
  CONSUMER_BROWSER_HOME
  CONSUMER_BROWSER_BACK
  CONSUMER_BROWSER_FORWARD
  CONSUMER_BROWSER_REFRESH
  CONSUMER_BROWSER_BOOKMARKS 
  (For more info on the Consumer API: https://github.com/NicoHood/HID/wiki/Consumer-API) */
#define SINGLE_PRESS      MEDIA_PLAY_PAUSE  // Quick press and release
#define DOUBLE_PRESS      MEDIA_NEXT        // Two quick presses and releases
#define TRIPPLE_PRESS     MEDIA_PREVIOUS    // Three quick presses and releases   
#define HOLD              MEDIA_VOLUME_MUTE // Press button and do not release, action is reverse when button is release (Attention mode)
#define RIGHT_TURN        MEDIA_VOLUME_UP   // Turn button clockwise
#define LEFT_TURN         MEDIA_VOLUME_DOWN // Turn button counter-clockwise

/* ==========================================================================
===========  END OF DEVICE CONFIG  ==========================================
===========================================================================*/

// Pins on Arduino Micro to which things are connected to
#define BTN_PIN 6
#define ROT_PIN_A 4 // If volume is lowered if turned clockwise, switch values of ROT_PIN_A and ROT_PIN_B around.
#define ROT_PIN_B 2

Button2 button;

void setup() {
  Serial.begin(115200);
  Serial.println("MediaKnob is starting up...");

  button.begin(BTN_PIN);
  button.setClickHandler(click);
  button.setDoubleClickHandler(doubleClick);
  button.setTripleClickHandler(trippleClick);
  button.setLongClickDetectedHandler(LongClickDetected);

  button.setLongClickTime(500); // Default LongClickTime is 200 ms

  pinMode(ROT_PIN_A, INPUT_PULLUP);
  pinMode(ROT_PIN_B, INPUT_PULLUP);
}

uint8_t has_turned = false;
uint8_t right_turn = false;

void loop() {
  button.loop();
  handle_rotary();

  // Logging
  if(has_turned) {
    Serial.print("Clockwise turn: ");
    Serial.println(right_turn);
  }

  // Executing HID commands to device, action per input is configured at top of the file
  if(has_turned && right_turn) Consumer.write(RIGHT_TURN);
  else if(has_turned && !right_turn) Consumer.write(LEFT_TURN);

  delay(5);
}

void click(Button2& btn) {
  Serial.println("Single press");
  Consumer.write(SINGLE_PRESS); 
}

void doubleClick(Button2& btn) {
  Serial.println("Double press");
  Consumer.write(DOUBLE_PRESS);
}

void trippleClick(Button2& btn) {
  Serial.println("Tripple press");
  Consumer.write(TRIPPLE_PRESS);
}

void LongClickDetected(Button2& btn) {
  Serial.print("Long Pressed ");
  Consumer.write(HOLD);

  while (btn.isPressed()) {
    delay(10);
    Serial.print(".");
    button.loop();
  }

  delay(100); 

  Serial.println("Long Unpressed");
  Consumer.write(HOLD);
}

int aState;
int aLastState; 

void handle_rotary() {
  aState = digitalRead(ROT_PIN_A);
  //Encoder rotation tracking
  if (aState != aLastState) { 
    has_turned = true;
    right_turn = digitalRead(ROT_PIN_B) == aState;
  } else {
      has_turned = false;
      right_turn = false;
  } 
  aLastState = aState;
}
