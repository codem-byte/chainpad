#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- FRAME 1: Cat Standing (Spans 2 columns wide: Left block & Right block) ---
byte cat1_left[8] = {
  B00000,
  B00010,
  B00111,
  B01101,
  B11111,
  B00101,
  B00101,
  B00000
};
byte cat1_right[8] = {
  B00000,
  B10000,
  B11100,
  B10100,
  B11111,
  B10100,
  B10100,
  B00000
};

// --- FRAME 2: Cat Mid-Air Tucked Flip ---
byte cat2_left[8] = {
  B00000,
  B00000,
  B00111,
  B01111,
  B11111,
  B00111,
  B00000,
  B00000
};
byte cat2_right[8] = {
  B00000,
  B00000,
  B11100,
  B11110,
  B11111,
  B11100,
  B00000,
  B00000
};

// --- FRAME 3: Cat Landing / Stretching ---
byte cat3_left[8] = {
  B00000,
  B00000,
  B00111,
  B01101,
  B11111,
  B01110,
  B01010,
  B00000
};
byte cat3_right[8] = {
  B00000,
  B00000,
  B11100,
  B10110,
  B11111,
  B01110,
  B01010,
  B00000
};

// --- METEOR / PARTICLE BLENDING SLOTS ---
byte meteorTail[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};

byte starSparkle[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  // --- SEQUENCE 1: Multi-Slot Cat Run & Flip Across Screen ---
  for (int col = 0; col < 14; col++) {
    lcd.clear();
    
    // Dynamically load frame chunks into slots 0, 1, 2 based on animation cycle
    if (col % 3 == 0) {
      lcd.createChar(0, cat1_left);
      lcd.createChar(1, cat1_right);
    } else if (col % 3 == 1) {
      lcd.createChar(0, cat2_left);
      lcd.createChar(1, cat2_right); // Flip frame
    } else {
      lcd.createChar(0, cat3_left);
      lcd.createChar(1, cat3_right);
    }

    // Render the 2-block wide cat sprite seamlessly
    lcd.setCursor(col, 1);
    lcd.write(byte(0)); // Left half of cat
    lcd.setCursor(col + 1, 1);
    lcd.write(byte(1)); // Right half of cat
    
    delay(120); // Fine-tune frame speed for fluid perception
  }

  // --- SEQUENCE 2: Pixel-Blended Meteor Shower & Falling Stars ---
  lcd.clear();
  
  // Register environmental particle slots
  lcd.createChar(4, meteorTail);
  lcd.createChar(5, starSparkle);

  // Render falling elements with pseudo-random pixel-blending spread
  for (int step = 0; step < 10; step++) {
    lcd.clear();
    
    // Draw diagonal meteor streak across row 0 and row 1
    int mCol = (step * 2) % 16;
    lcd.setCursor(mCol, 0);
    lcd.write(byte(4));
    if (mCol + 1 < 16) {
      lcd.setCursor(mCol + 1, 1);
      lcd.write(byte(4));
    }

    // Scatter fading star sparkles
    lcd.setCursor((step * 3) % 16, 0);
    lcd.write(byte(5));
    lcd.setCursor(15 - ((step * 2) % 16), 1);
    lcd.write(byte(5));

    delay(90);
  }
}