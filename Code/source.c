

#include <FastLED.h>

#define LONG_CRGB_P    12           //number of leds on the strip
#define LONG_CRGB_NUM  57
#define NEIGHBOR_NUM    8

#define SHORT_CRGB_P    14
#define SHORT_CRGB_NUM    8         //number of leds on the strip

#define LED_TYPE    WS2812          //Controller model
#define UPDATES_PER_SECOND 100
#define COLOR_ORDER GRB
#define PERIOD  5000                //period in program cycle in ms


CRGB SHORT_CRGB[SHORT_CRGB_NUM];    //declare our strip and give it an ID
CRGB LONG_CRGB[LONG_CRGB_NUM];      //declare our strip and give it an ID


#define DEF_MODE    1



int LONG_BRIGHTNESS = 222;
int SHORT_BRIGHTNESS = 222;

//int COLORS[] = {
// CRGB::Blue, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Maroon,
// CRGB::DarkRed,CRGB::White,CRGB::SeaGreen,CRGB::Aquamarine,CRGB::OliveDrab,CRGB::Aqua,
// CRGB::SkyBlue,CRGB::Navy,CRGB::Teal,CRGB::DarkCyan,CRGB::LimeGreen,
//};

int COLORS[] = {
 CRGB::Blue, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Maroon,
 CRGB::DarkRed,CRGB::White,CRGB::LimeGreen,CRGB::Red
};
int COLORS_ELE = sizeof(COLORS) / sizeof(COLORS[0]);



void pallete(void);
void pallete2(void);


void setup() {
 
    delay(1000);
    pinMode(LONG_CRGB_P, OUTPUT);
    pinMode(SHORT_CRGB_P, OUTPUT);
    delay( 3000 ); // power-up safety delay
    
    //initiate library
    //LONG
    FastLED.addLeds<LED_TYPE, LONG_CRGB_P, 
    COLOR_ORDER>(LONG_CRGB, LONG_CRGB_NUM).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(LONG_BRIGHTNESS);
    //SHORT
    FastLED.addLeds<LED_TYPE, SHORT_CRGB_P, 
    COLOR_ORDER>(SHORT_CRGB, SHORT_CRGB_NUM).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(SHORT_BRIGHTNESS);
}


void loop()
{



    pallete();
    pallete2();
     FastLED.show();
   // FastLED.setBrightness(  LONG_BRIGHTNESS );
    

   // LONG_BRIGHTNESS=+1;
    //if (LONG_BRIGHTNESS >=70)LONG_BRIGHTNESS=0;


 


    delay(PERIOD);
  
}


void pallete (void)
{
    bool frst_loop = true;
    //Loop from 0 until you reach the last neighbor
    //The last neighbor will get its color for the inner loop.
     for (int i = 0; i < LONG_CRGB_NUM; i+=NEIGHBOR_NUM)
    {
            
        LONG_CRGB[i] = COLORS[random(COLORS_ELE)];
        //Do the next NEIGHBOR_NUM leds.
        for (int u=0;u<NEIGHBOR_NUM;u++)
        {
            //Put the same current color on our neighbors
            LONG_CRGB[u+i] = LONG_CRGB[i];
        }
       
        frst_loop=false; //First loop no longer!
    }
    

}

void pallete2 (void)
{
        for (int i=0;i<SHORT_CRGB_NUM;i++)
        {
            SHORT_CRGB[i] = COLORS[random(COLORS_ELE)];
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

