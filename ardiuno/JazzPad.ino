#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 13 //Light strip out pin
#define N_LEDS 60 // Number of LED


char command;
String string;

int soundPin = A0; //Mic input pin
long randNumber1,randNumber2,randNumber3; //Random numbers to generate different colours
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800); //initilaizating the LED Strip

void setup() {
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  randomSeed(analogRead(5));
}

void loop() {

 if (Serial.available() > 0) 
    {string = "";}
    
    while(Serial.available() > 0)
    {
      command = ((byte)Serial.read());
      
      if(command == ':')
      {
        break;
      }
      
      else
      {
        string += command;
      }
      
      delay(1);
    }
    
    if(string == "TO")
    {
        colorWipe(strip.Color(255,   255,   255), 255); // Red
        colorWipe(strip.Color(255,   255,   255), 100); // Red
        colorWipe(strip.Color(255,   255,   255), 255); // Red
        //ledon = true;
    }
    
    if(string =="TF")
    {
        rainbow(1);
        Serial.println(string);
    }
    
    if ((string.toInt()>=0)&&(string.toInt()<=255))
    {
        int i = string.toInt();
        lightOff();
        for(int k = i*4; k< i*4+5;k++){
          strip.setPixelColor(k  , strip.Color(0, 0, 255)); // Draw new pixel
        
          }
          strip.show();
        
        //delay(10);
    }

  
//    randNumber1 = random(256);
//    randNumber2 = random(256);
//    randNumber3 = random(256);

   // chase(strip.Color(randNumber1, randNumber2, randNumber3),8,50,true);
    //chase(strip.Color(randNumber1, randNumber2, randNumber3),4,5,false);
   // chase(strip.Color(randNumber1, randNumber2, randNumber3),8,50,true);
    //chase(strip.Color(randNumber1, randNumber2, randNumber3),4,5,true);
      // Fill along the length of the strip in various colors...
  //colorWipe(strip.Color(255,   0,   0), 50); // Red
  //colorWipe(strip.Color(  0, 255,   0), 50); // Green
  //colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  //rainbow(1);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  
//    long sum = 0;
//    for(int i=0; i<50; i++)
//    {
//        int s = analogRead(soundPin);
//        sum += s;
//        Serial.println(s);
//    }
// 
//    sum = sum/50;
//    randNumber1 = random(256);
//    randNumber2 = random(256);
//    randNumber3 = random(256);
//    
//
//        lightOn(strip.Color(randNumber1, randNumber2, randNumber3),(int)sum/15);
//        delay(5);
}
 

//Dancing Steps
//introducing different steps with different specifications

//pattern chase
//Options
//  1)
static void chase(uint32_t c,int ledNum,int del,bool up) {
  if(up){
    for(uint16_t i=0; i<strip.numPixels()+ledNum; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-ledNum, 0); // Erase pixel a few steps back
      strip.show();
      delay(del);
    }
  }else{
    for(uint16_t i=0; i<strip.numPixels()+ledNum+1; i++) {
      strip.setPixelColor(strip.numPixels()-i  , c); // Draw new pixel
      strip.setPixelColor(strip.numPixels()+ledNum-i, 0); // Erase pixel a few steps back
      strip.show();
      delay(del);
    }
  }
}




static void lightOn(uint32_t c,int number){
    for(uint16_t i=0; i<number; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      //delay(3);
  }
  for(uint16_t i=number; i<strip.numPixels(); i++) {
      //strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i, 0); // Erase pixel a few steps back
      strip.show();
      //delay(5);
  }
}

static void lightOff(){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      //strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i, 0); // Erase pixel a few steps back
      strip.show();
      //delay(5);
  }
}


// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}