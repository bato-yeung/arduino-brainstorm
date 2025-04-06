#include <MD_MAX72xx.h> // For MAX7219 8x8 LED matrix
#include <Grove_LED_Bar.h> // For Grove LED Bar

// Pin definitions
const int ledPins[] = {2, 3}; // LED pins (reduced to 2)
const int buttonPins[] = {6, 7}; // Button pins (reduced to 2)
const int speakerPin = 10; // Speaker pin

// MAX7219 configuration
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1 // Number of cascaded MAX7219 modules
#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 12

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Grove LED Bar object
Grove_LED_Bar ledBar(9, 8, 0); // Clock pin, Data pin, Orientation

// Game variables
int lives = 10;
int score = 0;
int currentLed = -1;
bool hasAnswered = false;
unsigned long interval = 2000; // Interval for LED change
unsigned long lastUpdate = 0;

// Custom digit patterns for 8x8 LED matrix using binary format
const uint8_t digitPatterns[10][8] = {
  {B11100000, B10100000, B10100000, B10100000, B11100000, B00000000, B00000000, B00000000}, // 0
  {B00100000, B00100000, B00100000, B00100000, B00100000, B00000000, B00000000, B00000000}, // 1
  {B11100000, B00100000, B11100000, B10000000, B11100000, B00000000, B00000000, B00000000}, // 2
  {B11100000, B00100000, B11100000, B00100000, B11100000, B00000000, B00000000, B00000000}, // 3
  {B10100000, B10100000, B11100000, B00100000, B00100000, B00000000, B00000000, B00000000}, // 4
  {B11100000, B10000000, B11100000, B00100000, B11100000, B00000000, B00000000, B00000000}, // 5
  {B10000000, B10000000, B11100000, B10100000, B11100000, B00000000, B00000000, B00000000}, // 6
  {B11100000, B00100000, B00100000, B00100000, B00100000, B00000000, B00000000, B00000000}, // 7
  {B11100000, B10100000, B11100000, B10100000, B11100000, B00000000, B00000000, B00000000}, // 8
  {B11100000, B10100000, B11100000, B00100000, B00100000, B00000000, B00000000, B00000000}  // 9
};

void setup() {
  // Initialize LEDs and buttons
  for (int i = 0; i < 2; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Initialize MAX7219
  mx.begin();
  mx.clear();
  updateScoreDisplay();

  // Initialize Grove LED Bar
  ledBar.begin();
  ledBar.setGreenToRed(false);
  ledBar.setLevel(lives);

  // Seed random number generator
  randomSeed(analogRead(0));

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Game started. Monitoring button states...");
}

void loop() {
  unsigned long currentTime = millis();

  if (lives <= 0) {
    return;
  }

  if (currentLed == -1) {
    if (currentTime - lastUpdate > interval) {
      Serial.println("Current LED updated.");
      lastUpdate = currentTime;

      if (currentLed != -1) {
        digitalWrite(ledPins[currentLed], LOW);
      }

      currentLed = random(0, 2);
      digitalWrite(ledPins[currentLed], HIGH);

      updateScoreDisplay();
    }
  } else {
    checkButtonPress();

    if (currentTime - lastUpdate > interval) {
      incorrect();
    }

    if (hasAnswered == true) {
      hasAnswered = false;
      digitalWrite(ledPins[currentLed], LOW);
      currentLed = -1;

      ledBar.setLevel(lives);
      delay(1000);
    }
  }

  if (lives <= 0) {
    gameOver();
  }
}

void updateScoreDisplay() {
  mx.clear();

  // Extract tens and ones digits
  int tens = (score / 10) % 10;
  int ones = score % 10;

  // Combine tens and ones into a single 8x8 byte array
  for (int row = 0; row < 8; row++) {
    uint8_t combinedRow = (digitPatterns[tens][row]) | (digitPatterns[ones][row] >> 4);
    mx.setRow(0, row, combinedRow); // Set the combined row to the matrix
  }
}

void checkButtonPress() {
  for (int i = 0; i < 2; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (i == currentLed) {
        correct();
      } else {
        incorrect();
      }
    }
  }
}

void correct() {
  hasAnswered = true;
  score++;
  speedUp();
  tone(speakerPin, 1000, 100);

  updateScoreDisplay();

  Serial.print("Correct | Score: ");
  Serial.print(score);
  Serial.print(" | Interval: ");
  Serial.print(interval);
  Serial.println();
}

void incorrect() {
  hasAnswered = true;
  loseLife();
  tone(speakerPin, 500, 500);

  Serial.print("Incorrect | Remaining Lives: ");
  Serial.print(lives);
  Serial.println();
}

void speedUp() {
  interval = constrain(interval * 0.96, 100, 2000);
}

void loseLife() {
  lives = constrain(lives - 1, 0, 10);
}

void gameOver() {

  Serial.println("GameOver");

  delay(5000);

  // Reset game variables
  lives = constrain(10, 0, 10);
  score = 0;
  interval = constrain(2000, 500, 2000);
  lastUpdate = 0;
  currentLed = -1;

  updateScoreDisplay();
  ledBar.setLevel(lives);
}