#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Display Breite in Pixeln 
#define SCREEN_HEIGHT 64 // Display Höhe in Pixeln 

// größe der spielfigur
#define SIZE_X 9
#define SIZE_Y 9

// größe des Hindernis
#define HINDERNIS_SIZE_X 10
#define HINDERNIS_SIZE_Y 20

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char epd_bitmap_monster [] PROGMEM = {
	0x63, 0x00, 0x3e, 0x00, 0x6b, 0x00, 0xbe, 0x80, 0x1c, 0x00, 0x36, 0x00, 0x55, 0x00, 0x55, 0x00, 
	0x55, 0x00
};

const unsigned char epd_bitmap_hindernis [] PROGMEM = {
	0xff, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 
	0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xd5, 0x40, 
	0xaa, 0xc0, 0xd5, 0x40, 0xaa, 0xc0, 0xff, 0xc0
};

// position der Spielfigur
int position_x;
int position_y;

// position des Hindernis
int hindernis_x;
int hindernis_y;

void setup() { 
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed")); 
    } 

  // Startposition
  position_x = 30;
  position_y = 28;
  hindernis_x = 70;
  hindernis_y = 14;
} 

void loop() { 
    if( !kollisionMitObjekt() ) {
      position_x = position_x + 1; // Figur auf der x Achse verschieben
    }

    updateDisplay();
    delay(50); 
}

boolean kollisionMitObjekt() {
  // prüfen ob die objekte auf der x Achse auseinander liegen
  if (
    position_x > (hindernis_x + HINDERNIS_SIZE_X) || // spieler ist rechts von hindernis ODER
    hindernis_x > (position_x + SIZE_X) // hindernis ist rechts von spieler
  ) {
    return false;
  }

  // prüfen ob die objekte auf der y Achse auseinander liegen
  if (
    position_y > (hindernis_y + HINDERNIS_SIZE_Y) || // spieler ist unter hindernis ODER
    hindernis_y > (position_y + SIZE_Y) // hindernis ist unter spieler
  ) {
    return false;
  }

  // wenn die figuren weder auf x noch auf y achse auseinander liegen, heißt das, dass sie sich berühren
  return true;
}

void updateDisplay() {
  display.clearDisplay(); 
    
  display.drawBitmap(position_x, position_y, epd_bitmap_monster, SIZE_X, SIZE_Y, 1);  // Figur zeichnen
  display.drawBitmap(hindernis_x, hindernis_y, epd_bitmap_hindernis, HINDERNIS_SIZE_X, HINDERNIS_SIZE_Y, 1);  // Figur zeichnen

  display.display();
}