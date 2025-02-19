#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Display Breite in Pixeln 
#define SCREEN_HEIGHT 64 // Display Höhe in Pixeln 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Bild zum anzeigen. kopiert von https://javl.github.io/image2cpp/
const unsigned char epd_bitmap_cat [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0xcf, 0xff, 0xff, 0xff, 0xc3, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0x83, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x82, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xa0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x07, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xdf, 0xa0, 0x00, 0x00, 0x01, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xdf, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf7, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf9, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf1, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x7f, 0xff, 0xff, 0xc0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x01, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x3f, 0xff, 0xff, 0x00, 0x7f, 0x80, 0x08, 0x06, 0x40, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x01, 0xfe, 0x00, 0x1f, 0x00, 0x88, 0x46, 0x40, 0x20, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xca, 0xe6, 0x8c, 0x10, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0xcd, 0xf6, 0xfa, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x1f, 0xff, 0xf7, 0x00, 0x30, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x38, 0x1f, 0xf6, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x12, 0x01, 0x0d, 0xfe, 0x06, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x6f, 0xfe, 0x86, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x6f, 0xfc, 0x07, 0x00, 0x0f, 0xff, 0xff, 0xc7, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xc7, 0xfc, 0x0c, 0x00, 0x07, 0xff, 0xff, 0xc3, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x07, 0xfc, 0x18, 0x20, 0x03, 0xff, 0xff, 0xc3, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 0xa7, 0xfc, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xe3, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x77, 0xfc, 0x80, 0x20, 0x1f, 0xff, 0xff, 0xe1, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x35, 0xf0, 0xc0, 0xf0, 0x1f, 0xff, 0xff, 0xe1, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xc1, 0xf9, 0xf1, 0xe0, 0x00, 0x1f, 0xff, 0xff, 0xe1, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0xff, 0xff, 0x18, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0xff, 0xff, 
	0xc0, 0x00, 0x00, 0x00, 0x30, 0x01, 0xcf, 0xf2, 0x3e, 0x40, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xd6, 0x07, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x27, 0xff, 0x0f, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x60, 0x00, 0x00, 0x00, 0x07, 0x9f, 0xff, 0xdf, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x60, 0x00, 0x00, 0x00, 0x02, 0x2b, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x13, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x20, 0x00, 0x00, 0x00, 0xf0, 0x47, 0xff, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x70, 0x00, 0x00, 0x01, 0x7c, 0x07, 0xff, 0xff, 0xa0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x78, 0x00, 0x00, 0x00, 0x1c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x78, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x3f, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x60, 0x00, 0x00, 0x00, 0x2f, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x20, 0x00, 0x00, 0x00, 0x23, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x60, 0x00, 0x00, 0x00, 0x04, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xb7, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x06, 0x7f, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() { 
    // Hier wird das Display initialisiert: 
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        // Fehlermeldung falls die Verbindung zum Display nicht klappt 
        Serial.println(F("SSD1306 allocation failed")); 
    } 

  display.clearDisplay(); // löscht alles vom Display
  display.drawBitmap(0, 0, epd_bitmap_cat, 128, 64, 1); 
  display.display(); // "bestätigt" das was wir vorher gezeichnet haben
} 

void loop() { 
  // Hier ändert sich nach dem Start nichts mehr, desegen ist die loop-Methode leer
} 
