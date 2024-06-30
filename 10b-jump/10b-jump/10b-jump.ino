#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Display Breite in Pixeln 
#define SCREEN_HEIGHT 64 // Display Höhe in Pixeln 

// größe der spielfigur
#define SIZE_X 9
#define SIZE_Y 9

#define PIN_BLAU 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char epd_bitmap_monster [] PROGMEM = {
	0x63, 0x00, 0x3e, 0x00, 0x6b, 0x00, 0xbe, 0x80, 0x1c, 0x00, 0x36, 0x00, 0x55, 0x00, 0x55, 0x00, 
	0x55, 0x00
};

// position der Spielfigur
int position_x;
int position_y;

float gravity = 0;
float speed = 0;

int button_blau = 0;

void setup() { 
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed")); 
    } 

  pinMode(PIN_BLAU, INPUT);
} 

void loop() { 

  button_blau = digitalRead(PIN_BLAU); // blauer button gedrückt?

  if (button_blau) {
    gravity = -0.5; // nach oben beschleunigen
  } else {
    gravity = 0.2; // weiter fallen
  }

  speed += gravity;
  position_y += speed;

  updateDisplay();
  delay(50); 
}


void updateDisplay() {
  display.clearDisplay(); 
    
  display.drawBitmap(position_x, position_y, epd_bitmap_monster, SIZE_X, SIZE_Y, 1);  // Figur zeichnen

  display.display();
}