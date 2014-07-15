/*
 * Buttons
 * -------
 * 8 - Up
 * 9 - Down
 * 10 - Left
 * 11 - Right
 * 
 * LEDs
 * ----
 * 4 - Right
 * 5 - Left
 * 6 - Down
 * 7 - Up
 */

#define button_up 8
#define button_down 9
#define button_left 10
#define button_right 11

#define led_up 7
#define led_down 6
#define led_left 5
#define led_right 4

#define speaker 3
#define reset 2

int button;

byte* simon_dice;
int simon_size;

void setup() {
  simon_setup();

  // Randomize & alloc memory

  randomSeed(analogRead(0)); 
  simon_dice = (byte*) malloc(1*sizeof(byte));
  simon_size = 0; // No elements

  // Debug & delay

  Serial.begin(9600); // Debug
  delay(1000);
}

void loop() {
  // Play all
  simon_play();

  // Get new random LED
  simon_get();

  for (int i = 0; i < simon_size; i++) {
    // Wait for input...
    while ((button = simon_listen()) == -1);
    
    // Validate input
    if (simon_dice[i] != button) simon_lose();
  }
  
  // Success dude!
  simon_success();
  
  delay(500);
}

