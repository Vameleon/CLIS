

#include <FastLED.h>

#define HORIZONTAL_LED_P    12
#define VERTICAL_LED_NUM    8
#define HORIZONTAL_LED_NUM  57
#define NEIGHBOR_NUM    8

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define PERIOD  5000                //period in program cycle in ms
CRGB HRZNTAL_LEDS[HORIZONTAL_LED_NUM];      //declare our strip as HRZNTAL_LEDS
#define DEF_MODE    1


#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.


   int BRIGHTNESS = 222;
    int COLORS[] = {
     CRGB::Blue, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Maroon,
     CRGB::DarkRed,CRGB::White,CRGB::SeaGreen,CRGB::Aquamarine,CRGB::OliveDrab,CRGB::Aqua,
    CRGB::SkyBlue,CRGB::Navy,CRGB::Teal,CRGB::DarkCyan,CRGB::LimeGreen,
    };
    int COLORS_ELE = sizeof(COLORS) / sizeof(COLORS[0]);


void pallete(void);
void pallete2(void);
void setup() {
 
    delay(1000);
    pinMode(HORIZONTAL_LED_P, OUTPUT);
    delay( 3000 ); // power-up safety delay
    //initiate
    FastLED.addLeds<LED_TYPE, HORIZONTAL_LED_P, COLOR_ORDER>(HRZNTAL_LEDS, HORIZONTAL_LED_NUM).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

}


void loop()
{



    pallete();
    //pallete2();
   // FastLED.setBrightness(  BRIGHTNESS );
    

   // BRIGHTNESS=+1;
    //if (BRIGHTNESS >=70)BRIGHTNESS=0;


 


    delay(PERIOD);
  
}


void pallete (void)
{
    bool frst_loop = true;
    //Loop from 0 until you reach the last neighbor
    //The last neighbor will get its color for the inner loop.
     for (int i = 0; i < HORIZONTAL_LED_NUM; i+=NEIGHBOR_NUM)
    {
        //if first loop, make sure to do the first led
        //if (frst_loop)HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)];
        
        
        //leds[i] = COLORS[rand () % COLORS_ELE] ;
        //HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)] ;
        
        //Skip the next NEIGHBOR_NUM, since we already did them previous loop.
        //else HRZNTAL_LEDS[i+NEIGHBOR_NUM] = COLORS[random(COLORS_ELE)] ;
        
        
        HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)];
        //Do the next NEIGHBOR_NUM leds.
        for (int u=0;u<NEIGHBOR_NUM;u++)
        {
            //Put the same current color on our neighbors
            HRZNTAL_LEDS[u+i] = HRZNTAL_LEDS[i];
        }
        FastLED.show();
        frst_loop=false; //First loop no longer!
    }
    

}

void pallete2 (void)
{
    bool frst_loop = true;
    //Loop from 0 until you reach the last neighbor
    //The last neighbor will get its color for the inner loop.
    for (int i = 0; i < HORIZONTAL_LED_NUM; i+=NEIGHBOR_NUM)
    {
        //if first loop, make sure to do the first led
        //if (frst_loop)HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)];
        
        
        //leds[i] = COLORS[rand () % COLORS_ELE] ;
        //HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)] ;
        
        //Skip the next NEIGHBOR_NUM, since we already did them previous loop.
        //else HRZNTAL_LEDS[i+NEIGHBOR_NUM] = COLORS[random(COLORS_ELE)] ;
        
        
        HRZNTAL_LEDS[i] = COLORS[random(COLORS_ELE)];
        //Do the next NEIGHBOR_NUM leds.
        for (int u=0;u<NEIGHBOR_NUM;u++)
        {
            //Put the same current color on our neighbors
            HRZNTAL_LEDS[i+u] = HRZNTAL_LEDS[i];
        }
        FastLED.show();
        frst_loop=false; //First loop no longer!
    }
    

}


// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

