

#include <FastLED.h>

#define LONG_CRGB_P    12           //number of leds on the strip
#define LONG_CRGB_NUM  57
#define NEIGHBOR_NUM    8

#define SHORT_CRGB_P    14
#define SHORT_CRGB_NUM    8         //number of leds on the strip

#define LED_TYPE    WS2812          //Controller model
//#define UPDATES_PER_SECOND 500
#define COLOR_ORDER GRB
#define PERIOD  15000                //period in program cycle in ms
#define RED     CRGB::Red
#define GREEN   CRGB::Green 
#define BLACK   CRGB::Black
CRGB SHORT_CRGB[SHORT_CRGB_NUM];    //declare our strip and give it an ID
CRGB LONG_CRGB[LONG_CRGB_NUM];      //declare our strip and give it an ID

//---------------------End of Definition---------------------------------------//



enum MODES {NONE,BLINK_SIDES,BLINK_WHOLE,FLASH_SIDES,FLASH_WHOLE};
MODES INDICATE_M = BLINK_SIDES;

int LONG_BRIGHTNESS = 12;
int SHORT_BRIGHTNESS = 12;



//int COLORS[] = {
// CRGB::Blue, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Maroon,
// CRGB::DarkRed,CRGB::White,CRGB::SeaGreen,CRGB::Aquamarine,CRGB::OliveDrab,CRGB::Aqua,
// CRGB::SkyBlue,CRGB::Navy,CRGB::Teal,CRGB::DarkCyan,CRGB::LimeGreen,
//};

int COLORS[] = {
 CRGB::Blue, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Maroon,
 CRGB::DarkRed,CRGB::White,CRGB::LimeGreen,CRGB::Red,CRGB::Black
};
int COLORS_ELE = sizeof(COLORS) / sizeof(COLORS[0]);


void init();
void pallete(void);
void pallete2(void);
void on_left_right(int);
void off_left_right();


//-------------------------End of Declaration--------------------------//


void setup() {
 
    void init ();

}


void loop()
{



    //pallete();
    //pallete2();
    Serial.printf("Program is in loop\n");
    INDICATE(INDICATE_M);
    Serial.printf("Current Mode is %i\n",INDICATE_M);

   // on_left_right(RED);
    //delay(300);
    //off_left_right();
   // FastLED.setBrightness(  LONG_BRIGHTNESS );
    

   // LONG_BRIGHTNESS=+1;
    //if (LONG_BRIGHTNESS >=70)LONG_BRIGHTNESS=0;


 



  
}






void init()
{
    delay(1000);
    pinMode(LONG_CRGB_P, OUTPUT);
    pinMode(SHORT_CRGB_P, OUTPUT);
    Serial.begin(115200);
    Serial.printf("Initiating the MCU.....\n");
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




void INDICATE (int mode)
{
    switch (mode)
    {
        case NONE:
            off_left_right();
            return;
        case BLINK_SIDES:
            
            //start from the very last leds
            //long
            on_left_right(RED);
            FastLED.delay(100);
            off_left_right();
            INDICATE_M = NONE;
            return;

        case BLINK_WHOLE:
            break;

            
        case FLASH_SIDES:
            break;

        
        case FLASH_WHOLE:
            break;
    }
}















//-------------------------------------LOW layer functions----------------------//

//duration in ms
void on_left_right(int color)
{
    for (int i=LONG_CRGB_NUM-8;i<LONG_CRGB_NUM;i++)
    {
        LONG_CRGB[i]=color;
        yield();
        FastLED.show();
        yield();
    }
    
   for (int i=0;i<SHORT_CRGB_NUM;i++)
   {
       SHORT_CRGB[i]=color;
       yield();
       FastLED.show();
       yield();
   }
   

}

void off_left_right()
{
    for (int i=LONG_CRGB_NUM-8;i<LONG_CRGB_NUM;i++)
    {
        LONG_CRGB[i]=CRGB::Black;
        yield();
       FastLED.show();
        yield();
    }
    
    for (int i=0;i<SHORT_CRGB_NUM;i++)
    {
        SHORT_CRGB[i]=CRGB::Black;
        yield();
       FastLED.show();
        yield();
    }
   

}


//-----------------------------End of LOW layer functions----------------------//









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

