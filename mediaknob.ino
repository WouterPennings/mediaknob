#include "HID-Project.h" // Link to library: https://github.com/NicoHood/HID

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
#define SINGLE_PRESS      MEDIA_PLAY_PAUSE
#define DOUBLE_PRESS      MEDIA_NEXT            // TODO: Not implemented yet
#define TRIPLE_PRESS      MEDIA_PREVIOUS        // TODO: Not implemented yet
#define RIGHT_TURN        MEDIA_VOLUME_UP
#define LEFT_TURN         MEDIA_VOLUME_DOWN
#define PRESS_RIGHT_TURN  MEDIA_REWIND          // TODO: Not implemented yet
#define PRESS_LEFT_TURN   MEDIA_FAST_FORWARD    // TODO: Not implemented yet

/* ==========================================================================
===========  END OF DEVICE CONFIG  ==========================================
===========================================================================*/

// Pins on Arduino Micro to which things are connected to
#define BTN_PIN 6
#define ROT_PIN_A 4
#define ROT_PIN_B 2

#define BTN_PRESS_DELAY 100                 // 100 ms delay for double and tripple button presses

// This timer is used for dubble or tripple button presses
unsigned long timer;

void setup() {
  Serial.begin(115200);

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(ROT_PIN_A, INPUT_PULLUP);
  pinMode(ROT_PIN_B, INPUT_PULLUP);

  timer = millis();
  btn_time = 0;
  prev_btn_time = 0;
  prevprev_btn_time = 0;
}

uint8_t has_turned = false;
uint8_t right_turn = false;
uint8_t btn_pressed = false; 

void loop() {
  // Updating timer for double and triple button presses
  timer = millis();

  // Updates current state of rotary encoder and the accompanying buttoon
  handle_button();
  handle_rotary();

  // Logging
  if(btn_pressed) Serial.println(btn_pressed);
  if(has_turned) {
    Serial.print("Clockwise turn: ");
    Serial.println(right_turn);
  }

  // Executing HID commands to device, action per input is configured at top of the file
  if(btn_pressed) Consumer.write(SINGLE_PRESS); 
  else if(has_turned && right_turn) Consumer.write(RIGHT_TURN);
  else if(has_turned && !right_turn) Consumer.write(LEFT_TURN);

  delay(5);
}

static uint8_t prev_btn_state = LOW;
int aState;
int aLastState; 

void handle_button() {
  bool state = digitalRead(BTN_PIN);
  if (state != prev_btn_state) {
    prev_btn_state = state;
    if (state == HIGH) {
      btn_pressed = true;
      return;
    }
  }

  btn_pressed = false;
}

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

