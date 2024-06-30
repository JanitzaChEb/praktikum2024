#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Display Breite in Pixeln 
#define SCREEN_HEIGHT 64 // Display Höhe in Pixeln 

// größe der spielfigur
#define SIZE_X 9
#define SIZE_Y 9

// Pins der Buttons
#define PIN_BLAU 14
#define PIN_ROT 12

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

int blauer_button = 0;
int roter_button = 0;

void setup() { 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed")); 
  } 

  // buttons initialisieren
  pinMode(PIN_BLAU, INPUT);
  pinMode(PIN_ROT, INPUT);

  // Startposition
  position_x = 0;
  position_y = 28;

} 

void loop() { 

  blauer_button = digitalRead(PIN_BLAU);
  roter_button = digitalRead(PIN_ROT);

      if(blauer_button == 1) {
        position_y = position_y + 1;
      }
      if(roter_button == 1) {
        position_y = position_y - 1;
      }

   updateDisplay();
   delay(50); 
}

void updateDisplay() {
  display.clearDisplay(); 
    
  display.drawBitmap(position_x, position_y, epd_bitmap_monster, SIZE_X, SIZE_Y, 1);  // Figur zeichnen

  display.display();
}