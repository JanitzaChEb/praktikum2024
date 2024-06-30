#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Display Breite in Pixeln 
#define SCREEN_HEIGHT 64 // Display Höhe in Pixeln 

// größe der spielfigur
#define SIZE_X 9
#define SIZE_Y 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char epd_bitmap_monster [] PROGMEM = {
	0x63, 0x00, 0x3e, 0x00, 0x6b, 0x00, 0xbe, 0x80, 0x1c, 0x00, 0x36, 0x00, 0x55, 0x00, 0x55, 0x00, 
	0x55, 0x00
};

// position der Spielfigur
int position_x;
int position_y;

// geschwindigkeit der Spielfigur pro Richtung
int speed_x;
int speed_y;

void setup() { 
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed")); 
    } 

  // Startposition
  position_x = 50;
  position_y = 28;

  // Startgeschwindigkeit
  speed_x = 1;
  speed_y = 2;
} 

void loop() { 
    if( kollisionMitWandXAchse() ) {
      speed_y = speed_y * -1; // richtung auf der y Achse umdrehen 
    }
    if( kollisionMitWandYAchse() ) {
      speed_x = speed_x * -1; // richtung umdrehen 
    }

    // Objekt in die jeweiligen Richtungen verschieben
    position_x = position_x + speed_x;
    position_y = position_y + speed_y;

    updateDisplay();
    delay(50); 
}

boolean kollisionMitWandXAchse() {
  // prüfen ob die Spielfigur die Wand oben oder unten berührt
  if (position_y <= 0) { // obere Wand
    return true; 
  }
  if (position_y + SIZE_Y >= SCREEN_HEIGHT) { // untere Wand
    return true; 
  }

  return false;
}

boolean kollisionMitWandYAchse() {
  // prüfen ob die Spielfigur die Wand links oder rechts berührt
  if (position_x <= 0) { // linke Wand
    return true; 
  }
  if (position_x + SIZE_X >= SCREEN_WIDTH) { // rechte Wand
    return true; 
  }

  return false;
}

void updateDisplay() {
  display.clearDisplay(); 
    
  display.drawBitmap(position_x, position_y, epd_bitmap_monster, SIZE_X, SIZE_Y, 1);  // Figur zeichnen

  display.display();
}