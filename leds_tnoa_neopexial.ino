
#define Tnioa 22
#define Ledpiksel 23
#define LdrPin1 27
#define RedPin1 14
#define RedPin2 12
#define LdrPin2 25
#define RedPin4 26
#define LdrPin4 13
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 23 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



// פונקציה שמבצעת בדיקת תנועה
bool check_moving() {
  int value_move = digitalRead(Tnioa);
  Serial.print("value_move: "); Serial.println(value_move);
  return value_move == HIGH;
}



// פונקציה שמדליקה/מכבה את ה-NeoPixel
void On_Of_Light(int mode) {
  if (mode == 0) {
    pixels.clear();  // מכבה את כל הפיקסלים
    pixels.show();
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {  // מדליק כל פיקסל
      pixels.setPixelColor(i, pixels.Color(255, 255, 150));
    }
    pixels.show();  // שולח את הצבעים המעודכנים לחומרה
  }
}



void setup() {
  pinMode(Tnioa, INPUT); // הגדרת חיישן התנועה כקלט
  pinMode(Ledpiksel, OUTPUT);
  pixels.begin();  // אתחול NeoPixel strip

  // הגדרת חיישנים נוספים
  pinMode(LdrPin1, INPUT);
  pinMode(RedPin1, OUTPUT);
  pinMode(LdrPin2, INPUT);
  pinMode(RedPin2, OUTPUT);
  pinMode(LdrPin4, INPUT);
  pinMode(RedPin4, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  if (check_moving()) {
    On_Of_Light(1); // מדליק את ה-NeoPixels
  } else {
    On_Of_Light(0); // מכבה את ה-NeoPixels
  }
  // השהייה קטנה כדי למנוע דגימה מהירה מדי
  delay(100);
  // בדיקת חיישנים ומנורות חניה
  Serial.println(analogRead(LdrPin1));
  digitalWrite(RedPin1, (analogRead(LdrPin1) > 3000 ? LOW : HIGH));
  digitalWrite(RedPin2, (analogRead(LdrPin2) > 3000 ? LOW : HIGH));
  digitalWrite(RedPin4, (analogRead(LdrPin4) > 3000 ? LOW : HIGH));
}

