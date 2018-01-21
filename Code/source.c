#include <Adafruit_NeoPixel.h>



#define LONG_CRGB_P    12              //PHY pin
#define LONG_CRGB_NUM  (57)   //number of leds on the strip
#define NEIGHBOR_NUM    8

#define SHORT_CRGB_P    14
#define SHORT_CRGB_NUM    (8)         //number of leds on the strip


//Keep the following order at all times
#define RED         0
#define GREEN       1
#define BLUE        2
#define YELLOW      3
#define LIME        4
#define ORANGE      5
#define MAGENTA     6
#define PURPLE      7
#define TURQUOISE   8 


#define PERIOD  1000                //period in program cycle in ms

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel LONG_CRGB = Adafruit_NeoPixel(LONG_CRGB_NUM, LONG_CRGB_P, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SHORT_CRGB = Adafruit_NeoPixel(SHORT_CRGB_NUM, SHORT_CRGB_P, NEO_GRB + NEO_KHZ800);


//CRGB SHORT_CRGB[SHORT_CRGB_NUM];    //declare our strip and give it an ID
//CRGB LONG_CRGB[LONG_CRGB_NUM];      //declare our strip and give it an ID

//---------------------End of Definition---------------------------------------//





//-----------------------------Declaration-------------------------//
enum MODES {NONE,BLINK_SIDES,BLINK_WHOLE,FLASH_SIDES,FLASH_WHOLE};
MODES INDICATE_M = BLINK_SIDES;

uint32_t Magenttta = LONG_CRGB.Color(255,0,255);    //debug
uint32_t RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C;
uint32_t PALLETE []={RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C};
int PALLETE_ELEMENTS = sizeof(PALLETE)/sizeof(PALLETE[0]);        //return num of elements

typedef struct COLOR_CONTENT {
     uint32_t R,G,B;
};
//RED_COMP,GREEN_COMP,
//BLUE_COMP,YELLOW_COMP,LIME_COMP,
//ORANGE_COMP,MAGENTA_COMP,PURPLE_COMP,TURQUOISE_COMP;

//Array of structs
COLOR_CONTENT COLOR_CONTENT_ARY[9];

uint32_t DEF_BRIGHTNESS = 15; //Global color brightness in %, 0-100


void init();
void SET_BRIGHTNESS(int);
void SET_COLORS(void);

//-------------------------End of Declaration--------------------------//


void setup() {
 
    void init ();

}


void loop()
{
int i=0;
    Serial.printf("Program is in loop\n");
    //INDICATE(INDICATE_M);
    Serial.printf("Current Mode is %i\n",INDICATE_M);
    Serial.printf("You have %i Elements in your Pallete\n",PALLETE_ELEMENTS);
    Serial.printf("Printing your PAllete's int values: \n");
    for (int u=0;u<PALLETE_ELEMENTS;u++)
    {
        Serial.printf("-->%u\n",PALLETE[u]);
               
    }
    Serial.printf("Printing Magneta int value now: %i\n",Magenttta);
    //Serial.printf("Poll: Current color value is: %i\n",LONG_CRGB.getPixelColor(11));
    
    Serial.printf("Printing the RED_COMP:%i,%i,%i\n",COLOR_CONTENT_ARY[i].R,COLOR_CONTENT_ARY[i].G,COLOR_CONTENT_ARY[i].B);
    Serial.printf("------------------------------------------\n");
    LONG_CRGB.setPixelColor(10, Magenttta);
      LONG_CRGB.show();  
    
    delay(PERIOD);
    delay(PERIOD);
    delay(PERIOD);

    LONG_CRGB.setPixelColor(11, 255,0,255);
     LONG_CRGB.setPixelColor(12, 255,0,255);\
      LONG_CRGB.setPixelColor(13, 255,0,255);
       LONG_CRGB.setPixelColor(14, 255,0,255);
        LONG_CRGB.setPixelColor(15, 255,0,255);
    LONG_CRGB.show(); 
    delay(PERIOD);
    delay(PERIOD);
    delay(PERIOD);
    
    i++;
    if (i>PALLETE_ELEMENTS)i=0;
  
}






void init()
{
    delay(1000);
    pinMode(LONG_CRGB_P, OUTPUT);
    pinMode(SHORT_CRGB_P, OUTPUT);
    Serial.begin(115200);
    Serial.printf("Initiating the MCU.....\n");
    delay( 5000 ); // power-up safety delay
    
    //Initiate lib
    LONG_CRGB.begin();       // Initialize
    SHORT_CRGB.begin();      // Initialize                    
    
    LONG_CRGB.show();        // to off (black)
    SHORT_CRGB.show();       // to off (black) 
   
    SET_COLORS();             //Initialize color values
    SET_BRIGHTNESS(DEF_BRIGHTNESS);
    //LONG_CRGB.setPixelColor(11, 255, 0, 255);  
    //LONG_CRGB.show();     
    }  

















//-------------------------------------LOW layer functions----------------------//
//Init the color values
//Those values are never changing values
//Those values represent the default RGB color values


void SET_COLORS()
{
    //Set default color component values.

    COLOR_CONTENT_ARY[RED].R = 255, COLOR_CONTENT_ARY[0].G = 0,COLOR_CONTENT_ARY[0].B = 0;
    COLOR_CONTENT_ARY[GREEN].R = 0,   COLOR_CONTENT_ARY[1].G = 255,COLOR_CONTENT_ARY[1].B = 0;
    COLOR_CONTENT_ARY[BLUE].R = 0,   COLOR_CONTENT_ARY[2].G = 0,COLOR_CONTENT_ARY[2].B = 255;
    COLOR_CONTENT_ARY[YELLOW].R = 255, COLOR_CONTENT_ARY[3].G = 255,COLOR_CONTENT_ARY[3].B = 0;
    COLOR_CONTENT_ARY[LIME].R = 153, COLOR_CONTENT_ARY[4].G = 255,COLOR_CONTENT_ARY[4].B = 51;
    COLOR_CONTENT_ARY[ORANGE].R = 255, COLOR_CONTENT_ARY[5].G = 128,COLOR_CONTENT_ARY[5].B = 0;
    COLOR_CONTENT_ARY[MAGENTA].R = 255, COLOR_CONTENT_ARY[6].G = 0,COLOR_CONTENT_ARY[6].B = 255;
    COLOR_CONTENT_ARY[PURPLE].R = 127, COLOR_CONTENT_ARY[7].G = 0,COLOR_CONTENT_ARY[7].B = 255;
    COLOR_CONTENT_ARY[TURQUOISE].R = 0, COLOR_CONTENT_ARY[8].G = 255,COLOR_CONTENT_ARY[8].B = 255;


    
    //RED_COMP.R=255, RED_COMP.G=0, RED_COMP.B=0;
    //GREEN_COMP.R=0, GREEN_COMP.G=255, GREEN_COMP.B=0;
    //BLUE_COMP.R=0, BLUE_COMP.G=0, BLUE_COMP.B=255; 
    //YELLOW_COMP.R=255, YELLOW_COMP.G=255, YELLOW_COMP.B=0; 
    
    //LIME_COMP.R=153, LIME_COMP.G=255, LIME_COMP.B=51; 
    
    //ORANGE_COMP.R=255, ORANGE_COMP.G=128, ORANGE_COMP.B=0; 
    
    //MAGENTA_COMP.R=255, MAGENTA_COMP.G=0, MAGENTA_COMP.B=255; 
    
    //PURPLE_COMP.R=127, PURPLE_COMP.G=0, PURPLE_COMP.B=255; 
    
    //TURQUOISE_COMP.R=0, TURQUOISE_COMP.G=255, TURQUOISE_COMP.B=255;  
}




//Mapping the colors components(RGB) of the colors given in PALLETE to new values
//The precent value is multiplied into each component of all PALLETE colors
void SET_BRIGHTNESS(int percent)
{
   for (int i=0;i<PALLETE_ELEMENTS;i++)
   {
      PALLETE[i]= LONG_CRGB.Color((uint32_t) COLOR_CONTENT_ARY[i].R * (percent/100), (uint32_t) COLOR_CONTENT_ARY[i].G * (percent/100), (uint32_t) COLOR_CONTENT_ARY[i].B * (percent/100));
      //debug
      //PALLETE[i]= LONG_CRGB.Color(COLOR_CONTENT_ARY[i].R, COLOR_CONTENT_ARY[i].G, COLOR_CONTENT_ARY[i].B);

      Serial.printf("%i. R:%i------G:%i------B:%i\n",i,COLOR_CONTENT_ARY[i].R,COLOR_CONTENT_ARY[i].G,COLOR_CONTENT_ARY[i].B);
      
   }
      //Red Green Blue order
   //RED = LONG_CRGB.Color(RED_COMP.R * (precent/100), RED_COMP.G * (precent/100), RED_COMP.B * (precent/100));
   //GREEN = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //BLUE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //YELLOW = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //LIME = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //ORANGE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //MAGENTA = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //PURPLE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //TURQUOISE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
}




//-----------------------------End of LOW layer functions----------------------//


