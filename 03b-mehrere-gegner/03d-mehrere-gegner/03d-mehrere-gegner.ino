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

// position der Hindernisse
int hindernis_postionen[4][2] = {{128, 3}, {160, 50}, {192, 5}, {224, 30}};

int blauer_button;
int roter_button;

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

  // prüfen ob button gedrückt wird
  blauer_button = digitalRead(PIN_BLAU);
  roter_button = digitalRead(PIN_ROT);

  if( !kollisionIrgendeinHindernisMitSpieler() ) {

    for (int i = 0; i < 4; i++) { // schleife über alle Hindernisse
      hindernis_postionen[i][0] -= 1; // hindernis um 1 nach links schieben
      if(hindernis_postionen[i][0] <= 0) { // wenn das Hindernis an der linken Wand ist:
        hindernis_postionen[i][0] = SCREEN_WIDTH; // an den rechten Rand zurücksetzen
        hindernis_postionen[i][1] = random(0, SCREEN_HEIGHT-HINDERNIS_SIZE_Y); // die Höhe zufällig auswählen
      }
    }

      if(blauer_button == 1) {
        position_y = position_y + 1;
      }
      if(roter_button == 1) {
        position_y = position_y - 1;
      }

  }

   updateDisplay();
   delay(50); 
}

boolean kollisionIrgendeinHindernisMitSpieler() {
  for (int i = 0; i < 4; i++) { // schleife über alle Hindernisse
    if(kollisionHindernisMitSpieler(hindernis_postionen[i][0], hindernis_postionen[i][1])) {
      return true;
    }
  }

  // das darf erst hinter der Schleife stehen, weil sonst beim ersten Hindernis, das nicht den Spieler trifft schon abgebrochen wird
  // (obwohl vielleicht das 3. Hindernis den Spieler trifft)
  return false;
}

boolean kollisionHindernisMitSpieler(int hindernis_x, int hindernis_y) {
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

  for (int i = 0; i < 4; i++) { // schleife über alle Hindernisse
    display.drawBitmap(hindernis_postionen[i][0], hindernis_postionen[i][1], epd_bitmap_hindernis, HINDERNIS_SIZE_X, HINDERNIS_SIZE_Y, 1);  // Figur zeichnen
  }

  display.display();
}